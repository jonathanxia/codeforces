#!/usr/bin/env python3
"""
Tree shaker for expanded solutions.

Run this on a file *after* preprocess.py has inlined lib/. It parses the file
with libclang, builds a graph of which declarations reference which, and
deletes every declaration (function, class, method, typedef, global, macro)
that isn't reachable from main().

    python3 shake.py A.cpp          # shake in place
    python3 shake.py A.cpp -c       # print to stdout instead
    python3 shake.py A.cpp -o B.cpp

Things that are never removed, because the compiler can call them without a
visible reference: constructors, destructors, conversion functions,
operators, virtual methods, fields, and begin/end/get members (range-for and
structured bindings). Calls inside uninstantiated templates that clang can't
resolve fall back to keeping everything with that name.

After shaking, the result is syntax-checked. If it doesn't compile, anything
named in the errors is restored and we retry; if that still fails the file is
left untouched.

Before analysis, #if/#ifdef blocks are resolved the way the judge sees them
(using unifdef): ONLINE_JUDGE is defined, DEBUG isn't, and flag macros like
INTERACTIVE count as defined only if the file #defines them. Dead branches are
deleted, so the shaken file is for submission, not for local debugging.
"""

import argparse
import os
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

import clang.cindex as ci

from compiler_config import get_compiler

K = ci.CursorKind
REPO = Path(__file__).resolve().parent

LIBCLANG_CANDIDATES = [
    "/Library/Developer/CommandLineTools/usr/lib/libclang.dylib",
    "/opt/homebrew/opt/llvm/lib/libclang.dylib",
    "/usr/local/opt/llvm/lib/libclang.dylib",
]

CLASS_KINDS = {
    K.STRUCT_DECL, K.CLASS_DECL, K.UNION_DECL, K.CLASS_TEMPLATE,
    K.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION, K.ENUM_DECL,
}
TYPE_KINDS = CLASS_KINDS | {
    K.TYPEDEF_DECL, K.TYPE_ALIAS_DECL, K.TYPE_ALIAS_TEMPLATE_DECL,
}
FUNC_KINDS = {K.FUNCTION_DECL, K.FUNCTION_TEMPLATE, K.CXX_METHOD}
# Kinds that become removable units at namespace scope
TOP_UNIT_KINDS = TYPE_KINDS | FUNC_KINDS | {K.VAR_DECL}
# Kinds that become removable units inside a class
MEMBER_UNIT_KINDS = TYPE_KINDS | {K.CXX_METHOD, K.FUNCTION_TEMPLATE}
# Members the compiler may call implicitly
IMPLICIT_MEMBER_NAMES = {"begin", "end", "rbegin", "rend", "get", "swap"}
REF_KINDS = {
    K.DECL_REF_EXPR, K.MEMBER_REF_EXPR, K.MEMBER_REF, K.TYPE_REF,
    K.TEMPLATE_REF, K.OVERLOADED_DECL_REF, K.CALL_EXPR, K.VARIABLE_REF,
    K.NAMESPACE_REF,
}
IDENT = re.compile(r"[A-Za-z_]\w*")

# How the judge compiles: these are resolved out of #if blocks before shaking
JUDGE_DEFINED = ["ONLINE_JUDGE"]
JUDGE_UNDEFINED = ["DEBUG"]
# Defined only if the solution itself #defines them
FILE_FLAGS = ["INTERACTIVE", "PRINT_MI_FRAC", "GLOBAL_MOD"]
JUDGE_FLAGS = [f"-D{m}" for m in JUDGE_DEFINED]


def setup_libclang():
    path = os.environ.get("LIBCLANG_PATH")
    if not path:
        path = next((p for p in LIBCLANG_CANDIDATES if os.path.exists(p)), None)
    if path:
        ci.Config.set_library_file(path)


def clang_args():
    """Flags for libclang, matching the compiler test.py uses."""
    cmd = shlex.split(get_compiler())
    args = ["-x", "c++", "-std=c++17", "-I", str(REPO)] + JUDGE_FLAGS + cmd[1:]
    try:
        rd = subprocess.run(
            [cmd[0], "-print-resource-dir"], capture_output=True, text=True
        ).stdout.strip()
        if rd:
            args += ["-resource-dir", rd]
    except OSError:
        pass
    return args


class Unit:
    """A removable chunk of source: one declaration (plus out-of-line defs)."""

    def __init__(self, uid, cur, parent):
        self.id = uid
        self.name = cur.spelling
        self.kind = cur.kind
        self.parent = parent
        self.extents = []  # list of (start, end) byte offsets
        self.edges = set()  # unit ids
        self.name_edges = set()  # names to resolve by name
        self.is_macro = False

    def is_class(self):
        return self.kind in CLASS_KINDS


def byte_to_char_map(text):
    """libclang offsets are UTF-8 byte offsets; map them to str indices."""
    m = []
    for i, ch in enumerate(text):
        m.extend([i] * len(ch.encode("utf-8")))
    m.append(len(text))
    return m


class Shaker:
    def __init__(self, path, text):
        self.path = path
        self.text = text
        self.b2c = byte_to_char_map(text)
        self.units = []
        self.by_key = {}  # decl location offset -> unit id
        self.by_name = {}  # name -> [unit ids]
        self.macros = {}  # macro name -> [unit ids]
        self.roots = set()
        self.root_names = set()

    # ---------- parsing ----------

    def parse(self):
        tu = ci.Index.create().parse(
            self.path,
            args=clang_args(),
            unsaved_files=[(self.path, self.text)],
            options=ci.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD,
        )
        errors = [d for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error]
        if errors:
            raise RuntimeError(
                "file doesn't parse:\n" + "\n".join(str(d) for d in errors[:10])
            )
        self.tu = tu
        self.file = tu.spelling

    def in_main(self, cur):
        f = cur.location.file
        return f is not None and f.name == self.file

    def new_unit(self, cur, parent):
        u = Unit(len(self.units), cur, parent.id if parent is not None else None)
        self.units.append(u)
        self.by_name.setdefault(u.name, []).append(u.id)
        return u

    def ext(self, cur):
        """A cursor's extent as str indices into self.text."""
        return (self.b2c[cur.extent.start.offset], self.b2c[cur.extent.end.offset])

    def add_extent(self, u, cur):
        self.by_key[cur.location.offset] = u.id
        ext = self.ext(cur)
        if ext not in u.extents:
            u.extents.append(ext)

    def is_member_unit(self, cur, cls):
        if cur.kind not in MEMBER_UNIT_KINDS:
            return False
        name = cur.spelling
        if cur.kind in (K.CXX_METHOD, K.FUNCTION_TEMPLATE):
            if name.startswith("operator") or name.startswith("~"):
                return False
            if name.split("<")[0] == cls.spelling.split("<")[0]:
                return False  # constructor template (`Point<T>` in a class template)
            if name in IMPLICIT_MEMBER_NAMES:
                return False
            if cur.kind == K.CXX_METHOD and cur.is_virtual_method():
                return False
        return True

    def is_top_unit(self, cur):
        if cur.kind not in TOP_UNIT_KINDS:
            return False
        if cur.spelling == "main" and cur.kind == K.FUNCTION_DECL:
            return False
        return True

    def collect(self):
        """First pass: find all units and their extents."""
        prev_stmt = {}  # (start offset) -> unit, to merge `int a, b;`

        def visit(cur, parent_unit, parent_cur):
            for c in cur.get_children():
                if not self.in_main(c):
                    continue
                unit = None
                if c.kind == K.NAMESPACE and c.spelling == "std":
                    continue  # hash<> specializations etc: used by std itself
                if c.kind == K.NAMESPACE:
                    unit = self.new_unit(c, parent_unit)
                    self.add_extent(unit, c)
                    visit(c, unit, c)
                    continue
                is_class_scope = parent_cur is not None and parent_cur.kind in CLASS_KINDS
                sem = c.semantic_parent
                out_of_line = (
                    sem is not None
                    and sem.kind in CLASS_KINDS
                    and not is_class_scope
                )
                if out_of_line:
                    # `ret Cls::method(...) {...}` outside the class: belongs to
                    # the in-class declaration's unit (resolved in second pass).
                    self.out_of_line.append((c, parent_unit))
                    continue
                if is_class_scope:
                    if self.is_member_unit(c, parent_cur):
                        unit = self.new_unit(c, parent_unit)
                elif self.is_top_unit(c):
                    start = c.extent.start.offset
                    if c.kind == K.VAR_DECL and start in prev_stmt:
                        unit = prev_stmt[start]
                        self.add_extent(unit, c)
                        continue
                    unit = self.new_unit(c, parent_unit)
                    prev_stmt[start] = unit
                if unit is not None:
                    self.add_extent(unit, c)
                    if c.kind in CLASS_KINDS:
                        visit(c, unit, c)
                elif c.kind in CLASS_KINDS:
                    # e.g. an anonymous struct; treat as part of the parent
                    visit(c, parent_unit, c)

        self.out_of_line = []
        visit(self.tu.cursor, None, None)
        for c, _ in self.out_of_line:
            u = self.unit_of_decl(c)
            if u is not None:
                self.units[u].extents.append(self.ext(c))
                self.by_key[c.location.offset] = u

        # Macros
        for c in self.tu.cursor.get_children():
            if c.kind == K.MACRO_DEFINITION and self.in_main(c):
                if c.spelling.startswith("__"):
                    continue
                u = self.new_unit(c, None)
                u.is_macro = True
                s, e = self.ext(c)
                u.extents.append((s, e))
                self.macros.setdefault(c.spelling, []).append(u.id)
                body = self.text[s:e]
                u.name_edges |= set(IDENT.findall(body)[1:])

        # Macros tested by the preprocessor (#ifdef X, #if defined(X), ...)
        # have no expansion record, so root them.
        for m in re.finditer(r"^[ \t]*#[ \t]*(?:if|ifdef|ifndef|elif|undef)\b(.*)$",
                             self.text, re.M):
            self.root_names |= set(IDENT.findall(m.group(1)))

    def unit_of_decl(self, cur, depth=0):
        """Map a referenced declaration to the unit that contains it."""
        if cur is None or depth > 20 or not self.in_main(cur):
            return None
        for cand in (cur, cur.canonical):
            if cand is not None and self.in_main(cand):
                u = self.by_key.get(cand.location.offset)
                if u is not None:
                    return u
        # A field / ctor / local variable: find its enclosing unit
        return self.unit_of_decl(cur.semantic_parent, depth + 1)

    # ---------- references ----------

    def enclosing_unit(self, offset):
        """Innermost unit whose extent contains offset (for macro expansions)."""
        best, best_len = None, None
        for u in self.units:
            if u.is_macro:
                continue
            for s, e in u.extents:
                if s <= offset < e and (best_len is None or e - s < best_len):
                    best, best_len = u.id, e - s
        return best

    def add_edge(self, src, dst=None, name=None):
        if src is None:
            if dst is not None:
                self.roots.add(dst)
            if name:
                self.root_names.add(name)
            return
        u = self.units[src]
        if dst is not None:
            u.edges.add(dst)
        if name:
            u.name_edges.add(name)

    def record_ref(self, c, cur_unit):
        ref = c.referenced
        if c.kind == K.OVERLOADED_DECL_REF or (
            ref is not None and ref.kind == K.OVERLOADED_DECL_REF
        ):
            # Dependent call in a template (incl. operators): any overload
            # with this name might be picked at instantiation.
            self.add_edge(cur_unit, name=c.spelling or ref.spelling)
            return
        if ref is not None and ref.kind == K.NAMESPACE:
            # A namespace ref only needs *some* block of it to survive
            self.add_edge(cur_unit, self.unit_of_decl(ref))
            return
        if ref is not None:
            if not self.in_main(ref):
                return  # std:: etc.
            u = self.unit_of_decl(ref)
            if u is not None:
                self.add_edge(cur_unit, u)
                return
        if c.kind == K.TYPE_REF:
            return
        # Unresolved (dependent) reference: keep everything with that name
        name = c.spelling
        if not name and c.kind == K.MEMBER_REF_EXPR:
            # `x.foo` with x dependent has no spelling; use the last token
            idents = [t.spelling for t in c.get_tokens()
                      if t.kind == ci.TokenKind.IDENTIFIER]
            name = idents[-1] if idents else ""
        if ref is None and name:
            self.add_edge(cur_unit, name=name)

    def walk_refs(self):
        decl_kinds = TOP_UNIT_KINDS | MEMBER_UNIT_KINDS | {
            K.NAMESPACE, K.CONSTRUCTOR, K.DESTRUCTOR, K.CONVERSION_FUNCTION,
        }

        def visit(cur, cur_unit):
            for c in cur.get_children():
                if not self.in_main(c):
                    continue
                if c.kind == K.MACRO_INSTANTIATION:
                    continue
                u = cur_unit
                if c.kind in decl_kinds:
                    u = self.by_key.get(c.location.offset, cur_unit)
                if c.kind in REF_KINDS:
                    self.record_ref(c, u)
                visit(c, u)

        visit(self.tu.cursor, None)

        # A free operator on a lib type can be called from inside std (e.g.
        # operator< by std::sort), so it lives as long as the type does.
        for u in self.units:
            if u.name.startswith("operator") and u.kind in FUNC_KINDS:
                for v in list(u.edges):
                    if self.units[v].is_class():
                        self.units[v].edges.add(u.id)

        # Macro expansions: attribute to the innermost enclosing unit
        for c in self.tu.cursor.get_children():
            if c.kind == K.MACRO_INSTANTIATION and self.in_main(c):
                src = self.enclosing_unit(self.ext(c)[0])
                for m in self.macros.get(c.spelling, []):
                    self.add_edge(src, m)

    # ---------- reachability ----------

    def lookup_name(self, name):
        return self.by_name.get(name, [])

    def reachable(self, force=(), banned=(), follow_names=True):
        """Units reachable from main. `banned` units are treated as absent."""
        keep = set()
        self.why = {}  # unit id -> reason it was kept (for --why)
        stack = [(v, "used at top level / in main") for v in self.roots]
        for n in self.root_names:
            stack += [(v, f"name '{n}' used at top level or in #if") for v in self.lookup_name(n)]
        for n in force:
            stack += [(v, "--keep / restored after compile error") for v in self.lookup_name(n)]

        def push(uid, reason):
            if uid not in keep:
                stack.append((uid, reason))

        while stack:
            uid, reason = stack.pop()
            if uid in keep or uid in banned:
                continue
            keep.add(uid)
            self.why[uid] = reason
            u = self.units[uid]
            src = f"{u.name} (line {self.line(u)})"
            if u.parent is not None:
                push(u.parent, f"contains {src}")
            for v in u.edges:
                push(v, f"referenced by {src}")
            if follow_names or u.is_macro:
                for n in u.name_edges:
                    for v in self.lookup_name(n):
                        push(v, f"unresolved name '{n}' in {src}")
            if u.is_class():
                # Specializations share the primary template's name
                for v in self.lookup_name(u.name):
                    if self.units[v].is_class():
                        push(v, f"same name as {src}")
        return keep

    def guessed(self, keep, force=()):
        """Kept units that are only there because of a by-name guess."""
        sure = self.reachable(force, follow_names=False)
        return sorted(
            uid for uid in keep - sure
            if not self.units[uid].is_macro and self.units[uid].kind != K.NAMESPACE
        )

    def line(self, u):
        return self.text.count("\n", 0, u.extents[0][0]) + 1 if u.extents else "?"

    # ---------- rewriting ----------

    def removal_ranges(self, keep):
        ranges = []
        for u in self.units:
            if u.id in keep:
                continue
            if u.parent is not None and u.parent not in keep:
                continue  # removed along with parent
            for s, e in u.extents:
                ranges.append(self.widen(s, e, u.is_macro))
        ranges.sort()
        merged = []
        for s, e in ranges:
            if merged and s <= merged[-1][1]:
                merged[-1] = (merged[-1][0], max(e, merged[-1][1]))
            else:
                merged.append((s, e))
        return merged

    def widen(self, s, e, is_macro):
        t = self.text
        if is_macro:
            s = t.rfind("\n", 0, s) + 1  # back to the `#define`
        else:
            # swallow a trailing `;` (class/var/typedef extents stop before it)
            j = e
            while j < len(t) and t[j] in " \t\r\n":
                j += 1
            if j < len(t) and t[j] == ";":
                e = j + 1
        # whole lines if the declaration owns them
        line_start = t.rfind("\n", 0, s) + 1
        if t[line_start:s].strip() == "":
            s = line_start
            s = self.eat_leading_comment(s)
        nl = t.find("\n", e)
        nl = len(t) if nl == -1 else nl
        rest = t[e:nl].strip()
        if rest == "" or (rest.startswith("//") and s == line_start):
            e = min(nl + 1, len(t))
        return s, e

    def eat_leading_comment(self, s):
        """Extend s upward over a doc comment directly above the declaration."""
        t = self.text
        while s > 0:
            prev_start = t.rfind("\n", 0, s - 1) + 1
            line = t[prev_start:s].strip()
            if line.startswith("// #include"):
                break
            if line.startswith("//"):
                s = prev_start
            elif line.endswith("*/"):
                open_ = t.rfind("/*", 0, s)
                if open_ == -1:
                    break
                ls = t.rfind("\n", 0, open_) + 1
                if t[ls:open_].strip() != "":
                    break
                s = ls
            else:
                break
        return s

    def analyze(self):
        self.parse()
        self.collect()
        self.walk_refs()

    def render(self, keep):
        """Source with everything not in `keep` cut out, plus removed names."""
        out, pos = [], 0
        for s, e in self.removal_ranges(keep):
            out.append(self.text[pos:s])
            pos = e
        out.append(self.text[pos:])
        removed = sorted({u.name for u in self.units if u.id not in keep and u.name})
        return tidy("".join(out)), removed

    def explain(self, name):
        for uid in self.lookup_name(name) + self.macros.get(name, []):
            u = self.units[uid]
            print(f"{u.name} (line {self.line(u)}): "
                  f"{self.why.get(uid, 'REMOVED')}", file=sys.stderr)


def tidy(text):
    # A namespace block left empty can go if another block of it survives
    # (it's only kept because `using namespace X;` resolved to that block).
    empty = re.compile(r"^[ \t]*namespace\s+(\w+)\s*\{\s*\}[ \t]*\n?", re.M)
    for m in reversed(list(empty.finditer(text))):
        rest = text[:m.start()] + text[m.end():]
        if re.search(r"namespace\s+" + m.group(1) + r"\s*\{", rest):
            text = rest
    return re.sub(r"\n{3,}", "\n\n", text)


def resolve_conditionals(text):
    """Delete #if branches the judge won't compile (see JUDGE_* above)."""
    if not shutil.which("unifdef"):
        sys.stderr.write("shake: unifdef not found; leaving #if blocks alone\n")
        return text
    args = [f"-D{m}" for m in JUDGE_DEFINED] + [f"-U{m}" for m in JUDGE_UNDEFINED]
    for m in FILE_FLAGS:
        d = re.search(rf"^[ \t]*#[ \t]*define[ \t]+{m}\b[ \t]*(.*)$", text, re.M)
        if d is None:
            args.append(f"-U{m}")
        else:
            val = d.group(1).split("//")[0].strip()
            args.append(f"-D{m}={val}" if val else f"-D{m}")
    # unifdef predates C++14 digit separators and reads 400'000 as a char literal
    sep = "__SHAKE_DIGIT_SEP__"
    masked = re.sub(r"(?<=\d)'(?=[0-9a-fA-F])", sep, text)
    if not masked.endswith("\n"):
        masked += "\n"  # a trailing `// ...` with no newline reads as an open comment
    r = subprocess.run(["unifdef", *args], input=masked, capture_output=True, text=True)
    if r.returncode not in (0, 1):  # 1 just means it changed something
        sys.stderr.write(f"shake: unifdef failed, leaving #if blocks alone:\n{r.stderr}")
        return text
    return r.stdout.replace(sep, "'")


def symbols(text, suffix):
    """
    Compile to an object file at -O0 and return (C++ symbol names, stderr).
    Symbols are None if it doesn't compile.

    At -O0 every template instantiation that gets used is emitted, so this is
    how we see what clang actually picked during overload resolution.
    """
    with tempfile.TemporaryDirectory() as d:
        src, obj = os.path.join(d, "x" + suffix), os.path.join(d, "x.o")
        with open(src, "w") as f:
            f.write(text)
        cmd = (f"{get_compiler()} -std=c++17 -O0 -w -c {' '.join(JUDGE_FLAGS)} "
               f"-I {shlex.quote(str(REPO))} "
               f"{shlex.quote(src)} -o {shlex.quote(obj)}")
        r = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        if r.returncode != 0:
            return None, r.stderr
        nm = subprocess.run(["nm", obj], capture_output=True, text=True).stdout
        return {line.split()[-1] for line in nm.splitlines()
                if line.strip() and "_Z" in line.split()[-1]}, ""


class Verifier:
    """A shaken file is ok if it compiles and emits no symbol the original didn't."""

    def __init__(self, text, suffix):
        self.suffix = suffix
        self.orig, err = symbols(text, suffix)
        if self.orig is None:
            raise RuntimeError("original file doesn't compile:\n" + err[:3000])
        self.compiles = 0

    def check(self, text):
        self.compiles += 1
        syms, err = symbols(text, self.suffix)
        if syms is None:
            return err
        extra = syms - self.orig
        if extra:
            return "overload resolution changed; new symbols: " + " ".join(sorted(extra)[:5])
        return ""


def main():
    ap = argparse.ArgumentParser(description="Remove unused lib code from an expanded solution")
    ap.add_argument("source")
    ap.add_argument("-c", "--console", action="store_true", help="print to stdout")
    ap.add_argument("-o", "--output", help="write here instead of in place")
    ap.add_argument("--keep", action="append", default=[], help="name to always keep")
    ap.add_argument("--fast", action="store_true",
                    help="skip the compiler-checked pass that prunes by-name guesses")
    ap.add_argument("--no-verify", action="store_true",
                    help="don't compile anything (implies --fast; unsafe)")
    ap.add_argument("--why", action="append", default=[],
                    help="explain why NAME was kept (repeatable); doesn't write")
    opts = ap.parse_args()

    setup_libclang()
    path = os.path.abspath(opts.source)
    original = open(path).read()
    suffix = Path(path).suffix
    text = resolve_conditionals(original)
    log = lambda msg: sys.stderr.write(f"shake: {msg}\n")

    sh = Shaker(path, text)
    sh.analyze()
    force = set(opts.keep)

    if opts.why:
        sh.reachable(force)
        for n in opts.why:
            sh.explain(n)
        return

    # Pass 1: static reachability, restoring names from compile errors
    # Baseline is the untouched file, so the unifdef step gets checked too
    verifier = None if opts.no_verify else Verifier(original, suffix)
    for attempt in range(5):
        keep = sh.reachable(force)
        shaken, removed = sh.render(keep)
        if verifier is None:
            break
        err = verifier.check(shaken)
        if not err:
            break
        names = set(re.findall(r"'([A-Za-z_]\w*)'", err)) & set(removed)
        if "operator" in err or "invalid operands" in err or "new symbols" in err:
            names |= {n for n in removed if n.startswith("operator")}
        names -= force
        if not names:
            log("result doesn't compile and I can't tell what to restore; "
                "leaving the file alone. Errors:\n" + err[:3000])
            sys.exit(1)
        log(f"restoring {sorted(names)} and retrying")
        force |= names
    else:
        log("gave up after 5 attempts; leaving the file alone")
        sys.exit(1)

    # Pass 2: try dropping things that were only kept by a by-name guess,
    # bisecting on failure. Each try is one compile.
    if verifier is not None and not opts.fast:
        banned = set()

        def attempt(cands):
            nonlocal shaken
            trial = sh.reachable(force, banned | set(cands))
            if trial == sh.reachable(force, banned):
                return
            out, _ = sh.render(trial)
            if not verifier.check(out):
                banned.update(cands)
                shaken = out
            elif len(cands) > 1:
                mid = len(cands) // 2
                attempt(cands[:mid])
                attempt(cands[mid:])

        cands = sh.guessed(keep, force)
        if cands:
            attempt(cands)
        log(f"pruned {len(banned)}/{len(cands)} by-name guesses "
            f"({verifier.compiles} compiles)")

    before, after = original.count("\n"), shaken.count("\n")
    log(f"{before} -> {after} lines ({len(original)} -> {len(shaken)} bytes)")

    if opts.console:
        sys.stdout.write(shaken)
    else:
        with open(opts.output or path, "w") as f:
            f.write(shaken)


if __name__ == "__main__":
    main()

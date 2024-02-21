#!/usr/bin/env python3

import sys
import re
import subprocess

included_fnames = set()

REG = r"#include\s*<(lib/.*\.(h|py))"

def open_filename(fname, comment):
    output = []
    with open(fname, "r") as f:
        for line in f.readlines():
            line = line.rstrip()

            if "#pragma once" in line:
                continue

            mm = re.match("^" + REG, line)
            mm_comment = re.match(comment + r"\s*" + REG, line)

            # If we had already imported it, don't import it again,
            # but mark that we have imported it to avoid double
            # imports
            if mm_comment is not None:
                incl_fn = mm_comment.group(1)
                included_fnames.add(incl_fn)
                continue
        
            if mm is not None:
                incl_fn = mm.group(1)
                if incl_fn in included_fnames:
                    continue

                output.extend(open_filename(incl_fn, comment))
                included_fnames.add(incl_fn)

            else:
                output.append(line)
                continue

    return output

def run_atcoder_process(fname):
    subprocess.run([
        "python3",
        "expander.py",
        fname
    ])

if __name__ == "__main__":
    fname = sys.argv[1]
    is_cpp = False
    if fname.endswith(".py"):
        comment = "#"
    else:
        is_cpp = True
        comment = "//"

    out = "\n".join(open_filename(fname, comment))
    preamble = "\n".join(
        [f"{comment} #include<{fname}>" for fname in included_fnames]
    )

    with open(fname, "w") as f:
        f.write(preamble + "\n" + out)

    # If we are in c++, we should run the atcoder preprocessor first
    # This SHOULD be a nop if you don't use the atcoder library at all
    if is_cpp:
        run_atcoder_process(fname)


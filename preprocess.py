#!/usr/bin/env python3

import sys
import re

included_fnames = set()

def open_filename(fname):
    output = []
    with open(fname, "r") as f:
        for line in f.readlines():
            line = line.rstrip()
            mm = re.match(r"#include\s*<(lib/.*\.h)", line)
            if not mm:
                output.append(line)
                continue
                
            incl_fn = mm.group(1)
            if incl_fn in included_fnames:
                continue

            output.extend(open_filename(incl_fn))
            included_fnames.add(incl_fn)

    return output


if __name__ == "__main__":
    fname = sys.argv[1]
    out = "\n".join(open_filename(fname))
    preamble = "\n".join(
        [f"// #include<{fname}>" for fname in included_fnames]
    )

    with open(fname, "w") as f:
        f.write(preamble + "\n" + out)
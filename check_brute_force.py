#!/usr/bin/env python3
import sys
import os
import numpy as np
from subprocess import run, check_output, STDOUT

COMPILE_CMD = "g++ -g -Wno-return-type -Wshadow -O0 -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=undefined,address -ftrapv"
TESTCASE_FILE = "brute_force.input"

def list_to_str(arr):
    return " ".join([str(x) for x in arr])

# Create your own test case, you can specify your own parameters
# and then iterate over them in generate_test_cases

# The prnt function is for convenience
def create_test_case(N, M, K, prnt):
    prnt(N, M, K)

    locs = set()
    for i in range(K):
        x, y = 1, 1
        while (x, y) == (1, 1) or (x, y) in locs:
            x = np.random.randint(1, N + 1)
            y = np.random.randint(1, M + 1)

        locs.add((x, y))
        prnt(x, y)

def generate_test_cases():
    with open(TESTCASE_FILE, "w") as f:
        def prnt(*args, **kwargs):
            kwargs["file"] = f
            print(*args, **kwargs)
        
        counter = 0
        for N in range(100, 101):
            for M in range(100, 101):
                K = min(N * M - 1, 20)
                for trial in range(10):
                    counter += 1
                    print("Checking test", counter)

                    create_test_case(N, M, K, prnt)
                    f.flush()
                    validate_test()
                    print("OK")

def validate_test():
    a_result = check_output("./a.out", stdin=open(TESTCASE_FILE, "r"), shell=True, timeout=5)
    b_result = check_output("./b.out", stdin=open(TESTCASE_FILE, "r"), shell=True, timeout=5)

    if a_result != b_result:
        print("Received different results on test case, see", TESTCASE_FILE)
        print("Result from a.out:")
        print(a_result)
        print()
        print("Result from b.out:")
        print(b_result)
        sys.exit(1)

if __name__ == "__main__":
    src_code = sys.argv[1]
    # Compile the source code
    print("Compiling", src_code, "...")
    os.system(f"{COMPILE_CMD} {src_code} -o a.out")

    print("Compiling", "brute.cpp", "...")
    os.system(f"{COMPILE_CMD} brute.cpp -o b.out")

    if len(sys.argv) >= 3 and sys.argv[2] == "chk":
        validate_test()
    else:
        generate_test_cases()
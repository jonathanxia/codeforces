#!/usr/bin/env python3
import sys
import os
import numpy as np
from subprocess import run, check_output, STDOUT
import random
import string

COMPILE_CMD = "g++ -g -Wno-return-type -Wshadow -O3 -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=undefined,address -ftrapv"
TESTCASE_FILE = "brute_force.input"

NUM_TRIALS = 4

# To use this, create a separate checker called brute.cpp
# If you want to just catch a runtime error, you can of course
# just copy paste your solution into brute.cpp

# Then, specify the functions create_test_case and generate_test_cases

# Then, run check_brute_force.py <your src code>

def list_to_str(arr):
    return " ".join([str(x) for x in arr])

def generate_tree(N, w_max=10 ** 9):
    """
    Generates a tree with N vertices and weights

    A list of triples (u, v, w) which are 1 indexed.
    """
    edges = []
    for i in range(2, N + 1):
        edges.append((i, np.random.randint(1, i), np.random.randint(1, w_max + 1)))
    
    return edges

def generate_random_string(length):
    """
    Generate a random string of the specified length.

    Parameters:
    - length (int): The length of the random string to generate.

    Returns:
    - str: The generated random string.
    """
    characters = string.ascii_letters + string.digits  # You can customize this if you want other characters
    random_string = ''.join(random.choice(characters) for _ in range(length))
    return random_string

def generate_random_lowercase_string(length):
    """
    Generate a random string of lowercase letters with the specified length.

    Parameters:
    - length (int): The length of the random string to generate.

    Returns:
    - str: The generated random string.
    """
    characters = string.ascii_lowercase
    random_string = ''.join(random.choice(characters) for _ in range(length))
    return random_string


# Create your own test case, you can specify your own parameters
# and then iterate over them in generate_test_cases

# The prnt function is for convenience
def create_test_case(N, K, M, prnt):
    prnt(1)
    prnt(N, K, M)

    prnt(generate_random_lowercase_string(M))

def generate_test_cases():
    counter = 0
    for N in range(1, 27):
        # for M in range(1, 40, 4):
        for K in range(1, 27):
            for M in [1, 2, 3, 10, 100, 1000]:
                for _ in range(NUM_TRIALS):
                    counter += 1
                    print("Checking test", counter)

                    # Erase the test case file
                    with open(TESTCASE_FILE, "w") as f:
                        def prnt(*args, **kwargs):
                            kwargs["file"] = f
                            print(*args, **kwargs)
                
                        create_test_case(N, K, M, prnt)
                        f.flush()
                        validate_test()
                        print("OK")

def validate_test():
    a_result = check_output("./a.out", stdin=open(TESTCASE_FILE, "r"), shell=True, timeout=5)
    b_result = check_output("./b.out", stdin=open(TESTCASE_FILE, "r"), shell=True, timeout=5)

    if a_result != b_result:
        print("Received different results on test case, see", TESTCASE_FILE)
        print("Result from a.out:")
        print(a_result.decode("utf-8"))
        print()
        print("Result from b.out:")
        print(b_result.decode("utf-8"))
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
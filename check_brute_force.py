#!/usr/bin/env python3
import sys
import os
import argparse
from subprocess import run, check_output, STDOUT, PIPE
import subprocess

COMPILE_CMD = "g++ -g -Wno-return-type -Wshadow -O3 -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=undefined,address -ftrapv -I ."
COMPILE_CMD = "g++ -g -Wno-return-type -Wshadow -O3 -std=c++17 -I . -Wl,-stack_size,0x20000000"
TESTCASE_FILE = "brute_force.input"
SAVE_TESTCASE_FILE = "bad_input"

NUM_TRIALS = 1000

# To use this, create a separate checker called brute.cpp
# If you want to just catch a runtime error, you can of course
# just copy paste your solution into brute.cpp

# Then, specify the functions create_test_case and generate_test_cases

# Then, run check_brute_force.py <your src code>

def run_script_and_save_output(script_path, output_file):
    """
    Runs a script and saves the output
    """
    with open(output_file, 'w') as f:
        run(['python', script_path], stdout=f, stderr=PIPE, text=True)

def generate_test_cases(mode, gen_script):
    for counter in range(NUM_TRIALS):
        print("Checking test", counter)
        run_script_and_save_output(gen_script, TESTCASE_FILE)

        if mode == "stress" or mode == "check":
            check_test()
        elif mode == "validate":
            validate_test()
        else:
            raise ValueError(f"Unknown mode {mode}")

        print("OK")

def copy_file_contents(source_file, destination_file):
    try:
        with open(source_file, 'r') as source:
            with open(destination_file, 'w') as destination:
                destination.write(source.read())
    except FileNotFoundError:
        print("File not found:", source_file)

def check_test():
    a_result = check_output("./a.out", stdin=open(TESTCASE_FILE, "r"), shell=True, timeout=5)
    b_result = check_output("./b.out", stdin=open(TESTCASE_FILE, "r"), shell=True, timeout=5)

    if a_result != b_result:
        print("Received different results on test case, see", TESTCASE_FILE)
        print("Input test case also saved in", SAVE_TESTCASE_FILE)
        print("Result from your file (a.out):")
        print(a_result.decode("utf-8"))
        print()
        print("Result from brute force (b.out):")
        print(b_result.decode("utf-8"))

        # Do this at the end in case copy file contents has a bug
        copy_file_contents(TESTCASE_FILE, SAVE_TESTCASE_FILE)
        sys.exit(1)


def run_executable_with_input(executable, input_data, timeout):
    result = subprocess.run(
        executable,
        input=input_data,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        timeout=timeout
    )
    return result.stdout.strip(), result.stderr.strip()

def validate_test():
    # Run executable a.out with input from TESTCASE_FILE
    A_OUT_EXECUTABLE = "./a.out"
    B_OUT_EXECUTABLE = "./b.out"

    with open(TESTCASE_FILE, 'r') as f:
        input_data = f.read()
    
    a_out_stdout, a_out_stderr = run_executable_with_input(A_OUT_EXECUTABLE, input_data, 5)
    if a_out_stderr:
        print("Received stderr:")
        print(a_out_stderr)
        print(f"Check {TESTCASE_FILE} for test case")
        sys.exit(1)

    # Append a_out_stdout to the input data and run executable b.out
    input_data_with_a_out_stdout = input_data + "\n" + a_out_stdout
    b_out_stdout, b_out_stderr = run_executable_with_input(B_OUT_EXECUTABLE, input_data_with_a_out_stdout, 5)
    
    # Check if b_out_stdout is exactly "OK"
    if b_out_stdout.strip() == "OK":
        print("Test passed.")
    else:
        print("Test failed.")
        print("Output message from b.out:", b_out_stdout)
        print("Error message from b.out:", b_out_stderr)
        print(f"Contents of {TESTCASE_FILE}:")
        print(input_data)
        print("Output of a.out:")
        print(a_out_stdout)
        sys.exit(1)


def parse_arguments():
    """
    Parses arguments for the various modes
    """
    parser = argparse.ArgumentParser(description='Parse command line arguments.')
    parser.add_argument('filename', type=str, help='Main filename')
    parser.add_argument('--brute_force', type=str, default='brute.cpp', help='Filename of the brute force file (default: brute.cpp)')
    parser.add_argument('--generate_script', type=str, default='generate.py', help='Script the will output a test case')
    parser.add_argument('--mode', type=str, required=True, help='Check mode. Options are "check", "stress", "validate"')
    args = parser.parse_args()
    return args

if __name__ == "__main__":
    opts = parse_arguments()

    src_code = opts.filename
    mode     = opts.mode

    # Compile the source code
    print("Compiling", src_code, "...")
    os.system(f"{COMPILE_CMD} {src_code} -o a.out")

    # The second file depends on the mode that we are running
    if mode == "check" or mode == "validate":
        truth_code = opts.brute_force
    elif mode == "stress":
        truth_code = src_code
    else:
        raise ValueError(f"Unknown mode: {mode}")

    print("Compiling", truth_code, "...")
    os.system(f"{COMPILE_CMD} {truth_code} -o b.out")

    generate_test_cases(mode, opts.generate_script)
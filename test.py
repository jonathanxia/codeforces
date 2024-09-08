import os
from multiprocessing import Pool
import re
import subprocess
import tempfile
import requests
import argparse
import hashlib
from bs4 import BeautifulSoup
import sys
import json

def hash_url(url):
    """Returns a hashed version of the URL."""
    return url.replace("/", "_").replace(":", "_")

def cache_test_cases(url, inputs, outputs):
    """Caches the test cases on disk using the hashed URL."""
    cache_dir = 'test_case_cache'
    os.makedirs(cache_dir, exist_ok=True)
    cache_path = os.path.join(cache_dir, f"{hash_url(url)}.txt")
    
    with open(cache_path, 'w') as cache_file:
        for input_data, output_data in zip(inputs, outputs):
            cache_file.write('INPUT:\n')
            cache_file.write(input_data)
            cache_file.write('\nOUTPUT:\n')
            cache_file.write(output_data)
            cache_file.write('\n---\n')

def load_cached_test_cases(url):
    """Loads cached test cases from disk if available."""
    cache_path = os.path.join('test_case_cache', f"{hash_url(url)}.txt")
    if not os.path.exists(cache_path):
        return None
    
    inputs = []
    outputs = []
    with open(cache_path, 'r') as cache_file:
        content = cache_file.read().split('\n---\n')
        for section in content:
            if section.strip():
                parts = section.split('\nOUTPUT:\n')
                inputs.append(parts[0].replace('INPUT:\n', '').strip())
                outputs.append(parts[1].strip())

    if len(inputs) == 0 or len(outputs) == 0:
        return None
    return inputs, outputs

def extract_test_cases(url):
    """Extracts test cases, either from the cache or by scraping the URL."""
    cached = load_cached_test_cases(url)
    if cached is not None:
        return cached

    response = requests.get(url, headers = {"User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36",
                                            "Connection": "keep-alive"})
    soup = BeautifulSoup(response.content, 'html.parser')

    inputs = []
    outputs = []

    if 'codeforces.com' in url:
        input_elements = soup.find_all('div', class_='input')
        output_elements = soup.find_all('div', class_='output')
        for inp, out in zip(input_elements, output_elements):
            inputs.append(inp.pre.get_text('\n', strip=True))
            outputs.append(out.pre.get_text('\n', strip=True))
    elif 'atcoder.jp' in url:
        sample_tests = soup.find_all('div', class_='part')
        for test in sample_tests:
            title = test.h3.text.strip()
            if title.startswith('Sample Input'):
                inputs.append(test.pre.get_text('\n', strip=True))
            elif title.startswith('Sample Output'):
                outputs.append(test.pre.get_text('\n', strip=True))
    
    if len(inputs) == 0 or len(outputs) == 0:
        print(f"Couldn't load inputs and outputs for {url}", response)
    else:
        cache_test_cases(url, inputs, outputs)
    return inputs, outputs

def save_failed_test_case(filename, test_case_number, input_data, expected_output, actual_output):
    os.makedirs('failed_test', exist_ok=True)
    file_path = os.path.join('failed_test', f'{filename}_test_case_{test_case_number}.txt')
    with open(file_path, 'w') as file:
        file.write(f'Input:\n{input_data}\n\n')
        file.write(f'Expected Output:\n{expected_output}\n\n')
        file.write(f'Actual Output:\n{actual_output}\n')
    print(f"Failed test case saved to {file_path}")

def normalize_output(output):
    return '\n'.join(line.rstrip() for line in output.strip().splitlines())

def check_cpp_file(file_path, exit_on_fail):
    tests_passed = True
    with open(file_path, 'r') as file:
        first_line = file.readline().strip()
        match = re.match(r'// Link: (https://(codeforces|atcoder).(com|jp)/[\S]+)', first_line)

        if not match:
            print(f"Skipping {file_path}: No valid Link comment found.")
            return True

        url = match.group(1)
        filename = os.path.splitext(os.path.basename(file_path))[0]
        inputs, outputs = extract_test_cases(url)
        if len(inputs) == 0 or len(outputs) == 0:
            # Something went wrong, try again
            inputs, outputs = extract_test_cases(url)
        
        if len(inputs) == 0 or len(outputs) == 0:
            print("Failed to load test cases from:", file_path)
            return False

        with tempfile.TemporaryDirectory() as tmpdirname:
            exec_path = os.path.join(tmpdirname, 'a.out')
            compile_command = f"g++ -g -Wno-return-type -Wshadow -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=undefined,address -ftrapv -I . {file_path} -o {exec_path}"
            compile_process = subprocess.run(compile_command, shell=True, stderr=subprocess.PIPE, text=True)

            if compile_process.returncode != 0:
                print(f"Error compiling {file_path}:\n{compile_process.stderr}")
                return False

            for i, (input_data, expected_output) in enumerate(zip(inputs, outputs)):
                result = subprocess.run(exec_path, input=input_data, text=True, capture_output=True)
                actual_output = result.stdout.strip()

                if normalize_output(actual_output) == normalize_output(expected_output):
                    print(f"{file_path} test case {i+1}: OK")
                else:
                    print(f"{file_path} test case {i+1}: Error\nExpected: {expected_output}\nGot: {actual_output}")
                    save_failed_test_case(filename, i+1, input_data, expected_output, actual_output)
                    tests_passed = False
                    if exit_on_fail:
                        return False

    return tests_passed

def extract_link_input_output_from_cph(filename):
    # Find the relevant test case in the cph directory
    inputs = []
    outputs = []
    link = ""
    for root, _, files in os.walk(".cph"):
        for file in files:
            if file.endswith('.prob') and (filename in file):
                cph_filename = os.path.join(root, file)
                with open(cph_filename, "r") as f:
                    line = f.readline().strip()
                    data = json.loads(line)
                    link = data["url"]
                    tests = data['tests']
                    for testcase_number in range(len(tests)):
                        inputs.append(tests[testcase_number]['input'])
                        outputs.append(tests[testcase_number]['output'])
    
    return link, inputs, outputs



def install_test_case(source_code, user):
    os.makedirs(f"solutions/{user}", exist_ok=True)
    with open(source_code, "r") as f:
        src_str = f.read()
    
    link, inputs, outputs = extract_link_input_output_from_cph(source_code)
    src_str = f"// Link: {link}\n" + src_str
    
    with open(f"solutions/{user}/{source_code}", "w") as f:
        f.write(src_str)
    
    cache_test_cases(link, inputs, outputs)


def main():
    parser = argparse.ArgumentParser(description='Check C++ solutions against sample test cases.')
    parser.add_argument("--install", type=str, help="Install the source code as a test case. Requires .cph directory")
    parser.add_argument("--user", type=str, help="Install the source code as a test case. Requires .cph directory")
    parser.add_argument('--exit_on_fail', action='store_true', help='Exit on the first failed test case.')
    parser.add_argument('--filename', type=str, help='Run only on files containing this substring in their name.')
    parser.add_argument('-n', '--num_threads', type=int, default=1, help='Number of threads to use (default 1)')
    
    args = parser.parse_args()
    
    if args.install is not None:
        if args.user is None:
            print("--user argument required if using --install. E.g. --user jonathan")
            sys.exit(1)
        install_test_case(args.install, args.user)
        return


    failed_tests = []
    file_list = []
    for root, _, files in os.walk('solutions'):
        for file in files:
            file_path = os.path.join(root, file)
            if file.endswith('.cpp') and (args.filename is None or args.filename in file_path):
                file_list.append([file_path, args.exit_on_fail])


    p = Pool(args.num_threads)
    passed_list = p.starmap(check_cpp_file, file_list)
    for passed, (file_name, _) in zip(passed_list, file_list):
        if not passed:
            failed_tests.append(file_name)
    

    if len(failed_tests) == 0:
        print("All test passed: OK")
    else:
        print(len(failed_tests), "tests failed:")
        for t in failed_tests:
            print(t)

if __name__ == "__main__":
    main()

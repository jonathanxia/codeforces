import os
import re
import subprocess
import tempfile
import requests
import argparse
from bs4 import BeautifulSoup

def extract_test_cases(url):
    response = requests.get(url)
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
    with open(file_path, 'r') as file:
        first_line = file.readline().strip()
        match = re.match(r'// Link: (https://(codeforces|atcoder).(com|jp)/[\S]+)', first_line)
        
        if not match:
            print(f"Skipping {file_path}: No valid Link comment found.")
            return
        
        url = match.group(1)
        filename = os.path.splitext(os.path.basename(file_path))[0]
        inputs, outputs = extract_test_cases(url)
        
        with tempfile.TemporaryDirectory() as tmpdirname:
            exec_path = os.path.join(tmpdirname, 'a.out')
            compile_command = f"g++ -g -Wno-return-type -Wshadow -std=c++17 -D_GLIBCXX_DEBUG -fsanitize=undefined,address -ftrapv -I . {file_path} -o {exec_path}"
            compile_process = subprocess.run(compile_command, shell=True, stderr=subprocess.PIPE, text=True)
            
            if compile_process.returncode != 0:
                print(f"Error compiling {file_path}:\n{compile_process.stderr}")
                return
            
            for i, (input_data, expected_output) in enumerate(zip(inputs, outputs)):
                result = subprocess.run(exec_path, input=input_data, text=True, capture_output=True)
                actual_output = result.stdout.strip()
                
                if normalize_output(actual_output) == normalize_output(expected_output):
                    print(f"{file_path} test case {i+1}: OK")
                else:
                    print(f"{file_path} test case {i+1}: Error\nExpected: {expected_output}\nGot: {actual_output}")
                    save_failed_test_case(filename, i+1, input_data, expected_output, actual_output)
                    if exit_on_fail:
                        return

def main():
    parser = argparse.ArgumentParser(description='Check C++ solutions against sample test cases.')
    parser.add_argument('--exit_on_fail', action='store_true', help='Exit on the first failed test case.')
    parser.add_argument('--filename', type=str, help='Run only on files containing this substring in their name.')
    
    args = parser.parse_args()
    
    for root, _, files in os.walk('solutions'):
        for file in files:
            if file.endswith('.cpp') and (args.filename is None or args.filename in file):
                file_path = os.path.join(root, file)
                check_cpp_file(file_path, args.exit_on_fail)

if __name__ == "__main__":
    main()

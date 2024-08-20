import os
import argparse
import json

def print_testcase(file_path, testcase_number, in_path, out_path):
    with open(file_path, 'r') as file:
        line = file.readline().strip()
        input_string = json.loads(line)['tests'][testcase_number]['input']
        output_string = json.loads(line)['tests'][testcase_number]['output']
        if in_path is None:
            print(input_string)
        else:
            with open(in_path, 'w') as in_file:
                in_file.write(input_string)

        if out_path is None:
            print(output_string)
        else:
            with open(out_path, 'w') as out_file:
                out_file.write(output_string)



def main():
    parser = argparse.ArgumentParser(description='Converts cph-generated .prob files into readable format, useful for gdbq')
    parser.add_argument('-s', '--source_dir', default='.cph', help='Directory in which to search for .prob file (default .cph)')
    parser.add_argument('filename', help='Name of code file')
    parser.add_argument('test_number', nargs='?', default=1, type=int, help='Test case number (default 1)')
    parser.add_argument('-i', '--in_file', help='Filename of where to put testcase input')
    parser.add_argument('-o', '--out_file', help='Filename of where to put testcase expected output')

    args = parser.parse_args()

    for root, _, files in os.walk(args.source_dir):
        for file in files:
            if file.endswith('.prob') and (args.filename in file):
                print_testcase(os.path.join(root, file), args.test_number - 1, args.in_file, args.out_file)

if __name__ == "__main__":
    main()
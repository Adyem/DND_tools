#!/usr/bin/env python3
import sys
import re
import shutil

def validate_argument(arg):
    # Validate that first character is a lowercase letter [a-z]
    if not re.match(r'^[a-z]', arg):
        print("Error: The first character must be a lowercase letter [a-z].")
        sys.exit(1)
    # Validate that the argument contains only lowercase letters and underscores
    if not re.fullmatch(r'[a-z_]+', arg):
        print("Error: Argument can only contain lowercase letters [a-z] and underscores [_].")
        sys.exit(1)

def copy_file(src, dst):
    try:
        shutil.copyfile(src, dst)
    except Exception as e:
        print(f"Error copying {src} to {dst}: {e}")
        sys.exit(1)

def replace_in_file(filename, replacements):
    try:
        with open(filename, 'r') as f:
            content = f.read()
        # Replace each key with its corresponding value
        for old, new in replacements.items():
            content = content.replace(old, new)
        with open(filename, 'w') as f:
            f.write(content)
    except Exception as e:
        print(f"Error processing file {filename}: {e}")
        sys.exit(1)

def main():
    # Ensure exactly one argument is provided
    if len(sys.argv) != 2:
        print("Error: You must provide exactly one argument.")
        sys.exit(1)
    
    arg = sys.argv[1]
    validate_argument(arg)
    
    # Define file names
    src_hpp = "template.hpp"
    src_cpp = "template.cpp"
    dst_hpp = f"{arg}.hpp"
    dst_cpp = f"{arg}.cpp"
    
    # Copy template files
    copy_file(src_hpp, dst_hpp)
    copy_file(src_cpp, dst_cpp)
    
    # Compute uppercase and capitalized versions
    arg_upper = arg.upper()
    arg_capitalized = arg[0].upper() + arg[1:]
    
    # Define replacements
    replacements = {
        "template": arg,
        "TEMPLATE": arg_upper,
        "Template": arg_capitalized
    }
    
    # Replace content in the copied files
    for filename in (dst_hpp, dst_cpp):
        replace_in_file(filename, replacements)
    
    print(f"Successfully created {dst_hpp} and {dst_cpp} from template files.")

if __name__ == '__main__':
    main()

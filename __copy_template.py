import sys
import re
import shutil

def validate_argument(arg):
    if not re.match(r'^[a-z]', arg):
        print("Error: The first character must be a lowercase letter [a-z].")
        sys.exit(1)
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
        pattern = r'template\s*<\s*int\s+Amount\s*,\s*int\s+Faces\s*>'
        placeholder = "__TEMPLATE_INT_AMOUNT_INT_FACES__"
        content = re.sub(pattern, placeholder, content)
        for old, new in replacements.items():
            content = content.replace(old, new)
        content = content.replace(placeholder, "template <int Amount, int Faces>")
        with open(filename, 'w') as f:
            f.write(content)
    except Exception as e:
        print(f"Error processing file {filename}: {e}")
        sys.exit(1)

def main():
    if len(sys.argv) != 2:
        print("Error: You must provide exactly one argument.")
        sys.exit(1)
    arg = sys.argv[1]
    validate_argument(arg)
    src_hpp = "template.hpp"
    src_cpp = "template.cpp"
    dst_hpp = f"{arg}.hpp"
    dst_cpp = f"{arg}.cpp"
    copy_file(src_hpp, dst_hpp)
    copy_file(src_cpp, dst_cpp)
    arg_upper = arg.upper()
    arg_capitalized = arg[0].upper() + arg[1:]
    replacements = {
        "template": arg,
        "TEMPLATE": arg_upper,
        "Template": arg_capitalized
    }
    for filename in (dst_hpp, dst_cpp):
        replace_in_file(filename, replacements)
    print(f"Successfully created {dst_hpp} and {dst_cpp} from template files.")

if __name__ == '__main__':
    main()

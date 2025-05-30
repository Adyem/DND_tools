#!/usr/bin/env python3
import platform
import subprocess
import sys
import shutil
import ctypes  # Moved import to the top

def install_dependencies_ubuntu():
    packages = ['clang', 'make']  # Removed 'libsfml-dev'
    print("Updating package lists (Ubuntu)...")
    try:
        subprocess.run(["sudo", "apt-get", "update"], check=True)
    except subprocess.CalledProcessError:
        print("Failed to update package lists. Exiting.")
        sys.exit(1)
    
    print("Installing required packages on Ubuntu: " + ", ".join(packages))
    try:
        subprocess.run(["sudo", "apt-get", "install", "-y"] + packages, check=True)
    except subprocess.CalledProcessError:
        print("Failed to install one or more packages on Ubuntu. Exiting.")
        sys.exit(1)

def install_dependencies_macos():
    print("Detected macOS.")
    if shutil.which("brew") is None:
        print("Homebrew not found. Please install Homebrew from https://brew.sh/ and re-run this script.")
        sys.exit(1)
    if shutil.which("clang") is None or shutil.which("make") is None:
        print("clang or make not found. Please install Xcode command line tools by running 'xcode-select --install'.")
        sys.exit(1)
    print("Updating Homebrew...")
    try:
        subprocess.run(["brew", "update"], check=True)
    except subprocess.CalledProcessError:
        print("Failed to update Homebrew. Exiting.")
        sys.exit(1)
    # SFML installation removed

def install_dependencies_windows():
    print("Detected Windows 11.")
    if shutil.which("choco") is None:
        print("Chocolatey not found. Installing Chocolatey...")
        try:
            subprocess.run([
                "powershell",
                "-NoProfile",
                "-ExecutionPolicy", "Bypass",
                "-Command",
                "Set-ExecutionPolicy Bypass -Scope Process -Force; "
                "[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.SecurityProtocolType]::Tls12; "
                "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
            ], shell=True, check=True)
        except subprocess.CalledProcessError:
            print("Failed to install Chocolatey. Please install it manually from https://chocolatey.org/install and re-run this script.")
            sys.exit(1)
    print("Upgrading all Chocolatey packages...")
    try:
        subprocess.run(["choco", "upgrade", "all", "-y"], shell=True, check=True)
    except subprocess.CalledProcessError:
        print("Failed to upgrade packages with Chocolatey. Continuing...")
    # Removed SFML from the installation list
    packages = [("llvm", "LLVM (includes clang)"), ("make", "Make")]
    for pkg, desc in packages:
        print(f"Installing {desc} with Chocolatey...")
        try:
            subprocess.run(["choco", "install", pkg, "-y"], shell=True, check=True)
        except subprocess.CalledProcessError:
            print(f"Failed to install {desc} using Chocolatey. Please check your installation or install it manually.")
            sys.exit(1)

def compile_source():
    print("Compiling source using make...")
    try:
        subprocess.run(["make"], check=True)
    except subprocess.CalledProcessError:
        print("Compilation failed. Please check your Makefile and source code.")
        sys.exit(1)
    print("Compilation successful!")

def main():
    current_os = platform.system()
    if current_os == "Linux":
        print("Detected Linux OS. Assuming Ubuntu for now.")
        install_dependencies_ubuntu()
        compile_source()
    elif current_os == "Darwin":
        install_dependencies_macos()
        compile_source()
    elif current_os == "Windows":
        try:
            is_admin = ctypes.windll.shell32.IsUserAnAdmin()
        except Exception:
            is_admin = False
        if not is_admin:
            print("Re-launching script as administrator...")
            params = " ".join(sys.argv)
            ctypes.windll.shell32.ShellExecuteW(None, "runas", sys.executable, params, None, 1)
            sys.exit(0)
        install_dependencies_windows()
        compile_source()
    else:
        print(f"This script does not currently support OS: {current_os}")
        sys.exit(1)

if __name__ == "__main__":
    main()

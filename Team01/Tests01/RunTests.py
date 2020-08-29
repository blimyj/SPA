#
# A friendly script to help with system testing :)
#

import argparse
import os
import re
import subprocess
import sys



AUTOTESTER_DIRECTORIES = [".", "../Code01/Debug"]
AUTOTESTER_FILE_NAME = "AutoTester.exe"
OUTPUT_DIRECTORY = "./RunTestsOutput"

QUERIES_EXTENSION = "qry"
SOURCE_EXTENSION = "src"
SOURCE_DEPENDENCIES_EXTENSION = "dep"

WARNING_COLOR = "\033[93m"
ERROR_COLOR = "\033[91m"
END_COLOR = "\033[0m"



def printinfo(s):
    print("Info: {}".format(s))

def printerr(s):
    print("{}Error: {}{}".format(ERROR_COLOR, s, END_COLOR))
    exit(1)

def printwarn(s):
    print("{}Warning: {}{}".format(WARNING_COLOR, s, END_COLOR))



# Find AutoTester.exe
def find_autotester_path():
    printinfo("Finding '{}'...".format(AUTOTESTER_FILE_NAME))
    autotester_path = None
    for path in AUTOTESTER_DIRECTORIES:
        path = os.path.join(os.getcwd(), path, AUTOTESTER_FILE_NAME)
        if os.path.isfile(path):
            autotester_path = os.path.abspath(path)
            break

    if not autotester_path:
        printerr("'{}' not found! Please check that you have built AutoTester, and it is in any of these directories:\n{}"
            .format(AUTOTESTER_FILE_NAME, "\n".join(map(lambda p : os.path.abspath(p), AUTOTESTER_DIRECTORIES))))

    printinfo("'{}' found! '{}'".format(AUTOTESTER_FILE_NAME, autotester_path))
    return autotester_path

# Find all query and source files
def get_tests_paths():
    printinfo("Finding all query and source files...")
    queries_paths = []
    source_paths = []
    for (dir_path, dirs, files) in os.walk(tests_dir_path):
        for f in files:
            match = re.search("^(.+)\\.([^.]+)$", f)
            if not match:
                continue

            name = match.group(1)
            ext = match.group(2)

            path = os.path.join(dir_path, name)
            path = os.path.abspath(path)
            if ext == QUERIES_EXTENSION:
                queries_paths.append(path)
            elif ext == SOURCE_EXTENSION:
                source_paths.append(path)
    return (queries_paths, source_paths)



def parse_source(content):
    print(content)



# Summarize 'coverage' of all .qry and .src files
def analyse():
    printerr("This function is not implemented yet :)")

# Generate .lab files from existing .src files
def label():
    queries_paths, source_paths = get_tests_paths()

    printinfo("Generating .lab files...")
    for source_path in source_paths:
        dir_path = os.path.dirname(source_path)
        source_path = "{}.{}".format(source_path, SOURCE_EXTENSION)

        with open(source_path) as d:
            content = "".join(d.readlines())

        ast = parse_source(content)
        break

# Tests all .src files using AutoTester
def run():
    autotester_path = find_autotester_path()
    queries_paths, source_paths = get_tests_paths()

    if len(source_paths) == 0:
        printwarn("No source files were found! Exiting...")
        exit()

    # Check dependencies of source files
    printinfo("Checking source dependencies files...")
    tests = []
    for source_path in source_paths:
        dependencies_path = "{}.{}".format(source_path, SOURCE_DEPENDENCIES_EXTENSION)
        if not os.path.isfile(dependencies_path):
            path = "{}.{}".format(source_path, SOURCE_EXTENSION)
            path = os.path.relpath(path)
            printwarn("'{}' is missing its dependency file! Skipping...".format(path))
            continue

        with open(dependencies_path) as d:
            for line in d:
                line = line.rstrip()
                queries_path = os.path.join(os.path.dirname(source_path), line)
                queries_path = os.path.abspath(queries_path)

                if not queries_path in queries_paths:
                    d_path = os.path.relpath(dependencies_path)
                    q_path = "{}.{}".format(queries_path, QUERIES_EXTENSION)
                    q_path = os.path.relpath(q_path)
                    printwarn("'{}': '{}' query file does not exist! Skipping...".format(d_path, q_path))
                    continue

                tests.append((source_path, queries_path))

    # Test each source file with it's queries
    printinfo("Testing all source files...")
    for index, (source_path, queries_path) in enumerate(tests):
        source_full_path = "{}.{}".format(source_path, SOURCE_EXTENSION)
        queries_full_path = "{}.{}".format(queries_path, QUERIES_EXTENSION)

        # Output Name Format: Source Path (Relative Query Path)
        s_name = os.path.relpath(source_path, tests_dir_path)
        s_name = os.path.normpath(s_name)
        s_name = "-".join(s_name.split(os.sep))
        q_name = os.path.relpath(queries_path, os.path.dirname(source_path))
        q_name = os.path.normpath(q_name)
        q_name = "-".join(q_name.split(os.sep))
        output_full_path = "{} ({}).xml".format(s_name, q_name)
        output_full_path = os.path.join(OUTPUT_DIRECTORY, output_full_path)
        output_full_path = os.path.abspath(output_full_path)

        # Run AutoTester
        printinfo("Running test ({}/{}): {} ({})".format(index+1, len(tests), s_name, q_name))
        process = subprocess.run([autotester_path, source_full_path, queries_full_path, output_full_path], stdout=subprocess.DEVNULL)

        if not process.returncode == 0:
            printerr("'{}' returned with non-zero exit code :(\nFull Command: {} {} {} {}"
            .format(AUTOTESTER_FILE_NAME, autotester_path, source_full_path, queries_full_path, output_full_path))

    printinfo("All tests done! :) Please check '{}' directory for all AutoTester outputs!".format(os.path.relpath(OUTPUT_DIRECTORY)))



# Ensure python is 3.0.0 or higher
if not sys.version_info.major >= 3:
    printerr("Please run this script with python 3.0.0 or higher!")

# Parse command arguments
parser = argparse.ArgumentParser()
parser.add_argument("-a", "--analyse", action="store_true", help="Summarize 'coverage' of all .qry and .src files")
parser.add_argument("-l", "--label", action="store_true", help="Generate .lab files from existing .src files")
parser.add_argument("-r", "--run", action="store_true", help="Tests all .src files using AutoTester")
parser.add_argument("tests_dir_path", help="Path of directory containing tests")
args = parser.parse_args()

# If no options are selected, run by default
if not (args.analyse or args.label or args.run):
    args.run = True

# Check tests_path
tests_dir_path = args.tests_dir_path
if not os.path.isdir(tests_dir_path):
    path = os.path.abspath(tests_dir_path)
    printerr("'{}' is not a directory!".format(path))

# Create output directory
if not os.path.exists(OUTPUT_DIRECTORY):
    os.mkdir(OUTPUT_DIRECTORY)

# Check output directory
if not os.path.isdir(OUTPUT_DIRECTORY):
    printerr("{} is not a directory! Please delete it.".format(OUTPUT_DIRECTORY))

# Run options
if args.analyse:
    analyse()

if args.label:
    label()

if args.run:
    run()

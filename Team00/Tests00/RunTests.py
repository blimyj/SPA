import os
import re
import subprocess
import sys



# TODO: Change Code00 when appropriate
AUTOTESTER_DIRECTORIES = [".", "../Code00/Debug"]
AUTOTESTER_FILE_NAME = "AutoTester.exe"
OUTPUT_DIRECTORY = "./RunTestsOutput"

QUERIES_EXTENSION = "qry"
SOURCE_EXTENSION = "src"
SOURCE_DEPENDENCIES_EXTENSION = "dep"



def printinfo(s):
    print("Info: {}".format(s))

def printerr(s):
    print("Error: {}".format(s))

def printwarn(s):
    print("Warning: {}".format(s))



# Ensure python is 3.0.0 or higher
if not sys.version_info.major >= 3:
    printerr("Please run this script with python 3.0.0 or higher!")
    exit()

if len(sys.argv) <= 1:
    print("Usage: python RunTests.py <Directory Containing Tests>")
    exit()

# Check tests_path
tests_dir_path = os.path.join(os.getcwd(), sys.argv[1])
if not os.path.isdir(tests_dir_path):
    path = os.path.abspath(tests_dir_path)
    printerr("'{}' is not a directory!".format(path))
    exit()

# Create output directory
if not os.path.exists(OUTPUT_DIRECTORY):
    os.mkdir(OUTPUT_DIRECTORY)

# Check output directory
if not os.path.isdir(OUTPUT_DIRECTORY):
    printerr("{} is not a directory! Please delete it.".format(OUTPUT_DIRECTORY))
    exit()

# Find AutoTester.exe
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
    exit()

printinfo("'{}' found! '{}'".format(AUTOTESTER_FILE_NAME, autotester_path))

# Find all query and source files
printinfo("Finding all query and source files...")
queries_paths = set()
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
            queries_paths.add(path)
        elif ext == SOURCE_EXTENSION:
            source_paths.append(path)

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

            tests.append([source_path, queries_path])

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
        printerr("'{}' returned with non-zero exit code :(".format(AUTOTESTER_FILE_NAME))
        printerr("Full Command: {} {} {} {}".format(autotester_path, source_full_path, queries_full_path, output_full_path))
        exit()

printinfo("All tests done! :) Please check '{}' directory for all AutoTester outputs!".format(os.path.relpath(OUTPUT_DIRECTORY)))

#
# A friendly script to help with system testing :)
#

import argparse
import collections
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
LABEL_EXTENSION = "lab"

WARNING_COLOR = "\033[93m"
ERROR_COLOR = "\033[91m"
END_COLOR = "\033[0m"

LABEL_INDENTATION = "    "

TOKEN_NAME = 0
TOKEN_INTEGER = 1
TOKEN_OPEN_BRACKET = 2
TOKEN_CLOSE_BRACKET = 3
TOKEN_OPEN_BRACE = 4
TOKEN_CLOSE_BRACE = 5
TOKEN_SEMICOLON = 6
TOKEN_EXPR = 7
TOKEN_TERM = 8
TOKEN_REL_EXPR = 9
TOKEN_NOT = 10
TOKEN_AND = 11
TOKEN_OR = 12
TOKEN_EQUALS = 13
TOKEN_EOF = 14

NODE_PROGRAM = 0
NODE_PROCEDURE = 1
NODE_STATEMENT_LIST = 2
NODE_STATEMENT_READ = 3
NODE_STATEMENT_PRINT = 4
NODE_STATEMENT_WHILE = 5
NODE_STATEMENT_IF = 6
NODE_STATEMENT_ASSIGN = 7

TOKENS_PATTERN = {
    "[A-Za-z][A-Za-z\d]*": TOKEN_NAME,
    "\d+": TOKEN_INTEGER,
    "\(": TOKEN_OPEN_BRACKET,
    "\)": TOKEN_CLOSE_BRACKET,
    "{": TOKEN_OPEN_BRACE,
    "}": TOKEN_CLOSE_BRACE,
    ";": TOKEN_SEMICOLON,
    "\+|-": TOKEN_EXPR,
    "\*|\/|%": TOKEN_TERM,
    ">=|<=|==|!=|>|<": TOKEN_REL_EXPR,
    "!": TOKEN_NOT,
    "&&": TOKEN_AND,
    "\|\|": TOKEN_OR,
    "=": TOKEN_EQUALS,
    "\s+": None,
    ".": None
}



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



def tokenize_source(content):
    out = collections.deque()
    while True:
        length = len(content)
        if length == 0:
            out.append((TOKEN_EOF, "EOF"))
            return out

        for k, v in TOKENS_PATTERN.items():
            match = re.match(k, content)
            if not match:
                continue

            word = match.group()
            content = content[len(word):]
            if not v == None:
                out.append((v, word))
            break

        if length == len(content):
            raise Exception("Failed to tokenize! :(")

def not_none(n, error):
    if n is None:
        raise Exception(error)
    return n

def parse_program(tokens):
    children = []
    children.append(not_none(parse_procedure(tokens), "Expected 'PROCEDURE'!"))
    if not tokens[0][0] == TOKEN_EOF:
        raise Exception("Expected 'EOF' after 'PROCEDURE'!")
    return (NODE_PROGRAM, children)

def parse_procedure(tokens):
    if not (tokens[0][0] == TOKEN_NAME and tokens[0][1] == "procedure"):
        return None
    children = []
    tokens.popleft()
    token = tokens.popleft()
    if not token[0] == TOKEN_NAME:
        raise Exception("Expected 'NAME' after 'procedure'!")
    children.append(token[1])
    if not tokens.popleft()[0] == TOKEN_OPEN_BRACE:
        raise Exception("Expected '{{' after 'procedure {}'!".format(children[0]))
    children.append(not_none(parse_statement_list(tokens), "Expected 'STATEMENT_LIST' after 'procedure {} {{'!".format(children[0])))
    if not tokens.popleft()[0] == TOKEN_CLOSE_BRACE:
        raise Exception("Expected '}}' after 'procedure {} {{ STATEMENT_LIST'!".format(children[0]))
    return (NODE_PROCEDURE, children)

def parse_statement_list(tokens):
    children = []
    while True:
        c = parse_statement(tokens)
        if c is None:
            break
        children.append(c)
    if len(children) < 1:
        return None
    return (NODE_STATEMENT_LIST, children)

def parse_statement(tokens):
    for f in [parse_assign, parse_read, parse_print, parse_while, parse_if]:
        o = f(tokens)
        if not o is None:
            return o
    return None

def parse_read(tokens):
    if not (tokens[0][0] == TOKEN_NAME and tokens[0][1] == "read"):
        return None
    children = []
    tokens.popleft()
    token = tokens.popleft()
    if not token[0] == TOKEN_NAME:
        raise Exception("Expected 'NAME' after 'read'!")
    children.append(token[1])
    if not tokens.popleft()[0] == TOKEN_SEMICOLON:
        raise Exception("Expected ';' after 'read {}'!".format(children[0]))
    return (NODE_STATEMENT_READ, children)

def parse_print(tokens):
    if not (tokens[0][0] == TOKEN_NAME and tokens[0][1] == "print"):
        return None
    children = []
    tokens.popleft()
    token = tokens.popleft()
    if not token[0] == TOKEN_NAME:
        raise Exception("Expected 'NAME' after 'print'!")
    children.append(token[1])
    if not tokens.popleft()[0] == TOKEN_SEMICOLON:
        raise Exception("Expected ';' after 'print {}'!".format(children[0]))
    return (NODE_STATEMENT_PRINT, children)

def parse_while(tokens):
    if not (tokens[0][0] == TOKEN_NAME and tokens[0][1] == "while"):
        return None
    children = []
    tokens.popleft()
    if not tokens.popleft()[0] == TOKEN_OPEN_BRACKET:
        raise Exception("Expected '(' after 'while'!")
    children.append(not_none(parse_cond_expr(tokens), "Expected 'COND_EXPR' after 'while ('!"))
    if not tokens.popleft()[0] == TOKEN_CLOSE_BRACKET:
        raise Exception("Expected ')' after 'while ({}'!".format(children[0]))
    if not tokens.popleft()[0] == TOKEN_OPEN_BRACE:
        raise Exception("Expected '{{' after 'while ({})'!".format(children[0]))
    children.append(not_none(parse_statement_list(tokens), "Expected 'STATEMENT_LIST' after 'while ({}) {{'!".format(children[0])))
    if not tokens.popleft()[0] == TOKEN_CLOSE_BRACE:
        raise Exception("Expected '}}' after 'while ({}) {{ STATEMENT_LIST'!".format(children[0]))
    return (NODE_STATEMENT_WHILE, children)

def parse_if(tokens):
    if not (tokens[0][0] == TOKEN_NAME and tokens[0][1] == "if"):
        return None
    children = []
    tokens.popleft()
    if not tokens.popleft()[0] == TOKEN_OPEN_BRACKET:
        raise Exception("Expected '(' after 'if'!")
    children.append(not_none(parse_cond_expr(tokens), "Expected 'COND_EXPR' after 'if' (!"))
    if not tokens.popleft()[0] == TOKEN_CLOSE_BRACKET:
        raise Exception("Expected ')' after 'if ({}'!".format(children[0]))
    token = tokens.popleft()
    if not (token[0] == TOKEN_NAME and token[1] == "then"):
        raise Exception("Expected 'then' after 'if ({})'!".format(children[0]))
    if not tokens.popleft()[0] == TOKEN_OPEN_BRACE:
        raise Exception("Expected '{{' after 'if ({}) then'!".format(children[0]))
    children.append(not_none(parse_statement_list(tokens), "Expected 'STATEMENT_LIST' after 'if ({}) then {{'!".format(children[0])))
    if not tokens.popleft()[0] == TOKEN_CLOSE_BRACE:
        raise Exception("Expected '}}' after 'if ({}) then {{ STATEMENT_LIST'!".format(children[0]))
    token = tokens.popleft()
    if not (token[0] == TOKEN_NAME and token[1] == "else"):
        raise Exception("Expected 'else' after 'if ({}) then {{ STATEMENT_LIST }}'!".format(children[0]))
    if not tokens.popleft()[0] == TOKEN_OPEN_BRACE:
        raise Exception("Expected '{{' after 'if ({}) then {{ STATEMENT_LIST }} else'!".format(children[0]))
    children.append(not_none(parse_statement_list(tokens), "Expected 'STATEMENT_LIST' after 'if ({}) then {{ STATEMENT_LIST }} else {{'!".format(children[0])))
    if not tokens.popleft()[0] == TOKEN_CLOSE_BRACE:
        raise Exception("Expected '}}' after 'if ({}) then {{ STATEMENT_LIST }} else {{ STATEMENT_LIST'!".format(children[0]))
    return (NODE_STATEMENT_IF, children)

def parse_assign(tokens):
    if not (tokens[0][0] == TOKEN_NAME and tokens[1][0] == TOKEN_EQUALS):
        return None
    children = []
    children.append(tokens.popleft()[1])
    tokens.popleft()
    children.append(not_none(parse_expr(tokens), "Expected 'EXPR' after '{} ='!".format(children[0])))
    if not tokens.popleft()[0] == TOKEN_SEMICOLON:
        raise Exception("Expected ';' after '{} = {}'!".format(children[0], children[1]))
    return (NODE_STATEMENT_ASSIGN, children)

def parse_cond_expr(tokens):
    if tokens[0][0] == TOKEN_OPEN_BRACKET:
        o = tokens.popleft()[1]
        o += not_none(parse_cond_expr(tokens), "Expected 'COND_EXPR' after '('!")
        token = tokens.popleft()
        if not token[0] == TOKEN_CLOSE_BRACKET:
            raise Exception("Expected ')' after '{}'!".format(o))
        o += token[1]
        token = tokens.popleft()
        if not (token[0] == TOKEN_AND or token[0] == TOKEN_OR):
            raise Exception("Expected '&&' or '||' after '{}'!".format(o))
        o += " {} ".format(token[1])
        token = tokens.popleft()
        if not token[0] == TOKEN_OPEN_BRACKET:
            raise Exception("Expected '(' after '{}'!".format(o))
        o += token[1]
        o += not_none(parse_cond_expr(tokens), "Expected 'COND_EXPR' after '{}'!".format(o))
        token = tokens.popleft()
        if not token[0] == TOKEN_CLOSE_BRACKET:
            raise Exception("Expected ')' after '{}'!".format(o))
        o += token[1]
        return o
    elif tokens[0][0] == TOKEN_NOT:
        o = tokens.popleft()[1]
        token = tokens.popleft()
        if not token[0] == TOKEN_OPEN_BRACKET:
            raise Exception("Expected '(' after '{}'!".format(o))
        o += token[1]
        o += not_none(parse_cond_expr(tokens), "Expected 'COND_EXPR' after '{}'!".format(o))
        token = tokens.popleft()
        if not token[0] == TOKEN_CLOSE_BRACKET:
            raise Exception("Expected ')' after '{}'!".format(o))
        o += token[1]
        return o
    o = parse_rel_expr(tokens)
    if o is None:
        return None
    return o

def parse_rel_expr(tokens):
    o = parse_rel_factor(tokens)
    if o is None:
        return None
    if not tokens[0][0] == TOKEN_REL_EXPR:
        raise Exception("Expected '>=' or '<=' or '==' or '!=' or '>' or '<' after '{}'!".format(o))
    o += " {} ".format(tokens.popleft()[1])
    o += not_none(parse_rel_factor(tokens), "Expected 'REL_FACTOR' after '{}'!".format(o))
    return o

def parse_rel_factor(tokens):
    o = parse_expr(tokens)
    if not o is None:
        return o
    if tokens[0][0] == TOKEN_NAME or tokens[0][0] == TOKEN_INTEGER:
        return tokens.popleft()[1]
    return None

def parse_expr(tokens):
    o = parse_term(tokens)
    if o is None:
        return None
    if not tokens[0][0] == TOKEN_EXPR:
        return o
    o += " {} ".format(tokens.popleft()[1])
    o += parse_expr(tokens)
    return o

def parse_term(tokens):
    o = parse_factor(tokens)
    if o is None:
        return None
    if not tokens[0][0] == TOKEN_TERM:
        return o
    o += " {} ".format(tokens.popleft()[1])
    o += parse_term(tokens)
    return o

def parse_factor(tokens):
    if tokens[0][0] == TOKEN_NAME or tokens[0][0] == TOKEN_INTEGER:
        return tokens.popleft()[1]
    if tokens[0][0] == TOKEN_OPEN_BRACKET:
        o = tokens.popleft()[1]
        o += parse_expr(tokens)
        token = tokens.popleft()
        if not token[0] == TOKEN_CLOSE_BRACKET:
            raise Exception("Expected ')' after '{}'!".format(o))
        o += token[1]
        return o
    return None



# Summarize 'coverage' of all .qry and .src files
def analyse():
    printerr("This function is not implemented yet :)")

# Check that all .src files contain valid grammar
def check():
    queries_paths, source_paths = get_tests_paths()

    if len(source_paths) == 0:
        printwarn("No source files were found!")
        return

    printinfo("Checking .src files...")
    for index, source_path in enumerate(source_paths):
        source_full_path = "{}.{}".format(source_path, SOURCE_EXTENSION)

        with open(source_full_path) as f:
            content = "".join(f.readlines())

        path = os.path.relpath(source_full_path)
        printinfo("Checking ({}/{}): '{}'".format(index+1, len(source_paths), path))

        try:
            parse_program(tokenize_source(content))
        except Exception as err:
            printwarn("Invalid grammar!\nError Message: {}".format(err))
            continue

        printinfo("Valid grammar :)")

    printinfo("All done! :)")


# Generate .lab files from existing .src files
def label():
    queries_paths, source_paths = get_tests_paths()

    if len(source_paths) == 0:
        printwarn("No source files were found!")
        return

    printinfo("Generating .lab files...")
    for index, source_path in enumerate(source_paths):
        source_full_path = "{}.{}".format(source_path, SOURCE_EXTENSION)
        label_full_path = "{}.{}".format(source_path, LABEL_EXTENSION)

        with open(source_full_path) as f:
            content = "".join(f.readlines())

        try:
            tokens = tokenize_source(content)
            ast = parse_program(tokens)
        except:
            continue

        path = os.path.relpath(label_full_path)
        printinfo("Labelling ({}/{}): '{}'".format(index+1, len(source_paths), path))
        statements = []
        for i, p in enumerate(ast[1]):
            if i != 0:
                statements.append((False, 0, ""))
            v = "procedure {} {{".format(p[1][0])
            statements.append((False, 0, v))
            statements.extend(label_statements(p[1][1][1], 1))
            statements.append((False, 0, "}"))

        lines = []
        n = 0
        for b, i, v in statements:
            indent = LABEL_INDENTATION * i
            if b:
                n += 1
                lines.append("{:03d} {}{}\n".format(n, indent, v))
            else:
                lines.append("--- {}{}\n".format(indent, v))

        with open(label_full_path, "w") as f:
            f.writelines(lines)

    printinfo("All done! :)")

def label_statements(statement_list, indent):
    result = []
    for s in statement_list:
        if s[0] == NODE_STATEMENT_READ:
            v = "read {};".format(s[1][0])
            result.append((True, indent, v))
        elif s[0] == NODE_STATEMENT_PRINT:
            v = "print {};".format(s[1][0])
            result.append((True, indent, v))
        elif s[0] == NODE_STATEMENT_WHILE:
            v = "while ({}) {{".format(s[1][0])
            result.append((True, indent, v))
            result.extend(label_statements(s[1][1][1], indent + 1))
            result.append((False, indent, "}"))
        elif s[0] == NODE_STATEMENT_IF:
            v = "if ({}) then {{".format(s[1][0])
            result.append((True, indent, v))
            result.extend(label_statements(s[1][1][1], indent + 1))
            result.append((False, indent, "} else {"))
            result.extend(label_statements(s[1][2][1], indent + 1))
            result.append((False, indent, "}"))
        elif s[0] == NODE_STATEMENT_ASSIGN:
            v = "{} = {};".format(s[1][0], s[1][1])
            result.append((True, indent, v))
    return result

# Tests all .src files using AutoTester
def run():
    autotester_path = find_autotester_path()
    queries_paths, source_paths = get_tests_paths()

    if len(source_paths) == 0:
        printwarn("No source files were found!")
        return

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
parser.add_argument("-c", "--check", action="store_true", help="Check that all .src files contain valid grammar")
parser.add_argument("-l", "--label", action="store_true", help="Generate .lab files from existing .src files")
parser.add_argument("-r", "--run", action="store_true", help="Tests all .src files using AutoTester")
parser.add_argument("tests_dir_path", help="Path of directory containing tests")
args = parser.parse_args()

# If no options are selected, run by default
if not (args.analyse or args.check or args.label or args.run):
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

if args.check:
    check()

if args.label:
    label()

if args.run:
    run()

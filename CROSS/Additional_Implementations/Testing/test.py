import sys
import os
import itertools
import subprocess
import csv

# print in green
def printg(s):
    print(f"\033[32m>>>> {s}\033[0m")

# print in red
def printr(s):
    print(f"\033[31m>>>> {s}\033[0m")

# run a shell command
def run(command):
    result = subprocess.run(command, shell=True)
    if result.returncode != 0:
        os.chdir(base_directory)
        printr(f"{command}")
        printr(f"failed with return code {result.returncode}")
        sys.exit(result.returncode)

# run the test on a specific CROSS variant
def run_test(test, problem, category, target, implementation, compiler, compiler_options):
    test_directory = os.path.join(base_directory, test)
    # test.c
    if(test_info[test]["test_type"] == "c"):
        # create the build directory
        build_directory = os.path.join(test_directory, "build")
        run(f"rm -rf {build_directory}")
        run(f"mkdir -p {build_directory}")
        os.chdir(build_directory)
        run( "echo '*' > .gitignore")
        # copy CMakelists.txt since it's common to all C tests
        cmake_directory = os.path.join(test_directory, "cmake")
        run(f"rm -rf {cmake_directory}")
        run(f"mkdir -p {cmake_directory}")
        run(f"echo '*' > {cmake_directory}/.gitignore")
        run(f"cp {base_directory}/helpers/CMakeLists.txt {cmake_directory}/CMakeLists.txt")
        # build
        run(f"cmake {cmake_directory} "
            f"      -DCMAKE_RULE_MESSAGES=OFF "
            f"      -DCROSS_PROBLEM={problem} "
            f"      -DCROSS_CATEGORY={category} "
            f"      -DCROSS_TARGET={target} "
            f"      -DCROSS_IMPLEMENTATION={implementation} "
            f"      -DCMAKE_C_COMPILER={compiler} "
            f"      -DCMAKE_C_FLAGS=\"{compiler_options}\" ")
        run( "make -s -j$(nproc)")
        # run
        run( "./bin/test.o")
    # test.py
    elif(test_info[test]["test_type"] == "py"):
        os.chdir(test_directory)
        run(f"python3 test.py {problem} {category} {target} {implementation}")
    # test.sh
    elif(test_info[test]["test_type"] == "sh"):
        cross_directory = os.path.join(base_directory, "..", "..")
        script=os.path.join(test_directory, "test.sh")
        os.chdir(cross_directory)
        run(f"{script}") # {problem} {category} {target} {implementation}
    else:
        printr(f"Error: Test not found in {test_directory}")
        sys.exit()
    os.chdir(base_directory)

###############################################################################
#################################### main #####################################
###############################################################################

# move to the directory where the script is located
base_directory = os.path.dirname(os.path.realpath(__file__))
os.chdir(base_directory)

# each test is stored in a separate subdirectory
available_tests = [folder.name for folder in os.scandir(base_directory) if folder.is_dir() and folder.name.startswith('test_')]

args = sys.argv[1:]

selections = {}

allowed_values = {
    "test" : available_tests,
    "problem": ["RSDP", "RSDPG"],                   # CROSS problem
    "category": ["1", "3", "5"],                    # CROSS security category
    "target": ["balanced", "fast", "small"],        # CROSS optimization target
    "implementation": ["optimized", "reference"],   # CROSS implementation
    "compiler": ["gcc", "clang"],                   # compiler
}

default_values = {
    "compiler" : "gcc",
    "compiler_options" : "-Wall -Wuninitialized -march=native -O3 -g3 -fsanitize=address", # -pedantic
}

# set selections to their default value
for key in allowed_values:
    selections[key] = ""
for key in default_values:
    selections[key] = default_values[key]

# get test info from csv
test_info = {}
with open('test.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)     
    key_column = reader.fieldnames[0]
    for row in reader:
        key = row[key_column]
        test_info[key] = {col: row[col] for col in row if col != key_column}

# print help
help_strings = ["-h", "--help", "-help", "help"]
if set(help_strings) & set(args):
    printg("OPTIONS:")
    for key in selections:
        if key in allowed_values:
            printg(f"{key} = {allowed_values[key]}")
        else:
            printg(f"{key} = <string>")
        if key in default_values:
            printg(f"  default: {default_values[key]}")
    printg("TESTS:")
    for test in available_tests:
        printg(f"{test}: {test_info[test]['description']}")
    sys.exit()

# set selections to the values passed as arguments
for arg in args:
    if ("=" not in arg) or (arg.split("=", 1)[0] not in selections):
        printr(f"Error: Invalid argument '{arg}'. Allowed arguments are {list(selections.keys())}")
        sys.exit()
    key, value = arg.split("=", 1)
    if key in allowed_values:
        if value in allowed_values[key]:
            selections[key] = value
        else:
            printr(f"Error: Invalid value '{value}' for '{key}'. Allowed values are {allowed_values[key]}")
            sys.exit()
    else:
        selections[key] = value

completed_tests = []

# run the test
for test in available_tests:
    if selections["test"] == "" or selections["test"] == test:
        # a test might ignore some parameters
        ignored_parameters = test_info[test]["ignored_parameters"].split(",")
        if ignored_parameters == ["all"]:
            ignored_parameters = list(selections.keys())
            ignored_parameters.remove("test")
        # generate all possible combinations of CROSS parameters
        combinations = itertools.product(
            allowed_values["problem"],
            allowed_values["category"],
            allowed_values["target"],
            allowed_values["implementation"])
        for pr,ca,ta,im in combinations:
            if (pr == selections["problem"] or selections["problem"] == "") and \
            (ca == selections["category"] or selections["category"] == "") and \
            (ta == selections["target"] or selections["target"] == "") and \
            (im == selections["implementation"] or selections["implementation"] == ""):
                if ("problem" in ignored_parameters): pr=""
                if ("category" in ignored_parameters): ca=""
                if ("target" in ignored_parameters): ta=""
                if ("implementation" in ignored_parameters): im=""
                if (test,pr,ca,ta,im) not in completed_tests:
                    printg(f"Running {test} on CROSS {pr} {ca} {ta} {im}")
                    run_test(test, pr, ca, ta, im, selections["compiler"], selections["compiler_options"])
                    completed_tests.append((test,pr,ca,ta,im))

printg("All tests completed")

# for key, value in selections.items():
#     printg(f"{key} = {value}")

# TODO:
# parametrize NUM_TESTS
# test_endinness on single message, not KAT
# add parameter "implementation" to test_endianness
# save KAT to file in test_kat

# global variables:
# base_directory
# test_info

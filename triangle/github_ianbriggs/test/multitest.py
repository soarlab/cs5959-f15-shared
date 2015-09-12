#!/usr/bin/env python3

# standard imports
import os as OS
import sys as SYS
import argparse as AP
import re as R

# imports from local files
import python_utils as PU

def build_argument_parser():
    parser = AP.ArgumentParser("runs a black box tester against all executables "
                               "in a directory")
    parser.add_argument("-v", "--verbose", help="increase output verbosity",
                        action="store_true")
    parser.add_argument("-d", "--directory",
                        help="Directory that contains the executables",
                        type=str, default=".")
    parser.add_argument("-t", "--tester",
                        help="Black box tester, must take exe as first arg",
                        type=str)
    parser.add_argument("-a", "--args",
                        help="additional arguments for the tester",
                        type=str)
    
    return parser
    
def get_all_executables(directory):
    executables_list = list()
    for file in OS.listdir(directory):
        if file[0] != '.':
            full_path = OS.path.join(directory, file)
            executables_list.append(full_path)
    return executables_list


def run_all_tests(tester, executables_list, test_args):
    for exe in executables_list:
        tester_output = PU.run(tester, [exe] + test_args, "Testing failed")
        PU.log(1, "Testing: {}\nOutput:\n{}\n".format(exe, tester_output))


    
def main():
    parser = build_argument_parser()
    arguments = parser.parse_args()
    if arguments.verbose:
        PU.set_log_level(1)
    directory = arguments.directory
    if not OS.path.exists(directory):
        PU.error("Directory {} does not exist".format(directory))
        SYS.exit(2)
    executables_list = get_all_executables(directory)
    print(executables_list)
    test_args = [arguments.args]
    run_all_tests(arguments.tester, executables_list, test_args)


if __name__ == "__main__":
    main()

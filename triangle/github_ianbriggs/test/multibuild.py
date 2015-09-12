#!/usr/bin/env python3

# standard imports
import os as OS
import sys as SYS
import argparse as AP
import re as R

# imports from local files
import python_utils as PU

compiler_name_regex = R.compile(r"((gcc)|(clang))(-\d\.\d)?\Z")

def build_argument_parser():
    parser = AP.ArgumentParser("runs the given C compile command with all "
                               "versions of gcc and clang in PATH")
    parser.add_argument("-v", "--verbose", help="increase output verbosity",
                        action="store_true")
    parser.add_argument("-o", "--output",
                        help="Basename for generated executables",
                        type=str, default="a.out")
    parser.add_argument("-c", "-ca", "--compiler-arguments",
                        help="Arguments to  give the C compilers",
                        type=str)
    
    return parser
    
def get_all_c_compilers():
    search_path_list = OS.environ.get("PATH").split(':')
    compiler_list = list()
    for single_path in search_path_list:
        for executable in OS.listdir(single_path):
            if compiler_name_regex.match(executable):
                full_path = OS.path.join(single_path, executable)
                compiler_list.append(full_path)
    return compiler_list


def build_with_all_c_compilers(compiler_arguments_list,
                               output_directory, output_name):
    compiler_list = get_all_c_compilers()
    for compiler in compiler_list:
        compiler_basename = OS.path.basename(compiler)
        output_filename = "{}-{}".format(output_name, compiler_basename)
        output_fullpath = OS.path.join(output_directory, output_filename)
        output_arg = "-o {}".format(output_fullpath)
        temp_args = compiler_arguments_list.copy() + [output_arg]
        compiler_output = PU.run(compiler, temp_args, "Unable to compile")
        PU.log(1, "Command: {}\nOutput:\n{}\n".format(compiler+' '+' '.join(temp_args),
                                                       compiler_output))


    
def main():
    parser = build_argument_parser()
    arguments = parser.parse_args()
    if arguments.verbose:
        PU.set_log_level(1)
    output_directory, output_name = OS.path.split(arguments.output)
    if not OS.path.exists(output_directory):
        PU.error("Requested output basename of {}".format(arguments.output))
        PU.error("    but directory {} does not exist".format(output_directory))
        SYS.exit(2)
    compiler_arguments_list = [arguments.compiler_arguments]
    build_with_all_c_compilers(compiler_arguments_list, output_directory,
                               output_name)


if __name__ == "__main__":
    main()

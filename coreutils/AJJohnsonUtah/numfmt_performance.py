import random
import subprocess
import sys
import time

def create_file_with_numbers(count):
    file = open (str(count) + "_numbers.txt", 'w')
    random.seed(count);
    for n in range(0, count):
        file.write(str(random.randint(0,99999999999)) + " ")

def create_string_with_numbers(count):
    random.seed(count)
    result_string = ""
    for n in range(0, count):
        result_string += str(random.randint(0,99999)) + " "
    return result_string

num_params = 1;
for count in range(0, 5):
    params = create_string_with_numbers(num_params)
    start_time = time.clock()
    subprocess.check_output("numfmt --to=si " + params, shell=True)
    end_time = time.clock()
    run_time = end_time - start_time
    print("Runtime for " + str(num_params) + " numbers: " + str(run_time) + "s (" + str(run_time/num_params) + "s/number)")
    num_params *= 10


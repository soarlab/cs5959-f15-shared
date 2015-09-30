# @author: Leland Stenquist
#
# A simple fuzzer to test the coreutils wc functionality
#

import subprocess
import random
import sys
import string
import time
import os
import threading

start = time.clock() # seperate timer not on a thread. This is just interesting.
print "Hello! \nLet's Start Our Fuzzer."

# Global variable
logged_files = 0
seed = 0
run_time = 3600.0 
end_prog = False
print "Your run time is " + str(run_time) + " seconds."

# This funtion gets called to terminate the program when the timer runs out
def endProg():
	global end_prog
	end_prog = True
	print "The program should terminate shortly."

# start our timer
t = threading.Timer(run_time, endProg)
t.start()

# get our random value as defined by our seed
def get_random_val():
	global seed
	random.seed(seed)
	return int(random.random() * 1000000)

# This function call the wc command and compares its output against the proper
#   testing output
def check_wc(test_file, length, flag = ""):
	cmd = "./src/wc " + flag + test_file		
	output = subprocess.check_output(cmd, shell=True)
	output = int("".join([i for i in output if i.isdigit()]))
	# if the flag is for bytes then we are just going to test against the
	#   stadard wc for bytes.
	if(flag == "-c "):
		length = subprocess.check_output("wc -c "+test_file, shell=True)
		length = int("".join([i for i in length if i.isdigit()]))
	elif(flag == "-L "):
		length = subprocess.check_output("wc -L "+test_file, shell=True)
		length = int("".join([i for i in length if i.isdigit()]))
	#print("%d:%d" % (length, output))
	return (output != length)
		
# if a test fails, this function is called to write the test to the 
#   log folder
def write_to_log(test):
	global seed
	global logged_files
	logged_files += 1
	if not os.path.exists("fuzzer_log"):
		os.makedirs("fuzzer_log")
	log_name = "fuzzer_log/"+ test + "_"  + str(seed)+ ".txt"
	with open(log_name, 'w+') as log:
		f = open('fuzz_file.txt','r')
		text = f.read()
		log.write(text)
		f.close()

# creates a files with size amount of chars
def create_char_file(size):
	count = 0
	
	with open('fuzz_file.txt', 'w+') as fuzz_f:
		while (count < size):
	        	count+=1
	        	fuzz_f.write(random.choice(string.printable))

# creates a file with size amount of words
def create_word_file(size):
	count = 0
	
	with open('fuzz_file.txt', 'w+') as fuzz_f:
		while (count < size):
	        	count+=1
			str_in = " "+"".join(random.choice(string.letters) for _ in range(4))
	        	fuzz_f.write(str_in)

# creates a file with size amount of lines
def create_line_file(size):
	count = 0

	with open('fuzz_file.txt', 'w+') as fuzz_f:
		while (count < size):
	        	count+=1
	        	fuzz_f.write("\n")

# The main loop of the program
while not (end_prog):
       	# Get our random variable
        val = get_random_val()
	# create a file with val amount of chars
	create_char_file(size = val)
	# check the byte count against standard io byte count
	if(check_wc(test_file = "fuzz_file.txt", flag = "-c ", length = val)):
		write_to_log(test = "byte")
	# check the char count against the file just created
	if(check_wc(test_file = "fuzz_file.txt", flag = "-m ", length = val)):
		write_to_log(test = "char")
	create_word_file(size = val)
	# check the word count against the file just created
	if(check_wc(test_file = "fuzz_file.txt", flag = "-w ", length = val)):
		write_to_log(test = "word")
	# check the line Length against standard io line length
	if(check_wc(test_file = "fuzz_file.txt", flag = "-L ", length = val)):
		write_to_log(test = "line_length")
	create_line_file(size = val)
	# check the line count against the file just created
	if(check_wc(test_file = "fuzz_file.txt", flag = "-l ", length = val)):
		write_to_log(test = "line")
	seed+=1

# Print Closing Messages
print "All Done!\nFiles Logged: " + str(logged_files)
print "Time Logged: " + str(time.clock()-start)


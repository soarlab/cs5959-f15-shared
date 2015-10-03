#fuzzer.py
# fuzzes: 1) add word, line, and/or byte

import random
import string
import subprocess

expected_word_count = 0
expected_line_count = 0
expected_byte_count = 0
logged_errs = 0

def set_zero():
	global expected_byte_count
	global expected_word_count
	global expected_line_count
	expected_word_count = 0
	expected_line_count = 0
	expected_byte_count = 0

def add_random():
	add_what = random.randint(0,1)
	added = ""
	if (add_what == 0):
		added = add_line()
	if (add_what == 1):
		added = add_word()
	return added

def add_word():
	global expected_word_count
	global expected_byte_count
	expected_word_count = expected_word_count + 1
	word = " "
	all_c = string.ascii_letters + string.digits
	# not a realistic distribution...
	word_length = random.randint(1, 16)
	for i in range(0, word_length):
		word = word + random.choice(all_c)
	expected_byte_count = expected_byte_count + len(word)
	return word

def add_line():
	global expected_line_count
	global expected_byte_count
	expected_line_count = expected_line_count + 1
	expected_byte_count = expected_byte_count + 1
	return '\n'

def add_byte():
	global expected_byte_count
	expected_byte_count = expected_byte_count + 1
	character = random.choice(string.ascii_letters + string.digits)
	return character

def create_file(test_file_name, size):
	f = open(test_file_name, 'w')
	# get a bunch of things
	# write out to file 
	for i in range(0, size):
		f.write(add_random())
	f.close()

def main():
	logged_errs = 0
	# maximum number of random things
	maxi = 1000000
	test_file_name = 'testfile'
	while(True):
		set_zero()
		size = random.randint(0, maxi)
		create_file(test_file_name, size)
		# run wc on file (all ways)
		res = subprocess.check_output(["wc", test_file_name])
		# compare wc output to expected, log if problem
		log_name = "log{errs}".format(errs=logged_errs)
		log = open(log_name, 'w')
		res = res.split()
		actual_line_count = int(res[0])
		actual_word_count = int(res[1])
		actual_byte_count = int(res[2])
		line_err = actual_line_count != expected_line_count
		byte_err = actual_byte_count != expected_byte_count
		word_err = actual_word_count != expected_word_count
		any_err = line_err or byte_err or word_err
		if (line_err):
			log.write("Line Count Error: expected - {expected}, actual = {actual}\n".format(actual=actual_line_count, expected=expected_line_count))
		if (byte_err):
			log.write("Byte Count Error: expected - {expected}, actual = {actual}\n".format(actual=actual_byte_count, expected=expected_byte_count))
		if (word_err):
			log.write("Word Count Error: expected - {expected}, actual = {actual}\n".format(actual=actual_word_count, expected=expected_word_count))
		if (any_err):
			f = open(test_file_name)
			log.write("File contents:\n" + f.read())
			log.write("\n\n\n\n")
			print("Error detected. Please see log.\n")
		log.close()

if __name__ == "__main__":
    main()

def expected():
	expected_word_count = len(raw.split())
	expected_line_count = len(raw.split('\n')) - 1
	expected_byte_count = os.path.getsize(file_name)
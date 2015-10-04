import subprocess
import logging
from random import randint

logger = logging.getLogger('exprTester')

def test(testcommand, expectedcommand):
	try:
		actual = subprocess.check_output(testcommand, shell=True)
	except subprocess.CalledProcessError as e:
		actual = e.returncode
	
	try:
		expected = subprocess.check_output(expectedcommand, shell=True)
	except subprocess.CalledProcessError as e:
		expected = e.returncode

	if(actual != expected):
		global logger
		logger.error("FAIL: coreutils 8.23 " + testcommand)
		logger.error("===== RESULT: " + str(actual))
		logger.error("===== coreutils 8.21 " + expectedcommand)
		logger.error("===== RESULT: " + str(expected))

def testWithKnownAnswer(command, answer):
	try:
		result = subprocess.check_output(command, shell=True)
	except subprocess.CalledProcessError as e:
		result = e.returncode

	if(result != answer):
		global logger
		logger.error("FAIL: coreutils 8.23 " + command)
		logger.error("===== RESULT: " + str(result))
		logger.error("===== ANSWER: " + answer)

		
def testNumeric(minValue, maxValue):
	options = ["E \+ E", "E \- E", "E / E", "E \* E", "#"]
	formula = options[randint(0,4)]
	
	i = 0
	
	# Generate a pseudo-random numeric expression
	while("E" in formula and i < 15):
		temp = ""
		for index in range(len(formula)):	
			if formula[index] == "E":
				if(index == 0):
					temp = options[randint(0,4)] + formula[1:]
				elif(index == len(formula) - 1):	
					temp = formula[:-1] + options[randint(0,4)]
				else:	
					temp = formula[0:index] + options[randint(0,4)] + formula[index + 1:]
		formula = temp
		i = i + 1
	
	formula = formula.replace("E", "#")

	# Replace all #'s with an actual number
	while("#" in formula):
		temp = ""
		for index in range(len(formula)):	
			if formula[index] == "#":
				if(index == 0):
					temp = str(randint(minValue, maxValue)) + formula[1:]
				elif(index == len(formula) - 1):	
					temp = formula[:-1] + str(randint(minValue, maxValue))
				else:	
					temp = formula[0:index] + str(randint(minValue, maxValue)) + formula[index + 1:]
		formula = temp
	
	test("../../src/expr " + formula, "expr " + formula)

def testRelation(minValue, maxValue):
	options = ["E '|' E", "E '&' E", "# '<' #", "# '<=' #", "# '==' #", "# '>' #", "# '>=' #", "# '!=' #", "# '%' #"]
	formula = options[randint(0,7)]
	
	i = 0
	
	# Generate a pseudo-random numeric expression
	while("E" in formula and i < 15):
		temp = ""
		for index in range(len(formula)):	
			if formula[index] == "E":
				if(index == 0):
					temp = options[randint(0,7)] + formula[1:]
				elif(index == len(formula) - 1):	
					temp = formula[:-1] + options[randint(0,7)]
				else:	
					temp = formula[0:index] + options[randint(0,7)] + formula[index + 1:]
		formula = temp
		i = i + 1
	
	formula = formula.replace("E", "#")

	# Replace all #'s with an actual number
	while("#" in formula):
		temp = ""
		for index in range(len(formula)):	
			if formula[index] == "#":
				if(index == 0):
					temp = str(randint(minValue, maxValue)) + formula[1:]
				elif(index == len(formula) - 1):	
					temp = formula[:-1] + str(randint(minValue, maxValue))
				else:	
					temp = formula[0:index] + str(randint(minValue, maxValue)) + formula[index + 1:]
		formula = temp
	
	test("../../src/expr " + formula, "expr " + formula)
#	test("expr " + formula, "expr " + formula)



def main():

	# Set up logging
	global logger
	hdlr = logging.FileHandler('results.log')
	formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
	hdlr.setFormatter(formatter)
	logger.addHandler(hdlr) 
	logger.setLevel(logging.WARNING)

	for index in range(1000):
		testNumeric(-10000, -1)
	
	for index in range(1000):
		testRelation(1,10000)

	# Run a series of tests with the expected answer
	testWithKnownAnswer("../../src/expr aaa : 'a\+'", "3\n")
	testWithKnownAnswer("../../src/expr abc : 'a\(.\)c'", "b\n")
	testWithKnownAnswer("../../src/expr index abcdef cz", "3\n")
	testWithKnownAnswer("../../src/expr index \+ index a", "1\n")
	testWithKnownAnswer("../../src/expr abc : '^a[[:alnum:]]'", "2\n")
	testWithKnownAnswer("../../src/expr match abc '^a[[:alnum:]]'", "2\n")
	testWithKnownAnswer("../../src/expr substr 'dalton' 1 5", "dalto\n")
 	testWithKnownAnswer("../../src/expr index california 'i'", "4\n")
	
	# In this case the result is the return code which is 1 when the result is null or 0
	testWithKnownAnswer("../../src/expr index abcdefghijklmnopqrstuvwxy 'z'", "1")
	testWithKnownAnswer("../../src/expr length thisisateststring$%456^", "23\n")	
	testWithKnownAnswer("../../src/expr", "2")

	# Run to ensure correct output to screen
	subprocess.call("../../src/expr --help", shell=True)
	subprocess.call("../../src/expr --version", shell=True)	
	subprocess.call("../../src/expr index index a", shell=True)

if __name__ == '__main__':
	main()
	
	
	

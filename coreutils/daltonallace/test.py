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
	# test("expr " + formula, "expr " + formula)

def testRelation(minValue, maxValue):
	options = ["E '|' E", "E '&' E", "# '<' #", "# '<=' #", "# '==' #", "# '>' #", "# '>=' #", "# '!=' #"]
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
	# test("expr " + formula, "expr " + formula)



def main():

	# Set up logging
	global logger
	hdlr = logging.FileHandler('results.log')
	formatter = logging.Formatter('%(asctime)s %(levelname)s %(message)s')
	hdlr.setFormatter(formatter)
	logger.addHandler(hdlr) 
	logger.setLevel(logging.WARNING)

	for index in range(1):
		testNumeric(-50, -1)
	
	for index in range(1):
		testRelation(1,100)

if __name__ == '__main__':
	main()
	
	
	

# AUTHOR: Jared Potter (u0729256)
#
# DATE: September 29, 2015
#
# Python unittest tests for CoreUtils expr utility

import os
import string
import random
from datetime import datetime
from subprocess import Popen, PIPE

# A list of operators. 
myOperators = ["|", "&", "<", "<=", "=", "!=", ">=", ">", "+", "-", "*", "/", "%"] 

# CITATION:
# Random alpha numeric generator based on Stack Overflow user Ignacio Vazquez-Abrams
# http://stackoverflow.com/questions/2257441/random-string-generation-with-upper-case-letters-and-digits-in-python
def random_alpha_numeric_generator(size=6, strings=string.ascii_lowercase + string.ascii_uppercase + string.digits):
	return ''.join(random.SystemRandom().choice(strings) for _ in range(size))

# Randomly selects an operators from the myOperator list.
def random_operator_generator():
	return ''.join(random.SystemRandom().choice(myOperators) for _ in range(1))

# Checks if a given value is an integer. 
def Is_An_Int(value):
    try: 
        int(value)
        return True
    except ValueError:
        return False

def numberic_fuzz_tests():

	i = 2

	f = open("Fuzz Test Results/numberic_fuzz_tests " + str(datetime.now()) + '.txt' , 'w')

	# Iterates 1000 times. Each iteration has i operends and i - 1 operators. 
	while i < 1000:

		# Lists for holding the operends and operators.
		operends  = []
		operators = []

		# Fills the operends list with random numbers with 1 to 18 digits.
		for x in xrange(1, i + 1):
			operends.append(random_alpha_numeric_generator(random.randint(1, 18), string.digits))

		# Fills the operator list with random operators 
		for x in xrange(1, i):
			operators.append(random_operator_generator())

		# Setting first argument.
		CoreUtilsArgs = ["../coreutils/src/./expr"]

		# Loads the arguments with the operends and operator.
		for x in xrange(0, i - 1):
			CoreUtilsArgs.append(operends[x])
			CoreUtilsArgs.append(operators[x])
		CoreUtilsArgs.append(operends[i - 1]) # Loads last operend. 

		# Performs the CoreUtils shell commend with the given arguments. 
		cu_ps                  = Popen(CoreUtilsArgs, stdout=PIPE, stderr=PIPE)
		(CoreUtilsOut, cu_err) = cu_ps.communicate()
		coreUtil_exit_code     = cu_ps.wait()

		# Re-setting first argument.
		BSDsArgs    = CoreUtilsArgs
		BSDsArgs[0] = "expr" 

		# Performs the BSD expr shell commend with the given arguments. 
		bsd_ps             = Popen(BSDsArgs, stdout=PIPE, stderr=PIPE)
		(BSDsOut, bsd_err) = bsd_ps.communicate()
		bsd_exit_code      = bsd_ps.wait()

		# Compares the output of CoreUtils' expr output with BSD's expr output. If inconsistent, log error to file. 
		# Note: On errors, the printed syntax may differ. 
		if Is_An_Int(CoreUtilsOut) and Is_An_Int(BSDsOut):
			if int(CoreUtilsOut) != int(BSDsOut):
				s = ""
				s = s + "FAIL:\n" + str( " ".join(CoreUtilsArgs) + "\n")
				s = s + "[OUTPUT]\nCoreUtils' Output: " + CoreUtilsOut + "BSD's Output: " + BSDsOut + "\n"
				s = s + "[ERROR CODE]\nCoreUtils: " + str(cu_err)  +  "\nBSD: " + str(bsd_err)
				s = s + "[EXIT CODE]\nCoreUtils: " + str(coreUtil_exit_code)  +  "\nBSD: " + str(bsd_exit_code) + "\n\n"
				f.write(s)
				# f.write("FAIL:\n" + str( " ".join(CoreUtilsArgs)))
				# f.write("[OUTPUT]\nCoreUtils' Output: " + CoreUtilsOut + "BSD's Output: " + BSDsOut + "\n")
				# f.write("[ERROR CODE]\nCoreUtils: " + str(cu_err)  +  "\nBSD: " + str(bsd_err))
				# f.write("[EXIT CODE]\nCoreUtils: " + str(coreUtil_exit_code)  +  "\nBSD: " + str(bsd_exit_code) + "\n")
		else:
			if CoreUtilsOut != BSDsOut:
				s = ""
				s = s + "FAIL:\n" + str( " ".join(CoreUtilsArgs) + "\n")
				s = s + "[OUTPUT]\nCoreUtils' Output: " + CoreUtilsOut + "BSD's Output: " + BSDsOut + "\n"
				s = s + "[ERROR CODE]\nCoreUtils: " + str(cu_err)  +  "\nBSD: " + str(bsd_err)
				s = s + "[EXIT CODE]\nCoreUtils: " + str(coreUtil_exit_code)  +  "\nBSD: " + str(bsd_exit_code) + "\n\n"
				f.write(s)

		i = i + 1
	f.close()

def alphanumberic_fuzz_tests():

	i = 2
	
	f = open("Fuzz Test Results/alphanumberic_fuzz_tests " + str(datetime.now()) + '.txt' , 'w')

	# Iterates 1000 times. Each iteration has i operends and i - 1 operators. 
	while i < 1000:

		# Lists for holding the operends and operators.
		operends  = []
		operators = []

		# Fills the operends list with random numbers with 1 to 100 characters.
		for x in xrange(1, i + 1):
			operends.append(random_alpha_numeric_generator(random.randint(1, 100), string.ascii_lowercase + string.ascii_uppercase + string.digits))

		# Fills the operator list with random operators 
		for x in xrange(1, i):
			operators.append(random_operator_generator())

		# Setting first argument.
		CoreUtilsArgs = ["../coreutils/src/./expr"]

		# Loads the arguments with the operends and operator.
		for x in xrange(0, i - 1):
			CoreUtilsArgs.append(operends[x])
			CoreUtilsArgs.append(operators[x])
		CoreUtilsArgs.append(operends[i - 1]) # Loads last operend. 

		# Performs the CoreUtils shell commend with the given arguments. 
		cu_ps                  = Popen(CoreUtilsArgs, stdout=PIPE, stderr=PIPE)
		(CoreUtilsOut, cu_err) = cu_ps.communicate()
		coreUtil_exit_code     = cu_ps.wait()

		# Re-setting first argument.
		BSDsArgs    = CoreUtilsArgs
		BSDsArgs[0] = "expr" 

		# Performs the BSD expr shell commend with the given arguments. 
		bsd_ps             = Popen(BSDsArgs, stdout=PIPE, stderr=PIPE)
		(BSDsOut, bsd_err) = bsd_ps.communicate()
		bsd_exit_code      = bsd_ps.wait()

		# Compares the output of CoreUtils' expr output with BSD's expr output. If inconsistent, log error to file. 
		# Note: On errors, the printed syntax may differ. 
		if Is_An_Int(CoreUtilsOut) and Is_An_Int(BSDsOut):
			if int(CoreUtilsOut) != int(BSDsOut):
				s = ""
				s = s + "FAIL:\n" + str( " ".join(CoreUtilsArgs) + "\n")
				s = s + "[OUTPUT]\nCoreUtils' Output: " + CoreUtilsOut + "BSD's Output: " + BSDsOut + "\n"
				s = s + "[ERROR CODE]\nCoreUtils: " + str(cu_err)  +  "\nBSD: " + str(bsd_err)
				s = s + "[EXIT CODE]\nCoreUtils: " + str(coreUtil_exit_code)  +  "\nBSD: " + str(bsd_exit_code) + "\n\n"
				f.write(s)

		else:
			if CoreUtilsOut != BSDsOut:
				s = ""
				s = s + "FAIL:\n" + str( " ".join(CoreUtilsArgs) + "\n")
				s = s + "[OUTPUT]\nCoreUtils' Output: " + CoreUtilsOut + "BSD's Output: " + BSDsOut + "\n"
				s = s + "[ERROR CODE]\nCoreUtils: " + str(cu_err)  +  "\nBSD: " + str(bsd_err)
				s = s + "[EXIT CODE]\nCoreUtils: " + str(coreUtil_exit_code)  +  "\nBSD: " + str(bsd_exit_code) + "\n\n"
				f.write(s)

		i = i + 1
	f.close()


###########################################################

#numberic_fuzz_tests();
alphanumberic_fuzz_tests();


import subprocess


def test(command, expected):
	print("Testing: " + command)
	actual = subprocess.check_output(command, shell=True)
	if(actual != expected):
		print("FAIL: Expected " + expected + " Actual: " + actual);
	else:
		print("Test Passed")

def main():
	subprocess.call("make", shell=True)

	# Test each type of triangle combo possible
	test("./triangle -1 0 0 1 1 0", "isosceles right\n")
	test("./triangle -1 0 0 2 1 0", "isosceles acute\n")
	test("./triangle -2 0 2 0 0 1", "isosceles obtuse\n")
	test("./triangle -1 0 0 0 1 1", "scalene obtuse\n")
	test("./triangle -50 0 0 0 0 100", "scalene right\n")
	test("./triangle -1000 0 0 0 -1 1000", "scalene acute\n")
	
	# Test extremes
	test("./triangle -1073741823 0 1073741823 0 0 1073741823", "isosceles right\n")

	# Test invalid input
	test("./triangle 1 1 0 0 1 1073741824", "error\n")
	test("./triangle 1 1 1 1 1 1 1", "error\n")
	test("./triangle 1 1 1 1 1 1d", "error\n")
	test("./triangle notnumber 1 1 1 1 1", "error\n")
	test("./triangle 1.0 1 1 1 1 1", "error\n")

	# Test not a triangle
	test("./triangle 0 1 2 3 4 5", "not a triangle\n")
	test("./triangle 0 0 0 0 0 0", "not a triangle\n")
	
	subprocess.call("make clean", shell=True)

if __name__ == '__main__':
	main()
	
	
	

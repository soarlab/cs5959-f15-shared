import subprocess
import sys

tests_passed = 0
tests_run = 0

def tri_test(command, expected, description):
    global tests_run
    tests_run += 1
    test_output = subprocess.check_output(command, shell=True)
    if(test_output == expected):
        global tests_passed
        tests_passed += 1
        if(len(sys.argv) == 2 and (sys.argv[1] == "-v" or sys.argv[1] == "V")):
            print("PASSED: " + description)
        return True
    else:
        print("FAILED: %s\n\tIncorrect output: %s"
              % (description, test_output))
        return False


# Test - Too many inputs gives error.
tri_test("./triangle 1 2 3 4 5 6 7", "error\n", "Too many inputs gives error.")

# Test - Char input gives error
tri_test("./triangle 1 2 3 a 0 -1", "error\n", "Char input gives error.")

# Test - Mixed char/number input gives error
tri_test("./triangle 1 23b 4 5 6 7", "error\n", "Mixed char/number input gives error.")

# Test - Too few inputs gives error.
tri_test("./triangle 1", "error\n", "Too few inputs gives error.")

# Test - Invalid input gives error.
tri_test("./triangle 1 0 hello 2 3 4", "error\n", "Invalid input gives error.")

# Test - Too large of value gives error.
tri_test("./triangle 1 123456789012345 2 3 4 5", "error\n", "Too large of value gives error.")

# Test - Nearly equilateral, but not quite.
tri_test("./triangle -1073741823 -1073741823 -498325314 1073741823 1073741823 -498325314", "isosceles acute\n", "Nearly equilateral, but actually isosceles, acute.")

# Test - Barely exceed boundaries gives error.
tri_test("./triangle -1073741824 -1073741823 1073741823 -1073741823 1073741822 1073741823", "error\n", "Number below -(2^30 - 1) gives error.")

# Test - Not a triangle: All same point
tri_test("./triangle 6 6 6 6 6 6", "not a triangle\n", "Not a triangle: all points are the same.")

# Test - Not a triangle: Points are colinear
tri_test("./triangle -77 -77 1 1 12354 12354", "not a triangle\n", "Not a triangle: the points are colinear.")

# Test - Not a triangle: Points are far apart, colinear
tri_test("./triangle -1212341 1 0 0 1212341 -1", "not a triangle\n", "Not a triangle: the points are colinear.")

# Test - Valid Scalene, Right
tri_test("./triangle 0 -10000000 1 -10000000 0 10000000", "scalene right\n", "Scalene, right triangle.")

# Test - Valid Scalene, Acute
tri_test("./triangle 1 3 2 1234567 4 3", "scalene acute\n", "Scalene, acute triangle.")

# Test - Valid Scalene, Acute
tri_test("./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741822 1073741823", "scalene acute\n", "Scalene, acute triangle.")

# Test - Valid Scalene, Obtuse
tri_test("./triangle -4 1 -1 1 -2 2", "scalene obtuse\n", "Scalene, obtuse triangle.")

# Test - Valid Isosceles, Right
tri_test("./triangle -1 -1 -2 -1 -1 -2", "isosceles right\n", "Isosceles, right triangle.")

# Test - Valid Isosceles, Right
tri_test("./triangle -1 -1073741823 0 0 1073741823 -1", "isosceles right\n", "Isosceles, right triangle.")

# Test - Valid Isosceles, Acute
tri_test("./triangle 0 929887696 -536870912 0 536870912 0", "isosceles acute\n", "Isosceles, acute triangle.")

# Test - Valid Isosceles, Obtuse
tri_test("./triangle 0 -1 -536870912 0 536870912 0", "isosceles obtuse\n", "Isosceles, obtuse triangle.")

# Test - Valid Isosceles, Obtuse
tri_test("./triangle 0 1 -1073741823 0 1073741823 0", "isosceles obtuse\n", "Isosceles, obtuse triangle.")

if(tests_run == tests_passed):
    print("Success! All " + str(tests_run) + " tests passed.")
else:
    print("Failure! " + str(tests_run - tests_passed) + "/" + str(tests_run) + " tests failed.")

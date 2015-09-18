import subprocess

#1 too few arguments test
result = subprocess.check_output("./triangle 0 0 0 1 1", shell=True);
assert(result == "error\n"), "Program's output: " + result;

#2 too many arguments test
result = subprocess.check_output("./triangle 0 0 0 1 1 0 5", shell=True);
assert(result == "error\n"), "Program's output: " + result;

#3 scalene obtuse test
result = subprocess.check_output("./triangle 0 1 1 0 4 1", shell=True);
assert(result == "scalene obtuse\n"), "Program's output: " + result;

#4 scalene right test
result = subprocess.check_output("./triangle 0 0 0 1 70 0", shell=True);
assert(result == "scalene right\n"), "Program's output: " + result;

#5 scalene acute test
result = subprocess.check_output("./triangle 0 0 2 2 3 0", shell=True);
assert(result == "scalene acute\n"), "Program's output: " + result;


#6 isoceles right test
result = subprocess.check_output("./triangle 0 0 0 1 1 0",shell=True);
assert(result == "isosceles right\n"), "Program's output: " + result;

#7 isosceles acute test
result = subprocess.check_output("./triangle -1 2 4 2 3 -1", shell=True);
assert(result == "isosceles acute\n"), "Program's output: " + result;

#8 isosceles obtuse test 
result = subprocess.check_output("./triangle 0 0 -3 1 3 1",shell=True);
assert(result == "isosceles obtuse\n"), "Program's output: " + result;

#9 colinear test
result = subprocess.check_output("./triangle 0 0 -1 0 1 0", shell=True);
assert(result == "not a triangle\n"), "Program's output: " + result;

#10 large input test, this will pass on 64 bit.  Will fail on 32 bit
result = subprocess.check_output("./triangle 0 0 1073741823 0 0 -1073741823", shell=True);
assert(result == "isosceles right\n"), "Program's output: " + result;

#11 vertical line
result = subprocess.check_output("./triangle 0 1073741823 0 0 0 -1073741823", shell=True);
assert(result == "not a triangle\n"), "Program's output: " + result;

#invalid input
result = subprocess.check_output("./triangle 0 a b c d e", shell=True);
assert(result == "error\n"), "Program's output: " + result;

#large scalene right
result = subprocess.check_output("./triangle 0 -1073741823 1 -1073741823 0 1073741823", shell=True);
assert(result == "scalene right\n"), "Program's output: " + result;

#too large of a number
result = subprocess.check_output("./triangle 1 2 3 4 0 1073741824", shell=True);
assert(result == "error\n"), "Program's output: " + result;

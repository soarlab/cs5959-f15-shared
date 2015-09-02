import subprocess

#Not enough inputs
result = subprocess.check_output("./triangle 0 0 0 1 1", shell = True);
assert(result == "error\n");

#Input too large
result = subprocess.check_output("./triangle 1073741824 0 0 1 1 0", shell = True);
assert(result == "error\n");

#Input too small
result = subprocess.check_output("./triangle -1073741824 0 0 1 1 0", shell = True);
assert(result == "error\n");

#Duplicate Point
result = subprocess.check_output("./triangle 0 0 0 0 1 0", shell = True);
assert(result == "not a triangle\n");

#Straight Line
result = subprocess.check_output("./triangle 0 1 0 2 0 3", shell = True);
assert(result == "not a triangle\n");

#Inclined line
result = subprocess.check_output("./triangle 0 0 1 1 2 2", shell = True);
assert(result == "not a triangle\n");

#Scalene right triangle
result = subprocess.check_output("./triangle 0 0 0 1 2 1", shell = True);
assert(result == "scalene right\n");

#Scalene obtuse triangle
result = subprocess.check_output("./triangle 0 0 2 0 10 10", shell = True);
assert(result == "scalene obtuse\n");

#Scalene acute triangle
result = subprocess.check_output("./triangle 0 0 3 0 2 2", shell = True);
assert(result == "scalene acute\n");

#Isosceles obtuse triangle
result = subprocess.check_output("./triangle -2 0 2 0 0 1", shell = True);
assert(result == "isosceles obtuse\n");

#Isosceles right triangle
result = subprocess.check_output("./triangle -10 0 0 10 10 0", shell = True);
assert(result == "isosceles right\n");

#Isosceles acute triangle
result = subprocess.check_output("./triangle 0 0 2 1 0 2", shell = True);
assert(result == "isosceles acute\n");

#finished
print 'All tests passed!';
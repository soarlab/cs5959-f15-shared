import subprocess

#Letters in input
output = subprocess.check_output("./triangle 0al 0 0 0 0", shell = True);
assert(output == "error\n");

#Inputs out of range (over)
output = subprocess.check_output("./triangle 1073741832 0 0 1 1 0", shell = True);
assert(output == "error\n");

#Input out of range (under)
output = subprocess.check_output("./triangle -1073741829 0 0 1 1 0", shell = True);
assert(output == "error\n");

#Incorrect amount of inputs
output = subprocess.check_output("./triangle 0 0 0 0 0 0 0", shell = True);
assert(output == "error\n");

#Duplicates
output = subprocess.check_output("./triangle 0 0 0 0 1 0", shell = True);
assert(output == "not a triangle\n");

#Not a triangle line with a slope
output = subprocess.check_output("./triangle 0 0 1 1 2 2", shell = True);
assert(output == "not a triangle\n");

#Max size right triangle
output = subprocess.check_output("./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741823 1073741823", shell = True);
assert(output == "isosceles right\n");

#~Max size obtuse
output = subprocess.check_output("./triangle -1073741823 -1073741823 1073741822 -1073741823 1073741823 1073741823", shell = True);
assert(output == "isosceles obtuse\n");

#~Max size acute
output = subprocess.check_output("./triangle -1073741823 -1073741823 1073741823 -1073741823 1073741822 1073741823", shell = True);
assert(output == "isosceles obtuse\n");

print 'All tests passed!';

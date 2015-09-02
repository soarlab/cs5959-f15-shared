# triangle classifier test script
# note: equilateral not possible
# test cases with smallest numbers
# test cases with largest numbers
# right iscosceles
./triangle 0 0 1 1 0 1
./triangle -1073741823 -1073741823 1073741823 1073741823 -1073741823 1073741823
# obtuse isosceles
./triangle 0 0 2 1 4 0
./triangle -1073741823 -1073741823 0 -536870912 1073741823 -1073741823
# acute isosceles
./triangle 0 0 1 1 2 -1
./triangle -1073741823 0 0 1073741823 1073741823 -1073741823
# right scalene
./triangle 0 0 0 1 2 0
./triangle -1073741823 -1073741823 -1073741823 -536870912 1073741823 -1073741823
# obtuse scalene
./triangle 0 0 1 1 2 1
./triangle -1073741823 -1073741823 -536870912 -536870912 1073741823 -536870912
# acute scalene
./triangle 0 0 1 2 3 0
./triangle -1073741823 0 0 1073741823 1073741823 -536870912
# not triangles
./triangle 0 0 1 1 2 2
./triangle -1073741823 -1073741823 1073741823 1073741823 0 0
# too many arguments
./triangle 0 0 1 1 2 2 3
# too few
./triangle 0 0 1 1 2
# too big a number
./triangle 0 0 1 1 2 1073741824
./triangle 0 0 1 1 2 10737418240000000
# malformed input
./triangle 0 a 1 1 2 3
./triangle 0 10737f1800 0 1 1 1
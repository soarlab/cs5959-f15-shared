#!/usr/bin/env python3

#+------------------------------------------------------------------------------+
#| Lasciate ogne speranza, voi ch'intrate                                       |
#+------------------------------------------------------------------------------+


import random as R
import string as S
import subprocess as SP
import sys as SYS
import fractions as F
import math as M

"""
├── Error
│   ├── NotNumbers
│   ├── TooLarge
|   ├── WrongCount
│   └── StartsWithNumbers
├── NotATriangle
│   ├── CoincidingVertex
│   └── Collinear
└── Triangle
    ├── Equilateral
    │   └── Acute
    ├── Isosceles
    │   ├── Acute
    │   ├── Obtuse
    │   └── Right
    └── Scalene
        ├── Acute
        ├── Obtuse
        └── Right
"""

#Epsilon
EPS = 0.0001

# Bounds for valid output
MAX = 2**30 - 1
MIN = -MAX

# generate a numberin bounds
def in_range():
    return R.randint(MIN, MAX)

# check if a number is within bounds
def is_in_range(num):
    return (num >= MIN) and (num <= MAX)

# create valid argument list
def gen_valid_input():
    return [in_range() for _ in range(6)]

# create a valid point
def gen_valid_point():
    return (in_range(), in_range())

# generate a random alphanum string
def my_rand_string():
    ret = ''.join(R.choice(S.ascii_letters + S.digits) for _ in range(R.randint(1, 20)))
    return ret

# calculate the distance between points
def dist(x1,y1,x2,y2):
    return ((x1-x2)**2 + (y1-y2)**2)**.5

# calculate the dot product of two vectors
def dot(a,b,c,d):
    return a*c+b*d

# calculate the angle between 3 points, the middle point being the vertex
def angle(x1, y1, x2, y2, x3, y3):
    return M.acos((dist(x1,y1,x2,y2)**2+dist(x1,y1,x3,y3)**2-dist(x2,y2,x3,y3)**2)/
                  (2*dist(x1, y1, x2, y2) * dist(x1, y1, x3, y3)))



#+------------------------------------------------------------------------------+
#| Generate input which must lead to an error return value                      |
#+------------------------------------------------------------------------------+


# Create arguments which contain one non-number
def gen_Error_NotNumbers():
    args = gen_valid_input()
    non_num = my_rand_string()
    # the string may actually be a number, make sure it is not
    while non_num.isnumeric():
        non_num = my_rand_string()
    args[R.randint(0,5)] = non_num
    return " ".join([str(a) for a in args])

# Create arguments which contain one number beyond accepted bound
def gen_Error_TooLarge():
    args = gen_valid_input()
    too_large = in_range() + in_range()
    while is_in_range(too_large):
        too_large += in_range()
    args[R.randint(0,5)] = too_large
    return " ".join([str(a) for a in args])

# Create arguments which have the wrong cardinality
def gen_Error_WrongCount():
    count = R.randint(0,100)
    while count == 6:
        count = R.randint(0,100)
    args = [in_range() for _ in range(count)]
    return " ".join([str(a) for a in args])

# Create arguments which contain one non-number that starts with a valid number
def gen_Error_StartsWithNumbers():
    args = gen_valid_input()
    ending = my_rand_string()
    while ending[0].isnumeric():
        ending = my_rand_string()
    args[R.randint(0,5)] = str(in_range()) + ending
    return " ".join([str(a) for a in args])





#+------------------------------------------------------------------------------+
#| Generate input which is valid, but not a triangle                            |
#+------------------------------------------------------------------------------+


# Create arguments which represent a two points coinciding
def gen_NotATriangle_CoincidingVertex():
    (x0, y0) = gen_valid_point()
    (x1, y1) = gen_valid_point()
    while (x0==x1) and (y0==y1):
        (x1, y1) = gen_valid_point()
    points = [[x0,y0],[x0,y0],[x1,y1]]
    R.shuffle(points)
    args = sum(points, [])
    return " ".join([str(a) for a in args])

# Create arguments which represent a triangle which is a line
def gen_NotATriangle_Collinear():
    while True:
        (x0, y0) = gen_valid_point()
        (x1, y1) = gen_valid_point()
        while (x0==x1) and (y0==y1):
            (x1, y1) = gen_valid_point()
        slope = F.Fraction(y0-y1, x0-x1)
        iters = 1000
        while iters != 0:
            iters -= 1
            scale = R.randint(-100,100)
            (x2, y2) = (x0+scale*slope.denominator,
                        y0+scale*slope.numerator)
            if is_in_range(x2) and is_in_range(y2):
                break
        if iters == 0:
            continue
        args = [x0, y0, x1, y1, x2, y2]
        return " ".join([str(a) for a in args])




#+------------------------------------------------------------------------------+
#| Generate input which is an isosceles triangle                                |
#+------------------------------------------------------------------------------+

# Create arguments which represent a triangle which is isosceles
def gen_Triangle_Isosceles(angle_pred):
    while True:
        (x1, y1) = gen_valid_point()
        (x2, y2) = gen_valid_point()
        while (y1-y2)%2 != 0 or (x1-x2)%2 != 0:
            (x1, y1) = gen_valid_point()
            (x2, y2) = gen_valid_point()
        # take the midpoint of the two points and move orthogonally to them to
        #     make an isosceles triangle
        midx = min(x1,x2) + abs((x1-x2)//2)
        midy = min(y1,y2) + abs((y1-y2)//2)
        slope = F.Fraction(y1-y2, x1-x2)
        new_slope = - (slope**-1) # orthogonal slope
        scale = R.randint(1,100) * -1**R.randint(1,2) # non-zero scaling
        (x3, y3) = (midx+scale*new_slope.denominator,
                    midy+scale*new_slope.numerator)
        iters = 1000
        while (angle_pred(midx, midy, x1, y1, x2, y2, x3, y3) or
               (not is_in_range(x3)) or
               (not is_in_range(y3))):
            iters -= 1
            if iters == 0:
                break
            scale = R.randint(1,100) * -1**R.randint(1,2) # non-zero scaling
            (x3, y3) = (midx+scale*new_slope.denominator,
                        midy+scale*new_slope.numerator)
        if iters == 0:
            continue
        args = [x1, y1, x2, y2, x3, y3] 
        return " ".join([str(a) for a in args])

# Create arguments which represent a triangle which is isosceles acute
def gen_Triangle_Isosceles_Acute():
    acute_pred = lambda midx, midy, x1, y1, x2, y2, x3, y3 : (dist(midx,midy,x3,y3) / dist(midx,midy,x1,y1) < 1+EPS)
    return gen_Triangle_Isosceles(acute_pred)

# Create arguments which represent a triangle which is isosceles obtuse
def gen_Triangle_Isosceles_Obtuse():
    obtuse_pred = lambda midx, midy, x1, y1, x2, y2, x3, y3 : (dist(midx,midy,x3,y3) / dist(midx,midy,x1,y1) > 1-EPS)
    return gen_Triangle_Isosceles(obtuse_pred)

# Create arguments which represent a triangle which is isosceles right
def gen_Triangle_Isosceles_Right():
    while True:
        (x1, y1) = gen_valid_point()
        (x2, y2) = gen_valid_point()
        while (y1-y2)%2 != 0 or (x1-x2)%2 != 0:
            (x1, y1) = gen_valid_point()
            (x2, y2) = gen_valid_point()
        midx = min(x1,x2) + abs((x1-x2)//2)
        midy = min(y1,y2) + abs((y1-y2)//2)
        slope = F.Fraction(y1-y2, x1-x2)
        new_slope = - (slope**-1)
        scale = R.randint(1,100)
        direction = -1**R.randint(1,2)
        (x3, y3) = (x1+scale*direction*new_slope.denominator,
                    y1+scale*direction*new_slope.numerator)
        direction = -1**R.randint(1,2)
        (x2, y2) = (x1+scale*direction*slope.denominator,
                    y1+scale*direction*slope.numerator)
        iters = 100
        while ((not is_in_range(x2)) or
               (not is_in_range(y2)) or
               (not is_in_range(x3)) or
               (not is_in_range(y3))):
            iters -= 1
            if iters == 0:
                break
            scale = R.randint(1,100)
            direction = -1**R.randint(1,2)
            (x3, y3) = (x1+scale*direction*new_slope.denominator,
                        y1+scale*direction*new_slope.numerator)
            direction = -1**R.randint(1,2)
            (x2, y2) = (x1+scale*direction*slope.denominator,
                        y1+scale*direction*slope.numerator)

        if iters == 0:
            continue
    
        args = [x1, y1, x2, y2, x3, y3] 
        return " ".join([str(a) for a in args])
    




#+------------------------------------------------------------------------------+
#| Generate input which is an scalene triangle                                  |
#+------------------------------------------------------------------------------+


# Create arguments which represent a triangle which is scalene acute
def gen_Triangle_Scalene_Acute():
    while True:
        (x1, y1) = gen_valid_point()
        (x2, y2) = gen_valid_point()
        (x3, y3) = gen_valid_point()
        d1 = dist(x1,y1,x2,y2)
        d2 = dist(x2,y2,x3,y3)
        d3 = dist(x3,y3,x1,y1)
        iters = 1000
        try:
            while ((abs(d1-d2) < EPS) or
                   (abs(d2-d3) < EPS) or
                   (abs(d3-d1) < EPS) or
                   (angle(x1,y1,x2,y2,x3,y3) >= M.pi/2) or
                   (angle(x2,y2,x3,y3,x1,y1) >= M.pi/2) or
                   (angle(x3,y3,x1,y1,x2,y2) >= M.pi/2)):
                iters -= 1
                if iters == 0:
                    break
                (x2, y2) = gen_valid_point()
                (x3, y3) = gen_valid_point()
                d1 = dist(x1,y1,x2,y2)
                d2 = dist(x2,y2,x3,y3)
                d3 = dist(x3,y3,x1,y1)
        except:
            continue
        if iters == 0:
            continue
        args = [x1, y1, x2, y2, x3, y3] 
        return " ".join([str(a) for a in args])

# Create arguments which represent a triangle which is scalene obtuse
def gen_Triangle_Scalene_Obtuse():
    while True:
        (x1, y1) = gen_valid_point()
        (x2, y2) = gen_valid_point()
        (x3, y3) = gen_valid_point()
        d1 = dist(x1,y1,x2,y2)
        d2 = dist(x2,y2,x3,y3)
        d3 = dist(x3,y3,x1,y1)
        iters = 1000
        try:
            while ((abs(d1-d2) < EPS) or
                   (abs(d2-d3) < EPS) or
                   (abs(d3-d1) < EPS) or
                   ((angle(x1,y1,x2,y2,x3,y3) <= M.pi/2) and
                    (angle(x2,y2,x3,y3,x1,y1) <= M.pi/2) and
                    (angle(x3,y3,x1,y1,x2,y2) <= M.pi/2))):
                iters -= 1
                if iters == 0:
                    break
                (x3, y3) = gen_valid_point()
                d1 = dist(x1,y1,x2,y2)
                d2 = dist(x2,y2,x3,y3)
                d3 = dist(x3,y3,x1,y1)
        except:
            continue
        if iters == 0:
            continue
        args = [x1, y1, x2, y2, x3, y3] 
        return " ".join([str(a) for a in args])

# Create arguments which represent a triangle which is scaline right
def gen_Triangle_Scalene_Right():
    while True:
        (x1, y1) = gen_valid_point()
        (x2, y2) = gen_valid_point()
        while (y1-y2)%2 != 0 or (x1-x2)%2 != 0:
            (x1, y1) = gen_valid_point()
            (x2, y2) = gen_valid_point()
        midx = min(x1,x2) + abs((x1-x2)//2)
        midy = min(y1,y2) + abs((y1-y2)//2)
        slope = F.Fraction(y1-y2, x1-x2)
        new_slope = - (slope**-1)
        scale1 = R.randint(1,100)
        scale2 = R.randint(1,100)
        while scale1 == scale2:
            scale2 = R.randint(1,100)
        direction = -1**R.randint(1,2)
        (x3, y3) = (x1+scale1*direction*new_slope.denominator,
                    y1+scale1*direction*new_slope.numerator)
        direction = -1**R.randint(1,2)
        (x2, y2) = (x1+scale2*direction*slope.denominator,
                    y1+scale2*direction*slope.numerator)
        iters = 100
        while ((not is_in_range(x2)) or
               (not is_in_range(y2)) or
               (not is_in_range(x3)) or
               (not is_in_range(y3))):
            iters -= 1
            if iters == 0:
                break
            scale1 = R.randint(1,100)
            scale2 = R.randint(1,100)
            while scale1 == scale2:
                scale2 = R.randint(1,100)
            scale = R.randint(1,100)
            direction = -1**R.randint(1,2)
            (x3, y3) = (x1+scale1*direction*new_slope.denominator,
                        y1+scale1*direction*new_slope.numerator)
            direction = -1**R.randint(1,2)
            (x2, y2) = (x1+scale2*direction*slope.denominator,
                        y1+scale2*direction*slope.numerator)
        if iters == 0:
            continue
        args = [x1, y1, x2, y2, x3, y3] 
        return " ".join([str(a) for a in args])





#+------------------------------------------------------------------------------+
#| Test wrapping code                                                           |
#+------------------------------------------------------------------------------+


# Runs the given command with the given arg string and returns the output
def run(cmd, args):
    command = cmd+" "+args
    with SP.Popen(command,
                  stdout=SP.PIPE, stderr=SP.STDOUT,shell=True) as proc:
        output = proc.stdout.read().decode("utf-8")
        proc.wait()
    
        return output

# Use the given func to generate arguments for the triangle executable and
#     comapre that rturn to the given expected value
def test(func, expected):
    input = func()
    actual = run(EXE, input)

    if actual == expected:
        msg = "\x1b[32mpass\x1b[0m"
        #msg = "pass"
    else:
        msg = "\x1b[31mFAIL: Actual: {}\x1b[0m".format(actual)
        #msg = "FAIL: Actual: {}".format(actual)
    if len(input.split()) == 6:
        input = input.split()
        input = "({}, {}) ({}, {}) ({}, {})".format(input[0],input[1],input[2],input[3],input[4],input[5])
    print("Input: {} \nExpected: {}, {}".format(input, expected.replace("\n",""), msg))

# Test one of each type of input classes defined
def testall():
    expected = "error\n"
    test(gen_Error_NotNumbers, expected)
    test(gen_Error_TooLarge, expected)
    test(gen_Error_WrongCount, expected)
    test(gen_Error_StartsWithNumbers, expected)

    expected = "not a triangle\n"
    test(gen_NotATriangle_CoincidingVertex, expected)
    test(gen_NotATriangle_Collinear, expected)

    test(gen_Triangle_Isosceles_Acute, "isosceles acute\n")
    test(gen_Triangle_Isosceles_Obtuse, "isosceles obtuse\n")
    test(gen_Triangle_Isosceles_Right, "isosceles right\n")
    
    test(gen_Triangle_Scalene_Acute, "scalene acute\n")
    test(gen_Triangle_Scalene_Obtuse, "scalene obtuse\n")
    test(gen_Triangle_Scalene_Right, "scalene right\n")

    
    
if __name__ == "__main__":
    if len(SYS.argv) != 3:
        print("Usage: {} <executable> <number of repetitions of each test>".format(SYS.argv[0]))
        SYS.exit(-1)
    try:
        EXE = SYS.argv[1]
        tests = int(SYS.argv[2])
    except:
        print("Usage: {} <executable> <number of repetitions of each test>".format(SYS.argv[0]))
        SYS.exit(-1)

    R.seed(42)
    for _ in range(tests):
        testall()

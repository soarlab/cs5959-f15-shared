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
│   └── WrongCount
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
MAX = 2**30 - 1
MIN = -MAX

def in_range():
    return R.randint(MIN, MAX)

def my_rand_string():
    ret = ''.join(R.choice(S.ascii_letters + S.digits) for _ in range(R.randint(0, 20)))
    return ret





def gen_Error_NotNumbers():
    while True:
        args = [my_rand_string() for _ in range(6)]
        flag = 0
        for sub in args:
            flag += int(not sub.isnumeric())
            if flag == 0:
                continue
        return " ".join([str(a) for a in args])

def gen_Error_TooLarge():
    args = [0 for _ in range(6)]

    while (max(args) < MAX) and (min(args) > MIN):
        for i in range(6):
            args[i] += in_range()
            
    return " ".join([str(a) for a in args])

def gen_Error_WrongCount():
    while True:
        count = R.randint(0,100)
        if count == 6:
            continue

        args = [in_range() for _ in range(count)]
        return " ".join([str(a) for a in args])




def gen_NotATriangle_CoincidingVertex():
    while True:
        same = R.randint(2,3)
        x = in_range()
        y = in_range()
        xo = in_range()
        yo = in_range()
        if x==xo and y==yo:
            continue
        if same == 3:
            args = [x,y,x,y,x,y]
        else:
            args = [x,y,x,y,xo,yo]
        return " ".join([str(a) for a in args])

def gen_NotATriangle_Collinear():
    while True:
        x = in_range()
        y = in_range()
        dx = in_range()
        dy = in_range()

        cx = -1
        px = x
        while px < 2**30-1 and px > -2**30-1:
            px += dx
            cx += 1

        cy = -1
        py = y
        while py < 2**30-1 and py > -2**30-1:
            py += dy
            cy += 1 

        split = min(cx, cy)

        if split < 2:
            continue

        steps = R.randint(1, split)
        args = [x,y, x+steps*dx,y+steps*dy, x+(split-steps)*dx,y+(split-steps)*dy]
        return " ".join([str(a) for a in args])

def dist(x1,y1,x2,y2):
    return ((x1-x2)**2 + (y1-y2)**2)**.5

def dot(a,b,c,d):
    return a*c+b*d


def gen_Triangle_Isosceles_Acute():
    while True:
        x1 = in_range()
        y1 = in_range()
        x2 = in_range()
        y2 = in_range()

        if (y1-y2)%2 != 0 or (x1-x2)%2 != 0:
            continue

        mx = min(x1,x2) + abs((x1-x2)//2)
        my = min(y1,y2) + abs((y1-y2)//2)
        
        slope = F.Fraction(y1-y2, x1-x2)

        new_slope = - (slope**-1)

        x3 = mx
        y3 = my
        while (dist(mx,my,x3,y3) / dist(mx,my,x1,y1)) < 1.0001 or R.randint(1,3) == 1:
            tx = x3 + new_slope.denominator
            ty = y3 + new_slope.numerator
            if tx > MAX or tx < MIN or ty > MAX or ty < MIN:
                break
            x3 = tx
            y3 = ty

        if (x3 == mx and y3 == my):
            continue
        if ((dist(mx,my,x3,y3) / dist(mx,my,x1,y1)) < 1.0001):
            continue

        args = [x1,y1,x2,y2,x3,y3] 
        return " ".join([str(a) for a in args])

def gen_Triangle_Isosceles_Obtuse():
    while True:
        x1 = in_range()
        y1 = in_range()
        x2 = in_range()
        y2 = in_range()

        if (y1-y2)%2 != 0 or (x1-x2)%2 != 0:
            continue

        mx = min(x1,x2) + abs((x1-x2)//2)
        my = min(y1,y2) + abs((y1-y2)//2)
        
        slope = F.Fraction(y1-y2, x1-x2)

        new_slope = - (slope**-1)

        x3 = mx
        y3 = my
        while R.randint(1,3) == 1:
            tx = x3 + new_slope.denominator
            ty = y3 + new_slope.numerator
            if tx > MAX or tx < MIN or ty > MAX or ty < MIN:
                break
            x3 = tx
            y3 = ty

        if (x3 == mx and y3 == my):
            continue
        if ((dist(mx,my,x3,y3) / dist(mx,my,x1,y1)) > 1 - 0.001):
            continue

        args = [x1,y1,x2,y2,x3,y3] 
        return " ".join([str(a) for a in args])


def gen_Triangle_Isosceles_Right():
    while True:
        x1 = in_range()
        y1 = in_range()
        x2 = in_range()
        y2 = in_range()

        slope = F.Fraction(y1-y2, x1-x2)

        new_slope = - (slope**-1)

        one_or_two = R.randint(1,2)

        x3 = x1
        y3 = y1
            
        while abs(dist(x1,y1,x2,y2) - dist(x1,y1,x3,y3)) > .00001 :
            x3 += new_slope.denominator
            y3 += new_slope.numerator

        if x3 > MAX or x3 < MIN or y3 > MAX or y3 < MIN:
            continue

        args = [x1,y1,x2,y2,x3,y3] 
        return " ".join([str(a) for a in args])

def gen_Triangle_Scalene_Acute():
    while True:
        x1 = in_range()
        y1 = in_range()
        x2 = in_range()
        y2 = in_range()

        slope = F.Fraction(y1-y2, x1-x2)

        new_slope = - (slope**-1)

        one_or_two = R.randint(1,2)

        max_steps = min((x1-x2)//slope.denominator, (y1-y2)//slope.numerator)
        if max_steps < 3:
            continue
        steps = R.randint(1,max_steps)
        if steps == max_steps//2:
            continue
        x3 = min(x1,x2) + steps*abs(slope.denominator)
        y3 = min(y1,y2) + steps*abs(slope.numerator)

        try:
            while R.randint(1,3) == 1 or M.acos(dot(x3-x1,y3-y1,x3-x2,y3-y2)/
                                                (dist(x3,y3,x1,y1) * dist(x3,y3,x2,y2))) >= M.pi/2:
                x3 += new_slope.denominator
                y3 += new_slope.numerator

        except:
            continue
        if x3 > MAX or x3 < MIN or y3 > MAX or y3 < MIN:
            continue

        args = [x1,y1,x2,y2,x3,y3] 
        return " ".join([str(a) for a in args])

def gen_Triangle_Scalene_Obtuse():
    while True:
        x1 = in_range()
        y1 = in_range()
        x2 = in_range()
        y2 = in_range()

        slope = F.Fraction(y1-y2, x1-x2)

        new_slope = - (slope**-1)

        one_or_two = R.randint(1,2)

        max_steps = min((x1-x2)//slope.denominator, (y1-y2)//slope.numerator)
        if max_steps < 3:
            continue
        steps = R.randint(1,max_steps)
        if steps == max_steps//2:
            continue
        x3 = min(x1,x2) + steps*abs(slope.denominator) + new_slope.denominator 
        y3 = min(y1,y2) + steps*abs(slope.numerator) + new_slope.numerator

        try:
            while R.randint(1,3) == 1 and M.acos(dot(x3-x1,y3-y1,x3-x2,y3-y2)/
                                                (dist(x3,y3,x1,y1) * dist(x3,y3,x2,y2))) <= M.pi/2:
                x3 += new_slope.denominator
                y3 += new_slope.numerator

            if M.acos(dot(x3-x1,y3-y1,x3-x2,y3-y2)/(dist(x3,y3,x1,y1) * dist(x3,y3,x2,y2))) <= M.pi/2:
                continue
            
        except:
            continue
        
        if x3 > MAX or x3 < MIN or y3 > MAX or y3 < MIN:
            continue

        args = [x1,y1,x2,y2,x3,y3] 
        return " ".join([str(a) for a in args])


def gen_Triangle_Scalene_Right():
    while True:
        x1 = in_range()
        y1 = in_range()
        x2 = in_range()
        y2 = in_range()

        slope = F.Fraction(y1-y2, x1-x2)

        new_slope = - (slope**-1)

        one_or_two = R.randint(1,2)

        x3 = x1
        y3 = y1
            
        while R.randint(1,3) == 1:
            tx = x3 + new_slope.denominator
            ty = y3 + new_slope.numerator
            if tx > MAX or tx < MIN or ty > MAX or ty < MIN:
                break
            x3 = tx
            y3 = ty
            
        if (x3 == x1 and y3 == y1) or (x3 == x2 and y3 == y2):
            continue
        if abs(dist(x1,y1,x2,y2) - dist(x1,y1,x3,y3)) < .00001:
            continue
        args = [x1,y1,x2,y2,x3,y3] 
        return " ".join([str(a) for a in args])
    pass


def run(cmd, args):
    command = cmd+" "+args
    with SP.Popen(command,
                  stdout=SP.PIPE, stderr=SP.STDOUT,shell=True) as proc:
        output = proc.stdout.read().decode("utf-8")
        proc.wait()
    
        return output
    
def test(func, expected):
    input = func()
    actual = run(EXE, input)

    if actual == expected:
        msg = "\x1b[32mpass\x1b[0m"
    else:
        msg = "\x1b[31mFAIL: Actual: {}\x1b[0m".format(actual)
    if len(input.split()) == 6:
        input = input.split()
        input = "({}, {}) ({}, {}) ({}, {})".format(input[0],input[1],input[2],input[3],input[4],input[5])
    print("Input: {} \nExpected: {}, {}".format(input, expected.replace("\n",""), msg))

def testall():
    test(gen_Error_NotNumbers, "error\n")
    test(gen_Error_TooLarge, "error\n")
    test(gen_Error_WrongCount, "error\n")

    test(gen_NotATriangle_CoincidingVertex, "not a triangle\n")
    test(gen_NotATriangle_Collinear, "not a triangle\n")

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

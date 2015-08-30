Triangle Classifier
===================
A project that provides a classifier for a triangle according to the following criterion:

1. The classifier takes six command line arguments. The first two are respectively the x and y coordinates of the first vertex of the triangle, the second two are respectively the x and y coordinates of the second vertex, etc. 
2. Each coordinate is a decimal integer in the range –(2^30 – 1) to (2^30 – 1).
3. The output should match this regular expression:

    `(((scalene|isosceles|equilateral) (acute|obtuse|right))|not a triangle|error)\n`
    * The triangle analyzer should output “error” if the input format does not match the one specified above. Otherwise, it should output either "not a triangle" or the result of the analysis of the triangle. 
# Dependencies
* GCC/Clang
* make
* Python 2.7.x

# Building & Running
To build the project simply invoke the command
```
make
```
and run the binary that is output from the GCC/Clang compiler:
```
./a.out x1 y1 x2 y2 x3 y3
```
with `(x1, y1), (x2, y2), (x3, y3)` being integers with bounds `-(2^30 -1)` <= `i` <= `(2^30 -1)`. 

# Testing
To run the tests that accompany this project simply invoke the Python test script that comes along with the source:
```
python tester.py
```


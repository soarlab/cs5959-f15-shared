Triangle Classifier Assignment
=====================================


# To Run

Commands for compiling and executing this program are provided in the
accompanied Makefile. 

```
make				# cleans and compiles triangle.c
make triangle	    # compiles triangle.c
make test			# cleans, compiles triangle.c and runs tests
make testv			# same as test but with unittest verbose on
make clean			# removes executable
```

# Test Cases

Test cases were written in Python using Python's unittest. 
To execute:

```
python triangle_test.py
python triangle_test.py -v
```

or run:

```
make test
make testv
```

# Notes

I basically redid the entire project once I learned long long data types were enough. I used math cited from Wolfram to check for colinearity. I also implemented a basic array to store the sorted lengths of each side of the triangle. These improvements cut my code base in half! I would like to thank everyone in the class for their participation during lectures; you all helped me write this better.

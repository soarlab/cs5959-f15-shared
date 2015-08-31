# All Target
all: Triangle

# Tool invocations
Triangle: Triangle.o
	gcc -o "Triangle" Triangle.o -lm

Triangle.o: Triangle.c
	gcc -c Triangle.c

# Other Targets
clean:
	rm -rf Triangle
	rm -rf Triangle.o


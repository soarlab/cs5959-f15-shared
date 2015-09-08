#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>

// Question: Without adding the -lm flag to my makefile my program could not find the sqrt function
// even though i've included the math library, according to stack overflow there is a difference 
// between linking to the definitions of functions as apposed to just the definitions of those functions
// in the header file..

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

struct point 
{
	long x, y;
};


int64_t getDistanceSquared(struct point a, struct point b)
{
  // Don't take the square root so as to not lose precision
	int64_t val = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
	return val;
}

char* getType(int64_t a, int64_t b, int64_t c)
{
	if(a == b && a == c)
	{
		return "Equilateral";
	}
	else if(a != b && a != c && c != b)
	{
		return "Scalene";
	}
	else
	{
		return "Isosceles";
	}
}

char* getAngle(int64_t longest, int64_t other, int64_t another)
{
	if((other + another) > longest)
	{
		return "Acute";
	}
	else if((other + another) == longest)
	{
		return "Right";
	}
	else
	{
		return "Obtuse";
	}

}

char* getAngleType(int64_t a, int64_t b, int64_t c)
{
	// Find longest side
  int64_t max = MAX(a, b);
	max = MAX(max, c);

	if(max == a)
	{
		return getAngle(a, b, c);
	}
	else if(max == b)
	{
		return getAngle(b, a, c);
	}
	else
	{
		return getAngle(c, b, a);
	}
}

void isTriangle(struct point a, struct point b, struct point c)
{
	// Check the slopes against each other
	int64_t val1 = (b.y - a.y)*(c.x - b.x);
	int64_t val2 = (b.x - a.x)*(c.y - b.y);

	if(val1 == val2)
	{
		printf("not a triangle \n");
		exit(EXIT_FAILURE);
	}
	
}

int main (int argc, char** argv)
{
  // Ensure the valid number of arguments
	if(argc != 7)
	{
		printf("error \n");
		exit(EXIT_FAILURE);
	}

  int counter;
	long values[6];
	char *ptr;
	errno = 0;

	for(counter = 1; counter < argc; counter++)
	{
		long result = strtol(argv[counter], &ptr, 10);
	  
		if((errno == EINVAL && (result == LONG_MAX || result == LONG_MIN))
				|| (errno != 0 && result == 0)) {
		
			printf("error \n");
			exit(EXIT_FAILURE);

		}

		if(ptr == argv[counter])
		{
			printf("error \n");
			exit(EXIT_FAILURE);
		}
		
		values[counter - 1] = result;
	}

	struct point a;
	struct point b;
	struct point c;

	a.x = values[0];
	a.y = values[1];
	b.x = values[2];
	b.y = values[3];
	c.x = values[4];
	c.y = values[5];

	// Determine if 'Not A Triangle'
	isTriangle(a, b, c);

  // Determine side lengths
	int64_t lengthA = getDistanceSquared(a, b);
	int64_t lengthB = getDistanceSquared(b, c);
	int64_t lengthC = getDistanceSquared(c, a);

	char* triangleType = getType(lengthA, lengthB, lengthC);
	char* angleType;

	if(strcmp(triangleType,"Equilateral") == 0)
	{
		angleType = "Acute";	
	}
  else
	{
		angleType = getAngleType(lengthA, lengthB, lengthC);
	}
	printf("%s %s \n", triangleType, angleType);
}

/*
	AUTHOR: Jared Potter (u0729256)

	DATE: August 31, 2015

	Classifies triangles according to the regular expression:
	(((scalene|isosceles|equilateral) (acute|obtuse|right))|not a triangle|error)

	error - When the input is incorrect. Input is not in range [-(2^30) -> (2^30)]
			or input contains illegal characters. 

	not a triangle - When the input points do not make a triangle due to duplicate points
					 or the points are colinear.

	scalene - A scalene triangle is a triangle that has three unequal sides.

	isosceles - An isosceles triangle is a triangle that has two sides of equal length.

	equilateral - An equilateral triangle is a triangle in which all three sides are equal.

	~ ~ ~ ~ ~

	acute - An acute triangle is a triangle with all three angles less than 90°.

	obuse - An obtuse triangle is a triangle with an angle greater than 90°.

	right - A right triangle is a triangle with an angle exactly 90°.
*/

#include "triangle_classifier.h"
 
int main(int argc, char *argv[])
{
	// The test triangle.
	struct triangle testTriangle;
	struct triangle *triPtr = &testTriangle;

	// Validating the input.
	if(!ValidateInput(argc, argv, triPtr))
	{
		printf("error\n");
		return 0;
	}

	ClassifyTriangle(triPtr);

	return 0;
}

/*
 * Validates the input from the user. 
 *
 * Validates that exactly 6 points came from the command line.
 * Validates the success of the system library strtol().
 * Validates the range of the point values. 
 *
 * Returns 1 on valid input. Otherwise returns 0 on fail. 
 */
int ValidateInput(int argc, char *argv[], struct triangle *t)
{
	// Checks for the correct number of inputs.
	if(argc != 7)
	{
		return 0;
	}

	// For error checking strtol.
	char* endptr;

	// First point - A.
	t->pointA.x = strtol(argv[1], &endptr, 0);
	if(*endptr != '\0')
		return 0;
	t->pointA.y = strtol(argv[2], &endptr, 0);
	if(*endptr != '\0')
		return 0;

	// Second point - B.
	t->pointB.x = strtol(argv[3], &endptr, 0);
	if(*endptr != '\0')
		return 0;
	t->pointB.y = strtol(argv[4], &endptr, 0);
	if(*endptr != '\0')
		return 0;

	// Third point - C.
	t->pointC.x = strtol(argv[5], &endptr, 0);
	if(*endptr != '\0')
		return 0;
	t->pointC.y = strtol(argv[6], &endptr, 0);
	if(*endptr != '\0')
		return 0;

	// Validating input [-(2^30)-1, (2^30)-1].
	if(t->pointA.x > MAX || 
	   t->pointA.x < MIN ||
	   t->pointA.y > MAX || 
	   t->pointA.y < MIN ||
	   t->pointB.x > MAX ||
	   t->pointB.x < MIN ||
	   t->pointB.y > MAX ||
	   t->pointB.y < MIN ||
	   t->pointC.x > MAX ||
	   t->pointC.x < MIN ||
	   t->pointC.y > MAX ||
	   t->pointC.y < MIN
	  )
		return 0;

	// Input has been validated as correct. 
	return 1;
}

/*
 * Classifies a given triangle t. A detailed description at top of file.
 */
void ClassifyTriangle(struct triangle *t)
{
	// Checks if the points are colinear.
	if(ColinearityCheck(t))
	{
		printf("not a triangle\n");
		return;
	}

	// Computing the lengths of the edges.
	__int64_t lengthAB = CalculateLength(t->pointA, t->pointB);
	__int64_t lengthBC = CalculateLength(t->pointB, t->pointC);
	__int64_t lengthAC = CalculateLength(t->pointA, t->pointC);

	// Setting initial edges. 
	// 'a' should be shortest.
	// 'b' should be middle.
	// 'c' should be longest.
	__int64_t a = lengthBC;
	__int64_t b = lengthAC;
	__int64_t c = lengthAB;

	// Sorting edges by length.
	if(lengthBC > c && lengthBC > lengthAC)
	{
		a = lengthAB;
		b = lengthAC;
		c = lengthBC;
	}
	else if(lengthAC > c && lengthAC > lengthBC)
	{
		a = lengthAB;
		b = lengthBC;
		c = lengthAC;
	}

	// Classify the triangle's edge type through 
	// comparing for equal lengths.
	if(a == b == c) 
        printf("equilateral "); 
    else if(a == b | a == c | b == c) 
        printf("isosceles ");
    else 
        printf("scalene ");
    
	// Classify the triangle based on the lengths of the edges.
	// Compares the calculated hypotenuse (adding the 2 shortest edges).
	// with the longest given edge and prints out the correct message.
    if(a + b > c)
    	printf("acute\n");
    else if(a + b < c)
  		printf("obtuse\n");
  	else if(a + b == c)
  		printf("right\n");
}

/*
 *	Checks if 3 points are colinear (3 points that reside along a single line).
 *
 *	Returns 1 (true) if the 3 points are colinear. 0 (false) otherwise.
 */
int ColinearityCheck(struct triangle *t)
{
	if(((t->pointB.y - t->pointA.y)*(t->pointC.x - t->pointB.x)) == ((t->pointC.y - t->pointB.y)*(t->pointB.x - t->pointA.x)))	
		return 1;
	else 
		return 0;
}

/*
 *	Computes the length between 2 points. Uses standard distane formula
 *	but leaves the distance in squred form to avoid floating points
 *	involved with squreroots. The __int64_t data type is large enough to
 *	correctly represent the length. Even in the most extreme case
 *	point A = (-(2^30)-1, -(2^30)-1) and point B ((2^30)-1, (2^30)-1).
 *
 *	Ex. length^2 = [(x2 - x1)^2] + [(y2 - y1)^2]
 *		length^2 = [(x2 - x1) * (x2 - x1)] + [(y2 - y1) * (y2 - y1)]
 *		length^2 = [(((2^30)-1) - (-(2^30)-1)) * (((2^30)-1) - (-(2^30)-1))] + [(((2^30)-1) - (-(2^30)-1)) * (((2^30)-1) - (-(2^30)-1))]
 *		length^2 = [((2^31)-2)*((2^31)-2)] + [((2^31)-2)*((2^31)-2)]
 *		length^2 = [(2^62)-8,589,934,588] + [(2^62)-8,589,934,588]
 *		length^2 = [(2^63)-17,179,869,176]
 *	    which is 17,179,869,175 under the 64-bit signed integer limit (2^63)-1.
 */
__int64_t CalculateLength(struct point A, struct point B)
{
	__int64_t x1 = A.x;
	__int64_t y1 = A.y;

	__int64_t x2 = B.x;
	__int64_t y2 = B.y;

	// Computes the length.
	__int64_t length = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));

	// Asserts that the length did not overflow during computation. 
	assert(length > 0);

	return length;
}

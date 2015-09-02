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
	// checks for the correct number of inputs
	if(argc != 7)
	{
		printf("error\n");
		return 0;
	}

	// the triangle to be tested
	struct triangle testTriangle;

	// for error checking strtol.
	char* endptr;

	// first point - A
	testTriangle.pointA.x = strtol(argv[1], &endptr, 0);
	if(*endptr != '\0')
	{ printf("error\n"); return 0; }
	testTriangle.pointA.y = strtol(argv[2], &endptr, 0);
	if(*endptr != '\0')
	{ printf("error\n"); return 0; }

	// second point - B
	testTriangle.pointB.x = strtol(argv[3], &endptr, 0);
	if(*endptr != '\0')
	{ printf("error\n"); return 0; }
	testTriangle.pointB.y = strtol(argv[4], &endptr, 0);
	if(*endptr != '\0')
	{ printf("error\n"); return 0; }

	// third point - C
	testTriangle.pointC.x = strtol(argv[5], &endptr, 0);
	if(*endptr != '\0')
	{ printf("error\n"); return 0; }
	testTriangle.pointC.y = strtol(argv[6], &endptr, 0);
	if(*endptr != '\0')
	{ printf("error\n"); return 0; }

	// validating input [-(2^30)-1, (2^30)-1]
	if(testTriangle.pointA.x >  1073741823 || 
	   testTriangle.pointA.x < -1073741823 ||
	   testTriangle.pointA.y >  1073741823 || 
	   testTriangle.pointA.y < -1073741823 ||
	   testTriangle.pointB.x >  1073741823 ||
	   testTriangle.pointB.x < -1073741823 ||
	   testTriangle.pointB.y >  1073741823 ||
	   testTriangle.pointB.y < -1073741823 ||
	   testTriangle.pointC.x >  1073741823 ||
	   testTriangle.pointC.x < -1073741823 ||
	   testTriangle.pointC.y >  1073741823 ||
	   testTriangle.pointC.y < -1073741823
	  )
	{
		printf("error\n");
		return 0;
	}

	// checks if there is at least 1 pair of duplicate points
	if(DuplicatePointsCheck(testTriangle))
	{
		printf("not a triangle\n");
		return 0;
	}

	// checks if the points are colinear
	if(ColinearityCheck(testTriangle))
	{
		printf("not a triangle\n");
		return 0;
	}

	__int64_t lengthAB = CalculateLength(testTriangle.pointA, testTriangle.pointB);
	__int64_t lengthBC = CalculateLength(testTriangle.pointB, testTriangle.pointC);
	__int64_t lengthAC = CalculateLength(testTriangle.pointA, testTriangle.pointC);



	// Array for holding edge lengths.
	__int64_t edgeLengths[3];
	edgeLengths[0] = lengthAB;
	edgeLengths[1] = lengthBC;
	edgeLengths[2] = lengthAC;

	printf("AB Length: %lld\n", lengthAB);
	printf("BC Length: %lld\n", lengthBC);
	printf("AC Length: %lld\n", lengthAC);

	// counts the number of equal length edges
	int equalLengthCount = CountEqualLengths(edgeLengths);

	// Checks the number of equal lengths and prints correct message.
	if(equalLengthCount == 3) 
	{
		printf("equilateral ");
	}
	else if(equalLengthCount == 1) // 1 matching pair = 2 equal sides.
	{
		printf("isosceles ");
	}
	else if(equalLengthCount == 0) // 0 equal sides.
	{
		printf("scalene ");
	}

	// qsort(edgeLengths, 3, sizeof(__int64_t), CompareFunction);

	// Because qsort() was not working correctly for 
	// certain __int64_t inputs, Bubble sort was an 
	// easy alternative for the small N of 3.
	// By putting the lengths in order, determining
	// acute/obtuse/right becomes trivial.
	BubbleSort(edgeLengths, 3);



	// By calculating the hypotenuse, we can determine if a triangle is
	// acute, obtuse, or right without dealing with angles.
	__int64_t calculateHypotenuse = edgeLengths[0] + edgeLengths[1];
	__int64_t longestEdge = edgeLengths[2];

	// Compares the calculated hypotenuse (adding the 2 shortest edges)
	// with the longest given edge and prints out the correct message.
	if(calculateHypotenuse > longestEdge)
	{
		printf("acute\n");
	}
	else if(calculateHypotenuse < longestEdge)
	{
		printf("obtuse\n");
	}
	else if(calculateHypotenuse == longestEdge)
	{
		printf("right\n");
	}
  return 0;
}

/*
	Checks if any 2 points are the same. 

	Returns 1 (true) is at least 2 points are the same. 0 (false) otherwise.
*/
int DuplicatePointsCheck(struct triangle t)
{
	int duplicatePoints = 0;

	// The points of the triangle.
	struct point A = t.pointA;
	struct point B = t.pointB;
	struct point C = t.pointC;

	if(A.x == B.x && A.y == B.y)
		duplicatePoints = 1;
	if(B.x == C.x && B.y == C.y)
		duplicatePoints = 1;
	if(A.x == C.x && A.y == C.y)
		duplicatePoints = 1;

	return duplicatePoints;
}

/*
	Citation: modified from Andrei Ciobanu's.
	http://andreinc.net/2010/12/11/euclids-algorithm-reducing-fraction-to-lowest-terms/

	Finds the greatest common divisor of two integers. 
*/ 
__int64_t FindGCD(__int64_t number1, __int64_t number2)
{
	__int64_t temp;

	// Absolute value of __int64_t.
	if(number1 < 0)
		number1 *= -1;

	// Absolute value of __int64_t.
	if(number2 < 0)
		number2 *= -1;

	while (number1 > 0) {
		temp = number1;
		number1 = number2 % number1;
		number2 = temp;
	}
	return number2;
}

/*
	Checks if 3 points are colinear (3 points that reside along a single line).
	Uses 2 __int64_t integer values to represent the (rise/run) slope that is
	reduced using their GCD. 

	Returns 1 (true) if the 3 points are colinear. 0 (false) otherwise.
*/
int ColinearityCheck(struct triangle t)
{
	int colinear = 0;
	__int64_t tempGCD = 0;

	// The points of the triangle.
	struct point A = t.pointA;
	struct point B = t.pointB;
	struct point C = t.pointC;

	// Find slopes between each set of points. 

	__int64_t slope_numerator_AB   = A.y - B.y;
	__int64_t slope_denominator_AB = A.x - B.x;

	tempGCD = FindGCD(slope_numerator_AB, slope_denominator_AB);
	slope_numerator_AB /= tempGCD;
	slope_denominator_AB /= tempGCD;

	// Absolute value.
	if(slope_numerator_AB < 0)
		slope_numerator_AB *= -1;
	if(slope_denominator_AB < 0)
		slope_denominator_AB *= -1;

	__int64_t slope_numerator_BC   = B.y - C.y;
	__int64_t slope_denominator_BC = B.x - C.x;

	tempGCD = FindGCD(slope_numerator_BC, slope_denominator_BC);
	slope_numerator_BC /= tempGCD;
	slope_denominator_BC /= tempGCD;

	// Absolute value.
	if(slope_numerator_BC < 0)
		slope_numerator_BC *= -1;
	if(slope_denominator_BC < 0)
		slope_denominator_BC *= -1;

	__int64_t slope_numerator_AC   = A.y - C.y;
	__int64_t slope_denominator_AC = A.x - C.x;

	tempGCD = FindGCD(slope_numerator_AC, slope_denominator_AC);
	slope_numerator_AC /= tempGCD;
	slope_denominator_AC /= tempGCD;

	// Absolute value.
	if(slope_numerator_AC < 0)
		slope_numerator_AC *= -1;
	if(slope_denominator_AC < 0)
		slope_denominator_AC *= -1;

	// Checks if the points are colinear by comparing slopes.
	if(
	   (slope_numerator_AB == slope_numerator_BC && 
		slope_denominator_AB == slope_denominator_BC)
	   &&
	   (slope_numerator_BC == slope_numerator_AC && 
	   	slope_denominator_BC == slope_denominator_AC)
	   &&
	   (slope_numerator_AB == slope_numerator_AC && 
	   	slope_denominator_AB == slope_denominator_AC)
	  )
		colinear = 1;

	return colinear;
}

/*
	Computes the length between 2 points. Uses standard distane formula
	but leaves the distance in squred form to avoid floating points
	involved with squreroots. The __int64_t data type is large enough to
	correctly represent the length. Even in the most extreme case
	point A = (-(2^30)-1, -(2^30)-1) and point B ((2^30)-1, (2^30)-1).

	Ex. length^2 = [(x2 - x1)^2] + [(y2 - y1)^2]
		length^2 = [(x2 - x1) * (x2 - x1)] + [(y2 - y1) * (y2 - y1)]
		length^2 = [(((2^30)-1) - (-(2^30)-1)) * (((2^30)-1) - (-(2^30)-1))] + [(((2^30)-1) - (-(2^30)-1)) * (((2^30)-1) - (-(2^30)-1))]
		length^2 = [((2^31)-2)*((2^31)-2)] + [((2^31)-2)*((2^31)-2)]
		length^2 = [(2^62)-8,589,934,588] + [(2^62)-8,589,934,588]
		length^2 = [(2^63)-17,179,869,176]
	    which is 17,179,869,175 under the 64-bit signed integer limit (2^63)-1.
*/
__int64_t CalculateLength(struct point A, struct point B)
{
	__int64_t x1 = A.x;
	__int64_t y1 = A.y;

	__int64_t x2 = B.x;
	__int64_t y2 = B.y;

	// computes using 
	__int64_t length = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));

	return length;
}

/*
	Counts the number of triangle edges that are equal.
	Starts at 1 to  
*/
int CountEqualLengths(__int64_t arr[])
{
	int count = 0;

	if(arr[0] == arr[1]) //AB and BC
		count++;

	if(arr[1] == arr[2]) // BC and AC
		count++;

	if(arr[0] == arr[2]) // AB and AC
		count++;

	return count;
}

/*
	Currently unused due to qsort() not working for legal inputs.
*/
int CompareFunction(const void* a, const void* b)
{
	return (*(__int64_t*)a) - (*(__int64_t*)b);
}

/*
	Citation: Stackoverflow.com user Donotalo's 
	implementation of Bubble sort.

	http://stackoverflow.com/questions/3893937/c-array-sorting-tips

	The standard library sorting algorithm qsort() was not working 
	correctly for __int64_t types on certain inputs. But thankfully
	this implementation of bubble sort works like a charm. 
*/
void BubbleSort(__int64_t a[], int array_size)
{
	__int64_t i, j, temp;
	for (i = 0; i < (array_size - 1); ++i)
	{
		for (j = 0; j < array_size - 1 - i; ++j )
	  	{
	    	if (a[j] > a[j+1])
	        {
	            temp = a[j+1];
	            a[j+1] = a[j];
	            a[j] = temp;
	        }
	  	}
	}
}




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define MAX 1073741823
#define MIN -1073741823
#define PI   3.141592653
/*3.141592653589793238462643383279502884197169399375105820974944...*/

static int debugging = 0;

typedef struct
{
  int X1;
  int Y1;
  int X2;
  int Y2;
  int X3;
  int Y3;
  float angle_big;
  float angle_mid;
  float angle_small;
  float shortest; /**/
  float mid;
  float longest;
}Triangle;

/*
 *Finds the measurement of the angles for tri. sideA, sideB and sideC
 *must be defined before calling find_angles.
 */
void find_angles(Triangle *tri)
{
	float a, b, c, total;
	a = tri->shortest;
	b = tri->mid;
	c = tri->longest;

	/*Find largest angle first using cosine rule because sine rule
	  which will be used in the next
	  step only works with acute angles.*/
	tri->angle_big = acos((pow(a,2) + pow(b,2) - pow(c,2)) / (2*a*b));
	tri->angle_big = tri->angle_big * 180 / PI;
	/*Round big angle */
	tri->angle_big = roundf(tri->angle_big * 10000) / 10000;

	tri->angle_mid = asin( (b * sin(tri->angle_big))/c );
	tri->angle_mid = tri->angle_mid * 180 / PI;

	tri->angle_small = 180 - tri->angle_big - tri->angle_mid;

	total = tri->angle_small + tri->angle_big + tri->angle_mid;

	assert(total = 180);
}

/*
 *Returns the distance between two points (x1,y1) and (x2, y2).
 */
float distance(int x1, int y1, int x2, int y2)
{
    return sqrt( pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

/* qsort float comparison function 
 * found at: http://stackoverflow.com/questions/1169385/is-there-a-good-library-for-sorting-a-large-array-of-numbers-in-c
 */ 
int cmp_float(const void *a, const void *b)
{
	const float *fa = a; /*cast as float pointer*/
	const float *fb = b;

	if (*fa < *fb)
		return -1;

	if (*fa > *fb)
		return 1;

	return 0;
}
/*
 *Finds the lengths of the sides of a Triangle tri. Finds the longest side 
 *first and designates that side as sideA. All points must be defined
 *before calling.
 */
void find_sides(Triangle *tri)
{
	int i;
	int size = 3;
	float sides[size];

	sides[0] = distance(tri->X2, tri->Y2, tri->X3, tri->Y3);  /*p2, p3*/
	sides[1] = distance(tri->X2, tri->Y2, tri->X1, tri->Y1);  /*p2, p1*/
	sides[2] = distance(tri->X1, tri->Y1, tri->X3, tri->Y3);  /*p1, p3*/

	qsort (sides, size, sizeof(float), cmp_float);

	tri->shortest = sides[0];
	tri->mid = sides[1];
	tri->longest = sides[2];

	assert(tri->shortest <= tri->mid <= tri->longest);
	
	if(debugging)
    {
		for(i = 0; i < size; i++)
		{
			printf("%d: %f\n:",i , sides[i]);
		}

		printf("%s\n:", "sides:");
		printf("tri.shortest: %f\n:", tri->shortest);
		printf("tri.mid: %f\n:", tri->mid);
		printf("tri.longest: %f\n:", tri->longest);
    }
}
    /*
     * Returns 1 if tri's three points are colinear, 0 otherwise.
     */
int are_colinear(Triangle *tri)
{
	/* Based on the area formula.
	 * if x1(y2-y3) + x2(y3-y1) + x3(y1 - y2) = 0
	 * then the three points are colinear.
	 */
	int result;
	result = tri->X1 * (tri->Y2 - tri->Y3) + tri->X2 * (tri->Y3 - tri->Y1) + tri->X3 * (tri->Y1 - tri->Y2);
	return !result;

}

int main( int argc, const char* argv[] )
{
	int debugging = 0;
	int i;
	float test;
	Triangle tri;
	char * result;
	/*Check if inputs are valid:
	 *argc must be 6
	 *values must be between -(2^30-1) and (2^30-1)
	 */
	if(argc != 7)
    {
		printf("error\n");
		return 0;
    }
	for(i = 1; i < argc; i++)
    {
		if(atol(argv[i]) > MAX || atol(argv[i]) < MIN)
		{
			printf("error\n");
			return 0;
		}
    }

	tri.X1 = atol(argv[1]);
	tri.Y1 = atol(argv[2]);
	tri.X2 = atol(argv[3]);
	tri.Y2 = atol(argv[4]);
	tri.X3 = atol(argv[5]);
	tri.Y3 = atol(argv[6]);


	/*check if the points are colinear*/
	if(are_colinear(&tri))
    {
		printf("not a triangle\n");
		return 0;
    }
	
	/*Find side lengths*/
	find_sides(&tri);

	/*Find angle measurments*/
	find_angles(&tri);

	result = malloc(100*sizeof(char));

	if(debugging)
    {
		printf("%s\n:", "sides:");
		printf("tri.shortest: %f\n:", tri.shortest);
		printf("tri.mid: %f\n:", tri.mid);
		printf("tri.longest: %f\n:", tri.longest);

		printf("%s\n:", "angles:");
		printf("tri.angle_big: %f\n:", tri.angle_big);
		printf("tri.angle_mid: %f\n:", tri.angle_mid);
		printf("tri.angle_small: %f\n:", tri.angle_small);
    }

	if(tri.shortest == tri.mid == tri.longest)
		result = strcat(result, "equilateral");
	else if(tri.shortest == tri.mid || tri.shortest == tri.longest || tri.mid == tri.longest)
		result = strcat(result, "isosceles");
	else 
		result = strcat(result, "scalene");

	/*angles*/
	if(tri.angle_big == 90) 
		result = strcat(result, " right");
	else if(tri.angle_big > 90) 
		result = strcat(result, " obtuse");
	else 
		result = strcat(result, " acute");

	result = strcat(result, "\0");
	printf("%s\n", result);

	free(result);

	return 0;
}

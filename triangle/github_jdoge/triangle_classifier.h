#include <stdio.h>
#include <stdlib.h>

// the structure holding the (x, y) point
struct point
{
	__int64_t x;
	__int64_t y;
};

// the structure holding the 4 points of the triangle
struct triangle
{
	struct point pointA;
	struct point pointB;
	struct point pointC;
};

int DuplicatePointsCheck(struct triangle t);
int ColinearityCheck(struct triangle t);
__int64_t CalculateLength(struct point point1, struct point point2);
int CountEqualLengths(__int64_t arr[]); 
int CompareFunction(const void* a, const void* b);
__int64_t FindGCD(__int64_t number1, __int64_t number2);


void BubbleSort(__int64_t a[], int array_size);
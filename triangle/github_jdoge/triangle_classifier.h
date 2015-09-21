#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

const __int64_t MIN = -1073741823;
const __int64_t MAX = 1073741823;

int ValidateInput(int argc, char *argv[], struct triangle *t);
void ClassifyTriangle(struct triangle *t);
int ColinearityCheck(struct triangle *t);
__int64_t CalculateLength(struct point A, struct point B);

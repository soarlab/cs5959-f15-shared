/*
 ============================================================================
 Name        : Triangle.c
 Author      : Andrew Hendrix
 Uid         : u0358444
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define PI 3.14159265358979323846
// 2147483647

struct tcPoint
{
	long x;
	long y;
};
struct tcLine
{
	struct tcPoint start;
	struct tcPoint end;
};
struct tcAngle
{
	struct tcPoint left;
	struct tcPoint mid;
	struct tcPoint right;
};

#define ERROR_ANGLE 0
#define RIGHT_ANGLE 1
#define OBTUSE_ANGLE 2
#define ACUTE_ANGLE 3

struct tcTriangle
{
	struct tcPoint a;
	struct tcPoint b;
	struct tcPoint c;
	struct tcAngle abc;
	struct tcAngle bca;
	struct tcAngle cab;
	struct tcLine ab;
	struct tcLine bc;
	struct tcLine ca;


};
//Functions
struct tcTriangle makeTriangle(long x1, long y1, long x2, long y2, long x3, long y3)
{
	struct tcTriangle toReturn;
	toReturn.a.x = x1;
	toReturn.a.y = y1;
	toReturn.b.x = x2;
	toReturn.b.y = y2;
	toReturn.c.x = x3;
	toReturn.c.y = y3;
	toReturn.abc.left = toReturn.a;
	toReturn.abc.mid = toReturn.b;
	toReturn.abc.right = toReturn.c;
	toReturn.bca.left = toReturn.b;
	toReturn.bca.mid = toReturn.c;
	toReturn.bca.right = toReturn.a;
	toReturn.cab.left = toReturn.c;
	toReturn.cab.mid = toReturn.a;
	toReturn.cab.right = toReturn.b;
	toReturn.ab.start = toReturn.a;
	toReturn.ab.end = toReturn.b;
	toReturn.bc.start = toReturn.b;
	toReturn.bc.end = toReturn.c;
	toReturn.ca.start = toReturn.c;
	toReturn.ca.end = toReturn.a;
	return toReturn;

}

int pointEqual(struct tcPoint a, struct tcPoint b)
{
	return a.x == b.x && a.y == b.y;
}


unsigned long long getLineLengthSQ(struct tcLine line)
{
	long long x1 = line.start.x;
	long long x2 = line.end.x;
	long long y1 = line.start.y;
	long long y2 = line.end.y;//plugh
	long long x = x1-x2;
	if (x < 0)
		x = -x;
	long long y = y1-y2;
	if (y < 0)
		y = -y;
	unsigned long long finalx = x;
	unsigned long long finaly = y;//plugh

	unsigned long long toReturn = finalx*finalx + finaly*finaly;//a^2 + b^2 = c^2
	assert(toReturn > finaly && toReturn > finaly); //no overflow?
	return toReturn; 
}
double atan2pi(long double y, long double x)
{
	//Implemented from wikipedia's defenition of atan2 for long double
	assert(x != 0.0 || y != 0.0);//undefined
	double toReturn;
	double radtodegree = 180.0/PI;
	if (x > 0.0)
		toReturn = atan((double)(y / x));
	if (x < 0.0 && y >= 0.0)
		toReturn = atan((double)(y / x)) + PI;
	if (x < 0.0 && y < 0.0)
		toReturn = atan((double)(y / x)) - PI;
	if (x == 0.0)
	{
		if (y > 0.0)
		{
			toReturn = PI / 2.0;
		}
		if (y < 0.0)
		{
			toReturn = -PI / 2.0;
		}
	}
	return toReturn *radtodegree;
}

int strcmp2(char* a, char* b)
{
	assert(a != 0);//no null pointers
	assert(b != 0);//no null pointers
	int i = 0;
	while (1)
	{
		if (a[i] != b[i])
		{
			return 0;
		}
		if (a[i] == 0)//or b[i] == 0, but we've already established they're equal
		{
			break;
		}
		i++;
	}
	return 1;
}

int getAngleType(struct tcAngle angle)
{
	double anglea = atan2pi((long double)(angle.mid.y-angle.left.y),(long double)(angle.mid.x - angle.left.x));
	double angleb = atan2pi((long double)(angle.mid.y-angle.right.y), (long double)(angle.mid.x - angle.right.x));

	double angleToReturn = anglea - angleb;
	if (angleToReturn < 0.0)
		angleToReturn = -angleToReturn;
	if (angleToReturn > 180.0)
		angleToReturn = 360.0 - angleToReturn;
	assert(angleToReturn <= 180.0 && angleToReturn >= 0);

	if(angleToReturn == 0.0 || angleToReturn == 180.0)
		return ERROR_ANGLE;
	if (angleToReturn == 90.0)
		return RIGHT_ANGLE;
	if (angleToReturn < 90.0)
		return ACUTE_ANGLE;
	return OBTUSE_ANGLE;
}

int main(int argc, char **argv)
{
	if(argc != 7)
	{
		puts("error");
		return 1;
	}
	int in0 = strtol(argv[1],(char**)NULL,10);
	int in1 = strtol(argv[2],(char**)NULL,10);
	int in2 = strtol(argv[3],(char**)NULL,10);
	int in3 = strtol(argv[4],(char**)NULL,10);
	int in4 = strtol(argv[5],(char**)NULL,10);
	int in5 = strtol(argv[6],(char**)NULL,10);
	if ((in0 == 0 && !strcmp2(argv[1], "0")) || (in1 == 0 && !strcmp2(argv[2], "0")) || (in2 == 0 && !strcmp2(argv[3], "0")) || (in3 == 0 && !strcmp2(argv[4], "0")) || (in4 == 0 && !strcmp2(argv[5], "0")) || (in5 == 0 && !strcmp2(argv[6], "0")))
	{
		puts("error");
		return 1;
	}


	struct tcTriangle triangle = makeTriangle(in0,in1,in2,in3,in4,in5);
	if(pointEqual(triangle.a,triangle.b)||pointEqual(triangle.b,triangle.c)||pointEqual(triangle.c,triangle.a))
	{
		puts("not a triangle");
		return 0;
	}
	int abcangle = getAngleType(triangle.abc);
	int bcaangle = getAngleType(triangle.bca);
	int cabangle = getAngleType(triangle.cab);
	if(abcangle == ERROR_ANGLE || bcaangle == ERROR_ANGLE || cabangle == ERROR_ANGLE)
	{
		puts("not a triangle");
		return 0;
	}
	unsigned long long ablinesq = getLineLengthSQ(triangle.ab);
	unsigned long long bclinesq = getLineLengthSQ(triangle.bc);
	unsigned long long calinesq = getLineLengthSQ(triangle.ca);

	if(ablinesq == bclinesq && bclinesq == calinesq)
	{
		printf("equilateral ");//not possible I guess...
	}
	else if(ablinesq == bclinesq || bclinesq == calinesq || calinesq == ablinesq)
	{
		printf("isosceles ");
	}
	else
	{
		printf("scalene ");
	}

	if(abcangle == RIGHT_ANGLE || bcaangle == RIGHT_ANGLE || cabangle == RIGHT_ANGLE)
	{
		puts("right");
	}else if (abcangle == OBTUSE_ANGLE || bcaangle == OBTUSE_ANGLE || cabangle == OBTUSE_ANGLE)
	{
		puts("obtuse");
	}else
	{
		puts("acute");
	}

	return 0;
}

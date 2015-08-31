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

int lineEqual(struct tcLine a, struct tcLine b)
{
	return pointEqual(a.start,b.start) && pointEqual(a.end,b.end);
}

int angleEqual(struct tcAngle a, struct tcAngle b)
{
	return pointEqual(a.left,b.left) && pointEqual(a.mid,b.mid) && pointEqual(a.right,b.right);
}

long long getLineLengthSQ(struct tcLine line)
{
	long long x1 = line.start.x;
	long long x2 = line.end.x;
	long long y1 = line.start.y;
	long long y2 = line.end.y;
	long long x = x1-x2;
	long long y = y1-y2;
	return x*x + y*y; //a^2 + b^2 = c^2
}
double atan2pi(long double y, long double x)
{
	double toReturn;
	double radtodegree = 180/PI;
	if (x > 0)
		toReturn = atan((double)(y / x));
	if (x < 0 && y >= 0)
		toReturn = atan((double)(y / x)) + PI;
	if (x < 0 && y < 0)
		toReturn = atan((double)(y / x)) - PI;
	if (x == 0)
	{
		if (y > 0)
		{
			toReturn = PI / 2;
		}
		if (y < 0)
		{
			toReturn = -PI / 2;
		}
		if (y = 0)
		{
			//UNDEFINED
		}
	}
	
	//if(x == 0)
	//	return 90;
	//return radtodegree * atan((double)(y/x));
	return toReturn *radtodegree;
}

int getAngleType(struct tcAngle angle)
{
	//
	double anglea = atan2pi((long double)(angle.mid.y-angle.left.y),(long double)(angle.mid.x - angle.left.x));
	double angleb = atan2pi((long double)(angle.mid.y-angle.right.y), (long double)(angle.mid.x - angle.right.x));

	double angleToReturn = anglea - angleb;
	if (angleToReturn < 0.0)
		angleToReturn = -angleToReturn;


	if (angleToReturn > 180)
		angleToReturn = 360 - angleToReturn;

	if(angleToReturn == 0 || angleToReturn == 180)
		return ERROR_ANGLE;
	if (angleToReturn == 90)
		return RIGHT_ANGLE;
	if (angleToReturn < 90)
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
	struct tcTriangle triangle = makeTriangle(in0,in1,in2,in3,in4,in5);
	if(pointEqual(triangle.a,triangle.b)||pointEqual(triangle.b,triangle.c)||pointEqual(triangle.c,triangle.a))
	{
		puts("not a triangle1");
		return 0;
	}
	int abcangle = getAngleType(triangle.abc);
	int bcaangle = getAngleType(triangle.bca);
	int cabangle = getAngleType(triangle.cab);
	if(abcangle == ERROR_ANGLE || bcaangle == ERROR_ANGLE || cabangle == ERROR_ANGLE)
	{
		puts("not a triangle2");
		return 0;
	}
	long long ablinesq = getLineLengthSQ(triangle.ab);
	long long bclinesq = getLineLengthSQ(triangle.bc);
	long long calinesq = getLineLengthSQ(triangle.ca);

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

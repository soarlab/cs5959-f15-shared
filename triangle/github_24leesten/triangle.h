#ifndef TRIANGLE_H
#define TRIANGLE_H

struct Point
{
	long long x;
	long long y;
};

static int debug = 0;

long long distance(struct Point p1, struct Point p2);

long long nat(struct Point p1, struct Point p2, struct Point p3);

char* tri_side_def(long long s1, long long s2, long long s3);

char* tri_angle_def(long long side1, long long side2, long long side3);

long long gcd(long long a, long long b);

#endif

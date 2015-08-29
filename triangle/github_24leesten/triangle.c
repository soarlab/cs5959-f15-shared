#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "triangle.h"
// Helpful Websites
// http://www.teacherschoice.com.au/maths_library/trigonometry/triangle_given_3_points.htm
// http://www.tutorialspoint.com/cprogramming/c_header_files.htm
// http://stackoverflow.com/questions/4987644/validate-input-cmdline-input-argv-contains-all-integers
// https://en.wikipedia.org/wiki/Euclidean_algorithm

// @author: Leland Stenquist
// @unid: U0634909
//
// Triangle is ment to take in six numbers as x y coordinates for a triangle. 
//   The first two points are the x and y cooidnates of the first point. the 
//   next to coordinates the second point and so forth.  If a proper triangle is
//   entered the program will tell the user two things:
//   	1- Is the triangle scalene, equilateral, or isosceles?
//   	2- Is the triangle obtuse, acute, or right?
long long main (long long argc, char* argv[])
{
	struct Point point1, point2, point3; 
	long long distance1, dist1_2, dist2_3, dist1_3, test;
	char* tri_angle;
	char* tri_side;
	char * endptr = NULL;
	
	// do we have the correct amount of arguments
	if (argc != 7){
		printf("please enter six numbers\n");
		return 0;
	}
	
	// Make sure the args are numers and assign them.
	point1.x = strtoll(argv[1],&endptr,10);
	if(*endptr!=0){
		printf("error\n");
		return 0;
	}endptr = NULL;
	point1.y = strtoll(argv[2],&endptr,10);
	if(*endptr!=0){
		printf("error\n");
		return 0;
	}endptr = NULL;
	point2.x = strtoll(argv[3],&endptr,10);
	if(*endptr!=0){
		printf("error\n");
		return 0;
	}endptr = NULL;
	point2.y = strtoll(argv[4],&endptr,10);
	if(*endptr!=0){
		printf("error\n");
		return 0;
	}endptr = NULL;
	point3.x = strtoll(argv[5],&endptr,10);
	if(*endptr!=0){
		printf("error\n");
		return 0;
	}endptr = NULL;
	point3.y = strtoll(argv[6],&endptr,10);
	if(*endptr!=0){
		printf("error\n");
		return 0;
	}

	if(debug){
	  printf("p1: (%d,%d) | p2: (%d,%d) | p3 (%d,%d)\n",point1.x, point1.y, point2.x, point2.y, point3.x, point3.y);
	}
	
	// check that the points make a triangle
	if(nat(point1, point2, point3)){
		printf("not a triangle\n");
		return 0;
	}
	
	dist1_2 = distance(point1, point2);
	dist2_3 = distance(point2, point3);
	dist1_3 = distance(point1, point3);
	
	tri_side = tri_side_def(dist1_2, dist2_3, dist1_3);
	tri_angle = tri_angle_def(dist1_2, dist2_3, dist1_3);
	
	if(debug){
		printf("\tDistance 1: %d\n", dist1_2);
		printf("\tDistance 2: %d\n", dist2_3);
		printf("\tDistance 3: %d\n", dist1_3);
	}
	
	printf("(%s) (%s)\n", tri_side, tri_angle);
	
	
	return 0;

}

// Distance Formula:
// 	|d| = sqrt((x1 - x2)^2 + (y1 - y2)^2)
// I can ignore the sqrt because when I am trying to determine if the 
//   angle is acute, obtuse, or square I use the pythagorean theorum. 
//   This will square my values again anyway, so I might as well avoid
//   floating points and just use the lengths minus rooting them.
long long distance(struct Point p1, struct Point p2)
{
	long long x, y, sum;

	x = (p1.x - p2.x) * (p1.x - p2.x);
	y = (p1.y - p2.y) * (p1.y - p2.y);
	sum = x + y;	

	return sum;
}

// use pythagoreans theorum: 
//   c^2 = a^2 + b^2 indicates a right angle
//   c^2 < a^2 + b^2 indicates an acute triangle
//   c^2 > a^2 + b^2 indicates an obtuse triangle
// These values are already squared so we can ignore that step.
//   c:    represents the largest edge
//   a, b: represent the other two edges.
char* tri_angle_def(long long side1, long long side2, long long side3)
{
	long long angle_formula, largest, var1, var2;
	
	if (side1 >= side2 && side1 >= side3){
		largest = side1;
		var1 = side2;
		var2 = side3;
	}
	else if (side2 >= side1 && side2>=side3){
		largest = side2;
		var1 = side1;
		var2 = side3;
	}
	else{
		largest = side3;
		var1 = side1;
		var2 = side2;
	}
	
	if(largest == (var1 + var2))
		return "right";
	else if (largest < var1+var2)
		return "acute";
	else 
		return "obtuse";
}

// Sloop Formula:
//   (y2-y1)/(x2-x1) 
// Take the two shorter lengths of the triangle square then and add them 
//   together then multiplied by 2.  If this is equal to the lenght of the 
//   longest triangle squared then it is a straight line.
// Also make sure that none of the points are the same. 
long long nat(struct Point point1, struct Point point2, struct Point point3)
{
	double denominator1, denominator2, numerator1, numerator2;
	double gcd1, gcd2;
	
	// Check if any of the points are the same.
	if(point1.x == point2.x && point1.y == point2.y)
		return 1;
	if(point1.x == point3.x && point1.y == point3.y)
		return 1;
	if(point3.x == point2.x && point3.y == point2.y)
		return 1;

	// Calculate the sloop.
	numerator1 = point2.y - point1.y; 
	numerator2 = point3.y - point2.y;
	denominator1 = point2.x - point1.x; 
	denominator2 = point3.x - point2.x;

	gcd1 = gcd(numerator1, denominator1);
	gcd2 = gcd(numerator2, denominator2);
	
	numerator1 = numerator1 / gcd1; 
	numerator2 = numerator2 / gcd2;
	denominator1 = denominator1 / gcd1;
	denominator2 = denominator2 / gcd2;
	
	if(debug){
		printf("\tNumerator 1: %f\n\tNumerator 2: %f\n",numerator1, numerator2);
		printf("\tDenominator 1: %f\n\tDenominator 2: %f\n",denominator1,denominator2);
	}
	
	// Check if the sloop is the same.
	if(numerator1 == numerator2 && denominator1 == denominator2)
		return 1;
	
	return 0;
}

// Use Euclids formula to find the greates common divisor for the denominator
//   and the numerator
long long gcd(long long a, long long b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

// Determine if the triangle is equilateral, scalene, or isosceles
char* tri_side_def(long long s1, long long s2, long long s3)
{
	if(s1 == s2 && s1 == s3 && s2 == s3)
		return "equilateral";
	else if(s1 != s2 && s1 != s3 && s2 != s3)
		return "scalene";
	else
		return "isosceles";
}

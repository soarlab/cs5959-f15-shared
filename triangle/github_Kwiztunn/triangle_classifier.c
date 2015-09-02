#include "TRIANGLE_CLASSIFIER.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	long coords[6]; 
	int i, j;
	// no arguments, provide help
	if (argc == 1)
	{
		printf("%s\n", "Please provide 3 coordinates of a triangle in the form:");
		printf("%s\n", "X1 Y1 X2 Y2 X3 Y3");
		printf("%s %li %s %li \n", "Where X1-X3 and Y1-Y3 are integers between", MIN, "and", MAX);
		return 1;
	}
	// too few arguments, return Not-A-Triangle
	if (argc < 7)
	{
		printf("%s\n", "Not a triangle");
		return 1;
	}
	// Goldilocks arguments, begin parsing
	for (i = 0; i < 6; i++)
	{
		j = i+1; // index of args
		char* endc;
		coords[i] = strtol(argv[j], &endc, 10);
		// error checking heer
		if ( coords[i] < MIN || coords[i] > MAX || *endc != '\0')
		{
			printf("%s\n", "error");
			//printf("%s %li %s %li \n", "Coordinates must be integers between", MIN, "and", MAX);
			return 1;
		}
	}
	// make sure it is a triangle and not a line
	if (is_line(coords))
	{
		printf("%s\n", "Not a triangle");
		return 1;
	}
	

	long long sides[3];
	sides[0] = line_length_sq(coords[X1], coords[Y1], coords[X2], coords[Y2]);
	sides[1] = line_length_sq(coords[X1], coords[Y1], coords[X3], coords[Y3]);
	sides[2] = line_length_sq(coords[X3], coords[Y3], coords[X2], coords[Y2]);
	// sort sides
	long long tmp;
	for(i = 0; i < 3; i++)
    {
        for(j = i; j < 3; j++)
        {
            if(sides[i] > sides[j])
            {
                tmp = sides[i];
                sides[i] = sides[j];
                sides[j] = tmp;
        	}
        }
    }
	// determine angle
	if (is_right(sides))
		printf("%s ", "right");
	else if (is_acute(sides))
		printf("%s ", "acute");
	else if (is_obtuse)
		printf("%s ", "obtuse");
	else
	{
		printf("%s\n", "error");
		return 1;
	}
	// determine sides
	if (is_equilateral(sides))
		printf("%s\n", "equilateral");
	else if(is_isosceles(sides))
		printf("%s\n", "isosceles");
	else if (is_scalene(sides))
		printf("%s\n", "scalene");
	else
	{
		printf("%s\n", "error");
		return 1;
	}
	return 0;
}
long long line_length_sq(long p1_x, long p1_y, long p2_x, long p2_y)
{
	long long l = ((p1_x - p2_x) * (p1_x - p2_x)) + ((p1_y - p2_y) * (p1_y - p2_y));
	return l;
}
long is_line(long* coords)
{
	// if area is zero, we know it is a line
	long long area = (coords[X1] * (coords[Y2] - coords[Y3])) + (coords[X2] * (coords[Y3] - coords[Y1])) + (coords[X3] * (coords[Y1] - coords[Y2]));
	return area == 0;
}
long is_right(long long* sides)
{
	return sides[0] + sides[1] == sides[2];
}
long is_acute(long long* sides)
{
	return sides[0] + sides[1] > sides[2];
}
long is_obtuse(long long* sides)
{
	return sides[0] + sides[1] < sides[2];
}
long is_equilateral(long long* sides)
{
	return sides[0] == sides[1] && sides[1] == sides[2];
}
long is_isosceles(long long* sides)
{
	int s1_s2_eq = sides[0] == sides[1];
	int s1_s3_eq = sides[0] == sides[2];
	int s2_s3_eq = sides[1] == sides[2];
	return s1_s2_eq || s1_s3_eq || s2_s3_eq;
}
long is_scalene(long long* sides)
{
	int s1_s2_eq = sides[0] != sides[1];
	int s1_s3_eq = sides[0] != sides[2];
	int s2_s3_eq = sides[1] != sides[2];
	return s1_s2_eq && s1_s3_eq && s2_s3_eq;
}
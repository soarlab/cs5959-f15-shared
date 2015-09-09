#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// point & edge types
typedef struct{int x; int y;} point;

// makes a point, returns 0 upon success, -1 otherwise
int point_init(point* p, int x, int y);
// determines squared magnitude of an edge
long long get_mag(point* p_1, point* p_2);
// returns length of longest side
char get_longest_side(long long side_a, long long side_b, long long side_c);

// 3 global points
point p_a, p_b, p_c;

int main(int argc, char* argv[])
{
	// 3 local magnitudes and angles
	long double mag_a, mag_b, mag_c;
	
	// error validation
	char* end_ptr_a;
	char* end_ptr_b;

	// local output strings
	char* edge_t;
	char* angle_t;

	// check for correct number of args
	if(argc != 7)
	{
		printf("error\n");
		return -1;
	}

	//make 3 points, if any intializations fail, return and display errors.....
	//	inputs of '\0' will be treated as 0...
	// point a
	if(point_init(&p_a, strtoll(argv[1], &end_ptr_a, 10), strtoll(argv[2], &end_ptr_b, 10)) == -1)
	{
		printf("error\n");
		return -1;
	}
	// printf("end pointer check 1\n");
	// printf("end_ptr_a: %c\n", *end_ptr_a);
	// printf("end_ptr_b: %s\n", end_ptr_b);
	if(*end_ptr_a != 0 || *end_ptr_b != 0)
	{
		printf("error\n");
		return -1;	
	}
	// point b
	if(point_init(&p_b, strtoll(argv[3], &end_ptr_a, 10), strtoll(argv[4], &end_ptr_b, 10)) == -1)
	{
		printf("error\n");
		return -1;
	}
	if(*end_ptr_a != 0 || *end_ptr_b != 0)
	{
		printf("error\n");
		return -1;	
	}
	// point c
	if(point_init(&p_c, strtoll(argv[5], &end_ptr_a, 10), strtoll(argv[6], &end_ptr_b, 10)) == -1)
	{
		printf("error\n");
		return -1;
	}
	if(*end_ptr_a != 0 || *end_ptr_b != 0)
	{
		printf("error\n");
		return -1;	
	}
	
	// if one of the coordinates was non-numeric
	if(errno == EINVAL)
	{
		printf("error\n");
		return -1;
	}

	// get three edge magnitudes (squared)
	mag_a = get_mag(&p_a, &p_b);
	mag_b = get_mag(&p_b, &p_c);
	mag_c = get_mag(&p_c, &p_a);

	// printf("mag_a: %Lf\n", mag_a);
	// printf("mag_b: %Lf\n", mag_b);
	// printf("mag_c: %Lf\n", mag_c);

	//check for colinear points
	 //x_1(y_2-y_3)+x_2(y_3-y_1)+x_3(y_1-y_2)=0. 
	if((p_a.x*(p_b.y - p_c.y) + p_b.x*(p_c.y - p_a.y) + p_c.x*(p_a.y - p_b.y)) == 0)
	{
		printf("not a triangle\n");
		return 0;
	}

	// printf("ang_a: %f\n", ang_a);
	// printf("ang_b: %f\n", ang_b);
	// printf("ang_c: %f\n", ang_c);

	// if all three edges are the same length...
	if(fabsl(mag_a - mag_b) < 0.00000001 && fabsl(mag_b - mag_c) < 0.00000001 && fabsl(mag_c - mag_a) < 0.00000001)
	{
		edge_t = "equilateral";    	
	}
	// else if all three edges have unique lengths...
	else if(mag_a != mag_b && mag_a != mag_c && mag_b != mag_c)
	{
		edge_t = "scalene"; 
	}
	// else if two edge lengths are identical     
	else
	{
		edge_t = "isosceles";
	}

	if(strcmp(edge_t, "equilateral") == 0)
	{
		angle_t = "acute";
		printf("%s %s\n", edge_t, angle_t);
		return 0;
	}
	
// 	Let "c" be the longest side on each set of three numbers.
	// If c^2 = a^2+b^2, the triangle is right
	// If c^2 > a^2 + b^2, the triangle is obtuse
	// If c^2 < a^2 + b^2, the triangle is acute.

	if(get_longest_side(mag_a, mag_b, mag_c) == 'a')
	{
		if(mag_a == (mag_b + mag_c))
		{
			angle_t = "right";
		}
		else if(mag_a > (mag_b + mag_c))
		{
			angle_t = "obtuse";
		}
		else
		{
			angle_t = "acute";
		}
	}
	else if(get_longest_side(mag_a, mag_b, mag_c) == 'b')
	{
		if(mag_b == (mag_a + mag_c))
		{
			angle_t = "right";
		}
		else if(mag_b > (mag_a + mag_c))
		{
			angle_t = "obtuse";
		}
		else
		{
			angle_t = "acute";
		}
	}
	else
	{	
		if(mag_c == (mag_a + mag_b))
		{
			angle_t = "right";
		}
		else if(mag_c > (mag_a + mag_b))
		{
			angle_t = "obtuse";
		}
		else
		{
			angle_t = "acute";
		}
	}

	printf("%s %s\n", edge_t, angle_t);
}

// Validates a point and sets its guys.
int point_init(point* p, int x, int y)
{
	// check for points being within bounds
	if((x > (pow(2, 30) - 1)) || (y > (pow(2, 30) - 1)) || (x < -(pow(2,30) - 1)) || (y < -(pow(2,30) - 1)))
	{
		return -1;
	}

	p->x = x;
	p->y = y;
	// great success!
	return 0;
}

//	returns the squared magnitude of an edge.
long long get_mag(point* p_1, point* p_2)
{
	//printf("in Point: p_2->x - p_1->x = %d\n", p_2->x - p_1->x);
	//printf("in Point: p_2->y - p_1->y = %d\n", p_2->y - p_1->y);
	return pow((p_2->x - p_1->x), 2) + pow((p_2->y - p_1->y), 2);
}

// returns the length of the longest side (squared)
char get_longest_side(long long side_a, long long side_b, long long side_c)
{
	if(side_a >= side_b && side_a >= side_c)
	{
		return 'a';
	}
	else if(side_b >= side_a && side_b >= side_c)
	{
		return 'b';
	}
	else
	{
		return 'c';
	}
}

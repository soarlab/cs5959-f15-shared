
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

// point & edge types
typedef struct{int x; int y;} point;

// makes a point, returns 0 upon success, -1 otherwise
int point_init(point* p, int x, int y);
// determines magnitude of an edge
long double get_mag(point* p_1, point* p_2);

// 3 global points
point p_a, p_b, p_c;

int main(int argc, char* argv[])
{
	// 3 local magnitudes and angles
	long double mag_a, mag_b, mag_c;
	double ang_a, ang_b, ang_c;

	ang_a = ang_b = ang_c = 0;

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
	if( point_init(&p_a, strtol(argv[1], NULL, 10), strtol(argv[2], NULL, 10)) == -1 || 
		point_init(&p_b, strtol(argv[3], NULL, 10), strtol(argv[4], NULL, 10)) == -1 || 
		point_init(&p_c, strtol(argv[5], NULL, 10), strtol(argv[6], NULL, 10)) == -1)
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

	// get three edge magnitudes
	mag_a = get_mag(&p_a, &p_b);
	mag_b = get_mag(&p_b, &p_c);
	mag_c = get_mag(&p_c, &p_a);

	// determine 3 angles via cos and dot product (vectors)
	ang_a = (180/3.14159265359) * acos((((p_b.x - p_a.x) * (p_c.x - p_a.x)) + ((p_b.y - p_a.y) * (p_c.y - p_a.y))) / (mag_a * mag_c));
	ang_b = (180/3.14159265359) * acos((((p_a.x - p_b.x) * (p_c.x - p_b.x)) + ((p_a.y - p_b.y) * (p_c.y - p_b.y))) / (mag_a * mag_b));
	ang_c = (180/3.14159265359) * acos((((p_b.x - p_c.x) * (p_a.x - p_c.x)) + ((p_b.y - p_c.y) * (p_a.y - p_c.y))) / (mag_b * mag_c));
	
	// if any of the angles is 0 degrees...
	if(ang_a == 0 || ang_b == 0 || ang_c == 0)
	{
		printf("not a triangle\n");
		return 0;
	}

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

	// if right...
	if(fabs(ang_a - 90) < 0.0000001 || fabs(ang_b - 90) < 0.0000001 || fabs(ang_c - 90) < 0.0000001)
	{
		angle_t = "right";
	}
	// else if acute...
	else if(ang_a < 90 && ang_b < 90 && ang_c < 90)
	{
		angle_t = "acute";
	}
	// else if obtuse...
	else
	{
		angle_t = "obtuse";
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

//	returns the magnitude of an edge.
long double get_mag(point* p_1, point* p_2)
{
	return sqrtl(pow((p_2->x - p_1->x), 2) + pow((p_2->y - p_1->y), 2));
}

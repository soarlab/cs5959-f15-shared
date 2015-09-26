#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

int64_t length(int64_t x1, int64_t y1, int64_t x2, int64_t y2)
{
	return (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
}

// Checking the size relationship of the sides. I keep the sides squared to 
// eliminate the need to use any floating point operation.
const char* check_size(int64_t sides[])
{
	int i;
	
	for(i = 0; i < 3; i = i + 1)
	{
		if(sides[0] == sides[1] || sides[0] == sides[2] || sides[1] == sides[2])
		{
			return "isosceles ";
		}
		else if(sides[0] == sides[1] && sides[0] == sides[2] && sides[1] == sides[2])
		{
			return "equilateral ";
		}
		else
		{
			return "scalene ";
		}
		
	}
	return "error";
}






int compare (const void * a, const void * b){
  long long int x = *(long long int*)a;
  long long int y = *(long long int*)b;

  if(x == y){
    return 0;
  }else if (x < y){
    return -1;
  }else{
    return 1;
  }
}

// Check the angles using the Pythagorean theorem.
char* check_angle(int64_t sides[])
{	
	// a^2 + b^2 = c^2 right (1)
	// a^2 + b^2 > c^2 acute (2)
	// a^2 + b^2 < c^2 obtuse (3)
	qsort(sides, 3, sizeof(int64_t), compare);
	assert(sides[0] <= sides[1]);
	assert(sides[0] < sides[2]);
	assert(sides[1] < sides[2]);
	if(sides[0] + sides[1] == sides[2])
	{
		return "right";
	}
	else if(sides[0] + sides[1] > sides[2])
	{
		return "acute";
	}
	else if(sides[0] + sides[1] < sides[2])
	{
		return "obtuse";
	}
	else
	{
		return "error";
	}
}


// Checking if the points lie on the same line using the slope formula.
int colin_test(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3)
{
	if((y2-y1)*(x3-x2) == (y3-y2)*(x2-x1))
		return 1;
	else
		return 0; 

}


int main(int argc, char *argv[])
{
	char out_put[100] = "";
	if(argc != 7)
	{	
		strcat(out_put, "error\n");
		printf("%s", out_put);
		return 0;
	}
		
	else
	{
		int i;
		int j;
		int64_t p[6];
		char* error;
		for(i = 1; i < 7; i = i + 1)
		{	
			p[i-1] = strtoll(argv[i], &error, 10);
			if (*error != '\0')
			{
				strcat(out_put, "error\n");
				printf("%s", out_put);
				
				return 0;
			}
		}
		
		int64_t sides[3];
		sides[0] = length(p[0], p[1], p[2], p[3]);
		sides[1] = length(p[2], p[3], p[4], p[5]);
		sides[2] = length(p[4], p[5], p[0], p[1]);
		if(colin_test(p[0], p[1], p[2], p[3], p[4], p[5]))
		{
			strcat(out_put, "not a triangle");
			printf("%s", out_put);
			return 0;
		}
		
		for(i = 0; i < 3; i = i + 1)
		{
			if(sides[i] == 0)
			{
				strcat(out_put, "not a triangle");
				printf("%s", out_put);
				return 0;
			}
		
		
		}
		strcat(out_put, check_size(sides));
		strcat(out_put, check_angle(sides));
		printf("%s\n", out_put);
		return 0;
	}

}




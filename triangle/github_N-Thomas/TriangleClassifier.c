#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int main(int argc, char *argv[]){

	int verbose = 0; //print detailed information about result

	/* Check to make sure number of inputs is correct */
	if(argc != 7){
		printf("error\n");
		if(verbose){
			printf("Number of arguments is not 6\n It is %d\n", argc);
		}
		return 0;
	}


	/* Inputs converted to long points with simple naming for clarity. 
	* Bad conversions will result in undefined behavior. */
	char *endptr;

  	long x1 = strtol(argv[1], &endptr, 10);
  	if(*endptr != '\0'){
  		printf("error\n");
  		return 0;
  	}
  	assert(x1 > -1073741823 && x1 < 1073741823);

  	long y1 = strtol(argv[2], &endptr, 10);
  	if(*endptr != '\0'){
  		 printf("error\n");
  		return 0;
  	}
  	assert(y1 > -1073741823 && y1 < 1073741823);

  	long x2 = strtol(argv[3], &endptr, 10);
  	if(*endptr != '\0'){
  		printf("error\n");
  		return 0;
  	}
	assert(x2 > -1073741823 && x2 < 1073741823);

  	long y2 = strtol(argv[4], &endptr, 10);
  	if(*endptr != '\0'){
  		printf("error\n");
  		return 0;
  	}
	assert(y2 > -1073741823 && y2 < 1073741823);

  	long x3 = strtol(argv[5], &endptr, 10);
  	if(*endptr != '\0'){
  		printf("error\n");
  		return 0;
  	}
	assert(x3 > -1073741823 && x3 < 1073741823);

  	long y3 = strtol(argv[6], &endptr, 10);
  	if(*endptr != '\0'){
  		printf("error\n");
  		return 0;
  	}
	assert(y3 > -1073741823 && y3 < 1073741823);

	/* Check that triangle does not have any duplicate points - REDUNDANT */
	if ( (x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3) ){
		printf("not a triangle\n");
		if(verbose){
			printf("duplicate point(s)");
		}
		return 0;
	}

	long long side1 = (((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)));
	long long side2 = (((x3-x1)*(x3-x1)) + ((y3-y1)*(y3-y1)));
	long long side3 = (((x3-x2)*(x3-x2)) + ((y3-y2)*(y3-y2)));

	//Make side1 the largest side
	if(side2 > side1 && side2 > side3){
		long long temp = side1;
		side1 = side2;
		side2 = temp;
	}
	else if(side3 > side1 && side3 > side2){
		long long temp = side1;
		side1 = side3;
		side3 = temp;
	}

	assert(side1 > side2 && side1 > side3); //Assert that the largest side was successfully set. 

	if(verbose){
		printf("side1 = %lld, side2 = %lld, side3 = %lld\n", side1, side2, side3);
	}

	/* Check that triangle is actually a triangle and not a line */
	if ( (sqrt(side3) + sqrt(side2)) == sqrt(side1) ){
		printf("not a triangle\n");
		if(verbose){
			printf("points are on a line");
		}
		return 0;
	}

	if(side1 == side2 == side3){
		printf("equilateral");
	}

	else if(side1 == side2 || side1 == side3 || side2 == side3){
		printf("isosceles");
	}

	else{
		printf("scalene");
	}

	if(side1 == (side2 + side3)){
		printf(" right\n");
	}

	else if(side1 > (side2 + side3)){
		printf(" obtuse\n");
	}

	else if(side1 < (side2 + side3)){
		printf(" acute\n");
	}

	else{
		printf("error");
	}

	return 0;
}

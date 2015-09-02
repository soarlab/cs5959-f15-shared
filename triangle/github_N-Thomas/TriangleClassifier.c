#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
*  Computes the largest angle based on side length
*
*  TODO: handle overflow
*/
double findAngle(double a, double b, double c){
	//printf("a = %f, b = %f, c = %f\n", a, b , c);
	double angle = (b*b) + (c*c) - (a*a);
	angle = angle / (2 * b * c);
	angle = acos(angle);

	return angle * (180/3.14);
}

int main(int argc, char *argv[]){

	int verbose = 0; //print detailed information about result

	/*
	*	Check to make sure number of inputs is correct
	*/
	if(argc != 7){
		printf("error\n");
		if(verbose){
			printf("Number of arguments is not 6\n It is %d\n", argc);
		}
		return 0;
	}


	/*
	*	Check to make sure type and range of inputs is correct
	*/
	else{
		for (int j = 1; j < 7; j++){
			if(atol(argv[j]) > 1073741823 || atol(argv[j]) < -1073741823){
				printf("error\n");
				if(verbose){
					printf("Number is not int within range");
				}
				return 0;
			}
			
		}
	}


	/*
	*	Inputs converted to long points with simple naming for clarity. 
	*   Bad conversions will result in undefined behavior. 
	*/
	long x1 = atol(argv[1]);
	long y1 = atol(argv[2]);
	long x2 = atol(argv[3]);
	long y2 = atol(argv[4]);
	long x3 = atol(argv[5]);
	long y3 = atol(argv[6]);


	/*
	*	Check that triangle does not have any duplicate points
	*/
	if ( (x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3) ){
		printf("not a triangle\n");
		if(verbose){
			printf("duplicate point(s)");
		}
		return 0;
	}

	double side1 = sqrt(((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)));
	double side2 = sqrt(((x3-x1)*(x3-x1)) + ((y3-y1)*(y3-y1)));
	double side3 = sqrt(((x3-x2)*(x3-x2)) + ((y3-y2)*(y3-y2)));

	/*
	*	Check that triangle is actually a triangle and not a line
	*/
	if ( ((side1 + side2) == side3) || ((side1 + side3) == side2) || ((side2 + side3) == side1)){
		printf("not a triangle\n");
		if(verbose){
			printf("points are on a line");
		}
		return 0;
	}

	if(verbose){
		printf("a = %f, b = %f, c = %f\n", side1, side2, side3);
	}

	//Make side1 the largest side
	if(side2 > side1 && side2 > side3){
		double temp = side1;
		side1 = side2;
		side2 = temp;
	}
	else if(side3 > side1 && side3 > side2){
		double temp = side1;
		side1 = side3;
		side3 = temp;
	}


	double largestAngle = findAngle(side1, side2, side3); //The largest angle is always opposite to the largest side
	if(verbose){
		printf("The largest Angle is %f\n", largestAngle);
	}

	if(side1 == side2 == side3){
  		//T is equilateral
		//do i need to check angles or just sides?

		printf("equilateral");
	}

	else if(side1 == side2 || side1 == side3 || side2 == side3){
	  //T is isosceles
		printf("isosceles");
	}

	else{
		printf("scalene");
	  //T is scalene
	}

	if(largestAngle > 89.9 && largestAngle < 90.1){ //TODO: Chance this back to a pure 90 check; maybe check points instead of calculating angle
		printf(" right\n");
		//Right
	}

	else if(largestAngle < 90){
		printf(" acute\n");
		//acute
	}

	else if(largestAngle > 90){
		printf(" obtuse\n");
		//obtuse
	}

	else{
		printf("error");
		//error
	}

}


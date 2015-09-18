//Andrew Stoddard
//u0693122


#include <stdio.h>
#include <math.h>

long long line1;	//global variables set once we determine the line distance between (x1, y1) - (x2, y2)
long long line2;	//(x2, y2) - (x3, y3)
long long line3;	//(x1, y1) - (x3, y3)

long long sidesArray[3]; //hold all sides so I can sort according to largest, largest will be the hypotenuse


void main( int argc, char *argv[] ) {

	//check for correct amount of inputs
	if (argc != 7){
		printf("error\n");
		return;
	}

	//check for collinearity
	if ( argv[0] == argv[2] && argv[0] == argv[4]){
		printf("Not a Triangle\n");
		return;
	}

	if ( argv[1] == argv[3] && argv[1] == argv[5]){
		printf("Not a Triangle\n");
		return;
	}




	char *endptr;
	long long inputs[6];


	//chack for inputs outside of given range
	for (int i = 1; i < 7; i++){
		inputs[i-1] = strtol(argv[i], &endptr, 10);
		if(*endptr != '\0'){
			printf("error\n");
			return;
		}
		if ( inputs[i-1] < -1073741824 || inputs[i-1] >  1073741823){
			printf("error\n");
			return;
		}


	}


	if (slopeCheck(strtol(argv[1], &endptr, 10), strtol(argv[2], &endptr, 10), strtol(argv[3], &endptr, 10), strtol(argv[4], &endptr, 10), strtol(argv[5], &endptr, 10), strtol(argv[6], &endptr, 10), strtol(argv[7], &endptr, 10)))
	{
		printf("error\n");
	}



	calcSideLength(inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5]);


	if (scalene() == 1){
		printf("scalene\n");
	}

	if (equilateral() == 1){
		printf("equilateral\n");
	}

	if (isosceles() == 1){
		printf("isosceles\n");
	}

	if (rightTriangle() == 1){
		printf("right\n");
		return;
	}

	if (obtuse() == 1){
		printf("obtuse\n");
		return;
	}

	if (acute() == 1){
		printf("acute\n");
		return; 
	}
}

//can use pythagorean theroem to determine lengths. Since we are only comparing the lengths to each other, no need to take square roots, and as such I can
//avoid using doubles and floating point. Max will be used to determine the hypotenuse used in determining right, acute or obtuse.


int calcSideLength(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){

	long long max = 0;

	line1 = ((x2-x1) * (x2-x1)) + ((y2-y1) * (y2 - y1));

	line2 = ((x3 - x2) * (x3 - x2)) + ((y3 - y2) * (y3 - y2));

	line3 = ((x3-x1) * (x3 - x1)) + ((y3 - y1) * (y3 - y1));

	sidesArray[0] = line1;
	sidesArray[1] = line2;
	sidesArray[2] = line3;

	if (line1 > line2 && line1 > line3){
		sidesArray[0] = line1;
		sidesArray[1] = line2;
		sidesArray[2] = line3;
 	}

 	if (line2 > line3 && line2 > line1){
		sidesArray[0] = line2;
		sidesArray[1] = line1;
		sidesArray[2] = line3;
 	}

 	if (line3 > line1 && line3 > line2){
 		sidesArray[0] = line3;
 		sidesArray[1] = line1;
 		sidesArray[2] = line2;
 	}

}


int equilateral(){
	if (line1 == line2){
		if (line2 == line3){
			return 1;
		}
	}

	return 0;
}

int isosceles(){

	if (line1 == line2 && line1 != line3){
		return 1;
	}

	if (line1 == line3 && line1 != line2){
		return 1;
	}

	return 0;

}

int scalene(){

	if (line1 != line2 && line1 != line3 && line2 != line3){
		return 1;
		
	}

	return 0;

}

//Use Pythagorean Thearom (a^2 + b^2 = c^2) to determine if the triangle is right, obtuse (a^2 + b^2 < c^2), or acute (a^2 + b^2 > c^2).

int rightTriangle(){

	long long hypotenuse = sidesArray[0];
	long long a = sidesArray[1];
	long long b = sidesArray[2];

	//since all lengths are already squared in the array this is the correct check for pythagorean theorem
	if ((a + b) == hypotenuse){
		return 1;
	}

	return 0;


}

//a^2 + b^2 > c^2 is acute

int acute(){

	long long hypotenuse = sidesArray[0];
	long long a = sidesArray[1];
	long long b = sidesArray[2];

	if ((a + b) > hypotenuse){
		return 1;
	}

	return 0;
}

//a^2 + b^2 < c^2 is obtuse

int obtuse(){

	long long hypotenuse = sidesArray[0];
	long long a = sidesArray[1];
	long long b = sidesArray[2];

	if ((a + b) < hypotenuse){
		return 1;
	}

	return 0;
}


//Check to make sure that the slope is different on points, to check for collinearity

int slopeCheck(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
	long long numerator1 = y2 - y1;
	long long numerator2 = y3 - y2;

	long long denominator1 = x2 - x1;
	long long denominator2 = x3 - x2;

	//Multiplies both sides of fractional slope to check for equal slopes (i.e. 1/2 = 2/4)
	numerator1 = numerator1 * denominator2;
	denominator1 = denominator1 * denominator2;

	numerator2 = numerator2 * denominator1;
	denominator2 = denominator2 * denominator1;


	if (numerator1 == numerator2){
		return 1;
	}

	return 0;
	
}



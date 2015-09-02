//Andrew Stoddard
//u0693122


#include <stdio.h>
#include <math.h>

long line1;	//global variables set once we determine the line distance between (x1, y1) - (x2, y2)
long line2;	//(x2, y2) - (x3, y3)
long line3;	//(x1, y1) - (x3, y3)

long angle1;
long angle2;
long angle3;

void main( int argc, char *argv[] ) {

	if (argc != 7){
		printf("Input Error\n");
		return;
	}

	if ( argv[0] == argv[2] && argv[0] == argv[4]){
		printf("Not a Triangle\n");
		return;
	}

	if ( argv[1] == argv[3] && argv[1] == argv[5]){
		printf("Not a Triangle\n");
		return;
	}

	if ( argv[1] < -1073741824 || argv[1] >  1073741823){
		printf("Input Error");
	}

	if ( argv[2] < -1073741824 || argv[2] >  1073741823){
		printf("Input Error");
	}

	if ( argv[3] < -1073741824 || argv[3] >  1073741823){
		printf("Input Error");
	}

	if ( argv[4] < -1073741824 || argv[4] >  1073741823){
		printf("Input Error");
	}

	if ( argv[5] < -1073741824 || argv[5] >  1073741823){
		printf("Input Error");
	}

	if ( argv[6] < -1073741824 || argv[6] >  1073741823){
		printf("Input Error");
	}

	if ( argv[7] < -1073741824 || argv[7] >  1073741823){
		printf("Input Error");
	}

	calcSideLength(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));


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

int calcSideLength(long x1, long y1, long x2, long y2, long x3, long y3){

	long distance1 = ((x2 - x1) * (x2-x1)) + ((y2-y1) * (y2 - y1));
	printf("%lu\n", distance1);
	distance1 = sqrt(distance1);

	line1 = distance1;

	long distance2 = ((x3-x2) * (x3 - x2)) + ((y3-y2) * (y3 - y2));
	distance2 = sqrt(distance2);

	line2 = distance2;

	long distance3 = ((x3-x1) * (x3-x1)) + ((y3-y1) * (y3 - y1));
	distance3 = sqrt(distance3);

	line3 = distance3;

	angle1 = atan2(y1 - y2, x1 - x2);
	angle1 = angle1 * 180/M_PI;

	angle2 = atan2(y2 - y3, x2 - x3);
	angle2 = angle2 * 180/M_PI;

	angle3 = atan2(y1 - y3, x1 - x3);
	angle3 = angle3 * 180/M_PI;

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

int rightTriangle(){

	if (angle1 < 91 && angle1 > 89){
		return 1;
	}

	if (angle2 < 91 && angle2 > 89){
		return 1;
	}

	if (angle3 < 91 && angle3 > 89){
		return 1;
	}

	return 0;
}

int acute(){

	if (angle1 < 89 && angle2 < 89 && angle3 < 89){
		return 1;
	}
	return 0;
}

int obtuse(){

	if (angle1 > 90){
		return 1;
	}

	if (angle2 > 90){
		return 1;
	}

	if (angle3 > 90){
		return 1;
	}

	return 0;
}




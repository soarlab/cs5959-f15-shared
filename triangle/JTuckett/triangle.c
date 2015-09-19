/*Dustin Jay Tuckett, Triangle classifier*/
#include "triangle.h"
#include "assert.h"

/*
 * This program can only accept 6 numbers as arguments.  The 6 numbers will represent the
 * x and y coordinates of six points ( x1, y1,...).  The points may be in decimal notation
 * but the decimal will be truncated.  If the points do not make a triangle 'not a triangle'
 * is printed, otherwise the classification of the triangle (in lower case) is printed.
 * If the input is not valid, 'error' is printed. +/-1073741823 are the largest acceptable
 * numbers.
 */
int main (int argc, char **argv)
{

  long points[6];
  long long sides[3];
  if ( !parseInput( argc, argv, points ) ) {
    printf("error\n");
    return 1;
  }
  if ( checkColinear( points ) ) {
    printf("not a triangle\n");
    return 1;
  }

  calculateSidesAndSort( points, sides);
  assert( points != NULL );
  assert( sides != NULL );
  printResult( whatClass( sides ), whatType( sides ) );

  return 0;
}


/*
 * Parses the input from the command line and catches errors.
 * 1 is returned if there was an error, 0 otherwise.
 */
int parseInput( int argc, char **argv, long *points){
	char *endptr;
	if (argc != 7) {
		return FALSE;
	}
	for (int i = 1; i < argc ; i++) {
		long point = points[ i - 1 ] = strtol(argv[i], &endptr, 10);
    //valid() ensures that the numbers are not bigger than the limit
		if ( !valid( point ) ) {
			return FALSE;
		}
    if ( *endptr != '\0' ) {
      return FALSE;
    }
	}
  return TRUE;
}
/*
 * This method calculates the square of lengths of the sides
 * of the triangle.  The square is used to avoid the use of doubles.
 * This method also sorts the sides from smallest to largest to
 * facilitate easy comparison.
 */
void calculateSidesAndSort( long *points, long long sides[] ) {
  //ensure that parameters have been created before calling this method
  assert( sides != NULL );
  assert( points != NULL );
	sides[0] = dSquared ( points[0], points[1], points[2], points[3]);
	sides[1] = dSquared ( points[0], points[1], points[4], points[5]);
	sides[2] = dSquared ( points[2], points[3], points[4], points[5]);

	int minIndex = 0;
	for(int i=0; i<3; i++) {
		minIndex = i;

		for(int j=i; j<3; j++) {
			if(sides[minIndex]>sides[j]) {
				minIndex = j;
			}
		}

		long long temp = sides[i];

		sides[i] = sides[minIndex];

		sides[minIndex] = temp;
	}
}
/*
 * Using the side lengths, this method determines if a triangle is
 * scalene (returns 0), isosceles ( returns 1 ), or equilateral ( returns 2 ).
 */
int whatClass( long long sides[] ){
  //precondition:  sides must be created appropriately
  assert( sides != NULL );
	if ( sides[0] == sides[1] && sides[0] == sides[2] ) {
		return EQUILATERAL;
	}
	if( sides[0] == sides[1] || sides[0] == sides[2] || sides[1] == sides[2] ) {
		return ISOSCELES;
	}
	return SCALENE;


}
/*
 * This method determines whether a triangle is acute (returns 0),
 * obtuse ( returns 1 ) or right ( returns 2)
 */
int whatType( long long sides[] ){
  assert( sides != NULL );
	long long hypotenusOfRight = sides[0] + sides[1];
	if( hypotenusOfRight == sides[2] ) {
		return RIGHT;
	}
	if (hypotenusOfRight > sides[2] ) {
		return ACUTE;
	}
	return OBTUSE;
}

/*
 * Prints the classification of the triangle to the
 * console.  i.e. scalene right
 */
void printResult( int tClass, int tType ) {

  switch ( tClass ) {
    case SCALENE:
      printf("scalene ");
      break;
    case ISOSCELES:
      printf("isosceles ");
      break;
    case EQUILATERAL:
      printf("equilateral ");
      break;
    default:;
  }

  switch ( tType ) {
    case ACUTE:
      printf("acute\n");
      break;
    case OBTUSE:
      printf("obtuse\n");
      break;
    case RIGHT:
      printf("right\n");
      break;
    default:;
  }
}
/*
 *  Calculates the length of the side specified by the given points
 */
long long dSquared( long x1, long y1, long x2, long y2 ) {
  long long result = ( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
  return result;
}
/*
 *  Determines whether the parsed number is within the valid range. ( +/- LARGEST)
 */
int valid( long x ) {
  return ( LARGEST >= abs(x) );
}
/*
 * This definition for checking for collinear points is not of my own devising.  I
 * used the equation found here:  (written by  Abhishek Gupta )
 * http://www.bscshortnote.com/2014/12/c-program-to-check-collinearity-of-three-points.html
 * It checks the area of the triangle, if the area is zero, the points are colinear.
 */
int checkColinear( long *points ) {
  assert( points != NULL );
  return ( points[0]*(points[3]-points[5])+points[2]*(points[5]-points[1])+points[4]*(points[1]-points[3]) == 0 );
}

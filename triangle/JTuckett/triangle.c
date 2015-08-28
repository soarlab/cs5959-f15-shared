/*Dustin Jay Tuckett, Triangle classifier*/
#include <stdio.h>
#include <stdlib.h>
/*
 * This definition for checking for collinear points is not of my own devising.  I
 * used the equation found here:  (written by  Abhishek Gupta )
 * http://www.bscshortnote.com/2014/12/c-program-to-check-collinearity-of-three-points.html
 */
#define checkColinear( x1, y1, x2, y2, x3, y3)  (x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)==0)
#define dSquared( x1, y1, x2, y2 )  ( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) )
#define largest 1073741823
#define valid( x ) (largest >= abs(x))

/*
 *Define my method signatures for later use.
 */
int parseInput( int argc, char **argv, long * points);
void getSidesAndSort( long *points, long long sides[] );
int whatClass( long long sides[] );
int whatType( long long sides[] );
void printResult( int tClass, int tType );
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
	
	if ( parseInput( argc, argv, points ) == 1) {
    printf("error\n");
		return 1;
	}
  if ( checkColinear( points[0], points[1], points[2], points[3], points[4], points[5]) ) {
    printf("not a triangle\n");
    return 1;
  }

	getSidesAndSort( points, sides);
  printResult( whatClass( sides ), whatType( sides ) );
	
  return(0);
}

/*
 * Prints the classification of the tryangle to the 
 * console.  i.e. scalene right
 */
void printResult( int tClass, int tType ) {
	
	switch ( tClass ) {
		case 0://scalene
			printf("scalene ");
			break;
		case 1://iso
			printf("isosceles ");
			break;
		case 2://equi
			printf("equilateral ");
			break;
		default:;
	}

  switch ( tType ) {
    case 0://acute
      printf("acute\n");
      break;
    case 1://obtuse
      printf("obtuse\n");
      break;
    case 2://right
      printf("right\n");
      break;
    default:;
  }

}
/*
 * Parses the input from the command line and catches errors.
 * 1 is returned if there was an error, 0 otherwise.
 */
int parseInput( int argc, char **argv, long * points){
	char *endptr;
	if (argc != 7) {
		return(1);
	}
	for (int i = 1; i < argc ; i++) {
		long point = points[ i - 1 ] = strtol(argv[i], &endptr, 10);
    //valid() ensures that the numbers are not bigger than the limit
		if ( !valid( point ) ) {
			return(1);
		}
    /*If it is a valid digit break otherwise,
      error*/
    switch ( *endptr) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case (int)'.':
      break;
      default:
      return (1);
    }
	}
  return ( 0 );
}
/*
 * This method calculates the square of lengths of the sides
 * of the triangle.  The square is used to avoid the use of doubles.
 * This method also sorts the sides from smallest to largest to 
 * facilitate easy comparison.
 */
void getSidesAndSort( long *points, long long sides[] ) {
	
	sides[0] = dSquared ( points[0], points[1], points[2], points[3]);	
	sides[1] = dSquared ( points[0], points[1], points[4], points[5]);	
	sides[2] = dSquared ( points[2], points[3], points[4], points[5]);
	
	int minIndex = 0;
	for(int i=0; i<3; i++)
	{
		int minIndex = i;

		for(int j=i; j<3; j++)

		{
			if(sides[minIndex]>sides[j])

			{
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
	if ( sides[0] == sides[1] && sides[0] == sides[2] )
	{
		return 2;
	}
	if( sides[0] == sides[1] || sides[0] == sides[2] || sides[1] == sides[2] ) {
		return 1;
	}
	return 0;

	
}
/*
 * This method determines whether a triangle is acute (returns 0),
 * obtuse ( returns 1 ) or right ( returns 2)
 */
int whatType( long long sides[] ){
	long long hypotenusOfRight = sides[0] + sides[1];
	if( hypotenusOfRight == sides[2] ) {
		return 2;
	}
	if (hypotenusOfRight > sides[2] )
	{
		return 0;
	}
	return 1;	
}


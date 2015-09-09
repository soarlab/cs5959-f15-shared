/*
 *  Dustin Jay Tuckett, U0204088 September 9th 2015
 *  Triangle Classifier 
 */

#include <stdio.h>
#include <stdlib.h>
/*
 *  Define Contstants used in classifications
 */
#define LARGEST 1073741823  //The largest magnitude that is allowed as input
#define SCALENE 0
#define ISOSCELES 1
#define EQUILATERAL 2
#define ACUTE 0
#define OBTUSE 1
#define RIGHT 2
#define FALSE 0
#define TRUE 1


 /*
  *Define my method signatures
  */
int parseInput( int argc, char **argv, long * points);
void calculateSidesAndSort( long *points, long long sides[] );
int whatClass( long long sides[] );
int whatType( long long sides[] );
void printResult( int tClass, int tType );
long long dSquared( long x1, long y1, long x2, long y2 );
int valid( long x );
/*
 * This definition for checking for collinear points is not of my own devising.  I
 * used the equation found here:  (written by  Abhishek Gupta )
 * http://www.bscshortnote.com/2014/12/c-program-to-check-collinearity-of-three-points.html
 * It checks the area of the triangle, if the area is zero, the points are colinear.
 */
int checkColinear( long *points );  

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define DEBUG 0

typedef struct {
    long int x;
    long int y;
} point;

/**
 * Determines if 3 points lie on the same line.
 *
 * If the 3 points lie on the same line then they will have the same slope. Otherwise they
 * make a triangle.
 *
 * Comparison come from: http://math.stackexchange.com/a/405981
 */
int make_line(point *p1, point *p2, point *p3) {
    if ( (p2->y - p1->y)*(p3->x - p2->x) == (p3->y - p2->y)*(p2->x - p1->x) )
        return 1;
    else
 	return 0;
}

/**
 * Classsifies the Triangle given by the 3 points that were specified.
 * 
 * A Triangle is classified as follows:
 *   1. Scalene | Equilateral | Isosceles
 *   2. Acute   | Obtuse      | Right
 *   3. Not A Triangle
 */
void classify_triangle(point *p1, point *p2, point *p3) {
    
    if ( DEBUG )
        printf("Classifying Triangle with points: (%li, %li), (%li, %li), (%li, %li)...\n", p1->x, p1->y, p2->x, p2->y, p3->x, p3->y);
    
    long int l1 = (p2->x - p1->x)*(p2->x - p1->x) + (p2->y - p1->y)*(p2->y - p1->y);    
    long int l2 = (p3->x - p2->x)*(p3->x - p2->x) + (p3->y - p2->y)*(p3->y - p2->y);
    long int l3 = (p3->x - p1->x)*(p3->x - p1->x) + (p3->y - p1->y)*(p3->y - p1->y);
    
    if ( DEBUG ) {
        printf("l1: %li\n", l1);
        printf("l2: %li\n", l2);
        printf("l3: %li\n", l3);
    }

    /* If the three points lie on the same line then they will have the same slope, otherwise
     * they make a triangle.
     *
     * Comparison comes from: http://math.stackexchange.com/a/405981
     */
    if ( make_line(p1, p2, p3) ) {
        printf("not a triangle");
	return;
    }

    if ( l1 == l2 == l3 ) {
        printf("equilateral "); 
    } else if ( l1 == l2 | l1 == l3 | l2 == l3 ) {
        printf("isosceles ");
    } else {
        printf("scalene ");
    }

    // find the longest side length
    long int a = l2, b = l3, c = l1;
    if ( l2 > c && l2 > l3 ) {
        a = l1;
        b = l3;
        c = l2;
    }
    else if (l3 > c && l3 > l2 ) {
        a = l1;
        b = l2;
        c = l3;
    }

    // classify according to angle by using Pythagorean's theorem
    // here a = a^2, b = b^2, and c = c^2 (as you can see from above)
    if ( a + b == c )
        printf("right");
    else if ( a + b > c )
    	printf("acute");
    else
  	printf("obtuse");
}

/**
 * Validates the input arguments according to the supplied criterion for this assignment.
 * 
 * Each of the six arguments 
 */
int valid_input(int argc, char **argv) {
    
    // if less or more than 6 arguments were supplied, then print an error message.
    if ( argc != 7 ) {
        return 0;
    }    

    /* check if each argument is an integer and within the range specified by the
     * assignment
     * 
     * For more information see: http://www.cplusplus.com/reference/cstdlib/strtol/
     */
    int i;
    for (i = 1; i < 7; i++) {
        char * endPtr;
        long int res = strtol(argv[i], &endPtr, 10);
	if ( *endPtr != '\0' )
            return 0; 
        else if ( res > 1073741823 || res < -1073741823 )
     	    return 0;
    }
   
    // otherwise each of the arguments was valid
    return 1; 
}

/**
 * Main entry point for the Triangle classifier.
 */
int main(int argc, char **argv) {

    if ( !valid_input(argc, argv) ) {
        printf("error\n");
        return 0;
    }    
 
    // otherwise all of the supplied arguments were valid. pass the points through
    // to the Triangle classifier.
    long int x1, x2, x3, y1, y2, y3;

    x1 = strtol(argv[1], NULL, 10), y1 = strtol(argv[2], NULL, 10);
    x2 = strtol(argv[3], NULL, 10), y2 = strtol(argv[4], NULL, 10);
    x3 = strtol(argv[5], NULL, 10), y3 = strtol(argv[6], NULL, 10);
    point p1 = {x1, y1};
    point p2 = {x2, y2};
    point p3 = {x3, y3};

    if ( DEBUG ) {
        printf("p1: (%li, %li)\n", p1.x, p1.y);
        printf("p2: (%li, %li)\n", p2.x, p2.y);
        printf("p3: (%li, %li)\n", p3.x, p3.y);
     }

    classify_triangle(&p1, &p2, &p3);
    printf("\n");

    return 0;
}

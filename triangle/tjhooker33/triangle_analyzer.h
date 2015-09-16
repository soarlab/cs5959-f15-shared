/*******************************************************************************************
 * AUTHOR :     Taylor Wilson
 * UID :        U0323893
 *
 * DATE :       August 25, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 */

#include <assert.h> /* assert  */
#include <ctype.h>  /* isDigit */
#include <stdio.h>  /* printf  */
#include <stdlib.h> /* strtoll */
#include <string.h> /* strlen  */

/*******************************************************************************************
 * Custom macros
 */
#define ARG_COUNT 7           /* max argument count for program main */
#define MAX_RANGE 1073741823  /* largest  acceptable integer value */
#define MIN_RANGE -1073741823 /* smallest acceptable integer value */
#define ERROR() {     \
	printf("error\n");	\
    return -1;	      \
  }
#define NAT() { 	            \
  printf("not a triangle\n");	\
    return -1;								\
  }

#define ASSERT_DISTANCE(res, dx, dy) { 						\
	assert(res > 0);																\
	if (dx == 0) {																	\
		assert(res % dy == 0);												\
	} else if ((dx == 1 || dx == -1) && dy == 0) {	\
		assert(res == 1);															\
	} else {																				\
		assert(res > dx);															\
	}																								\
}


/*******************************************************************************************
 * Encapsulates 2 long integers representing an (x,y) coordinate pair.
 */
typedef struct coordinate {
  long x;
  long y;
} coordinate;

/*******************************************************************************************
 * NAME :             check_arg_count(argc)
 *
 * DESCRIPTION :      Checks argument count for the expected value.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          int       argc            number of arguments
 *
 * OUTPUTS :
 *      RETURN :
 *          int                       0 on success, -1 on failure
 */
int check_arg_count(int argc);

/*******************************************************************************************
 * NAME :             check_colinearity()
 *
 * DESCRIPTION :      Determines of three coordinate pairs represent a valid triangle.
 *                    Mathematical implementation obtained from:
 *                    
 *                      http://mathworld.wolfram.com/Collinear.html
 *                      
 *                      x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)
 *
 * INPUTS :
 *      GLOBALS :   
 *          struct    triangle_points[]  reads coordinate pairs for array
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          0 on success, -1 on failure
 */
int check_colinearity(void);

/*******************************************************************************************
 * NAME :             check_range(num)
 *
 * DESCRIPTION :      Checks if input num is bounded by MAX and MIN range.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          long      * num             value to check if bounded by range
 * OUTPUTS :
 *      RETURN :
 *          int                         0 on success, -1 on failure
 */
int check_range(long *num);

/*******************************************************************************************
 * NAME :             create_point_component(num, component)
 *
 * DESCRIPTION :      Converts string num to a long and checks if value is bounded by range.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          char      * num             string representing a numeric value
 *          long      * component       either an 'x' or 'y' component of a coordinate pair
 *
 * OUTPUTS :
 *      RETURN :
 *          int                         0 on success, -1 on failure
 */
int create_point_component(char *num, long *component);

/*******************************************************************************************
 * NAME :             create_triangle(argv)
 *
 * DESCRIPTION :      Parses arguments to construct (x,y) coordinate pairs representing a
 *                    triangle.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          char      * argv[]           strings containing program name, (x,y) pairs
 *      GLOBALS :
 *          struct    triangle_points[]  writes coordinate pair values to array
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          0 on success, -1 on failure
 */
int create_triangle(char *argv[]);

/*******************************************************************************************
 * NAME :             compute_distance(p1, p2)
 *
 * DESCRIPTION :      Computes the distance between two coordinate pairs.
 *                    (x2 - x1)^2 + (y2 - y1)^2
 *
 * INPUTS :
 *      PARAMETERS :   
 *          coordinate  * p1             a coordinate pair (x,y)
 *          coordinate  * p2             a coordinate pair (x,y)
 *
 * OUTPUTS :
 *      RETURN :
 *          long long                    distance between p1 and p2
 */
long long compute_distance(coordinate *p1, coordinate *p2);

/*******************************************************************************************
 * NAME :             compute_triangle_sides()
 *
 * DESCRIPTION :      Computes and sorts the lengths of each side of the triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_points[]  reads coordinate pairs for array
 *
 * OUTPUTS :
 *      GLOBALS :
 *          struct    triangle_sides[]   writes side lengths in global array
 */
void compute_triangle_sides(void);

/*******************************************************************************************
 * NAME :             is_isosceles()
 *
 * DESCRIPTION :      Determines if triangle is classified as an isosceles triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_points[]  reads coordinate pairs for array
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is isosceles, 0 otherwise
 */
int is_isosceles(void);

/*******************************************************************************************
 * NAME :             is_scalene()
 *
 * DESCRIPTION :      Determines if triangle is classified as a scalene triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_sides[]   read side lengths of the triangle
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is scalene, 0 otherwise
 */
int is_scalene(void);

/*******************************************************************************************
 * NAME :             is_scalene()
 *
 * DESCRIPTION :      Determines if triangle is classified as an acute triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_sides[]   read side lengths of the triangle
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is acute, 0 otherwise
 */
int is_acute(void);

/*******************************************************************************************
 * NAME :             is_right()
 *
 * DESCRIPTION :      Determines if triangle is classified as a right triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_sides[]   read side lengths of the triangle
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is right, 0 otherwise
 */
int is_right(void);

/*******************************************************************************************
 * NAME :             is_obtuse()
 *
 * DESCRIPTION :      Determines if triangle is classified as a obtuse triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_sides[]   read side lengths of the triangle
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is obtuse, 0 otherwise
 */
int is_obtuse(void);

/*******************************************************************************************
 * NAME :             print_classification()
 *
 * DESCRIPTION :      Prints the classification of the triangle to the console.
 *                    Eg: "isosceles right\n", or "scalene obtuse\n", etc.
 */
void print_classification(void);

/*******************************************************************************************
 * NAME :             swap_traingle_sides(i, j)
 *
 * DESCRIPTION :      Swaps the value of the two dereferenced inputs.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          long long   * i             swap dereferenced value with *j
 *          long long   * j             swap dereferenced value with *i
 */
void swap_triangle_sides(long long *i, long long *j);

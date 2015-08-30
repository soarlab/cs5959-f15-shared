/*******************************************************************************************
 * AUTHOR :     Taylor Wilson
 * UID :        U0323893
 *
 * DATE :       August 25, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 *
 *******************************************************************************************
 */

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Colors for standard out
#define KCYN  "\x1B[36m"
#define KGRN  "\x1b[32m"
#define KMAG  "\x1b[35m"
#define KRED  "\x1B[31m"
#define RESET "\033[0m"

#define POSITIVE 0
#define NEGATIVE -1

#define ERROR() {     \
    printf("error\n");\
    return -1;	      \
  }
#define NAT()   {               \
    printf("not a triangle\n");	\
    return -1;			\
  }

typedef struct coordinate {
  uint64_t x;
  uint64_t y;
  int x_sign;
  int y_sign;
} coordinate;

typedef struct slope {
  uint64_t rise;
  uint64_t run;
  int sign;
} slope;

typedef struct length_slope {
  uint64_t length;
  slope m;
} length_slope;

typedef struct euclid_tuple {
  uint64_t x;
  uint64_t y;
  uint64_t d;
} euclid_tuple;

// Prints points A,B,C to stdout
void print_points(void);

// Program must run with 7 arguements (first is executable).
// Returns -1 arg count is not 7, otherwise returns 0.
int check_arg_count(int argc);

// Returns -1 if any two points ABC are equal, otherwise returns 0.
int check_duplicate_points(void);

// Checks if points ABC form a diagonal line.
// Returns -1 if ABC form a line, otherwise returns 0.
int check_equal_slopes(slope a, slope b, slope c);

// Each character of each input string must be a number.
// Only exception is a '-' sign as the left most character.
// Returns -2 on error, -1 if input is negative, 0 if input is non-negative.
int check_input_format(char *str);

// Absolute value of input must not exceed 2^30-1.
// Returns -1 if input is out of range, otherwise returns 0.
int check_range(uint64_t num);

// Checks if points ABC represent a valid triangle.
// Returns -1 if not, otherwise returns 0.
int check_triangle(void);

// Checks if points ABC form a horizontal or vertical line.
// Returns -1 if ABC form a line, otherwise returns 0.
int check_vert_horz_lines(void);

// Computes the length or slope between p1 and p2. The length is
// computed by making a call to *compute* providing X or Y coordinates
// as inputs. The slope is computed by making a call to *compute* providing
// deltaY or deltaX parameters as inputs.
// Example:
// 		rise = compute(Y1, Y2);
//	    run  = compute(X1, X2);
uint64_t compute(uint64_t p1, uint64_t p2);

// Determines whether the slope value between 2 points is negative or non-negative.
// Returns -1 if slope is negative, otherwise returns 0.
int compute_slope_sign(uint64_t x1, uint64_t x2, uint64_t y1, uint64_t y2);

// Creates a point of the triangle based on x,y coordinate pair and signs.
// Parameters  :
//		point  : 1 for point A, 2 for point B, 3 for point C of the triangle ABC 
// 		x_sign : sign flag for unsigned x value
//      y_sign : sign flag for unsigned y value
//      *x     : string containing numeric value of x coordinate
//      *y     : string containing numeric value of y coordinate
// Returns -1 if an error occurs, otherwise returns 0.
int create_point(int point, int x_sign, int y_sign, char *x, char *y);

// Constructs a set of points ABC representing a triangle from the input arguments.
// Returns -1 if an error occurs, otherwise returns 0.
int create_triangle(char *argv[]);

// Recursively finds the GCD of inputs a and b.
// Returns the GCD as a tuple* (x, y, d) such that
//   d = GCD(a, b) and ax + by = d
// The returned tuple is dynamically allocated. The caller is 
// responsible for freeing the returned tuple.
euclid_tuple* extended_euclid(uint64_t a, uint64_t b);

// Because this program uses unsigned values to represent points in
// a 4 quadrant plane, points must be translated to the same quadrant
// in order to find an accurate length or slope. This function determines
// which quadrant inputs P1 and P2 are in, makes any necessary translations, and
// then computes the length and slope between P1 and P2.
// 
// Returns a struct* containing the length and slope values. The struct is
// dynamically allocated; it is the responsibility of the caller to free it.
length_slope* find_length_and_slope(coordinate P1, coordinate P2);

// Returns an integer representing the x,y quadrant the point is in.
int find_quadrant(coordinate pair);

// Returns 1 if sides AB, AC, CB of triangle ABC represent an equilateral triangle.
// Otherwise returns 0.
int is_equilateral(length_slope AB, length_slope AC, length_slope CB);

// Returns 1 if sides AB, AC, CB of triangle ABC represent an isosceles triangle.
// Otherwise returns 0.
int is_isosceles(length_slope AB, length_slope AC, length_slope CB);

// Returns 1 if sides AB, AC, CB of triangle ABC represent a scalene triangle.
// Otherwise returns 0.
int is_scalene(length_slope AB, length_slope AC, length_slope CB);

// Returns 1 if sides AB, AC, CB of triangle ABC represent an acute triangle.
// Otherwise returns 0.
int is_acute(length_slope AB, length_slope AC, length_slope CB);

// Returns 1 if sides AB, AC, CB of triangle ABC represent a right triangle.
// Otherwise returns 0.
int is_right(length_slope AB, length_slope AC, length_slope CB);

// Returns 1 if sides AB, AC, CB of triangle ABC represent an obtuse triangle.
// Otherwise returns 0.
int is_obtuse(length_slope AB, length_slope AC, length_slope CB);

// Reduces the slope represented by the inputs rise/run.
void reduce_slope(uint64_t *rise, uint64_t *run);

// Prints the classification of the triangle ABC based on sides AB, AC, BC.
void print_classification(length_slope AB, length_slope AC, length_slope CB);

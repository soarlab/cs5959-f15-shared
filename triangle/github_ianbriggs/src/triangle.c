/* 
 * Assignment: Triangle Classifier
 *      Class: CS5959
 *    Teacher: Zvonimir Rakamaric
 *    Student: Ian Briggs
 *       UNID: U0692013
 *  Github ID: ianbriggs
 *
 * Assignment Specification:
 *
 * The classifier takes six command line arguments. The first two are 
 * respectively the x and y coordinates of the first vertex of the triangle, the
 * second two are respectively the x and y coordinates of the second vertex, etc.
 * Each coordinate is a decimal integer in the range –(2^30 – 1) to (2^30 – 1).
 *
 * The output of the triangle analyzer is a single line of text that is 
 * terminated by a newline. The triangle analyzer should output “error” if the
 * input format does not match the one specified above. Otherwise, it should
 * output either "not a triangle" or the result of the analysis of the triangle.
 * The output should match this regular expression:
 (((scalene|isosceles|equilateral) (acute|obtuse|right))|not a triangle|error)\n
 *
 * Three vertices are not a triangle if they are colinear. A triangle is
 * equilateral if all three sides have the same length, isosceles if exactly two
 * sides have the same length, and scalene otherwise. A triangle is right if one
 * of its angles is 90 degrees, it is obtuse if one of its angles exceeds 90
 * degrees, and is acute otherwise.
 *
 * Non-functional requirements:
 *     - The classifier must be written in C that can be compiled by GCC and
 *        Clang on a Linux machine. The test machine is x86-64, but your code
 *        should also work when compiled to a 32-bit target, and should in 
 *        general be as portable as possible.
 *     - It is fine to use external libraries but please email me if you want to
 *         use something that is not standard.
 *
 * Submission:
 *     - Push your analyzer to a directory in the class github repo called
 *        "triangle/username" where "username" is your github user name.
 *     - Include a makefile so that when someone types "make" in your triangle
 *        directory, the result is an executable called "triangle".
 *     - Do not add your executable to git.
 *     - Try not to make your code or makefile machine- or OS-specific; ideally
 *        it can be compiled on any Linux machine.
 *
 * Finally, apart from the above, also submit a collection of reasonable tests
 * (at least 10) along with your code.
 *
 */

#include <stdio.h>  /* printf */
#include <stdint.h> /* int32_t int64_t uint64_t */
#include <stdlib.h> /* strtoll */
#include <assert.h> /* assert */

/********************************************************************************
 * Defines/Structs/Typedefs/Enums                                               *
 *    Normally I would put these in a seperate file, but this is a one off task *
 * so I'll just put them here                                                   *
 *******************************************************************************/

/* Function return values */
#define FAIL (-1)
#define PASS (0)

/* Bounds given for valid input range to the program */
#define LOW_BOUND (-1073741823)
#define HIGH_BOUND (1073741823)

/* Representation of a point on the xy plane */
typedef struct point{
  int64_t x;
  int64_t y;
} point_s;

/* Enums used for the state of the program */

// all use the same unset value
#define UNSET (0)

typedef enum {
  condition_e_unuset,
  INPUT_ERROR,
  NOT_A_TRIANGLE,
  TRIANGLE,
} condition_e;

typedef enum {
  length_name_e_unset,
  SCALENE,
  ISOSCELES,
  EQUILATERAL
} length_name_e;

typedef enum {
  angle_name_e_unset,
  ACUTE,
  OBTUSE,
  RIGHT
} angle_name_e;

typedef struct result{
  condition_e condition;
  length_name_e first;
  angle_name_e second;
} result_s;

/* strings used in printing */
char * LENGTH_NAMES[] = {"\nINTERNAL ERROR length_name_e variable not set\n",
			 "scalene",
			 "isosceles",
			 "equilateral"};

char * ANGLE_NAMES[] = {"\nINTERNAL ERROR angle_name_e variable not set\n",
			"acute",
			"obtuse",
			"right"};






/********************************************************************************
 * Utilities.                                                                   *
 *    Normally I would put these in a seperate file, but this is a one off task *
 * so I'll just put them here                                                   *
 *******************************************************************************/

/* Initialize a struct of type result_s */
void
result_init(result_s *result)
{
  assert(result != NULL);
  result->condition = UNSET;
  result->first = UNSET;
  result->second = UNSET;
}


/* swap two values of two uint64s */
void
swap(uint64_t *first, uint64_t *second)
{
  assert(first != NULL);
  assert(second != NULL);
  uint64_t temp = *first;
  *first = *second;
  *second = temp;
}


/* sort an array of type uint64 */
void
sort(uint64_t *array, const size_t length)
{
  assert(array != NULL);
  uint64_t max;
  size_t index_of_max;

  size_t scan;
  /* standard insertion sort, a little overkill for 3 items */
  for (size_t current=0; current<length; current++) {
    max = array[current];
    index_of_max = current;
    for (scan=current+1; scan<length; scan++) {
      if (array[scan] > max) {
	max = array[scan];
	index_of_max = scan;
      }
    }
    swap(&array[current], &array[index_of_max]);
  }
}

/* Parse the given string as a 64 bit signed int, and verrify that it is within
 * bounds given. Bounds are inclusive and must not be max or min values for
 * 64 bit signed int
 * returns FAIL on failure and PASS on success
 */
int
parse_int_ranged(const char *string, const int64_t min, const int64_t max,
		 int64_t *out)
{
  assert(string != NULL);
  assert(out != NULL);
  assert(min <= max);
  assert(min > INT64_MIN);
  assert(max < INT64_MAX);
  char *end;
  long long int parsed = strtoll(string, &end, 10);

  if ((parsed < min) ||
      (parsed > max) ||
      (*end != '\0')){
    return FAIL;
  }

  *out = (int64_t) parsed;
  return PASS;
}


/* Parse a list of strings into a list of 64 bit ints, if any parse fails returns
 * FAIL, if all pass return PASS
 */
int
parse_int_array_ranged(const char *strings[], const size_t length,
		       const int64_t min, const int64_t max,
		       int64_t outs[])
{ 
  assert(strings != NULL);
  assert(outs != NULL);
  for (size_t i=0; i<length; i++) {
    if (parse_int_ranged(strings[i], min, max, &outs[i]) == FAIL) {
      return FAIL;
    }
  }

  return PASS;
}

/* Parse a list of strings as points x0 y0 x1 y1 .... 
 * returns FAIL if any parse fails and PASS is all pass 
 */
int
parse_points(const char *strings[], const size_t length,
	     const int64_t low, const int64_t high,
	     point_s out[])
{
  assert(strings != NULL);
  assert(outs != NULL);
  assert(length%2 == 0);

  int64_t numbers[6];
  if (parse_int_array_ranged(strings, length, low, high, numbers) == FAIL) {
    return FAIL;
  }
  
  for (size_t i=0; i<length; i+=2) {
    out[i/2].x = numbers[i];
    out[i/2].y = numbers[i+1];
  }

  return PASS;
}

/* Prints the representation of the values held in a result_s */
void
print_result(const result_s *result)
{
  assert(result != NULL);
  
  switch (result->condition) {
  case UNSET:
    printf("\nINTERNAL ERROR cannot print a result that was not set");
    break;
  case INPUT_ERROR:
    printf("error");
    break;
  case NOT_A_TRIANGLE:
    printf("not a triangle");
    break;
  case TRIANGLE:
    printf("%s %s", LENGTH_NAMES[result->first], ANGLE_NAMES[result->second]);
    break;
  default:
    printf("\nINTERNAL ERROR result_t.condition holds value outside of enum");
  }

  printf("\n");
}




/********************************************************************************
 * Main functions                                                               *
 *******************************************************************************/

/* computes the distance squared between two points */
uint64_t
distance_squared(const point_s p1, const point_s p2)
{
  int64_t delta_x = p1.x -  p2.x;
  if (delta_x < 0) {delta_x *= -1;}
  int64_t delta_y = p1.y - p2.y;
  if (delta_y < 0) {delta_y *= -1;}
  
  uint64_t delta_x_squared = (uint64_t) delta_x * (uint64_t) delta_x;
  uint64_t delta_y_squared = (uint64_t) delta_y * (uint64_t) delta_y;

  return delta_x_squared + delta_y_squared;
}

/* sets the given result indicating if 3, 2, or no edges have the same length */
void
classify_length_name(const uint64_t lengths[],
		     result_s *result)
{
  assert(lengths != NULL);
  assert(result != NULL);
  
  if ((lengths[0] == lengths[1]) && (lengths[1] == langths[2])) {
    result->first = EQUILATERAL;
  }
  else if ((lengths[0] == lengths[1]) || (lengths[1] == lengths[2])) {
    result->first = ISOSCELES;
  }
  else {
    result->first = SCALENE;
  }
}

/* set the given result indicating if any angle is 90 degrees, any angle is more
 * than 90 degrees, or all are below 90 degrees
 */
void
classify_angle_name(const uint64_t lengths[],
		    result_s *result)
{
  assert(lengths != NULL);
  assert(result != NULL);
  
  /* use pythagoras: h^2 == a^2 + b^2 iff the triangle contains a 90 degree 
   *  side 
   */
  if (lengths[0] == lengths[1] + lengths[2]) {
    result->second = RIGHT;
  }
  else if (lengths[0] < lengths[1] + lengths[2]) {
    result->second = ACUTE;
  }
  else {
    result->second = OBTUSE;
  }
}


/* Do all the operations of main, but only set the result instead of printing */
void
nonprinting_main(const int argc, const char *argv[],
			result_s *result)
{
  assert(argv != NULL);
  assert(result != NULL);
  
  // We must have 6 things given to us
  if (argc != 7) {
    result->condition = INPUT_ERROR;
    return;
  }

  // These 6 things must be numbers, which we interpret as points
  point_s points[3];
  if (parse_points(&argv[1], 6, LOW_BOUND, HIGH_BOUND, points) == FAIL) {
    result->condition = INPUT_ERROR;
    return;
  }

  // Compute the distance squared of each side of the triangle
  uint64_t distances_squared[3];
  for (size_t i=0; i<3; i++) {
    distances_squared[i] = distance_squared(points[i], points[(i+1)%3]);
  }

  // Sort them from largest to smallest
  sort(distances_squared, 3);

  // If the area of the triangle is zero it is not a triangle to us
  // based on http://mathworld.wolfram.com/Collinear.html
  if (((points[0].x * (points[1].y - points[2].y) +
	points[1].x * (points[2].y - points[0].y) +
	points[2].x * (points[0].y - points[1].y)) == 0)) {
    result->condition = NOT_A_TRIANGLE;
    return;
  }

  // We finally have a triangle, set langth based name, and angle based name
  result->condition = TRIANGLE;
  classify_length_name(distances_squared, result);
  classify_angle_name(distances_squared, result);
}


int
main(const int argc, const char *argv[])
{
  // initialize result 
  result_s result;
  result_init(&result);

  // call the internal main
  nonprinting_main(argc, argv, &result);

  // print the results found
  print_result(&result);

  // return -1 if error occured
  return -(result.condition == INPUT_ERROR);
}

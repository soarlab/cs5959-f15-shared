/*******************************************************************************************
 * AUTHOR :     Taylor Wilson
 * UID :        U0323893
 *
 * DATE :       August 25, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 */

#include "triangle_analyzer.h"

/*******************************************************************************************
 * Globals for (x,y) coordinate pairs and sides (used to store distances between points) 
 */
coordinate triangle_points[3];
long long  triangle_sides [3];

/*******************************************************************************************
 * NAME :             int main(argc, argv)
 *
 * DESCRIPTION :      Parses arguments to construct a set of points representing a triangle.
 *                    Prints to the console the classification of the triangle or an error.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          int       argc            number of arguments in argv
 *          char      * argv[]        strings containing program name, (x,y) pairs
 */
int main (int argc, char *argv[]) {
  if (check_arg_count(argc)) { ERROR(); }
  if (create_triangle(argv)) { ERROR(); }
  if (check_colinearity())   { NAT(); }
  
  compute_triangle_sides();
  print_classification();

  return 0;
}

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
int check_arg_count(int argc) {
  if (argc == ARG_COUNT) { 
    return 0; 
  }
  return -1;
}

/*******************************************************************************************
 * NAME :             check_colinearity()
 *
 * DESCRIPTION :      Determines if three coordinate pairs represent a valid triangle.
 *                    Mathematical implementation obtained from:
 *                    
 *                      http://mathworld.wolfram.com/Collinear.html
 *                      
 *                      x_1 * (y_2 - y_3) + x_2 * (y_3 - y_1) + x_3 * (y_1 - y_2)
 *
 * INPUTS :
 *      GLOBALS :   
 *          struct    triangle_points[] an array of coordinate points
 *
 * OUTPUTS :
 *      RETURN :
 *          int                         0 on success, -1 on failure
 */
int check_colinearity(void) {
  if ( triangle_points[0].x * (triangle_points[1].y - triangle_points[2].y)
     + triangle_points[1].x * (triangle_points[2].y - triangle_points[0].y)
     + triangle_points[2].x * (triangle_points[0].y - triangle_points[1].y) == 0 ) {
    return -1;
  }
  return 0;
}

/*******************************************************************************************
 * NAME :             check_input_format(num)
 *
 * DESCRIPTION :      Check each char of the string to make sure a valid int is represented.
 *
 * INPUTS :
 *      PARAMETERS :   
 *          char      * num             string representing a numeric value
 *
 * OUTPUTS :
 *      RETURN :
 *          int                         0 on success, -1 on failure
 */
int check_input_format(char *num) {
  int i, length;

  length = strlen(num);
  for (i = 0; i < length; i++) {
    /* Allows left most char to represent numeric sign */
    if (i == 0 && (num[i] == '-' || num[i] == '+')) {
      if (length == 1) {
        return -1; 
      }
      continue;
    } else if (!isdigit(num[i])) {
      return -1; 
    }
  }
  return 0;
}

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
int check_range(long *num) {
  if (*num > MAX_RANGE || *num < MIN_RANGE) {
    return -1; 
  }
  return 0;
}

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
int create_point_component(char *num, long *component) {
  char *endptr;

  if (check_input_format(num)) {
    return -1;
  }
  *component = strtol(num, &endptr, 10);
  if (*endptr != '\0' || check_range(component)) {
    return -1;
  }
  return 0;
}

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
 *          struct    triangle_points[]  an array of coordinate pairs
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          0 on success, -1 on failure
 */
int create_triangle(char *argv[]) {
  int i, j;  

  /* j keeps track of the coordinate pair */
  /* i keeps track of the individual component parsed from argv */
  j = 0;
  for(i = 1; i < 7; i+=2, j++) {
    if ( create_point_component(argv[i],   &(triangle_points[j].x)) 
      || create_point_component(argv[i+1], &(triangle_points[j].y)) ) {
      return -1;
    }
  }
  return 0;
}

/*******************************************************************************************
 * NAME :             compute_distance(p1, p2)
 *
 * DESCRIPTION :      Computes the distance between two coordinate pairs.
 *                    (x_2 - x_1)^2 + (y_2 - y_1)^2
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
long long compute_distance(coordinate *p1, coordinate *p2) {
  long long dx, dy;

  dx = p2->x - p1->x;
  dy = p2->y - p1->y;
  return (dx * dx) + (dy * dy);
}



/*******************************************************************************************
 * NAME :             compute_triangle_sides()
 *
 * DESCRIPTION :      Computes and sorts the lengths of each side of the triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_points[]  an array of coordinate pairs
 *
 * OUTPUTS :
 *      RETURN :
 *          long long                    distance between p1 and p2
 */
void compute_triangle_sides(void) {
  int i, j;

  triangle_sides[0] = compute_distance(&triangle_points[0], &triangle_points[1]);
  triangle_sides[1] = compute_distance(&triangle_points[0], &triangle_points[2]);
  triangle_sides[2] = compute_distance(&triangle_points[2], &triangle_points[1]);

  /* Ascending order sort by length */
  for (i = 0; i < 2; i++) {
    for (j = i + 1; j < 3; j++) {
      if (triangle_sides[j] < triangle_sides[i]) {
        swap_triangle_sides(&triangle_sides[j], &triangle_sides[i]);
      }
    }
  }
  return;
}

/*******************************************************************************************
 * NAME :             is_isosceles()
 *
 * DESCRIPTION :      Determines if triangle is classified as an isosceles triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_points[]  an array of coordinate pairs
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is isosceles, 0 otherwise
 */
int is_isosceles(void) {
  if (triangle_sides[0] == triangle_sides[1]) {
    return 1;
  }
  return 0;
}

/*******************************************************************************************
 * NAME :             is_scalene()
 *
 * DESCRIPTION :      Determines if triangle is classified as a scalene triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_points[]  an array of coordinate pairs
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is scalene, 0 otherwise
 */
int is_scalene(void) {
  if (is_isosceles()) {
    return 0;
  }
  return 1;
}

/*******************************************************************************************
 * NAME :             is_scalene()
 *
 * DESCRIPTION :      Determines if triangle is classified as an acute triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_points[]  an array of coordinate pairs
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is acute, 0 otherwise
 */
int is_acute(void) {
  if (triangle_sides[0] + triangle_sides[1] > triangle_sides[2]) {
    return 1;
  }
  return 0;
}

/*******************************************************************************************
 * NAME :             is_right()
 *
 * DESCRIPTION :      Determines if triangle is classified as a right triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_points[]  an array of coordinate pairs
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is right, 0 otherwise
 */
int is_right(void) {
 if (triangle_sides[0] + triangle_sides[1] == triangle_sides[2]) {
    return 1;
  }
  return 0; 
}

/*******************************************************************************************
 * NAME :             is_obtuse()
 *
 * DESCRIPTION :      Determines if triangle is classified as a obtuse triangle.
 *
 * INPUTS : 
 *      GLOBALS :
 *          struct    triangle_points[]  an array of coordinate pairs
 *
 * OUTPUTS :
 *      RETURN :
 *          int                          1 if triangle is obtuse, 0 otherwise
 */
int is_obtuse(void) {
 if (triangle_sides[0] + triangle_sides[1] < triangle_sides[2]) {
    return 1;
  }
  return 0; 
}

/*******************************************************************************************
 * NAME :             print_classification()
 *
 * DESCRIPTION :      Prints the classification of the triangle to the console.
 *                    Eg: "isosceles right\n", or "scalene obtuse\n", etc.
 */
void print_classification(void) {
  if (is_isosceles()) {
    printf("isosceles ");
  } else {
    printf("scalene ");
  }

  if (is_acute()) {
    printf("acute\n");
  } else if (is_right()) {
    printf("right\n");
  } else {
    printf("obtuse\n");
  }
}

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
void swap_triangle_sides(long long *i, long long *j) {
  long long temp;
  temp = *j;
  *j   = *i;
  *i   = temp;
  return;
}

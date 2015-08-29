#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

const int side_count = 3;

enum TRIANGLE_TYPE { scalene, isosceles, equilateral };
enum ANGLE_TYPE { acute, right, obtuse };

struct TrianglePoint {
  long x;
  long y;  
};

/**
 * Convert a string argument into an integer.
 * *err will be -1 if an error occurs while parsing.
 *
 * Returns the string parsed to an integer if successful
 **/
long arg_to_long(char* str, int* err) {
  long parsed_val = strtol(str, NULL, 0);
  long max_val = 1073741823L;
  long min_val = -1L * max_val;
  // Determine if an error occured while parsing the string
  if(parsed_val == 0 && (strlen(str) != 1 || str[0] != '0')) {
    // Error from strtol()
    *err = -1;
  } else if(parsed_val > max_val || parsed_val < min_val) {
    // Error from exceeding boundaries.
    *err = -1;
  } else {
    *err = 0;    
  }
  return (long) parsed_val;
}

/**
 * Parse the arguments (argv) into the points array.
 * The first argument will be the name of the executable file
 * The remaining arguments should be the coordinates of the points, arranged
 * in ordered pairs (x, y).
 *
 * Returns -1 if an error occurs, and 0 otherwise.
 **/
int parse_args(int argc, char** argv, struct TrianglePoint* points) {
  int expected_args = 7;
  int error_val = 0;
  if(argc != expected_args) {
    return -1;
  }

  int arg_index;
  for(arg_index = 1; arg_index < argc; arg_index++) {

    // 1 & 2 are first point, 3 & 4 are second, 5 & 6 are third.
    struct TrianglePoint* curr_point = &points[(arg_index - 1) / 2];

    long parsed_arg = arg_to_long(argv[arg_index], &error_val);
    if(error_val < 0) {
      return -1;
    }
    if(arg_index % 2 == 1) {
      curr_point->x = parsed_arg;
    } else {
      curr_point->y = parsed_arg;
    }
  }
  return 0;
}

/**
 * Computes the functional lengths of the sides of the triangle, storing them
 * in the lengths array.
 *
 * A "functional length" is the length of its respective side SQUARED.
 **/
void compute_side_lengths(struct TrianglePoint* points, long* lengths) {
  int point_index;
  for(point_index = 0; point_index < side_count; point_index++) {
    long x1 = points[point_index].x;
    long y1 = points[point_index].y;
    long x2 = points[(point_index == side_count - 1 ? 0 : point_index + 1)].x;
    long y2 = points[(point_index == side_count - 1 ? 0 : point_index + 1)].y;
    lengths[point_index] = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
  }
}

/**
 * Determines if the provided points actually make a triangle.
 *
 * Returns 0 if points are not a triangle, and 1 otherwise
 **/
int is_triangle(struct TrianglePoint* points) {
  // Use the Shoelace Formula to determine "triangularity".
  // If the area between the points is 0, the points do not make a triangle.
  if((points[0].x * points[1].y 
     + points[1].x * points[2].y
     + points[2].x * points[0].y
     - points[1].x * points[0].y
     - points[2].x * points[1].y
      - points[0].x * points[2].y) == 0) {
    return 0;
  } else {
    return 1;
  }
}

/**
 * Determine the type of the triangle based on the lengths of the sides.
 **/
enum TRIANGLE_TYPE determine_triangle_type(long* side_lengths) {
  if(side_lengths[0] == side_lengths[1]
     && side_lengths[0] == side_lengths[2]) {
    return equilateral;
  } else if (side_lengths[0] == side_lengths[1]
	     || side_lengths[1] == side_lengths[2]
	     || side_lengths[0] == side_lengths[2]) {
    return isosceles;
  } else {
    return scalene;
  }
}

/**
 * Determine the type of the angle based on the lengths of the sides.
 **/
enum ANGLE_TYPE determine_angle_type(long* side_lengths) {
  // Determine which side is the longest, store it in side_c
  long side_a, side_b, side_c;
  if(side_lengths[0] > side_lengths[1]
     && side_lengths[0] > side_lengths[2]) { 
    side_a = side_lengths[1];
    side_b = side_lengths[2];
    side_c = side_lengths[0];
  } else if(side_lengths[1] > side_lengths[0]
     && side_lengths[1] > side_lengths[2]) {
    side_a = side_lengths[0];
    side_b = side_lengths[2];
    side_c = side_lengths[1];
  } else if(side_lengths[2] > side_lengths[0]
     && side_lengths[2] > side_lengths[1]) {
    side_a = side_lengths[0];
    side_b = side_lengths[1];
    side_c = side_lengths[2];
  } else {
    // all sides are equal in length, equilaterals are acute.
    return acute;
  }

  // Abuse law of cosines:
  //   A^2 + B^2 = C^2 --> Right
  //   A^2 + B^2 > C^2 --> Acute
  //   A^2 + B^2 < C^2 --> Obtuse

  long a_sqaured_plus_b_squared = side_a + side_b;
  long c_squared = side_c;
   
  if(a_sqaured_plus_b_squared < c_squared) {
    return obtuse;
  } else if (a_sqaured_plus_b_squared > c_squared){
    return acute;
  } else {
    return right;
  }
}

char* triangle_type_to_str(enum TRIANGLE_TYPE triangle_type) {
  switch(triangle_type) {
  case scalene: return "scalene";
  case isosceles: return "isosceles";
  case equilateral: return "equilateral";
  }
}

char* angle_type_to_str(enum ANGLE_TYPE angle_type) {
  switch(angle_type) {
  case acute: return "acute";
  case right: return "right";
  case obtuse: return "obtuse";
  }
}

/**
 * Classifies a triangle based on the input of three ordered pairs.
 * 
 * Possible outputs match the following regular expression:
 * (((scalene|isosceles|equilateral) (acute|obtuse|right))|not a triangle|error)\n
 **/
main(int argc, char** argv) {

  struct TrianglePoint points[side_count];
  long squared_side_lengths[side_count];
  enum TRIANGLE_TYPE triangle_type;
  enum ANGLE_TYPE angle_type;
  if(parse_args(argc, argv, points) < 0) {
    printf("error\n");
    return 0;
  }

  if(!is_triangle(points)) {
    printf("not a triangle\n");
    return 0;
  }

  compute_side_lengths(points, squared_side_lengths);

  triangle_type = determine_triangle_type(squared_side_lengths);
  angle_type = determine_angle_type(squared_side_lengths);
        
  printf("%s %s\n", 
	 triangle_type_to_str(triangle_type),
	 angle_type_to_str(angle_type));
  return 0;
}

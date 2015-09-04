/*
 * AUTHOR :     Taylor Wilson
 * UID :        U0323893
 *
 * DATE :       August 25, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 *
 *
 */

#include "triangle_analyzer.h"

coordinate triangle_points[3];
long long  triangle_sides [3];

int main (int argc, char *argv[]) {
  if (check_arg_count(argc)) { ERROR(); }
  if (create_triangle(argv)) { ERROR(); }
  if (check_colinearity())   { NAT(); }
  
  compute_triangle_sides();
  print_classification();

  return 0;
}

int check_arg_count(int argc) {
  if (argc == ARG_COUNT) { 
    return 0; 
  }
  return -1;
}

int check_input_format(char *num) {
  int i, length;

  length = strlen(num);
  for (i = 0; i < length; i++) {
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

int create_point(char *num, long *component) {
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

int check_range(long *num) {
  if (*num > MAX_RANGE || *num < MIN_RANGE) {
    return -1; 
  }
  return 0;
}

int create_triangle(char *argv[]) {
  int i, j;  

  j = 0;
  for(i = 1; i < 7; i+=2, j++) {
    if ( create_point(argv[i],   &(triangle_points[j].x)) 
      || create_point(argv[i+1], &(triangle_points[j].y)) ) {
      return -1;
    }
  }

  return 0;
}

long long compute_distance(coordinate *p1, coordinate *p2) {
  long long delta_x, delta_y;

  delta_x = p2->x - p1->x;
  delta_y = p2->y - p1->y;

  return (delta_x * delta_x) + (delta_y * delta_y);
}

void swap_triangle_sides(long long *i, long long *j) {
  long long temp;
  temp = *j;
  *j   = *i;
  *i   = temp;
}

// http://mathworld.wolfram.com/Collinear.html
int check_colinearity(void) {
  if ( triangle_points[0].x * (triangle_points[1].y - triangle_points[2].y)
     + triangle_points[1].x * (triangle_points[2].y - triangle_points[0].y)
     + triangle_points[2].x * (triangle_points[0].y - triangle_points[1].y) == 0 ) {
    return -1;
  }
  return 0;
}

void compute_triangle_sides(void) {
  int i, j;

  triangle_sides[0] = compute_distance(&triangle_points[0], &triangle_points[1]);
  triangle_sides[1] = compute_distance(&triangle_points[0], &triangle_points[2]);
  triangle_sides[2] = compute_distance(&triangle_points[2], &triangle_points[1]);

  for (i = 0; i < 3; i++) {
    for (j = i + 1; j < 3; j++) {
      if (triangle_sides[j] < triangle_sides[i]) {
        swap_triangle_sides(&triangle_sides[j], &triangle_sides[i]);
      }
    }
  }

  return;
}

int is_isosceles(void) {
  if (triangle_sides[0] == triangle_sides[1]) {
    return 1;
  }
  return 0;
}

int is_scalene(void) {
  if (is_isosceles()) {
    return 0;
  }
  return 1;
}

int is_acute(void) {
  if (triangle_sides[0] + triangle_sides[1] > triangle_sides[2]) {
    return 1;
  }
  return 0;
}

int is_right(void) {
 if (triangle_sides[0] + triangle_sides[1] == triangle_sides[2]) {
    return 1;
  }
  return 0; 
}

int is_obtuse(void) {
 if (triangle_sides[0] + triangle_sides[1] < triangle_sides[2]) {
    return 1;
  }
  return 0; 
}

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

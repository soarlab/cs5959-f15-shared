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

#include "triangle_analyzer.h"

coordinate POINT_A;
coordinate POINT_B;
coordinate POINT_C;

int ARG_COUNT = 7;
uint64_t MAX_RANGE = 1073741823;

void print_points(void) {
  printf(KMAG "Point A:\n" RESET);
  printf(KMAG "\t %" PRIu64 " \n" RESET, POINT_A.x);
  printf(KMAG "\t %" PRIu64 " \n" RESET, POINT_A.y);
  printf(KMAG "\t %d          \n" RESET, POINT_A.x_sign);
  printf(KMAG "\t %d          \n" RESET, POINT_A.y_sign);
  
  printf(KMAG "Point B:\n" RESET);
  printf(KMAG "\t %" PRIu64 " \n" RESET, POINT_B.x);
  printf(KMAG "\t %" PRIu64 " \n" RESET, POINT_B.y);
  printf(KMAG "\t %d          \n" RESET, POINT_B.x_sign);
  printf(KMAG "\t %d          \n" RESET, POINT_B.y_sign);
  
  printf(KMAG "Point C:\n" RESET);
  printf(KMAG "\t %" PRIu64 " \n" RESET, POINT_C.x);
  printf(KMAG "\t %" PRIu64 " \n" RESET, POINT_C.y);
  printf(KMAG "\t %d          \n" RESET, POINT_C.x_sign);
  printf(KMAG "\t %d          \n" RESET, POINT_C.y_sign);
}

int check_arg_count(int argc) {
  if (argc == ARG_COUNT) { return 0; }
  return -1;
}

int check_duplicate_points(void) {
  if (POINT_A.x == POINT_B.x && POINT_A.y == POINT_B.y) {
    if (POINT_A.x_sign == POINT_B.x_sign && POINT_A.y_sign == POINT_B.y_sign) {
      return -1;
    }
  }
  
  if (POINT_A.x == POINT_C.x && POINT_A.y == POINT_C.y) {
    if (POINT_A.x_sign == POINT_C.x_sign && POINT_A.y_sign == POINT_C.y_sign) {
      return -1;
    }
  }
  
  if (POINT_C.x == POINT_B.x && POINT_C.y == POINT_B.y) {
    if (POINT_C.x_sign == POINT_B.x_sign && POINT_C.y_sign == POINT_B.y_sign) {
      return -1;
    }
  }
  return 0;	
}

int check_equal_slopes(slope a, slope b, slope c) {
  if (a.rise == b.rise && a.rise == c.rise) {
    if (a.run == b.run && a.run == c.run) {
      return -1;
    }
  }
  return 0;
}

int check_input_format(char *str) {
  int i, length, sign;
  sign   = 0;
  length = strlen(str);
  for (i = 0; i < length; i++) {
    if (i == 0 && str[i] == '-') {
      if (length == 1) { return -2; }
      sign = -1;
      continue;
    } else if (!isdigit(str[i])) { return -2; }
  }
  return sign;
}

int check_range(uint64_t num) {
  if (num > MAX_RANGE) { return -1; }
  return 0;
}

int check_triangle(void) {
  if (check_duplicate_points()) { return -1; }
  if (check_vert_horz_lines())  { return -1; }
  return 0;
}

int check_vert_horz_lines(void) {
  // Vertical line
  if (POINT_A.x == POINT_B.x && POINT_A.x == POINT_C.x) {
    if (POINT_A.x_sign == POINT_B.x_sign && POINT_A.x_sign == POINT_C.x_sign) {
      return -1;
    }
  }
  
  // Horizontal line
  if (POINT_A.y == POINT_B.y && POINT_A.y == POINT_C.y) {
    if (POINT_A.y_sign == POINT_B.y_sign && POINT_A.y_sign == POINT_C.y_sign) {
      return -1;
    }
  }
  return 0;
}

uint64_t compute(uint64_t p1, uint64_t p2) {
  uint64_t d;
  d = 0;
  d = (p1 < p2) ? (p2 - p1) : (p1 - p2);
  return d;
}

int compute_slope_sign(uint64_t x1, uint64_t x2, uint64_t y1, uint64_t y2) {
  int ms;
  ms = 0;
  if (x1 < x2 && y2 < y1) {
    ms = -1;
  } else if (x2 < x1 && y1 < y2) {
    ms = -1;
  } else {
    ms = 0;
  }
  return ms;
}

int create_point(int point, int x_sign, int y_sign, char *x, char *y) {
  uint64_t pX, pY;
  
  pX = pY = errno = 0;
  pX = strtoll(x, NULL, 10);
  pY = strtoll(y, NULL, 10);
  
  if (errno != 0 || check_range(pX) || check_range(pY)) {
    return -1;
  }
  
  switch (point) {
  case 1:
    POINT_A.x      = strtoll(x, NULL, 10);
    POINT_A.y      = strtoll(y, NULL, 10);
    POINT_A.x_sign = x_sign;
    POINT_A.y_sign = y_sign;
    break;
  case 2:
    POINT_B.x      = strtoll(x, NULL, 10);
    POINT_B.y      = strtoll(y, NULL, 10);
    POINT_B.x_sign = x_sign;
    POINT_B.y_sign = y_sign;
    break;
  case 3:
    POINT_C.x      = strtoll(x, NULL, 10);
    POINT_C.y      = strtoll(y, NULL, 10);
    POINT_C.x_sign = x_sign;
    POINT_C.y_sign = y_sign;
    break;
  default:
    return -1;
  }
  return 0;
}

int create_triangle(char *argv[]) {
  char *str, *x, *y;
  int i, sign_x, sign_y;
  
  // Check that each input string is a valid number
  // Creates a new coordinate pair point every second iteration
  // If string has '-' character, the '-' is stripped and the value is stored as
  //   an unsigned value
  for (i = 1; i < ARG_COUNT; i++) {
    str = argv[i];
    
    if (i % 2 != 0) {
      if ((sign_x = check_input_format(str)) == -2) { return -1; }
      sign_x == 0 ? (x = str) : (x = str + sizeof(char));
    } else {
      if ((sign_y = check_input_format(str)) == -2) { return -1; }
      sign_y == 0 ? (y = str) : (y = str + sizeof(char));
      if (create_point(i / 2, sign_x, sign_y, x, y)) { return -1; }
    }
  }
  return 0;
}

euclid_tuple* extended_euclid(uint64_t a, uint64_t b) {
  euclid_tuple *result;
  uint64_t xp, yp, d;
  
  xp = yp = d = 0;
  
  if (b == 0) {
    result = (euclid_tuple*)malloc(sizeof(euclid_tuple));
    result->x = 1;
    result->y = 0;
    result->d = a;
    return result;
  }
  
  result    = extended_euclid(b, a % b);
  xp        = result->x;
  yp        = result->y;
  result->x = yp;
  result->y = xp - ((a/b) * yp);
  return result;
}

length_slope* find_length_and_slope(coordinate P1, coordinate P2) {
  length_slope *lm;
  slope *m;
  int q1, q2, sign;
  uint64_t a, b, c, x1, x2, y1, y2, rise, run, temp;
  
  q1 = q2 = sign = a = b = c = x1 = x2 = y1 = y2 = rise = run = temp = 0;
  q1 = find_quadrant(P1);
  q2 = find_quadrant(P2);
  
  // Points are in the same quadrant; no translation needed
  if (q1 == q2) {
    a    = compute(P1.x, P2.x);
    b    = compute(P1.y, P2.y);
    rise = compute(P1.y, P2.y);
    run  = compute(P1.x, P2.x);
    sign = compute_slope_sign(P1.x, P2.x, P1.y, P2.y);
  } else if (((q1 == 1 && q2 == 2) || (q1 == 2 && q2 == 1)) ||
	     ((q1 == 4 && q2 == 3) || (q1 == 3 && q2 == 4))) {
    // Points have same sign for X coordinate, but different signs for Y
    // Translate the points over the X axis
    if (q1 == 1 || q1 == 4) {
      x2 = x1 = P1.x;
      x1 = x1 + x1 + P2.x;
    } else {
      x1 = x2 = P2.x;
      x2 = x2 + x2 + P1.x;
    }
    a    = compute(x1, x2);
    b    = compute(P1.y, P2.y);
    rise = compute(P1.y, P2.y);
    run  = compute(x1, x2);
    sign = compute_slope_sign(x1, x2, P1.y, P2.y);
  } else if (((q1 == 1 && q2 == 4) || (q1 == 4 && q2 == 1)) ||
	     ((q1 == 2 && q2 == 3) || (q1 == 3 && q2 == 2))) {
    // Points have same sign for Y coordinate, but different signs for X
    // Translate the points over the Y axis
    if (q1 == 1 || q1 == 2) {
      y2 = y1 = P1.y;
      y1 = y1 + y1 + P2.y;
    } else {
      y1 = y2 = P2.y;
      y2 = y2 + y2 + P1.y;
    }
    a    = compute(P1.x, P2.x);
    b    = compute(y1, y2);
    rise = compute(y1, y2);
    run  = compute(P1.x, P2.x);
    sign = compute_slope_sign(P1.x, P2.x, y1, y2);
  } else {
    // Points are in diagonal quadrants. Translate points to quadrant 1
    if (q1 == 2 || q1 == 1) {
      x1 = P2.x;
      y1 = P1.y + P2.y;
      x2 = P2.x + P2.x + P1.x;
      y2 = 0;
    } else {
      x1 = P1.x;
      y1 = P2.y + P1.y;
      x2 = P1.x + P1.x + P2.x;
      y2 = 0;
    }
    a    = compute(x1, x2);
    b    = compute(y1, y2);
    rise = compute(y1, y2);
    run  = compute(x1, x2);
    sign = compute_slope_sign(x1, x2, y1, y2);
  }
  
  // Compute a^2+b^2=c^2
  c = (a * a) + (b * b);
  if (run == 0) {
    run  = rise;
    rise = 0;
  }
  
  // Setup return value
  reduce_slope(&rise, &run);
  assert (( m =        (slope*)malloc(sizeof(slope)))        != NULL);
  assert ((lm = (length_slope*)malloc(sizeof(length_slope))) != NULL);
  m->rise     = rise;
  m->run      = run;
  m->sign     = sign;
  lm->length  = c;
  lm->m       = *m;
  return lm;
}

int find_quadrant(coordinate pair) {
  if (pair.x_sign == POSITIVE && pair.y_sign == POSITIVE) {
    return 1;
  }
  
  if (pair.x_sign == NEGATIVE && pair.y_sign == POSITIVE) {
    return 2;
  }
  
  if (pair.x_sign == NEGATIVE && pair.y_sign == NEGATIVE) {
    return 3;
  }
  
  if (pair.x_sign == POSITIVE && pair.y_sign == NEGATIVE) {
    return 4;
  }
  return -1;
}

int is_equilateral(length_slope AB, length_slope AC, length_slope CB) {
  if (AB.length == AC.length &&
      AB.length == CB.length &&
      CB.length == AC.length) {
    return 1;
  }
  return 0;
}

int is_isosceles(length_slope AB, length_slope AC, length_slope CB) {
  if (is_equilateral(AB, AC, CB)) {
    return 0;
  }
  if (AB.length == AC.length ||
      AB.length == CB.length ||
      CB.length == AC.length) {
    return 1;
  }
  return 0;
}

int is_scalene(length_slope AB, length_slope AC, length_slope CB) {
  if (AB.length != AC.length &&
      AB.length != CB.length &&
      CB.length != AC.length) {
    return 1;
  }
  return 0;
}

int is_acute(length_slope AB, length_slope AC, length_slope CB) {
  if (AB.length + AC.length > CB.length &&
      AB.length + CB.length > AC.length &&
      AC.length + CB.length > AB.length) {
    return 1;
  }
  return 0;
}

int is_right(length_slope AB, length_slope AC, length_slope CB) {
  if (AB.length + AC.length == CB.length || 
      AB.length + CB.length == AC.length ||
      AC.length + CB.length == AB.length) {
    return 1;
  }
  return 0;
}

int is_obtuse(length_slope AB, length_slope AC, length_slope CB) {
  if (AB.length + AC.length < CB.length || 
      AB.length + CB.length < AC.length ||
      AC.length + CB.length < AB.length) {
    return 1;
  }
  return 0;
}

void reduce_slope(uint64_t *rise, uint64_t *run) {
  euclid_tuple *gcd;
  
  gcd   = extended_euclid(*rise, *run);
  *rise = *rise / gcd->d;
  *run  = *run  / gcd->d;
  
  free(gcd);
}

void print_classification(length_slope AB, length_slope AC, length_slope CB) {
  if (is_equilateral(AB, AC, CB)) {
    printf("equilateral acute\n");
  } else if (is_isosceles(AB,AC,CB) && is_acute (AB,AC,CB)) {
    printf("isosceles acute\n");
  } else if (is_isosceles(AB,AC,CB) && is_right (AB,AC,CB)) {
    printf("isosceles right\n");
  } else if (is_isosceles(AB,AC,CB) && is_obtuse(AB,AC,CB)) {
    printf("isosceles obtuse\n");
  } else if (is_scalene(AB,AC,CB) && is_acute (AB,AC,CB)) {
    printf("scalene acute\n");
  } else if (is_scalene(AB,AC,CB) && is_right (AB,AC,CB)) {
    printf("scalene right\n");
  } else if (is_scalene(AB,AC,CB) && is_obtuse(AB,AC,CB)) {
    printf("scalene obtuse\n");
  } else {
    printf("error\n");
  }
}

int main (int argc, char *argv[]) {
  length_slope *AB, *AC, *CB;
  
  if (check_arg_count(argc)) { ERROR(); }
  if (create_triangle(argv)) { ERROR(); }
  if (check_triangle())      { NAT(); }
  
  AB = find_length_and_slope(POINT_A, POINT_B);
  AC = find_length_and_slope(POINT_A, POINT_C);
  CB = find_length_and_slope(POINT_C, POINT_B);
  
  // Must find lengths and slopes before checking for diagonal line
  if (check_equal_slopes(AB->m, AC->m, CB->m)) { NAT(); }
  
  print_classification(*AB, *AC, *CB);
  
  free(AB);
  free(AC);
  free(CB);
  
  return 0;
}

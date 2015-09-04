/*
 * AUTHOR :     Taylor Wilson
 * UID :        U0323893
 *
 * DATE :       August 25, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_COUNT 7
#define MAX_RANGE 1073741823
#define MIN_RANGE -1073741823

#define ERROR() {     \
    printf("error\n");\
    return -1;	      \
  }
#define NAT()   {               \
    printf("not a triangle\n");	\
    return -1;			\
  }

typedef struct coordinate {
  long x;
  long y;
} coordinate;

int check_arg_count(int argc);
int check_input_format(char *num);
int create_point(char *num, long *component);
int check_range(long *num);
int create_triangle(char *argv[]);
long long compute_distance(coordinate *p1, coordinate *p2);
void swap_triangle_sides(long long *i, long long *j);
int check_colinearity(void);
void compute_triangle_sides(void);
int is_isosceles(void);
int is_scalene(void);
int is_acute(void);
int is_right(void);
int is_obtuse(void);
void print_classification(void);

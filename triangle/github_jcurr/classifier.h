/*
 * Classifier.h
 *
 * Jon Curry
 * 8/25/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

int get_equal_edge_length_count();
int check_dot_products();
int validate_range(long value);
int validate_triangle();
void print_error_and_close(char *msg);
char* classify_by_edges(int edges);
char* classify_by_angles(int result);
long extract_value_and_verify_strtol(char *str);

#endif

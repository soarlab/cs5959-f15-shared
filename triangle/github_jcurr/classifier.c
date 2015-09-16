/*
 * classifier.c
 *
 * Jon Curry 8/25/15
 */

#include "classifier.h"

// point variables
long x1,x2,x3,_y1,y2,y3;
// vector variables
long ax,bx,cx,ay,by,cy;

int main(int argc, char *argv[])
{
  //check the number of arguments
  if(argc != 7)
     print_error_and_close("error");

  // assign point data to globals
  x1 = extract_value_and_verify_strtol(argv[1]);
  x2 =  extract_value_and_verify_strtol(argv[3]);
  x3 =  extract_value_and_verify_strtol(argv[5]);
  _y1 =  extract_value_and_verify_strtol(argv[2]); 
  y2 =  extract_value_and_verify_strtol(argv[4]);
  y3 =  extract_value_and_verify_strtol(argv[6]);

  // assign vecter values to globals
  ax = x2 - x1;
  ay = y2 - _y1;
  bx = x3 - x1;
  by = y3 - _y1;
  cx = x3 - x2;
  cy = y3 - y2;

  // check if the points are collinear
  if(!validate_triangle())
    print_error_and_close("not a triangle");

  // count the number of equal edges
  int equal_edge_count = get_equal_edge_length_count();

  // produce a string with "isosceles" or "scalene" or "equilateral"
  char* edge_classification = classify_by_edges(equal_edge_count);

  // get a code indicating whether an obtuse or right triangel was detected
  int result = check_dot_products();

  // get a string based on the above code with "right/obtuse/acute"
  char* angle_classification = classify_by_angles(result);

  // print the result string
  printf("%s %s\n",edge_classification, angle_classification);

  return 0;
}

// return a string based on whether an obtuse/right/acute triangle was detected
char* classify_by_angles(int result)
{
  if(result == 0)
    return "right";
  else if(result == 1)
    return "acute";
  else
    return "obtuse";
}

// compute the dot product for each angle
// if any one angle was right or obtuse, return that code, else acute
int check_dot_products()
{
  long long a = ax*bx + ay*by;
  long long b = bx*cx + by*cy;
  long long c = -(cx*ax + cy*ay);

  if(a == 0 || b == 0 || c == 0)
    return 0;
  else if(a < 0 || b < 0 || c < 0)
    return -1;
  else
    return 1;
}

// get a string based on the number of equal edges
char* classify_by_edges(int edges)
{
  if(edges == 3)
    return "equilateral";
  else if(edges == 2)
    return "isosceles";
  else
    return "scalene";
}

// compare egdge lengths without using a division or square root to avoid
// introducing floating point precision errors
int get_equal_edge_length_count()
{
  int equal_count = 1;

  // compute edge lengths with out using sqrt() or floating point
  // this is safe becuase equality will be preserverd with out completing
  // the square root step
  long long a = ax*ax + ay*ay;
  long long b = bx*bx + by*by;
  long long c = cx*cx + cy*cy;

  if(a == b)
    equal_count++;

  if(a == c)
    equal_count++;

  if(b == c)
    equal_count++;

  return equal_count;
}

long extract_value_and_verify_strtol(char *str)
{
  char * endptr;
  long extracted_value = strtol(str, &endptr, 10);

  if(*endptr != '\0')
    print_error_and_close("error"); 

  if(!validate_range(extracted_value))
    print_error_and_close("error");  

  return extracted_value;
}

int validate_range(long value)
{
  long max = 1073741823;
  
  if(labs(value) > max)
    return 0;
  else
    return 1;
}

// compute the area of the supposed triangle, if 0, not a triangle
int validate_triangle()
{
  long long area = x1*(y2-y3) + x2*(y3-_y1) + x3*(_y1-y2);
  if(area == 0)
    return 0;
  return 1;
}

// print an error message and close the program
void print_error_and_close(char *msg)
{
  printf("%s\n",msg);
  exit(-1);
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Pre-declarations of methods */
double sideLen (long x1, long y1, long x2, long y2);
void checkPoints(long points[]);
void checkSides(long long sides[]);
void checkAngles(long points[]);
int valid(long point);
/*Global Variables */
char* sideType;
char* angleType;

/* Compute a side of the triangle 
* Should always return a postive length */
double sideLen (long x1, long y1, long x2, long y2){
  long long a = x1 - x2;
  long long b = y1 - y2;
  a = a*a;
  b = b*b;
  long long c = a+b;
  return c;
}

/* Check that the points aren't on the same line */
void checkPoints(long points[]){
 /* Assert that the points array has been filled otherwise the rest of the code from here will break*/
  assert(points != NULL);
  if((points[2] - points[0]) * (points[5] - points[1]) == (points[4] - points[0]) * (points[3] - points[1])) {
    printf("not a triangle");
    exit(0);
  }
  checkAngles(points);
}

int valid(long point){
  if(point > 1073741823 || point < -1073741823)
    return 1;
  else
    return 0;
}

/* Check the side lengths for patterns that will classify them.*/
void checkSides(long long sides[]){
  if (sides[0] == sides[1]){
    if(sides[0] == sides[2])
      sideType = "equialateral\0";
    else
      sideType = "isosceles\0";
  }
  else if (sides[0] == sides[2])
    sideType = "isosceles\0";
  else if (sides[1] == sides[2])
    sideType = "isosceles\0";
  else 
    sideType = "scalene\0";
}

void checkAngles(long points[]){
  long dotPoints[4];
  dotPoints[0] = points[2]-points[0];
  dotPoints[1] = points[3]-points[1];
  dotPoints[2] = points[4]-points[0];
  dotPoints[3] = points[5]-points[1];
  /* calculate the dot product of two lines*/
  long dot = dotPoints[0]*dotPoints[2]+dotPoints[1]*dotPoints[3];
  if (dot == 0){
    angleType = "right\0";
    return;
  }
  else if (dot < 0){
    angleType = "obtuse\0";
  }
  else {
    /* Assert that the dot product is greater than zero to make sure the previous angled measured as acute */
    assert(dot > 0);
    dotPoints[0] = points[0]-points[2];
    dotPoints[1] = points[1]-points[3];
    dotPoints[2] = points[4]-points[2];
    dotPoints[3] = points[5]-points[3];
    // The first angle is actue but one of the other could be right or obtuse
    dot = dotPoints[0]*dotPoints[2]+dotPoints[1]*dotPoints[3];   
    if (dot == 0){
      angleType = "right\0";
      return;
    }
    else if (dot < 0){
      angleType = "obtuse\0";
    }
    else {
    /* Assert that the dot product is greater than zero to make sure the previous angled measured as acute */
      assert(dot > 0);
      dotPoints[0] = points[0]-points[4];
      dotPoints[1] = points[1]-points[5];
      dotPoints[2] = points[2]-points[4];
      dotPoints[3] = points[3]-points[5];
      // The second angle is actue but the third could be right or obtuse
      dot = dotPoints[0]*dotPoints[2]+dotPoints[1]*dotPoints[3];
      if (dot == 0){
        angleType = "right\0";
        return;
      }
      else if (dot < 0){
        angleType = "obtuse\0";
      }
      else {
        angleType = "acute\0";
      }
    }
  }
}

int main (int argc, char **argv){

  long points[6];
  long long lengths[3];
  char *endptr;
 
  if (argc != 7) {
    printf("error\n");
    exit(0);
  }
  else{
    int i;
    for(i = 1; i < argc; i++){
      points[i-1] = strtol(argv[i], &endptr, 10);
      if(*endptr != '\0' || valid(points[i-1])){
          printf("error\n");
          exit(0);
        }
      /* Assert that the whole string was converted to a long */
      assert(*endptr == '\0');
      }
    }
  checkPoints(points);	
  lengths[0] = sideLen(points[0], points[1], points[2], points[3]);
  lengths[1] = sideLen(points[0], points[1], points[4], points[5]);
  lengths[2] = sideLen(points[2], points[3], points[4], points[5]);
  checkSides(lengths);
  printf("%s %s\n", sideType, angleType);
}

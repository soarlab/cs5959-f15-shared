#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Pre-declarations of methods */
double sideLen (int x1, int y1, int x2, int y2);
void checkPoints(int points[]);
void checkSides(double sides[]);
void checkAngles(int points[]);

/*Global Variables */
char* sideType;
char* angleType;
int rightTriangle;

/* Compute a side of the triangle 
* Should always return a postive length */
double sideLen (int x1, int y1, int x2, int y2){
  double a = x1 - x2;
  double b = y1 - y2;
  a = a*a;
  b = b*b;
  double c = sqrt(a+b);
  return c;
}

/* Check that the points aren't on the same line */
void checkPoints(int points[]){
  if (points[0] == points[2] && points[0] == points[4]){
    printf("not a triangle\n");
    exit(0);
  }
  if (points[1] == points[3] && points[1] == points[5]){
    printf("not a triangle\n");
    exit(0);
  }
  checkAngles(points);
}

/* Check the side lengths for patterns that will classify them.*/
void checkSides(double sides[]){
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

void checkAngles(int points[]){
  int i, j;
  int dotPoints[4];
  dotPoints[0] = points[2]-points[0];
  dotPoints[1] = points[3]-points[1];
  dotPoints[2] = points[4]-points[0];
  dotPoints[3] = points[5]-points[1];
  /* calculate the dot product of two lines*/
  int dot = dotPoints[0]*dotPoints[2]+dotPoints[1]*dotPoints[3];
  if (dot == 0){
    angleType = "right\0";
    return;
  }
  else if (dot < 0){
    angleType = "obtuse\0";
  }
  else {
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

  int points[6];
  double lengths[3]; 
  if (argc == 1 || argc != 7) {
    printf("HERE error\n");
    exit(0);
  }
  else{
    int i;
    for(i = 1; i < argc; i++){
      points[i-1] = atoi(argv[i]);
      if(points[i-1] == 0){
        char* possibleE = argv[i];
        if((*possibleE != '0')){
          printf("error\n");
          exit(0);
        }
      }
    }
    checkPoints(points);	
  }
  lengths[0] = sideLen(points[0], points[1], points[2], points[3]);
  lengths[1] = sideLen(points[0], points[1], points[4], points[5]);
  lengths[2] = sideLen(points[2], points[3], points[4], points[5]);
  checkSides(lengths);
  printf("%s %s\n", sideType, angleType);
}

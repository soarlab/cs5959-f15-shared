#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

/*note extra space after type of triangle to match regex
and new line after angles and errors;*/
#define EQUILATERAL "equilateral "
#define ISOSCELES "isosceles "
#define SCALENE "scalene "
#define ACUTE "acute\n"
#define OBTUSE "obtuse\n"
#define RIGHT "right\n"
#define ERROR "error\n"
#define NOT_A_TRIANGLE "not a triangle\n"

#define MAX 1073741823
#define MIN -1073741823

typedef struct{
  long int x;
  long int y;
}Point;

typedef struct{
  long int a;
  long int b;
  long int c;
}Triangle;

long int findSide(Point p1, Point p2);
long convert(char *arg);
int testColinear(Point p1, Point p2, Point p3);
void printTriangleType(Triangle t);
void printAngle(Triangle t);
int compare (const void * a, const void * b);
int checkOverflow(long int a, long int b);

int main(int argc, char *argv[]){
  Point p1;
  Point p2;
  Point p3;
  Triangle t;

  if(argc != 7){/*7*/
    printf(ERROR);
    exit(0);
  }
 
  /* get points from command line */
  p1.x = convert(argv[1]); /*1*/ 
  p1.y = convert(argv[2]); /*2*/
  
  p2.x = convert(argv[3]); /*3*/
  p2.y = convert(argv[4]); /*4*/

  p3.x = convert(argv[5]); /*5*/
  p3.y = convert(argv[6]); /*6*/
  
  if(testColinear(p1, p2, p3)){
    printf(NOT_A_TRIANGLE);
    exit(0);
  }

  /*calculate length of sides */
  t.a = findSide(p1, p2);
  t.b = findSide(p1, p3);
  t.c = findSide(p2, p3);

  printTriangleType(t);
  printAngle(t);

  exit(0);

}

long convert(char *arg){
  char *end = "\0";
  long l;
  errno = 0;
  l = strtol(arg, &end, 10);
  if(errno || strcmp(end, "\0")){
    printf(ERROR);
    exit(0);
  } else if(l > MAX || l < MIN){
    printf(ERROR);
    exit(0);
  }
  return l;
}

long int findSide(Point p1, Point p2){
  return  ((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y));
}

int testColinear(Point p1, Point p2, Point p3){
  if((p2.y - p1.y) * (p3.x - p2.x) == (p3.y - p2.y) * (p2.x - p1.x)){
    return 1;
  } else{
    return 0;
  }
}

void printTriangleType(Triangle t){
  if((t.a == t.b) == t.c){
    printf(EQUILATERAL);
  } else if(t.a == t.b || t.a == t.c || t.b == t.c){
    printf(ISOSCELES);
  } else{
    printf(SCALENE);
  }
}

void printAngle(Triangle t){
  long int side[3];
  side[0] = t.a;
  side[1] = t.b;
  side[2] = t.c;
  qsort(side, 3, sizeof(long int), compare);

  if((side[0] + side[1]) == (side[2])){
    printf(RIGHT);    
  } else if((side[2]) > (side[0] + side[1])){
    printf(OBTUSE);
  } else{
    printf(ACUTE);
  }
}

int checkOverflow(long int a, long int b){
  if ((b > 0 && a > LONG_MAX - b) || (b < 0 && a < LONG_MIN - b)){
    return 1;
  } else{
    return 0;
  }

}

int compare (const void * a, const void * b){
  long int x = *(long int*)a;
  long int y = *(long int*)b;

  if(x == y){
    return 0;
  }else if (x < y){
    return -1;
  }else{
    return 1;
  }
}

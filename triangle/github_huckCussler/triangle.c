#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>
#ifndef M_PI
#define M_PI acos(-1.0)
#endif

static const double e = .000000001; /* 8 zeros */

typedef struct{
  long x;
  long y;
} point;

/*struct point *points;*/

void print_error_and_exit(void){
  printf("error\n");
  exit(EXIT_FAILURE);
}

void find_sides(point *pees, double *esses){
  esses[0] = sqrt(pow((pees[1].x - pees[0].x), 2) + pow((pees[1].y - pees[0].y), 2));
  esses[1] = sqrt((double)(pow((pees[2].x - pees[1].x), 2) + pow((pees[2].y - pees[1].y), 2)));
  esses[2] = sqrt((double)(pow((pees[2].x - pees[0].x), 2) + pow((pees[2].y - pees[0].y), 2)));
}

void put_longest_in_middle(double *sides){
  double tmp;

  if(sides[0] > sides[1]){
    tmp = sides[0];
    sides[0] = sides[1];
    sides[1] = tmp;
  }

  if(sides[2] > sides[1]){
    tmp = sides[2];
    sides[2] = sides[1];
    sides[1] = tmp;
  }
}

int main(int argc, char *argv[]){
  int i, j;
  point *points;
  char *str, *endptr;
  long x, y;
  double *sides, angle;

  points = (point *)malloc(sizeof(point)*6);
  sides = (double *)malloc(sizeof(double)*3);
  /*angles = (double *)malloc(sizeof(double)*3);*/

  /* there should be six args */
  if(argc < 7)               /*fprintf(stderr, "Usage: %s x1 y1 x2 y2 x3 y3\n", argv[0]);*/
    print_error_and_exit();

  /* each arg should be an integer */
  for(i=1; i<7; i++){
    j = i / 2;
    str = argv[i++];

    x = strtol(str, &endptr, 10);
    if(errno != 0 && x == 0) /*perror("strtol");*/
      print_error_and_exit();
    if(endptr == str)        /*fprintf(stderr, "No digits were found\n");*/
      print_error_and_exit();
    str = argv[i];

    y = strtol(str, &endptr, 10);
    if(errno != 0 && y == 0) /*perror("strtol");*/
      print_error_and_exit();
    if(endptr == str)        /*fprintf(stderr, "No digits were found\n");*/
      print_error_and_exit();

    points[j].x = x;
    points[j].y = y;
  }
  
  /* foreach arg: -(2^30-1) <= arg <= 2^30-1 */
  for(i=0; i<3; i++)
    if(points[i].x < (-(pow(2, 30) - 1)) || points[i].x > (pow(2, 30) - 1)
       || points[i].y < (-(pow(2, 30) - 1)) || points[i].y > (pow(2, 30) - 1))
      /*fprintf(stderr, "All coordinates must be >= -(2^30-1) and <= 2^30-1\n");*/
      print_error_and_exit();
  
  /* find sides*/
  find_sides(points, sides);

  /* reorder so largest side is at index 1 */
  put_longest_in_middle(sides);

  /* use cosine rule to find largest angle*/
  /* cosine rule:*/
  /*   Let B be the largest angle and*/
  /*   a,b,c be the side lengths*/
  /*   with b the longest, then*/
  /*   B = cos^(-1)((a^2 + c^2 - b^2) / 2ac)*/  
  angle = acos((pow(sides[0], 2) + pow(sides[2], 2) - pow(sides[1], 2)) /
		   (2 * sides[0] * sides[2]));

  /* DEBUGGERY */
  /*for(i=0; i<3; i++)
    printf("sides[%d] is %f\n", i, sides[i]);
  printf("angle is %f\n", angle);
  printf("M_PI is %f\n", M_PI);
  printf("M_PI / 2 is %f\n", M_PI / 2);
  printf("fabs(M_PI / 2 - angle) is %f\n", fabs(M_PI / 2 - angle));
  printf("M_PI / 2 - angle is %f\n", M_PI / 2 - angle);
  printf("fabs(sides[0] - sides[2]) is %f\n", fabs(sides[0] - sides[2]));*/
  /* DEBUGGERY */
  
  /*if largest angle == 180 then not a triangle */
  if(fabs(M_PI - angle) < e){
    printf("not a triangle\n");
    return 0;
  }

  /* scalene || isosceles || equilateral (impossible) */
  if(fabs(sides[1] - sides[0]) < e || fabs(sides[2] - sides[0]) < e || fabs(sides[2] - sides[1]) < e)
    printf("isosceles ");
  else
    printf("scalene ");

  /* acute || obtuse || right */
  if(fabs(M_PI / 2 - angle) < e)
    printf("right\n");
  else if(angle < M_PI / 2)
    printf("acute\n");
  else
    printf("obtuse\n");
}

/*******************************************************************************************
 * AUTHOR :     Taylor Wilson
 * UID :        U0323893
 *
 * DATE :       September 26, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 */

#include <stdio.h>  /* standard sys calls */
#include <stdlib.h> /* random generator */
#include <time.h>   /* time */

void write_bytes(FILE *fp, long seed, long size) {
  char str[size];
  int i, r;
  
  printf("Random seed for base = %ld \n", seed);
  srand(seed);
  
  /* write MAX random bytes to the file */
  /* ASCII characters from 'SPACE' to '~' */
  for (i = 0; i < size; i++) {
    r = rand() % 32 + 94; 
    str[i] = r;
  }
  fwrite(str, 1, sizeof(str), fp);
}

int main(int argc, char *argv[]) {
  long seed = strtol(argv[1], NULL, 10);
  long max  = strtol(argv[2], NULL, 10);

  FILE *fp = fopen("base.txt", "w+");
  if (fp) {
    write_bytes(fp, seed, max);
    fclose(fp);
  } else {
    printf("Oh darn! It looks like fopen failed. \n");
  }

  return 0;
}
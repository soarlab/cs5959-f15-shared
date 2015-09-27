/*******************************************************************************************
 * AUTHOR :     Taylor Wilson
 * UID :        U0323893
 *
 * DATE :       September 26, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 */

#include <stdlib.h> /* strtonum */
#include <stdio.h>  /* standard sys calls */
#include <stdlib.h> /* random generator */
#include <time.h>   /* time */

void fuzz(FILE *fp1, long size, long index) {
  time_t now;
  // size_t bytes_read;
  char buffer[size];

  // bytes_read = fread(buffer, sizeof(buffer), 1, fp);
  fread(buffer, sizeof(buffer), 1, fp1);

  now = time(NULL);
  printf("Random seed for fuzz = %ld \n", (long)((double)now));
  srand(now);
  // r = rand() % sizeof(buffer);

  buffer[index] = rand() % 32 + 94;
  
  FILE *fp2 = fopen("fuzz.txt", "w+");
  if (fp2) {
    fwrite(buffer, 1, sizeof(buffer), fp2);
  } else {
    printf("Oh darn! It looks like the fuzzer won't work. \n");
  }
}

int main(int argc, char *argv[]) {
  long size  = strtol(argv[1], NULL, 10);
  long index = strtol(argv[2], NULL, 10);

  FILE *fp = fopen("base.txt", "r");
  if (fp) {
    fuzz(fp, size, index);
  } else {
    printf("Oh darn! It looks like the baser didn't work. \n");
  }
}
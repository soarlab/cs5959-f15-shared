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

void fuzz(FILE *fp1, long seed, long size, long index) {
  // time_t now;
  char buffer[size];
  char temp;

  fread(buffer, sizeof(buffer), 1, fp1);

  // now = time(NULL);
  // printf("Random seed for fuzz = %ld \n", (long)((double)now));
  printf("Random seed for fuzz = %ld \n", seed);
  srand(seed);
  // srand(now);

  /* check to make sure the new random byte isn't the same as the old one */
  do {
    temp = rand() % 32 + 94;
  } while (temp == buffer[index]);
  buffer[index] = temp;

  FILE *fp2 = fopen("fuzz.txt", "w+");
  if (fp2) {
    fwrite(buffer, 1, sizeof(buffer), fp2);
  } else {
    printf("Oh darn! It looks like the fuzzer won't work. \n");
  }
}

int main(int argc, char *argv[]) {
  long seed  = strtol(argv[1], NULL, 10);
  long size  = strtol(argv[2], NULL, 10);
  long index = strtol(argv[3], NULL, 10);

  FILE *fp = fopen("base.txt", "r");
  if (fp) {
    fuzz(fp, seed, size, index);
  } else {
    printf("Oh darn! It looks like the baser didn't work. \n");
  }
}
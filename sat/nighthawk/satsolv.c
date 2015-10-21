/* satsolv.c - A simple SAT solver.
 * 
 * <Authors>: Dalton Wallace, Jonathan Whitaker, Jay Tuckett, Tarik Courdy
 */

/* Includes */
#include <stdio.h>

/* Definitions */
#define SATISFIABLE 0
#define UNSATISFIABLE 1
#define UNKNOWN 2
#define ERROR 3
#define DEBUG 1

int main(int argc, char **argv)
{
    /* if an incorrect number of arguments was supplied, simply
       print an error and return. */
    if (argc != 2) {
        printf("ERROR\n");
        return 0;
    }

    /* attempt to open the file containing the logic formula */
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        if (DEBUG)
            fprintf(stderr, "Can't open input file '%s'!\n", argv[1]);

        printf("ERROR\n");
        return 0;
    }

    return 0;
}

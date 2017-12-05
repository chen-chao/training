#include <stdio.h>
#include <time.h>
#define MAXLINES 5000
#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines);
int readlines_all(char alllines[][MAXLEN], int maxlines);

int main(){
    int nlines;
    char alllines[MAXLINES][MAXLEN];
    clock_t start = clock();
    nlines = readlines_all(alllines, MAXLINES);
    printf("Ellapsed time is %ju for reading %d lines.\n", (clock()-start), nlines);

    char *lineptr[MAXLINES];
    start = clock();
    nlines = readlines(lineptr, MAXLINES);
    printf("Ellapsed time is %ju for reading %d lines.\n", (clock()-start), nlines);
    return 0;
}

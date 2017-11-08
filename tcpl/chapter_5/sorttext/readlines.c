#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

char *alloc(int);

int getline(char *line, int maxlen){
    int c;
    char *start = line;
    for (; maxlen>1 && (c=getchar()) != EOF && c != '\n'; --maxlen)
        *line++ = c;
    if (c == '\n')
        *line++ = '\n';
    *line = '\0';
    return line-start;
}

int readlines(char *lineptr[], int maxlines){
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = getline(line, MAXLEN))){
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* array form is not compatible with writelines and qsort.
 * this form is slower than the original, don't know why now*/
int readlines_all(char lineptr[][MAXLEN], int maxlines) {
    char line[MAXLEN];
    int len;
    int nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines)
            return -1;
        strcpy(&lineptr[nlines++][0], line);
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines){
    while (nlines-- > 0){
        printf("%s\n", *lineptr++);
    }
}
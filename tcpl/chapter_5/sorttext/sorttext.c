#include <stdio.h>
#include <string.h>
#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void quicksort(void *v[], int left, int right, int (*comp)(void *, void *), int ascend);
int numcmp(const char *s1, const char *s2);
int nocasecmp(const char *s1, const char *s2);
int dictcmp(const char *s1, const char *s2);
int nocasedictcmp(const char *s1, const char *s2);


int main(int argc, char *argv[]){
    int nlines;
    /* 1 for numeric, 2 for nocase, 4 for directory */
    int option = 0;
    int ascend = 1;
    int c;
    while(--argc > 0 && (*++argv)[0] == '-'){
            while ((c = *++argv[0])){
                    switch(c){
                    case 'n':
                            option += 1;
                            break;
                    case 'r':
                            ascend = 0;
                            break;
                    case 'f':
                            option += 2;
                            break;
                    case 'd':
                            option += 4;
                            break;
                    default:
                            argc = -1;
                            printf("error: unknow option %c\n", c);
                            break;
                    }
            }
    }
    if (argc < 0) {
            return -1;
    }
    int (*comp) (void *, void *);
    switch (option){
    case 0:
            comp = (int (*) (void *, void *)) strcmp;
            break;
    case 1:
            comp = (int (*) (void *, void *)) numcmp;
            break;
    case 2:
            comp = (int (*) (void *, void *)) nocasecmp;
            break;
    case 4:
            comp = (int (*) (void *, void *)) dictcmp;
            break;
    case 6:
            comp = (int (*) (void *, void *)) nocasedictcmp;
            break;
    default:
            printf("error: invalid comparation method\n");
            break;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
            quicksort((void **)lineptr, 0, nlines-1, comp, ascend);
            writelines(lineptr, nlines);
            return 0;
    } else {
            printf("error: input too big to sort\n");
            return 1;
    }
}

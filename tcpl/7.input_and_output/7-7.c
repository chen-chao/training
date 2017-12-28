/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 7.07 on page 165. Modify the pattern finding program of
 * Chapter 5 to take its input from a set of named files or, if no
 * files are named as arguments, from the standard input. Should the
 * file name be printed when a matching line is found? */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[]) {
    FILE *f;
    int c, number = 0, except = 0, found = 0;
    long lino = 0;
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'n':
                number = 1;
                break;
            case 'x':
                except = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
        }
    }

    char *pattern, *fname;
    if (argc < 1) {
        printf("Usage find [-x] [-n] pattern [FILES]\n");
    } else {
        pattern = *(argv++);
        argc--;
    }
    if (argc == 0) {
        f = stdin;
    } 

    char line[MAXLINE];
    do {
        // printf("argc: %d\n", argc);
        if (argc-- > 0){
            if ((f = fopen(fname=*(argv++), "r")) == NULL) {
                fprintf(stderr, "Error when opening file %s\n", fname);
            } else {
                printf("%s:\n", fname);
            }
        }
        if (f != NULL) {
            while (fgets(line, MAXLINE, f) != NULL) {
                lino++;
                if ((strstr(line, pattern) != NULL) != except) {
                    found++;
                    if (number)
                        printf("%ld: ", lino);
                    printf("%s", line);
                }
            }
        }
    } while (argc > 0);
    return found;
}

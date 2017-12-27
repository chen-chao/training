/* print the first different line of two file */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void print_differ_line(FILE *f1, FILE *f2){
    char *res1, *res2;
    char line1[MAXLINE];
    char line2[MAXLINE];
    do {
        res1 = fgets(line1, MAXLINE, f1);
        res2 = fgets(line2, MAXLINE, f2);
    } while (res1 != NULL && res2 != NULL && strcmp(line1, line2) == 0);

    if (! (res1 == NULL && res2 == NULL)) {
        printf("differ line is: \n%s%s", line1, line2);
    }
}

int main(int argc, char *argv[]){
    if (argc != 3) {
        printf("Please give two files.\n");
        return -1;
    }

    FILE *f1, *f2;
    if ((f1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: Can not open %s\n", argv[0], argv[1]);
        return -1;
    }
    
    if ((f2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "%s: Can not open %s\n", argv[0], argv[2]);
        return -1;
    } 

    print_differ_line(f1, f2);
    fclose(f1);
    fclose(f2);
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", argv[0]);
    }
    return 0;
}
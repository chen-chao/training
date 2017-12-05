#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINES 1000

int main(int argc, char *argv[]){
        int number = 10;
        /* using cyclic can reduce the array size to number */
        char *lines[MAXLINES];

        if (argc > 2){
                if (strcmp(*++argv, "-n")==0){
                        char *pos = *++argv;
                        for (; isdigit(*pos); pos++)
                                ;
                        if (*pos != '\0')
                                printf("unknown value: %s\n", *argv);
                        else
                                number = atoi(*argv);
                } else {
                        printf("unknow option: %s\n", *argv);
                }
        }

        ssize_t lim;
        int nline = 0;
        size_t MAXLEN = 1000;
        while ((lim = getline(&lines[nline], &MAXLEN, stdin)) != EOF)
                nline++;
        for (int i=nline-number; i<nline; i++)
                printf("%s", lines[i]);

        return 0;
}

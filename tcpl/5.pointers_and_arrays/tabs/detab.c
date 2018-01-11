#include <stdio.h>
#include <stdlib.h>


#define MAXLEN 30

int detab(int *tabpos, int maxlen);

int main(int argc, char *argv[]){
    int tabpos[MAXLEN], start, width = 0, i = 0;
    if (argc == 1) {
        start = 8;
        width = 8;
                      }

    while (--argc > 0) {
        switch ((*++argv)[0]) {
        case '-':
            start = atoi(++argv[0]);
            break;
        case '+':
            width = atoi(++argv[0]);
            break;
        default:
            tabpos[i++] = atoi(*argv);
            break;
        }
    }

    if (i == 0) {
        start = start == 0 ? 8 : start;
        width = width == 0 ? 8 : width;
    }
    
    if (width != 0)
        for (i = 0; i < MAXLEN; i++)
            tabpos[i] = start + width*i;

    int status;
    while ((status = detab(tabpos, MAXLEN)) == 0)
        ;
    return status;
}

int detab(int *tabpos, int len){
    int c, ind = 0, col = 0;
    while ((c = getchar()) != EOF){
        col++;
        if (c == '\t') {
            for (; tabpos[ind] < col && ind < len; ind++)
                ;
            if (ind == len)
                return -2;
            for (putchar(' '); col < tabpos[ind]; col++)
                putchar(' ');
        } else {
            putchar(c);
        }
    }
    return (c == EOF) ? -1 : 0;
}

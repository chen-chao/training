#include <stdio.h>
#include <stdlib.h>


int detab(int *tabpos);

int main(int argc, char *argv[]){
        int tabpos[] = {8, 16, 24, 32, 40, 48, 56, 64, 72,
                        80, 88, 96, 104, 112, 120, 128, 136};

        if (argc != 1){
                for (int i = 0; i < argc-1; i++)
                        tabpos[i] = atoi(argv[i+1]);
        }

        int status;
        while (1) {
                status = detab(tabpos);
                if (status != 0)
                        return -1;
        }
}

int detab(int *tabpos){
        int c, tabind = 0, col = 0;
        while ((c = getchar()) != EOF){
                if (c == '\t') {
                        for (; tabpos[tabind]<col; tabind++)
                                ;
                        /* should tab actually occupy a position? */
                        for (; col<tabpos[tabind]; col++)
                                putchar(' ');
                } else {
                        putchar(c);
                        col++;
                }
        }
        return (c == EOF) ? -1 : 0;
}

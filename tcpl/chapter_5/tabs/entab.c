#include <stdio.h>
#include <stdlib.h>


int entab(int *tabpos);

int main(int argc, char *argv[]){
        int tabpos[] = {8, 16, 24, 32, 40, 48, 56, 64, 72,
                        80, 88, 96, 104, 112, 120, 128, 136};

        if (argc != 1){
                for (int i = 0; i < argc-1; i++)
                        tabpos[i] = atoi(argv[i+1]);
        }

        int status;
        while (1) {
                status = entab(tabpos);
                if (status != 0)
                        return -1;
        }
}

int entab(int *tabpos){
        int lastc, c, ind = 0, col = 0, spacenum = 0;
        while ((c = getchar()) != EOF){
                if (c == ' ') {
                        for (; tabpos[ind]<col; ind++)
                                ;
                        if (col == tabpos[ind]){
                                putchar('\t');
                                /* putchar('t'); */
                                spacenum = 0;
                        }
                        spacenum++;
                } else {
                        if (lastc == ' ')
                                for (int i=0; i<spacenum; i++)
                                        putchar(' ');
                        spacenum = 0;
                        putchar(c);
                }
                lastc = c;
                col++;
        }
        return (c == EOF) ? -1 : 0;
}


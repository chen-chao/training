#include <stdio.h>

#define MAXLEN 1000

static int buffer[MAXLEN];
static int buffp = 0;

int getch(void){
        if (buffp > 0){
                return buffer[--buffp];
        } else {
                return getchar();
        }
}

void ungetch(int c){
        if (buffp > MAXLEN){
                printf("error: buffer is full.\n");
        } else {
                buffer[buffp++] = c;
        }
}

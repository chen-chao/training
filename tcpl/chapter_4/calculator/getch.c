/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 4.08 on page 79. Suppose there will never be more than one
 * character of pushback. Modify getch and ungetch accordingly. */

#include <stdio.h>
#include <string.h>

#define BUFSIZE 1


char buf[BUFSIZE];
int bufp = 0;

int getch(void){
        return (bufp > 0)? buf[--bufp] : getchar();
}

void ungetch(int c){
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}

void ungets(char s[]){
        for (int pos = strlen(s)-1; pos>=0; pos--)
                ungetch(s[pos]);
}

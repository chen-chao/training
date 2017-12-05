/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 4.08 on page 79. Suppose there will never be more than one
 * character of pushback. Modify getch and ungetch accordingly. */


#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

/* This is the exact menonsahab's answer from
 http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_9

 The reason why the code in K&R can't handle EOF is because it is
 defined as follows: #define EOF -1 i.e. its value is negative and a
 char array can't hold a negative value.  Change the buffer type to
 int and the problem is solved. */

int buf[BUFSIZE];
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

/* This is from
http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_7

There are a few situations wherein ungets() using ungetch() may cause
a problem.  It is because ungets() doesn't do any bounds checking. If
I have a string of length one million and one and the available space
in buf[] is only one million, then only after copying the first one
million characters will I come to know that there isn't any space for
the last character and depending upon the situation I might have to
undo the entire process. So ungets() must do its own bounds checking
for which it will require access to both buf[] and bufp.  Notice that
if you provide ungets() with access to buf[] and bufp, the whole idea
of using ungetch() becomes moot.  I'll still use it for brevity.*/

void ungets(char s[]){
        for (int pos = strlen(s)-1; pos>=0; pos--)
                ungetch(s[pos]);
}

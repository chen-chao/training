#include <stdio.h>
#include <ctype.h>
#include "calc.h"


/* get the next operator or number */
int getop(char s[]){
        int i;
        static int c;

        while ( c == '\0' || (s[0] = c) == ' ' || c == '\t')
                c = getchar();

        s[1] = '\0';
        i = 0;

        if (c == '+' || c == '-'){
                c = getchar();
                if (!isdigit(c)){
                        return s[0];
                } else {
                        s[++i] = c;
                }
        } else if (isalpha(c)){
                while (isalnum(s[++i] = c = getchar()))
                        ;
                s[i] = '\0';
                return VARFUNC;

        } else if (!isdigit(c) && c != '.'){
                /* not a number, since no extra character is read,
                 * clear static c for next reading */
                c = '\0';
                return s[0]; 
        }

        while (isdigit(s[++i] = c = getchar()))
                        ;
        if (c == '.')
                while (isdigit(s[++i] = c = getchar()))
                        ;
        s[i] = '\0';

        return NUMBER;
}

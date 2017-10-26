#include <stdio.h>
#include <ctype.h>
#include "calc.h"


int getch(void);
void ungetch(int);


/* get the next operator or number */
int getop(char s[]){
        int i, c;

        while ((s[0] = c = getch()) == ' ' || c =='\t')
                ;
        s[1] = '\0';
        i = 0;

        if (c == '+' || c == '-'){
                c = getch();
                if (!isdigit(c)){
                        ungetch(c);
                        return s[0];
                } else {
                        s[++i] = c;
                }
        } else if (isalpha(c)){
                while (isalnum(s[++i] = c = getch()))
                        ;
                s[i] = '\0';
                if (c != EOF)
                        ungetch(c);

                return VARFUNC;
                
        } else if (!isdigit(c) && c != '.'){
                return c;       /* not a number */
        }

        while (isdigit(s[++i] = c = getch()))
                        ;
        if (c == '.')
                while (isdigit(s[++i] = c = getch()))
                        ;
        s[i] = '\0';
        if (c != EOF)
                ungetch(c);

        return NUMBER;
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

#define FUNCNUM 9
const char *funclist[FUNCNUM] = {"sin", "cos", "tan", "exp", "log", "log10", "pow", "sqrt", "fabs"};


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
                if (i > 1) {
                        int pos;
                        for (pos=0; pos<FUNCNUM && strncmp(s, funclist[pos], i-1)!=0; pos++)
                                ;
                        if (pos < FUNCNUM){
                                ungetch(c);
                                return pos+1;
                        }
                }
                ungetch(c);
                return UNKNOWN_FUNC;
                
        } else if (!isdigit(c) && c != '.'){
                return c;       /* not a number */
        }

        if (isdigit(c))
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

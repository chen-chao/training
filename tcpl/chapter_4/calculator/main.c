#include <stdio.h>
#include <stdlib.h>             /* atof */
#include "calc.h"


#define MAXOP 100


int getop(char []);
void push(double);
double pop(void);


/* reverse polish notation */

int main(){
        int type;
        double op2;
        long long_op2;
        char s[MAXOP];

        while ((type = getop(s)) != EOF) {
                switch (type) {
                case NUMBER:
                        push(atof(s));
                        break;
                case '+':
                        push(pop()+pop());
                        break;
                case '*':
                        push(pop()*pop());
                        break;
                case '-':
                        op2 = pop();
                        push(pop()-op2);
                        break;
                case '/':
                        op2 = pop();
                        if (op2 != 0.0)
                                push(pop()/op2);
                        else
                                printf("error: zero divisor\n");
                        break;
                case '%':
                        long_op2 = (long) pop();
                        if (op2 != 0)
                                push(((long) pop()) % long_op2);
                        else
                                printf("error: zero divisor\n");
                        break;
                case '\n':
                        printf("\t%.8g\n", pop());
                        break;
                default:
                        printf("error: unknown command %s \n", s);
                        break;
                }
        }
        return 0;
}


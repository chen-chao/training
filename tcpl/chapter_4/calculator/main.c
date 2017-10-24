#include <stdio.h>
#include <stdlib.h>             /* to use atof */
#include <math.h>               /* to use sin cos pow, etc */
#include <string.h>             /* to use strcmp */
#include "calc.h"

#define FUNCNUM 12
#define MAXOP 100

const char *funclist[FUNCNUM] = {"set", "sin", "cos", "tan", "exp", "log",
                                 "log10", "pow", "sqrt", "fabs", "unset", "res"};
double res = 0.;

int getop(char []);
void push(double);
double pop(void);


/* reverse polish notation */

int main(){
        size_t len;
        int pos, type;
        double op1, op2;
        long long_op2;
        char s[MAXOP];
        char var;

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
                        if (long_op2 != 0)
                                push(((long) pop()) % long_op2);
                        else
                                printf("error: zero divisor\n");
                        break;
                case VARFUNC:
                        len = strlen(s);
                        if (len == 1){
                                var = s[0];
                                push(get_var(var));

                                break;
                        }

                        for (pos=0; pos<FUNCNUM && strcmp(s, funclist[pos])!=0; pos++)
                                ;

                        switch (pos) {
                        case 0:
                                set_var(var, pop());
                                pop(); /* already push original variable value to stack before set_var */
                                break;
                        case 1:
                                push(sin(pop()));
                                break;
                        case 2:
                                push(cos(pop()));
                                break;
                        case 3:
                                push(tan(pop()));
                                break;
                        case 4:
                                push(exp(pop()));
                                break;
                        case 5:
                                push(log(pop()));
                                break;
                        case 6:
                                push(log10(pop()));
                                break;
                        case 7:
                                op2 = pop();
                                op1 = pop();
                                if (op1 == 0 && op2 <= 0 ){
                                        printf("error: zero base with negative index\n");
                                } else if (op1 < 0 && (int) op2 != op2){
                                        printf("error: negative base with double index\n");
                                } else  {
                                        push(pow(op1, op2));
                                }
                                break;
                        case 8:
                                op2 = pop();
                                if (op2 >= 0)
                                        push(sqrt(pop()));
                                else
                                        printf("error: negative double to get square root.");
                                break;
                        case 9:
                                push(fabs(pop()));
                                break;
                        case 10:
                                unset_var(var);
                                break;
                        case 11:
                                push(res);
                                break;
                        default:
                                printf("error: unknow function %s \n", s);
                                break;
                        }
                        break;

                case '\n':
                        printf("\t%.8g\n", res=pop());
                        break;
                default:
                        printf("error: unknown command %s \n", s);
                        break;
                }
        }
        return 0;
}


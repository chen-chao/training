#include <stdio.h>
#include <stdlib.h>             /* to use atof */
#include <math.h>
#include <string.h>
#include <ctype.h>

#define NUMBER '0'
#define FUNCTION '1'
/* #define NAN '2'*/
/* NAN is already defined in math.h*/

void push(double);
double pop(void);
int getop(char *);

const char *funclist[] = {"sin", "cos", "expr", "log", "fabs", "pow", "sqrt"};
const int funcnum = 7;

int main(int argc, char *argv[]){
        int type, i;
        char *arg;
        double temp, temp2;
        while (--argc > 0){
                arg = *(++argv);
                type = getop(arg);
                switch(type) {
                case NUMBER:
                        push(atof(arg));
                        break;
                case '+':
                        push(pop()+pop());
                        break;
                case '-':
                        temp = pop();
                        push(pop()-temp);
                        break;
                case '*':
                        push(pop()*pop());
                        break;
                case '/':
                        temp = pop();
                        if (temp!=0) {
                                push(pop()/temp);
                        } else {
                                printf("error: zero divisor\n");
                                return -1;
                        }
                        break;
                case FUNCTION:
                        for (i=0; i<funcnum && strcmp(arg, funclist[i]) != 0; i++)
                                ;
                        switch(i){
                        case 0:
                                push(sin(pop()));
                                break;
                        case 1:
                                push(cos(pop()));
                                break;
                        case 2:
                                push(exp(pop()));
                                break;
                        case 3:
                                temp = pop();
                                if (temp > 0)
                                        push(log(temp));
                                else
                                        printf("error: negative value for log\n");
                                break;
                        case 4:
                                push(fabs(pop()));
                                break;
                        case 5:
                                temp = pop();
                                temp2 = pop();
                                if (temp == 0 && temp2 <= 0 ){
                                        printf("error: zero base with negative index\n");
                                } else if (temp < 0 && (int) temp2 != temp2){
                                        printf("error: negative base with double index\n");
                                } else  {
                                        push(pow(temp2, temp));
                                }
                                break;
                        case 6:
                                temp = pop();
                                if (temp >= 0)
                                        push(sqrt(temp));
                                else
                                        printf("error: negative value to get square root\n");
                                break;
                        default:
                                printf("error: unknown function %s\n", arg);
                                return -1;
                        }
                        break;
                default:
                        printf("error: unkonw operator %s\n", arg);
                        break;
                }
        }
        if (argc != 0)
                return -1;

        printf("%.8g\n", pop());
        return 0;
}


int getop(char *s){
        if (!isdigit(*s) && *(s+1) == '\0')
                return *s;
        
        if (*s == '+' || *s == '-'){
                s++;
        } else if (isalpha(*s)) {
                while (isalnum(*++s))
                        ;
                return (*s == '\0') ? FUNCTION : NAN;
        }
        /* former *s has not been checked */
        for (; isdigit(*s); s++)
                ;
        if (*s == '.')
                /* former *s=='.' must be excluded */
                while (isdigit(*++s))
                        ;
        return (*s == '\0') ? NUMBER : NAN;
}


#define MAXLEN 1000

static double buf[MAXLEN];
static int bufp = 0;

void push(double val){
        if (bufp < MAXLEN) {
                buf[bufp++] = val;
        } else {
                printf("error: statck is full\n");
        }
}

double pop() {
        if (bufp > 0){
                return buf[--bufp];
        }
        else{
                printf("error: stack is empty\n");
                return 0.;
        }
}

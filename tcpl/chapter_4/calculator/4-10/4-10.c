#include <stdio.h>
#include <ctype.h>              /* to use isdigit isalpha*/
#include <stdlib.h>               /* to use atof */
#include <string.h>               /* to use strlen strcmp */
#include <math.h>
#include "4-10.h"

#define MAXLEN 500
#define MAXOP 50
#define FUNCNUM 12

const char *funclist[FUNCNUM] = {"set", "sin", "cos", "tan", "exp", "log",
                                 "log10", "pow", "sqrt", "fabs", "unset", "res"};

char s[MAXLEN];
int pos = 0;
double res;


int getline(char s[], int lim){
        int i, c;
        for (i=0; (c=getchar()) != EOF && c != '\n' && lim>1; --lim)
                s[i++] = c;
        if (c == '\n')
                s[i++] = c;
        s[i] = '\0';
        return i;
} 

int getop(char val[]){
        int i, c;
        
        if (s[pos] == '\0')
                return -1;
        
        /* pos is always where we start to read s[MAXLEN] */
        while ((c=s[pos]) == ' ' || c == '\t')
                ++pos;

        val[0] = c;
        val[1] = '\0';
        i = 0;
        
        if (c == '+' || c == '-'){
                if (!isdigit(s[++pos])){
                        return c;
                } else {
                        val[++i] = s[pos];
                }
        } else if (isalpha(c)) {
                while (isalnum(val[++i] = s[++pos]))
                        ;
                val[i] = '\0';
                return VARFUNC;
        } else if (!isdigit(c) && c != '.'){
                ++pos;
                return c;
        }

        /* c is checked twice for number with sign like +12 or -12, need improvement? */
        while (isdigit(val[++i] = s[++pos]))
                ;
        if (val[i] == '.')
                while (isdigit(val[++i] = s[++pos]))
                        ;
        val[i] = '\0';
        return NUMBER;
}

int calc(){
        int varlen, linelen, type, i;
        double op1, op2;
        long long_op2;
        char val[MAXOP];
        char var;

        linelen = getline(s, MAXLEN);
        if (linelen < 1){
                 return -1;
        }
        
        while (pos < linelen){
                type = getop(val);
                switch (type) {
                case NUMBER:
                        push(atof(val));
                        break;
                case '+':
                        push(pop()+pop());
                        break;
                case '-':
                        op2 = pop();
                        push(pop()-op2);
                        break;
                case '*':
                        push(pop()*pop());
                        break;
                case '/':
                        op2 = pop();
                        if (op2 == 0)
                                printf("error: zero divisor\n");
                        else
                                push(pop()/op2);
                        break;
                case '%':
                        long_op2 = pop();
                        if (long_op2 != 0)
                                push(((long) pop()) % long_op2);
                        else
                                printf("error: zero divisor\n");
                        break;
                case VARFUNC:
                        varlen = strlen(val);
                        if (varlen == 1){
                                var = val[0];
                                push(get_var(var));
                                break;
                        }

                        for (i=0; i<FUNCNUM && strcmp(val, funclist[i]); i++)
                                ;
                        switch (i) {
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
                                printf("error: unknow function %s \n", val);
                                break;
                        }
                        break;
                case -1:
                case '\n':
                        printf("\t%.8g\n", res=pop());
                        break;
                default:
                        printf("error: unknown command %s \n", val);
                        break;
                }

                        
        }
        pos = 0;
        return 0;
}


int main(){
        int status;
        while (1) {
                status = calc();
                if (status != 0)
                        return 0;
        }
}



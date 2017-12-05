#include <stdio.h>

#define MAXVAL 100


int sp = 0;
double val[MAXVAL];

void push(double f){
        if (sp < MAXVAL)
                val[sp++] = f;
        else
                printf("error: stack full, can't push %g\n", f);
}


double pop(void){
        if (sp > 0){
                return val[--sp];
        } else {
                printf("error: stack empty\n");
                return 0.0;
        }
}

void print(void){
        if (sp > 0){
                printf("%.8g", val[sp-1]);
        } else {
                printf("error: stack empty\n");
        }
}

double copy(void){
        if (sp > 0){
                return val[sp-1];
        }
        else{
                printf("error: stack empty\n");
                return 0.0;
        }
}

void change(void){
        double tmp;
        if (sp > 1){
                tmp = val[sp-1];
                val[sp-1] = val[sp-2];
                val[sp-2] = tmp;
        } else if (sp < 1) {
                printf("error: stack empty\n");
        }
}

void clear(void){
        sp = 0;
}



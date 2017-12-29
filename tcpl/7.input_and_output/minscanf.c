/* 7-4, private version of scanf */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXCHARS 1000

int getch(void);
void ungetch(int);

int get_int() {
    int c, val = 0, sign;
    
    while (isspace(c = getch()))
        ;

    if (c == '-') {
        sign = -1;
        c = getch();
    } else if (c == '+') {
        sign = 1;
        c = getch();
    }

    while (isdigit(c)) {
        val = val*10 + c-'0';
        c = getch();
    }
    if (c != EOF)
        ungetch(c);
    
    return val*sign;
}

double get_float() {
    int c;
    double sign = 1.0, val = 0.0;
    while (isspace(c = getch()))
        ;
    if (c == '-') {
        sign = -1.0;
        c = getch();
    } else if (c == '+') {
        c = getch();
    }
    
    while (isdigit(c)) {
        val = val*10 + c-'0';
        c = getch();
    }
    double power = 1.;
    if (c == '.') {
        for (; isdigit(c = getch()); power*=10) {
            val =  val*10 + c-'0';
        }
    }

    val /= power;
    
    int index = 0, esign = 1;
    if (c == 'E' || c == 'e') {
        if ((c = getch()) == '-') {
            esign = -1;
            c = getch();
        } else if (c == '+') {
            c = getch();
        }

        while (isdigit(c)) {
            index = index*10 + c-'0';
            c = getch();
        }
    }

    if (c != EOF)
        ungetch(c);
    
    power = (esign == 1)? 10 : 0.1;
    for (; index > 0; index--) {
        val *= power;
    }
    
    return val*sign;
}


void get_str(char *s) {
    int c;
    while (isspace(c = getch()))
        ;
    for (; isalnum(*s = c); s++)
        c = getch();
    if (c != EOF)
        ungetch(c);
    *s = '\0';
}
    
int minscanf(char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);

    int vars = 0;
    int c, *ival;
    double *dval;
    char *sval, *p;
    for(p = fmt; *p; p++) {
        if (*p == ' ')
            continue;
        if (*p !=  '%'){
            while (isspace(c = getch()))
                ;
            if (c != *p){
                ungetch(c);
                return vars;
            }
            continue;
        }
        while (isspace(c = getch()))
            ;
        ungetch(c);
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int *);
            *ival = get_int();
            vars++;
            break;
        case 'f':
            dval = va_arg(ap, double *);
            *dval = get_float();
            vars++;
            break;
        case 's':
            sval = va_arg(ap, char *);
            get_str(sval);
            vars++;
            break;
        default:
            fprintf(stderr, "Unknown option %c\n", *p);
            break;
        }
    }
    va_end(ap);
    return vars;
}

int main() {
    int i;
    double d;
    char s[MAXCHARS];
    int vars = minscanf("here is %d bottles with tag %s price is %f.\n", &i, s, &d);
    printf("vars %d: %d, %s, %f\n", vars, i, s, d);
    return 0;
}

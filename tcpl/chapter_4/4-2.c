/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 4.02 on page 73. Extend atof to handle scientific notation
 * of the form 123.45e-6 where a floating-point number may be followed
 * by e or E and an optionally signed exponent. */


#include <stdio.h>
#include <ctype.h>

#define MAXLEN 100


double atof(char s[]);

int main(){
        char s[MAXLEN];
        char *res;
        while (1){
                printf("input a scientific notation: ");
                res = fgets(s, MAXLEN, stdin);
                if (res == NULL)
                        return 0;
                printf("your input is %12.6f\n", atof(s));
        }
}

double atof(char s[]){
        int i;
        double val = 0;
        for (i=0; isspace(s[i]); i++)
                ;

        double sign = 1;
        if (s[i] == '-'){
                sign = -1.;
                i++;
        } else if (s[i] == '+'){
                i++;
        }
        
        for (; isdigit(s[i]); i++){
                val = val*10 + s[i]-'0';
        }
        if (s[i] == '.')
                i++;
        
        double power = 1;
        for (; isdigit(s[i]); i++){
                val = val*10 + s[i]-'0';
                power *= 10;
        }
        val /= power;
        
        if (s[i] == 'e' || s[i] == 'E')
                i++;

        double exp_sign = 1;
        if (s[i] == '-'){
                exp_sign = -1.;
                i++;
        } else if (s[i] == '+'){
                i++;
        }

        double index = 0;
        for (; isdigit(s[i]); i++){
                index = index*10 + s[i]-'0';
        }

        /* This form may be better:
         * for (double exp=1; index>0; index--){...} */
        double exp = 1;
        for (i=0; i<index; i++){
                exp *= 10;
        }

        if (exp_sign == -1){
                val /= exp;
        } else {
                val *= exp;
        }
        
        return sign*val;
}

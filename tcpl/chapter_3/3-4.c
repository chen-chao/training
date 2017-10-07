/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie
 * Exercise 3.04 on page 64. In a two's complement number
 * representation, our version of itoa does not handle the largest
 * negative number, that is, the value of n equal to -(2 to the power
 * (wordsize - 1)) . Explain why not. Modify it to print that value
 * correctly regardless of the machine on which it runs.
 * Other solutions can be found here:
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_3:Exercise_4*/

#include <stdio.h>
#include <string.h>

#define MAXLEN 100

void reverse(char s[]){
        int c, i, j;

        for (i = 0, j = strlen(s)-1; i<j; i++, j--){
                c = s[i];
                s[i] = s[j];
                s[j] = c;
        }
}

void itoa(int n, char s[]){
        int i, sign;
        if ((sign = n) < 0)
                n = -n;
        i = 0;
        do {
                s[i++] = n%10+'0';
        } while ((n /= 10) > 0);
        if (sign < 0)
                s[i++] = '-';
        s[i] = '\0';
        reverse(s);
}

void itoa_for_negative(int n, char s[]){
        int i, sign;
        if ((sign = n) < 0)
                n = ~n;
        i = 0;
        do {
                s[i++] = n%10+'0';
        } while ((n /= 10) > 0);
        if (sign < 0){
                int j = 0;
                do {
                        s[j]++;
                } while (j<i && s[j++]-'9'>0);
                s[i++] = '-';                
        }

        s[i] = '\0';
        reverse(s);
}

int main(){
        int i = 1;
        int MAX_INT = ((unsigned) (~i))/2;
        int MAX_NEGATIVE = -MAX_INT-1;
        printf("MAX_INT: %d\n", MAX_INT);
        printf("MAX_NEGATIVE: %d\n", MAX_NEGATIVE);
        char s1[MAXLEN], s2[MAXLEN];
        char sn1[MAXLEN], sn2[MAXLEN];
        itoa(MAX_INT, s1);
        itoa(MAX_NEGATIVE, s2);
        itoa_for_negative(MAX_INT, sn1);
        itoa_for_negative(MAX_NEGATIVE, sn2);
        printf("n: %i, itoa: %s, itoa_for_negative: %s\n", MAX_INT, s1, sn1);
        printf("n: %i, itoa: %s, itoa_for_negative: %s\n", MAX_NEGATIVE, s2, sn2);
        return 0;
}


/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 3.05 on page 64. Write the function itob(n,s,b) that
 * converts the integer n into a base b character representation in
 * the string s . In particular, itob(n,s,16) formats n as a
 * hexadecimal integer in s . */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAXLEN 1000

void itob(int n, char *s, int b);

int main(){
        int b, x, status;
        char s[MAXLEN];
        printf("%s", "Program to transform an integer to string base is b.\n");
        do {
                printf("%s", "Please input the base b: \n");
                status = scanf("%d", &b);
                if (status == EOF)
                        return -1;
        } while (status != 1);

        do {
                printf("The base is %d, Please input an integer to transform: \n", b);                
                status = scanf("%d", &x);
                if (status == 1){
                        itob(x, s, b);
                        printf("%d -> %s\n", x, s);
                } else {
                        printf("%s", "Invalid input.\n");
                }
        } while (status != EOF);
        return 0;
}

void reverse(char s[]){
        int i, j, tmp;
        j = strlen(s)-1;
        
        for (i=0; i<j; i++, j--){
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
        }
}

void itob(int n, char s[], int b){
        /* This is from the exercise answer*/
        if ( b < 2 || b > 36 ) {
                fprintf(stderr, "Cannot support base %d\n", b);
                exit(EXIT_FAILURE);
        }
        
        int i = 0;
        int c;
        do {
                c = abs(n % b)+'0';
                s[i++] = (c > '9' ? (c-'9'+'A'-1): c);
        } while (n /= b);
        if (n < 0){
                s[i++] = '-';
        }
        s[i] = '\0';
        reverse(s);
}

/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 3.06 on page 64. Write a version of itoa that accepts
 * three arguments instead of two. The third argument is a minimum
 * field width; the converted number must be padded with blanks on the
 * left if necessary to make it wide enough. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAXLEN 200


void itoa(int n, char s[], int width);

int main(){
        int x, width, status;
        char s[MAXLEN];
        printf("This is a program to transform an integer to string.\n");
        printf("Please input the representation width: ");
        while ((status = scanf("%d", &width)) != 1){
                fgets(s, MAXLEN, stdin);
                printf("Please input the representation width: ");
        }
        
        do {
                printf("Please input an integer:");
                status = scanf("%d", &x);
                switch (status){
                case 1:
                        itoa(x, s, width);
                        printf("%d -> %s\n", x, s);
                        break;
                case EOF:
                        return 0;
                default:
                        fgets(s, MAXLEN, stdin);
                        printf("Invalid input. ");
                        break;
                }

        } while (1);

        return 0;
}

void reverse(char s[]){
        int i, j, tmp;
        j = strlen(s)-1;
        for (i = 0; i<j; i++, j--){
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
        }
}

void itoa(int n, char s[], int width){
        int i = 0;
        do {
                s[i++] = abs(n%10) + '0';
        } while (n /= 10);

        if (n < 0)
                s[i++] = '-';
        
        for (; i<width; i++){
                s[i] = ' ';
        }
        s[i] = '\0';
        reverse(s);
}

/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 2.03 on page 46. Write the function htoi(s) , which
 * converts a string of hexadecimal digits (including an optional 0x
 * or 0X) into its equivalent integer value. The allowable digits are
 * 0 through 9, a through f, and A through F . */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BASE 16
#define MAXLEN 100


int htoi(char s[]);
void eliminate_newline(char s[]);


int main(){
        char s[100];
        char *res;

        while (1){
                printf("Please input a hex string: ");
                res = fgets(s, MAXLEN, stdin);
                if (res == NULL)
                        return 0;
                eliminate_newline(s);
                printf("Your input is %d \n", htoi(s));
        }
}


void eliminate_newline(char s[]){
        int len;
        if ((len = strlen(s)) > 0 && s[len-1]=='\n'){
                s[len-1] = '\0';
        }
}


int htoi(char s[]){
        int i = 0;

        if (s[0] == '\0'){
                return -1;                
        }

        if (s[0] == '0') {
                i++;
                if (s[1] == '\0'){
                        return 0;
                } else if (s[i] == 'x' || s[i] == 'X'){
                        i++;
                } 
        }

        int val, alpha;
        val = 0;
        for (; s[i] != '\0'; i++){
                val *= BASE;
                if (isdigit(s[i])){
                        val += s[i]-'0';
                } else if (isalpha(s[i])){
                        alpha = toupper(s[i])-'A'+10;
                        if (alpha >= BASE)
                                return -1;
                        val += alpha;
                } else {
                        return -1;
                }
        }

        return val;
}

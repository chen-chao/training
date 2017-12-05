/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 4.01 on page 71. Write the function strrindex(s,t) , which
 * returns the position of the rightmost occurrence of t in s , or -1
 * if there is none.
 * Other solutions can be found at
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_1*/

#include <stdio.h>
#include <string.h>

#define MAXLEN 100


int strrindex(char s[], char t[]);
void eliminate_newline(char s[]);

int main(){
        char s[MAXLEN], t[MAXLEN];
        char *res;
        while (1) {
                printf("Please input string: ");
                res = fgets(s, MAXLEN, stdin);
                if (res == NULL)
                        return 0;
                
                printf("Please input substring to find: ");
                res = fgets(t, MAXLEN, stdin);
                if (res == NULL)
                        return 0;

                eliminate_newline(s);
                eliminate_newline(t);
                int pos = strrindex(s, t);

                if (pos == -1)
                        printf("substring is not found.\n");
                else
                        printf("substring is found at position %d\n", pos);
        }
}

void eliminate_newline(char s[]){
        int len;
        if ((len = strlen(s)) > 0 && s[len-1]=='\n'){
                s[len-1] = '\0';
        }
}

int strrindex_original(char s[], char t[]){
        int slen = strlen(s);
        int tlen = strlen(t);

        int i, j;
        for (i=slen-tlen; i>=0; i--){
                for (j=0; j<tlen && s[i+j]==t[j]; j++){
                        ;
                }
                if (j == tlen){
                        return i;
                }
        }
        return -1;
}

int strrindex(char s[], char t[]){
        /* Inspired by the tcpl book on page 59 chs / 69 eng */
        int slen = strlen(s);

        int i, j, k;

        for (i = slen-1; i>=0; i--){
                /* when j==slen, s[j]=='\0' will never equal to t[k]!='\0' */
                /* Or using a variable to store the maximum qualified position i to avoid using strlen */
                for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++){
                        ;
                }
                if (k>0 && t[k]=='\0'){
                        return i;
                }
        }
        return -1;
}


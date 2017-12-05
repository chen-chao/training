/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie
 * Exercise 3.03 on page 63 Write a function expand(s1,s2) that
 * expands shorthand notations like a-z in the string s1 into the
 * equivalent complete list abc...xyz in s2 . Allow for letters of
 * either case and digits, and be prepared to handle cases like a-b-c
 * and a-z0-9 and -a-z . Arrange that a leading or trailing - is taken
 * literally. Other solutions can be found here:
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_3:Exercise_3*/
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int expand(char *s1, char *s2);
size_t fill(char c1, char c2, char *s);

int main(){
        printf("%s", "Please input a string to expand:\n");
        size_t MAXLINE = 1000;
        size_t line_len;
        char *line = NULL;
        line_len = getline(&line, &MAXLINE, stdin);
        if (line_len <= 0)
                return -1;
        char *expand_line;
        expand_line = (char *)malloc(MAXLINE*sizeof(char));
        int status;
        status = expand(line, expand_line);
        printf("%s\n", expand_line);
        return status;
}

int expand(char *s1, char *s2){
        char last_c='\0';
        char next_c;
        size_t len;
        while (*s1){
                if (*s1=='-' && (next_c=*(s1+1)) && (len=fill(last_c, next_c, s2))){
                        s2 += len;
                } else {
                        *s2++ = *s1;
                }
                last_c = *s1++;
        }
        *s1 = '\0';
        return 0;
}
        

size_t fill(char c1, char c2, char *s){
        size_t len = 0;
        /* Drawback: middle letters are judged twice for consecutive dashes */
        if ((isdigit(c1) && isdigit(c2)) ||
            (islower(c1) && islower(c2)) ||
            (isupper(c1) && isupper(c2))){
                while (++c1 < c2){
                        *s++ = c1;
                        len++;
                }
        }
        return len;
}

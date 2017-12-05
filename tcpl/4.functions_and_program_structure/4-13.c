/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 4.13 on page 88. Write a recursive version of the function
 * reverse(s) , which reverses the string s in place. More answers see
 * here:
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_4:Exercise_13*/


#include <stdio.h>
#include <string.h>             /* to use strlen */

#define MAXLEN 100


void reverse(int len, int pos, char s[]){
        if (pos > len/2)
                return;
        
        int tmp, pair;
        pair = len-pos-1;
        tmp = s[pos];
        s[pos++] = s[pair];
        s[pair] = tmp;
        reverse(len, pos, s);
}


/* This is from the answer site, more efficient. */
int reverse_2(char v[], int i, int j){
  int temp;
  if(j == 1)
    return 1;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
  return reverse_2(v, ++i, --j);
}


int main(){
        char s[MAXLEN];
        char *res;
        int len;
        while (1){
                printf("Please input a string to reverse: ");
                res = fgets(s, MAXLEN, stdin);
                if (res == NULL)
                        return 0;
                len = strlen(s);
                if (s[len-1] == '\n')
                        s[--len] = '\0';
                
                reverse(len, 0, s);
                printf("Reverse string is: %s\n", s);
        }
        return 0;
}

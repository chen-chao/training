#include <stdio.h>


char lower(char c){
    return (c>='A' && c<='Z') ? c-'A'+'a' : c;
}

int main(){
    char s[31] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcde";
    int i;
    for (i=0; i<31; i++)
        printf("%c -> %c\n", s[i], lower(s[i]));
}

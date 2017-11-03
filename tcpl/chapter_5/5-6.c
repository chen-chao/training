#include <stdio.h>

#include <ctype.h>
int atoi(char *s){
    if (*s == '\0')
        return 0;
    int sign = (*s == '-') ? -1: 1;
    if (*s == '+' || *s == '-')
        s++;
    int res = 0;
    while (isdigit(*s)){
        res = res*10+*s++-'0';
    }
    res *= sign;
    return res;
}

void reverse(char *s){
    char *start = s;
    char tmp;
    while (*s)
        s++;
    while (start != --s){
        tmp = *start;
        *start++ = *s;
        *s = tmp;
    }
}

int main(){
    char a[] = "-578245";
    int d;
    d = atoi(a);
    printf("%s is decimal %d.\n", a, d);
    reverse(a);
    printf("reverse: %s", a);
    return 0;
}
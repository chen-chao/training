/* #Give nineteen programmers a spec, and you'll get at least
 * twenty completely different programs.*/
#include <stdio.h>

void strcat(char *s, char *t){
    while (*s)
        s++;
    while ((*s++ = *t++))
        ;
}

int strend(char *s, char *t){
    char *sstart = s;
    char *tstart = t; 

    while (*s)
        s++;
    while (*t)
        t++;
    for (; s >= sstart && t>= tstart && *s == *t; --s, --t)
        ;
    if (t < tstart)
        return 1;
    return 0;
}

void strncpy(char *s, char *t, int n){
    while (--n >= 0 && (*s++ = *t++))
       ;
    if (n <= 0)
        *s = '\0';
}

void strncat(char *s, char *t, int n){
    while (*s)
        s++;
    while (--n >= 0 && (*s = *t)){
        s++;
        t++;
    }
    if (n < 0)
        *s = '\0';
}

int strncmp(char *s, char *t, int n){
    for (; n>0 && *s==*t; --n, s++, t++)
        if (*s == '\0')
            return 0;
    return *s-*t;
}

int main(){
    char s1[1000] = "brown fox is ";
    char *s2 = "beautiful.";
    printf("s1: %s, s2: %s\n", s1, s2);
    strcat(s1, s2);
    printf("strcat: %s\n", s1);
    printf("strend: %d\n", strend(s1, s2));

    printf("s1: %s, s2: %s\n", s1, s2);
    strncpy(s1, s2, 10);
    printf("strncpy 10: %s\n", s1);

    printf("s1: %s, s2: %s\n", s1, s2);
    strncat(s1, s2, 10);
    printf("strncat 10: %s, s2: %s\n", s1, s2);
    printf("strncmp 10: %d\n", strncmp(s1, s2, 10));
    return 0;
}
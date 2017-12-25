#include <stdio.h>

void minprintf(char *, ...);
int main(){
    minprintf(":%8.4s:%10d:%10.3f:\n", "hello", 80, 72.44);
    return 0;
}
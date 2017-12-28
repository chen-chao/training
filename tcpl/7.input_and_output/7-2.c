#include <stdio.h>

#define MAX_ChAR_LINE 79

void sensible_printf(){
    int count, c;

    for (count = 0; (c = getchar()) != EOF; count++){
        if (count == MAX_ChAR_LINE && c != '\n'){
            putchar('\n');
            count = 0;
        } 
        if (c == 10){
            count = 0;
            putchar(c);
        } else if (c < 32 || c > 126){
            printf("%x", c);
        } else {
            putchar(c);
        }
    }
}

int main(){
    sensible_printf();
    return 0;
}

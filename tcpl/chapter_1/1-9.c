#include <stdio.h>

#define true 1
#define false 0

main(){
    int c;
    int last_white = false;
    
    while ((c=getchar()) != EOF){
        if (c != ' '){
            putchar(c);
            last_white = false;
        } else if (! last_white) {
            putchar(c);
            last_white = true;
        }
    }
}
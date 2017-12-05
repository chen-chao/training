#include <stdio.h>

main(){
    int c;
    int white, newline, tabs;
    white = 0;
    newline = 0;
    tabs = 0;
    
    while ((c=getchar()) != EOF){
        if (c==' '){
            ++white;
            continue;
        }
        
        if (c=='\t'){
            ++tabs;
            continue;
        }
        
        if (c=='\n'){
            ++newline;
            continue;
        }
            
    } 
    printf("whitespaces: %d\ntabs: %d\nnewlines: %d\n", white, tabs, newline);
}
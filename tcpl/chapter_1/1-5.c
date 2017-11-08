#include <stdio.h>

main(){
    float fahr, celsius;
    float lower, upper, step;
    
    lower = -300;
    upper = 300;
    step = 20;
    
    printf("Table of fahr to celsius\n");
    fahr = upper;
    while(fahr >= lower){
        celsius = 5*(fahr-32)/9.;
        printf("%6.1f\t%6.1f\n", fahr, celsius);
        fahr = fahr-step;
    }
}
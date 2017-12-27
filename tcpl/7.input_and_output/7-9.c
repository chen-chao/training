#include <stdio.h>
#include <time.h>
#include <stdlib.h> 

#define MAXLEN 100000
int isupper_disk(int c){
    return c>='A' && c<='Z';
}

const unsigned CAP_TABLE[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int isupper_time(int c){
    return CAP_TABLE[c];
}
int main(){
    clock_t start, end;
    char target[MAXLEN];
    int i;
    char cap[] = "Aa";
    for (i = 0; i < MAXLEN; i++){
        target[i] = rand() % 26 + cap[rand()%2];
    }

    for (i = 0; i < 100; i++){
        printf("%c, isupper_disk: %d, isupper_time: %d\n", target[i], isupper_disk(target[i]), isupper_time(target[i]));
    }
    start = clock();
    for (i = 0; i < MAXLEN; i++){
        isupper_disk(target[i]);
    }
    end = clock();
    printf("Ellapsed time for isupper_disk: %d\n", (int) (end-start));
    start = clock();
    for (i = 0; i < MAXLEN; i++){
        isupper_time(target[i]);
    }
    end = clock();
    printf("Ellapsed time for isupper_time: %d\n", (int) (end-start));
    return 0;
}
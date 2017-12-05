#include <stdio.h>
#include <time.h>

int bitcount_1(unsigned x){
    int b;
    for (b = 0; x != 0; x >>= 1){
        if (x & 01)
            b++;
    }
    return b;
}

int bitcount_2(unsigned x){
    int b;
    for (b = 0; x != 0; x &= (x-1)){
        b++;
    }
    return b; 
}

int main(){
    const unsigned x = 0xffff;
    const int maxtime = 1000000;
    clock_t start;
    int seconds;
    int count;
    start = clock();
    for (int i=0; i<maxtime; i++){
        count = bitcount_1(x);
    }
    seconds = (clock()-start);
    printf("bitcount_1 = %d, ellapsed time = %d\n", count, seconds);
    start = clock();
    for (int i=0; i<maxtime; i++){
        count = bitcount_2(x);
    }
    seconds = (clock()-start);
    printf("bitcount_2 = %d, ellapsed time = %d\n", count, seconds);
    return 0;
}
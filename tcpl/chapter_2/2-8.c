#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n){
    /* since sizeof is used here, this answer is more reasonable
     * size_t p = sizeof(x)*CHAR_BIT
     * return (x>>n) | (x <<(p-n))*/
    unsigned mask = (1 << n) -1;
    return ((x & mask) << (sizeof(x)*CHAR_BIT-n)) + (x & ~mask);
}

int main(){
    unsigned x = 0xfa2b;
    printf("%x, %x\n", x, rightrot(x, 4));
    x = 0x3b1c;
    printf("%x, %x\n", x, rightrot(x, 6));
}
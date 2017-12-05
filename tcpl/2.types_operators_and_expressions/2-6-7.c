/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 2.06 on page 49. Write a function setbits(x,p,n,y) that
 * returns x with the n bits that begin at position p set to the
 * rightmost n bits of y, leaving the other bits unchanged. */


#include <stdio.h>


unsigned setbits(unsigned x, int p, int n, unsigned y){
        int gap = p-n;
        y &= ((1<<n) -1);
        x &= ((~0 - (1<<p) +1) | ((1<<gap)-1));
        return (x | (y << gap));
}
 
unsigned invert(unsigned x, int p, int n){
        x ^= ((1<<p) - (1<<(p-n)));
        /* int gap = p-n; */
        /* x ^= (~(~0 << p) >> gap) << gap; */
        return x;
}

int main(){
        int x, p, n, y;
        
        x = 0x4f7a;
        p = 10;
        n = 6;
        y = 0xa91b;

        printf("x=%x, p=%d, n=%d, y=%x, setbits=%x\n", x, p, n, y, setbits(x, p, n, y));
        printf("x=%x, p=%d, n=%d, invert=%x\n", x, p, n, invert(x, p, n));
}

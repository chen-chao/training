/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 2.01 on page 36. Write a program to determine the ranges
 * of char , short , int , and long variables, both signed and
 * unsigned , by printing appropriate values from standard headers and
 * by direct computation. Harder if you compute them: determine the
 * ranges of the various floating-point types. */

#include <stdio.h>
#include <limits.h>

int main(){
        unsigned char uc_max = ~((unsigned char) 0);

        signed char c_max = 0;
        signed char c;
        for (c=0; c>=c_max; c++)
                c_max = c;
        signed char c_min = 0;
        for (c=0; c<=c_min; c--)
                c_min = c;
        printf("unsigned char max: %u, UCHAR_MAX: %u\n", uc_max, UCHAR_MAX);
        printf("signed char max: %d, CHAR_MAX: %d\n", c_max, CHAR_MAX);
        printf("signed char min: %d, CHAR_MIN: %d\n", c_min, CHAR_MIN);

        unsigned int ui_max = ~((unsigned int) 0);                
        signed int i_max = (ui_max >> 1);
        signed int i_min = -i_max-1;
        printf("unsignd int max: %u, UINT_MAX: %u\n", ui_max, UINT_MAX);
        printf("signed int max: %d, INT_MAX: %d\n", i_max, INT_MAX);
        printf("sigend int min: %d, INT_MIN: %d\n", i_min, INT_MIN);
        
        unsigned short us_max = ~((unsigned short) 0);
        signed short s_max = (us_max >> 1);
        signed short s_min = -s_max-1;
        printf("unsigned short max: %d, USHRT_MAX: %d\n", us_max, USHRT_MAX);
        printf("signed short max: %d, SHRT_MAX: %d\n", s_max, SHRT_MAX);
        printf("signed short min: %d, SHRT_MIN: %d\n", s_min, SHRT_MIN);

        unsigned long ul_max = ~((unsigned long) 0);
        signed long l_max = (ul_max >> 1);
        signed long l_min = -l_max-1;
        printf("unsigned long max: %lu, ULONG_MAX: %lu\n", ul_max, ULONG_MAX);
        printf("signed long max: %ld, LONG_MAX: %ld\n", l_max, LONG_MAX);
        printf("signed long min: %ld, LONG_MIN: %ld\n", l_min, LONG_MIN);

        return 0;
}

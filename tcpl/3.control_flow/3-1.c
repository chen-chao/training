/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie
 * Exercise 3.01 on page 58. Our binary search makes two tests inside
 * the loop, when one would suffice (at the price of more tests
 * outside). Write a version with only one test inside the loop and
 * measure the difference in run-time. Other solutions can be found
 * here:
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_3:Exercise_1.
 * A little faster, but no big improvement*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define len 100000
#define num 10000

int binsearch(int x, int v[], int n){
        int low, high, mid;

        low = 0;
        high = n-1;
        while (low <= high) {
                mid = (low+high)/2;
                if (x<v[mid]){
                        high = mid -1;
                } else if (x>v[mid]){
                        low = mid+1;
                } else {
                        return mid;
                }
                
        }
        return -1;
}

int binsearch_one_compare(int x, int v[], int n){
        int low, high, mid;

        low = 0;
        high = n-1;
        while (low<=high && v[mid=(low+high)/2]!=x){
                if (x<v[mid]) {
                        high = mid-1;
                } else {
                        low = mid+1;
                }
        }
        /* return (low>high ? -1: mid); */
        if (low>high){
                return -1;
        }
        return mid;
}

int main(){
        int v[len];
        
        for (int i=0; i<len; i++){
                v[i] = i*3+1;
        }
        
        int target[num];
        for (int i=0; i<num; i++){
                target[i] = rand()%(v[len-1]+1);
        }
        
        clock_t start, end;
        double elapsed_cpu_time;
        int res[num], res_one_compare[num];

        start = clock();
        for (int i=0; i<num; i++){
                res[i] = binsearch(target[i], v, len);
        }
        end = clock();
        elapsed_cpu_time = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("binsearch: elapsed time is %8.4f\n", elapsed_cpu_time);

        start = clock();
        for (int i=0; i<num; i++){
                res_one_compare[i] = binsearch_one_compare(target[i], v, len);
        }
        end = clock();

        for(int i=0; i<num; i++){
                assert(res[i]==res_one_compare[i]);
        }
        
        elapsed_cpu_time = ((double)(end-start))/CLOCKS_PER_SEC;
        printf("binsearch_one_compare: elapsed time is %8.4f\n", elapsed_cpu_time);

        return 0;
}

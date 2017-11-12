#include <stdio.h>
#include <string.h>

void  quicksort(void *v[], int left, int right, int (*comp)(void *, void *)){
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last-1, comp);
    quicksort(v, last+1, right, comp);
}

#include <stdlib.h>
void swap(void *v[], int i, int j){
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s1, char *s2){
        double v1, v2;
        v1 = atof(s1);
        v2 = atof(s2);
        if (v1 < v2)
                return -1;
        else if (v1 > v2)
                return 1;
        else
                return 0;
}

int reverse_comp(int (*comp)(void *, void *), char *s1, char *s2){
        return -1*comp(s1, s2);
}

int reverse_numcmp(char *s1, char *s2){
        return reverse_comp((int (*) (void *, void *))numcmp, s1, s2);
}

int reverse_strcmp(char *s1, char *s2){
        return reverse_comp((int (*) (void *, void *))strcmp, s1, s2);
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>


void  quicksort(void *v[], int left, int right, int (*comp)(void *, void *), int ascend){
    int i, last;
    void swap(void *v[], int, int);
    int sign = (ascend==1) ? 1 : -1;
    
    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (sign*(*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quicksort(v, left, last-1, comp, ascend);
    quicksort(v, last+1, right, comp, ascend);
}

#include <stdlib.h>
void swap(void *v[], int i, int j){
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(const char *s1, const char *s2){
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

int nocasecmp(const char *s1, const char *s2){
        for (; tolower(*s1) == tolower(*s2); s1++, s2++)
                if (*s1 == '\0')
                        return 0;
        return *s1-*s2;
}


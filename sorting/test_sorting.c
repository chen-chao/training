#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sorting.h"


void test_sorting(void (*func)(int *, int), char *func_name, int size) {
    int s[size];
    srand(time(NULL));
    printf("Test %s\n", func_name);
    for (int i = 0; i < size; i++) {
    /* Note this is not uniformly distributed */
        s[i] = rand() % size;
        printf(" %d", s[i]);
    }
    printf("\n");
    func(s, size);
    for (int i = 0; i < size; i++) {
        printf(" %d", s[i]);
    }
    printf("\n");
}


int main() {
    const int num = 7;
    void (*func[])(int *, int) = {&bubble_sort, &insertion_sort,
                                     &selection_sort, &shell_sort,
                                     &merge_sort, &quick_sort_kr,
                                     &quick_sort_sedgewick};
    char *func_name[] = {"bubble_sort", "insertion_sort",
                            "selection_sort", "shell_sort",
                            "merge_sort", "quick_sort_kr",
                            "quick_sort_sedgwick"};
    int size = 20;
    for (int i = 0; i < num; i++) {
        test_sorting(func[i], func_name[i], size);
    }
    
    return 0;
}

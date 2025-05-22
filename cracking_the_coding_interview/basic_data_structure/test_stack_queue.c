#include <stdio.h>
#include "stack_and_queue.h"

void test_stack(int n) {
    for (int i = 0; i < n; i++) {
        push(i);
    }
    int value;
    for (int i = 0; i <= n; i++) {
        value = pop();
        printf("%d ", value);
    }
    printf("\n");
}

void test_queue(int n) {
    for (int i = 0; i < n; i++) {
        enqueue(i);
    }
    int value;
    for (int i = 0; i < n/2; i++) {
        value = dequeue();
        printf("%d ", value);
    }
    
    for (int i = 0; i <= n/2; i++) {
        enqueue(i);
    }

    for (int i = 0; i <= n; i++) {
        value = dequeue();
        printf("%d ", value);
    }
    printf("\n");
}

int main() {
    int n = 10;
    test_stack(n);
    test_queue(n);
    return 0;
}

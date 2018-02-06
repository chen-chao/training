#include <stdio.h>

#define MAXLEN 10

static int data[MAXLEN];
static int first = 0, last = 0, full = 0;

void enqueue(int value) {
    if (first >= MAXLEN) {
        first = first % MAXLEN;
    }
    if (full) {
        printf("error: queue is full.\n");
    } else {
        data[first++] = value;
        if (first == last) {
            full = 1;
        }
    }
#ifdef DEBUG
    printf("enqueue: last: %d, first: %d\n", last, first);
#endif
}

int dequeue(void) {
    if (last >= MAXLEN) {
        last = last % MAXLEN;
    }
    if (last == first && !full) {
        printf("error: queue is empty.\n");
        return 0;
    } else {
#ifdef DEBUG
        printf("dequeue: last: %d, first: %d\n", last+1, first);
#endif
        if (full) {
            full = 0;
        }
        return data[last++];
    }
}

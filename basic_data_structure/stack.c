#include <stdio.h>
#define MAXLEN 1000

static int data[MAXLEN];
static int pos = 0;

void push(int value) {
    if (pos < MAXLEN) {
        data[pos++] = value;
    } else {
        printf("error: stack is full.\n");
    }
}

int pop(void) {
    if (pos <= 0) {
        printf("error: stack is empty.\n");
        return 0;
    } else {
        return data[--pos];
    }
}

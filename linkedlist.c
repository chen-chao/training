#include <stdio.h>
#include <stdlib.h>

struct linkedList {
    int label;
    struct linkedList *next;
};

struct linkedList *lookup(struct linkedList *list, int label) {
    for (; list != NULL && list->label != label; list = list->next)
        ;
    return list;
}

struct linkedList *add(struct linkedList *list, int label) {
    struct linkedList *node = NULL;
    node = (struct linkedList *) malloc(sizeof(*node));
    node->label = label;
    node->next = list;
    return node;
}

struct linkedList *append(struct linkedList *list, int label) {
    if (list == NULL) {
        list = add(list, label);
    } else if (list->label != label) {
        struct linkedList *node = list;
        for (; node->next != NULL; node = node->next)
            ;
        if (node->next == NULL) {
            node->next = add(node->next, label);
        }
    }
    return list;
}

void deleteNode(struct linkedList *list, int label) {
    struct linkedList *temp;
    if (list->label == label) {
        temp = list->next;
        *list = *temp;
        free((void *) temp);
        return;
    }
    for (; list->next != NULL; list = list->next) {
        if (list->next->label == label) {
            temp = list->next;
            list->next = list->next->next;
            free((void *) temp);
        }
    }
}

struct linkedList *reverse(struct linkedList *head) {
    struct linkedList *prev, *cur, *next;
    prev = NULL;
    cur = head;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

void inplace_reverse(struct linkedList **head) {
    struct linkedList *prev, *cur, *next;
    prev = NULL;
    cur = *head;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    *head = prev;
}

void show(struct linkedList *head) {
    for (; head != NULL; head = head->next) {
        printf("%d->", head->label);
    }
    printf("NULL\n");
}

int main() {
    int i;
    struct linkedList *foo = NULL, *bar = NULL;
    for (i = 1; i < 10; i++) {
        foo = add(foo, i);
        bar = append(bar, i);
    }
    printf("foo: ");
    show(foo);
    printf("bar: ");
    show(bar);
    inplace_reverse(&bar);
    printf("inplace reverse bar: ");
    show(bar);
    bar = reverse(bar);
    printf("reverse bar: ");
    show(bar);
    deleteNode(foo, 9);
    printf("delete head 9 from foo: ");
    show(foo);
    deleteNode(foo, 5);
    printf("delete 5 from foo: ");
    show(foo);
    return 0;
}

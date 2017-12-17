/* Write a program that prints the distinct words in its input sorted
 * into decreasing order of frequency of occurrence. Precede each word
 * by its count. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct wordcount {
        char *word;
        int count;
        struct wordcount *left;
        struct wordcount *right;
};

struct wordcount *walloc(){
        return (struct wordcount *) malloc(sizeof(struct wordcount));
}

struct wordcount *addword(struct wordcount *p, char *word){
        int cmp;
        if (p == NULL){
                p = walloc();
                p->word = strdup(word);
                p->count = 1;
                p->left = NULL;
                p->right = NULL;
        } else if ((cmp=strcmp(p->word, word)) == 0){
                p->count++;
        } else if (cmp < 0) {
                p->right = addword(p->right, word);
        } else {
                p->left = addword(p->left, word);
        }
        return p;
}

struct wordcount *add_by_count(struct wordcount *t, struct wordcount *p){
        if (p == NULL)
                return t;
        if (t == NULL){
                t = walloc();
                t->word = strdup(p->word);
                t->count = p->count;
                t->left = NULL;
                t->right = NULL;
        } else if (t->count > p->count){
                t->left = add_by_count(t->left, p);
        } else {
                t->right = add_by_count(t->right,p);
        }
        return t;
}

struct wordcount *sort_by_count(struct wordcount *t, struct wordcount *p){
        if (p != NULL){
                t = add_by_count(t, p);
                t = sort_by_count(t, p->left);
                t = sort_by_count(t, p->right);
        }
        return t;
}

void treeprint(struct wordcount *p){
        if (p != NULL){
                treeprint(p->left);
                printf("%d %s\n", p->count, p->word);
                treeprint(p->right);
        }
}

int main(){
        int getword(char *word, int lim);
        int type;
        char word[1000];
        struct wordcount *p = NULL;
        while ((type = getword(word, 1000)) != EOF){
                if (type == 0){
                        p = addword(p, word);
                }
        }
        /* treeprint(p); */
        struct wordcount *count = NULL;
        count = sort_by_count(count, p);
        treeprint(count);
        return 0;
}

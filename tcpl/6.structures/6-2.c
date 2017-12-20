/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 6.02 on page 143. Write a program that reads a C program
 * and prints in alphabetical order each group of variable names that
 * are identical in the first 6 characters but different somewhere
 * thereafter. Don't count words within strings and comments. Make 6 a
 * parameter that can be set from the command line. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

int getword(char *s, int lim);

int strneq(char *s, char *t, int n){
    for (; n>0 && *s == *t; s++, t++, n--)
        if (*s == '\0')
            return 1;
    return (n==0);
}

struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(){
    return (struct tnode *) malloc(sizeof(struct tnode));
}

void addtree(struct tnode **p, char *word){
    int cmp;
    if (*p == NULL){
        *p = talloc();
        (*p)->word = strdup(word);
        (*p)->left = NULL;
        (*p)->right = NULL;
    } else if ((cmp = strcmp((*p)->word, word)) < 0) {
        addtree(&((*p)->right), word);
    } else if (cmp > 0) {
        addtree(&((*p)->left), word);
    }
}

void treeprint(struct tnode *p, char *sep){
    if (p->left != NULL)
        treeprint(p->left, sep);
    printf("%s%s", p->word, sep);
    if (p->right != NULL)
        treeprint(p->right, sep);
}

/* here can use static variable to indicate whether the previous word
 * is printed, see group_with_previous, from
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_6:Exercise_2 */
struct tnode *group(struct tnode *p, char *out, int n){
    struct tnode *node;
    if (p == NULL)
        return p;

    if (p->left == NULL && p->right == NULL){
        strcat(out, p->word);
        return p;
    }

    if (p->left != NULL){
        node = group(p->left, out, n);
        if (strneq(p->word, node->word, n) == 1){
            strcat(out, " ");
        } else{
            strcat(out, "\n");
        }
    }
    strcat(out, p->word);

    char rightout[MAXLEN];
    rightout[0] = '\0';
    if (p->right != NULL){
        node = group(p->right, rightout, n);
        if (strneq(p->word, node->word, n) == 1)
            strcat(out, " ");
        else
            strcat(out, "\n");
        strcat(out, rightout);
    }

    return p;
}

void group_with_previous(struct tnode *p, int n){
    static struct tnode *previous;
    static unsigned print_previous = 1;

    /* This must be before the statements in (p != NULL), to print
     * the last word with print_previous */
    if (previous != NULL && print_previous == 1){
        printf("%s", previous->word);
        print_previous = 0;
    }
        
    if (p != NULL){
        group_with_previous(p->left, n);
        if (n <= 0) {
            printf("%s\n", p->word);
        } else {
            if (previous != NULL){
                if (strneq(p->word, previous->word, n) == 1){
                    printf(" %s", p->word);
                    print_previous = 0;
                } else {
                    printf("\n");
                    print_previous = 1;
                }
            } else {
                print_previous = 1;
            }
            previous = p;
        }
        group_with_previous(p->right, n);
    }
}

int main(int argc, char *argv[]){
    int n;
    n = (argc == 2) ? atoi(argv[1]) : 6; 
    int type;
    char word[100], out[MAXLEN];
    out[0] = '\0';
    struct tnode *p = NULL;
    while ((type = getword(word, 100)) != EOF){
        if (type == 0){
            addtree(&p, word);
        } 
    }
    group(p, out, n);
    printf("%s\n", out);
    printf("=====================================\n");
    group_with_previous(p, n);
    return 0;
}

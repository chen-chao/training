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
    return 0;
}

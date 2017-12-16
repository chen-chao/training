#include <stdio.h>
#include <stdlib.h>

struct tnode {
        char *word;
        int count;
        struct tnode *left;
        struct tnode *right;
};

struct tnode *talloc(){
        return (struct tnode *) malloc(sizeof(struct tnode));
}

/* addtree without returning unnecessary pointer to tree root*/
void void_addtree(struct tnode **p, char *w){
        int cond;
        if (*p == NULL){
                *p = talloc();
                (*p)->word = strdup(w);
                (*p)->count = 1;
                (*p)->left = NULL;
                (*p)->right = NULL;
        } else if ((cond=strcmp((*p)->word, w)) > 0) {
                void_addtree(&((*p)->left), w);
        } else if (cond < 0){
                void_addtree(&((*p)->right), w);
        } else {
                (*p)->count++;
        }
}
struct tnode *addtree(struct tnode *p, char *w){
        int cond;
        if (p == NULL){
                p = talloc();
                p->word = strdup(w);
                p->count = 1;
                p->left = NULL;
                p->right = NULL;
        } else if ((cond=strcmp(p->word, w)) > 0) {
                p->left = addtree(p->left, w);
        } else if (cond < 0){
                p->right = addtree(p->right, w);
        } else {
                p->count++;
        }
        return p;
}

void treeprint(struct tnode *tn){
        if (tn != NULL){
                treeprint(tn->left);
                printf("%s: %d\n", tn->word, tn->count);
                treeprint(tn->right);                
        }
}

int main(){
        char word[100];
        int type, getword(char *, int);
        struct tnode *tn1 = NULL;
        struct tnode *tn2 = NULL;
        while ((type=getword(word, 100))!=EOF){
                if (type == 0){
                        tn1 = addtree(tn1, word);
                        void_addtree(&tn2, word);
                }
        }
        printf("tn1:---------------------------\n");
        treeprint(tn1);
        printf("tn2:---------------------------\n");
        treeprint(tn2);
        return 0;
}

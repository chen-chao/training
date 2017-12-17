#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

int getword(char *s, int lim);

struct linolist {
        unsigned lino;
        struct linolist *next;
};

struct linolist *lalloc(){
        return (struct linolist *) malloc(sizeof(struct linolist));
}

struct linolist *addlino(struct linolist *l, unsigned lino){
        if (l == NULL){
                l = lalloc();
                l->lino = lino;
                l->next = NULL;
                return l;
        } else if (l->lino != lino) {
                struct linolist *newl;
                newl = lalloc();
                newl->lino = lino;
                newl->next = l;
                return newl;
        }
        return l;
}

struct wordlist {
        char *word;
        struct linolist *linos;
        struct wordlist *left;
        struct wordlist *right;
};


struct wordlist *walloc(){
        return (struct wordlist *) malloc(sizeof(struct wordlist));
}

struct wordlist *addword(struct wordlist *w, char *word, unsigned lino){
        int cond;
        if (w == NULL){
                w = walloc();
                w->word = strdup(word);
                w->linos = NULL;
                w->linos = addlino(w->linos, lino);
        } else if ((cond = strcmp(w->word, word)) < 0){
                w->right = addword(w->right, word, lino);
        } else if (cond > 0) {
                w->left = addword(w->left, word, lino);
        } else {
                w->linos = addlino(w->linos, lino);
        }
        return w;
}

void print_wordlist(struct wordlist *w){
        struct linolist *l;
        if (w != NULL){
                print_wordlist(w->left);
                printf("%s: ", w->word);
                l = w->linos;
                while (l->next != NULL){
                        printf("%d, ", l->lino);
                        l = l->next;
                }
                printf("%d\n", l->lino);
                print_wordlist(w->right);                
        }
}

int main(){
        int type;
        char word[100];
        unsigned lino = 1;
        struct wordlist *w = NULL;
        while ((type = getword(word, 100)) != EOF){
                if (type == 0){
                        w = addword(w, word, lino);
                }
                if (type == '\n'){
                        lino++;
                }
        }
        print_wordlist(w);
        return 0;
}

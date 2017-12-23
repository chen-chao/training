#include <stdio.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
struct nlist *undef(char *);

void print_item(char *name){
    struct nlist *np;
    if ((np = lookup(name)) != NULL){
        printf("%s: %s\n", np->name, np->defn);
    } else {
        printf("Haven't find %s\n", name);
    }
}

int main(){
    install("hello", "world");
    install("nano", "editor");
    install("file", "exists");
    print_item("hello");
    print_item("nano");
    print_item("notexists");
    undef("hello");
    print_item("hello");
    print_item("nano");
    return 0;
}

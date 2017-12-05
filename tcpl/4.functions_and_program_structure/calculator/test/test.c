#include <stdio.h>
#include "../calc.h"


void push(double);
double pop(void);
void print(void);
double copy(void);
void change(void);
void clear(void);
void ungets(char []);
int getch(void);
void ungetch(int);


int main(){
        int i;
        for (i=0; i<10; i++){
                push((double) i);
        }
        change();
        for (i=0; i<6; i++){
                print();
                printf("\npop: %.8g\n", pop());
        }
        printf("copy: %.8g\n", copy());
        clear();
        pop();
        push(1.);
        print();
        
        ungets("hello");
        for (i=0; i<5; i++){
                printf("%c ", getch());
        }
        return 0;
}


#include <stdio.h>

#define WORDLEN 100

int getword(char *, int);
int main(){
        int type;
        char word[WORDLEN];
        while ((type = getword(word, WORDLEN)) != EOF){
                if (type < 4)
                        printf("%d: %s\n", type, word);
        }
        return 0;
}

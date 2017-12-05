#include <stdio.h>
#include <ctype.h>

#define WORDLEN 100

enum {WORD, STRING, COMMENT, PRE};

int getword(char *word, int lim){
        int c, type, getch(void);
        void ungetch(int);
        char *w = word;

        while (isspace(c = getch()))
                ;
        if (c != EOF)
                *w++ = c;

        type = WORD;
        if (!isalpha(c) && c != '_'){
                switch (c){
                case '#':
                        type = PRE;
                        break;
                case '/':
                        if ((c=getch())=='*'){
                                *w++ = c;
                                type = COMMENT;
                                break;
                        } else if (isalpha(c)){
                                *--w = c;
                                break;
                        }
                case '\\':
                        *w++ = getch();
                        *w = '\0';
                        return c;
                case '\"':
                        type = STRING;
                        break;
                default:
                        /* can not use ungetch for next word token */
                        *w = '\0';
                        return c;
                }
        }

        if (type == STRING){
                while (--lim > 0 && (c=getch()) != EOF && c != '\"'){
                        *w++ = c;
                        if (c == '\\')
                                *w++ = getch();
                }

                if (c == EOF){
                        printf("error: missing right \"\n");
                } else {
                        *w++ = c;
                }
                *w = '\0';
        } else if (type == COMMENT){
                for (*w=getch(); --lim > 0 && (c=getch())!=EOF &&(c!='/' || *w!='*');)
                        *++w = c;
                if (c == EOF){
                        printf("error: missing right */\n");
                } else {
                        *++w = c;
                }
                *++w = '\0';
        } else {
                for (; --lim > 0 && (isalnum(*w =getch()) || *w=='_'); w++)
                        ; 
                ungetch(*w);
                *w = '\0';               
        }
        return type;
}

int main(){
        int type;
        char word[WORDLEN];
        while ((type = getword(word, WORDLEN)) != EOF){
                if (type < 4)
                        printf("%d: %s\n", type, word);
        }
        return 0;
}

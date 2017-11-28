#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS};

void dcl(void);
void dirdcl(void);
int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int getch(void);
void ungetch(int);

void dcl(void){
        int ns;

        for (ns = 0; gettoken() == '*';)
                ns++;
        dirdcl();
        while (ns-- > 0)
                strcat(out, " pointer to");
}

void dirdcl(void){
        int type;
        if (tokentype == '('){
                dcl();
                if (tokentype != ')')
                        printf("error: missing )\n");
        } else if (tokentype == NAME){
                strcpy(name, token);
        } else
                printf("error: expected name or (dcl)\n");
        while ((type=gettoken()) == PARENS || type == BRACKETS){
                if (type == PARENS)
                        strcat(out, " function returning");
                else {
                        strcat(out, " array");
                        strcat(out, token);
                        strcat(out, " of");
                }
        }
}

void checktoken(){
        char *p, *t;
        for (p=token+1; isdigit(*p); p++)
                ;
        for (t=p; *p == ' ' || *p == '\t'; p++)
                ;
        if (*p == ']'){
                *t++ = *p;
                *t = '\0';
        } else {
                printf("error: invalid token in brackets, %c\n", *p);
        }
}

int gettoken(void){
        int c;
        char *p = token;

        while ((c = getch()) == ' ' || c == '\t')
                ;
        if (c == '(') {
                while ((c = getch()) == ' ' || c == '\t')
                        ;
                if (c == ')') {
                        strcpy(token, "()");
                        return tokentype = PARENS;
                } else {
                        ungetch(c);
                        return tokentype = '(';
                }
        } else if (c == '[') {
                *p++ = c;
                while ((c = getch()) == ' ' || c == '\t')
                        ;
                for (*p++ = c; (*p = getch()) != ']' && *p != EOF; p++)
                        ;
                if (*p == EOF){
                        printf("error: missing ]\n");
                        *p = '\0';
                } else
                        checktoken();
                return tokentype = BRACKETS;
        } else if (isalpha(c)) {
                for (*p++ = c; isalnum(c = getch());)
                        *p++ = c;
                *p = '\0';
                ungetch(c);
                return tokentype = NAME;
        } else
                return tokentype = c;
}

int main(){
        char *p;
        while (1){
                for (p=datatype; (isalpha(*p=getch()) || *p == ' ') && *p != EOF; p++)
                        ;
                if (*p == EOF)
                        return 0;
                ungetch(*p);
                *p = '\0';
                out[0] = '\0';
                dcl();
                if (tokentype != '\n')
                        printf("syntax error\n");
                printf("%s: %s %s\n ", name, out, datatype);
        }
        return 0;
}

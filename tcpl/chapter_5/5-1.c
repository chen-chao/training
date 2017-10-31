#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000


int getch(void);
int ungetch(char);


int getint(int *pn){
        int c, sign, tmp;

        while (isspace(c = getch()))
                ;

        if (c == EOF)
                return 0;
        
        if (!isdigit(c) && c !='+' && c!='-'){
                ungetch(c);
                return 0;
        }

        sign = (c == '-') ? -1: 1;

        if (c == '+' || c == '-'){
                tmp = getch();
                if (!isdigit(tmp)){
                        ungetch(tmp);
                        ungetch(c);
                        return 0;
                } else {
                        c = tmp;
                }
        }

        for (*pn = c-'0'; isdigit(c = getch()); )
                *pn = *pn*10 + c-'0';

        *pn *= sign;

        if (c != EOF)
                ungetch(c);
                
        return c;
}


int main(){
        int status, res;
        
        while (1){
                printf("Please input an integer: ");
                status = getint(&res);
                if (status == 0)
                        return 0;
                printf("integer you input is %d\n", res);
        }
}

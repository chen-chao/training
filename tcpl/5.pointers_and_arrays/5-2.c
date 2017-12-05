#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

int getch(void);
void ungetch(char);


int getfloat(double *pn){
        int c, sign, tmp;

        while (isspace(c = getch()))
                ;

        if (c == EOF)
                return 0;

        sign = (c=='-') ? -1 : 1;
        if (c == '-' || c == '+'){
                if (isdigit(tmp = getch()) || tmp=='.'){
                        c = tmp;
                } else {
                        ungetch(tmp);
                        ungetch(c);
                        return 0;
                }
        } else if (!isdigit(c) && c != '.'){
                ungetch(c);
                return 0;
        }

        *pn = 0;
        while (isdigit(c)){
                *pn = *pn * 10 + c - '0';
                c = getch();
        }

        int part = 1;
        if (c == '.'){
                while (isdigit(c=getch())){
                        part *= 10;
                        *pn = *pn * 10 + c - '0';
                }
        }

        if (c != EOF)
                ungetch(c);

        *pn = sign * *pn / part;

        return c;
}

int main(){
        int status;
        double res;
        while (1){
                printf("Please input an integer: ");
                status = getfloat(&res);
                if (status == 0)
                        return 0;
                printf("integer you input is %.8g\n", res);
        }
}

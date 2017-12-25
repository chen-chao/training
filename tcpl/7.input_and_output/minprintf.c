#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

/* minprintf with variable length arguments */
void minprintf(char *fmt, ...){
    va_list ap;
    void itoa(int, char *, int);
    char *p, *sval;
    int ival;
    double dval;

    int i, len, maxlen, minlen;
    char mlen[255];
    char *mstart;
    va_start(ap, fmt);
    for (p=fmt; *p; p++){
        if (*p != '%'){
            putchar(*p);
            continue;
        }
        
        // unsigned align_left = 0;
        // if (*++p == '-')
        //     align_left = 1;
        for (p++, mstart=mlen; isdigit(*p); p++, mstart++)
            *mstart = *p;
        *mstart = '\0';
        maxlen = (mstart - mlen > 0)? atoi(mlen) : 0;
        if (*p == '.'){
            for (p++, mstart=mlen; isdigit(*p); p++, mstart++)
                *mstart = *p;
            *mstart = '\0';
        }
        minlen = (mstart - mlen > 0)? atoi(mlen) : 0;

        switch (*p){
            case 'd':
                ival = va_arg(ap, int);
                itoa(ival, mstart, maxlen);
                for (i = 0; i < maxlen; i++)
                    putchar(mlen[i]);
                break;
            case 'f':
                if (maxlen < minlen)
                    return;
                dval = va_arg(ap, double);
                ival = (int) dval;
                dval -= ival;
                if (minlen > 0) {
                    len = maxlen-minlen-1;
                    itoa(ival, mlen, len); 
                    for (i = 0; i < len && mlen[i]; i++)
                        putchar(mlen[i]);
                } else {
                    itoa(ival, mlen, 0);
                    for (i = 0; maxlen > 0 && mlen[i]; maxlen--, i++)
                        putchar(mlen[i]);
                }
                if (i < maxlen){
                    putchar('.');
                    for (i++; i < maxlen; i++){
                        dval *= 10;
                        len = (int) dval;
                        putchar('0'+len);
                        dval -= len;
                    }
                }
                break;
            case 's':
                if (minlen > 0)
                    for (; maxlen > minlen; maxlen--)
                        putchar(' ');
                else
                    minlen = maxlen;
                for (sval = va_arg(ap, char *); *sval && minlen > 0; sval++, minlen--)
                    putchar(*sval);
                for (; minlen > 0; minlen--)
                    putchar(' ');
                break;
            default:
                putchar(*p);
                break;
        }
    }    
    va_end(ap);
}

void reverse(char s[]){
        int i, j, tmp;
        j = strlen(s)-1;
        for (i = 0; i<j; i++, j--){
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
        }
}

void itoa(int n, char s[], int width){
        int i = 0;
        do {
                s[i++] = abs(n%10) + '0';
        } while (n /= 10);

        if (n < 0)
                s[i++] = '-';
        
        for (; i<width; i++){
                s[i] = ' ';
        }
        s[i] = '\0';
        reverse(s);
}
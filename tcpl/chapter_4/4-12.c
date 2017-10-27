#include <stdio.h>

#define MAXLEN 100


static int _itoa(unsigned n, int pos, char s[]){
        /* Recursivly transform an integer n into equivalent string s.
         * pos: position of s[] to write
         * RETURN VALUE: length of n*/
        
        int len;
        unsigned next;

        if ((next = n/10)){
                len = _itoa(next, pos, s);
                s[pos += len] = n%10+'0';
                s[++pos] = '\0';
                return len+1;
        } else {
                s[pos++] = n + '0';
                s[pos] = '\0';
                return 1;
        }

}

int itoa(int n, char s[]){
        if (n < 0){
                s[0] = '-';
                unsigned val = -n;
                return _itoa(val, 1, s)+1;
        } else {
                return _itoa(n, 0, s);
        }
}

int main(){
        char s[MAXLEN];
        int n, len, status;
        do {
                printf("Please input an integer: ");
                status = scanf("%d", &n);
                if (status == EOF)
                        return 0;
                len = itoa(n, s);
                printf("input integer is %s, length is %d \n", s, len);
                
        } while (status == 1);

        return 0;
}

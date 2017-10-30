#include <stdio.h>
#include <string.h>

#define MAXLEN 100


int squeeze(char s1[], char s2[]);
int any(char s1[], char s2[]);
void eliminate_newline(char s[]);

int main(){
        char s1[MAXLEN];
        char s2[MAXLEN];
        char *res;
        int pos, status;
        
        while (1){
                printf("Please input string to squeeze s1: ");
                res = fgets(s1, MAXLEN, stdin);
                if (res == NULL)
                        return 0;
                printf("Please input the reference string s2: ");
                res = fgets(s2, MAXLEN, stdin);
                if (res == NULL)
                        return 0;
                eliminate_newline(s1);
                eliminate_newline(s2);
                pos = any(s1, s2);
                if (pos > 0)
                        printf("First position of s2 chars in s1: %d\n", pos);
                else
                        printf("s2 chars not found in s1\n. ");
                                
                status = squeeze(s1, s2);
                if (status == 0)
                        printf("String after squeezing is: %s\n", s1);
        }
        
        return -1;
}

void eliminate_newline(char s[]){
        int len;
        if ((len = strlen(s)) > 0 && s[len-1]=='\n'){
                s[len-1] = '\0';
        }
}

int any(char s1[], char s2[]){
        int i, j, c;
        i = 0;

        while ((c = s1[i])){
                j = 0;
                while (s2[j] && c != s2[j])
                        j++;
                if (s2[j] != '\0')
                        return i;
                else
                        i++;
        }
        return -1;
}

int squeeze(char s1[], char s2[]){
        int i, pos, j, c;

        pos = 0;
        for (i = 0; (c=s1[i]) != '\0'; i++){
                for (j = 0; c != s2[j] && s2[j] != '\0'; j++)
                        ;
                if (s2[j] == '\0')
                        s1[pos++] = c;
        }
        s1[pos] = '\0';
        return 0;
}

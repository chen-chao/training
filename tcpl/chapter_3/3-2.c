#include <stdio.h>
#include <stdlib.h>


int escape(char *s, char *t){
    while (*s){
        switch (*s){
            case '\t':
                *t++ = '\\';
                *t++ = 't';
                s++;
                break;
            case '\n':
                *t++ = '\\';
                *t++ = 'n';
                s++;
                break;
            case '\\': case '\"': case '\'':
                *t++ = '\\';
            default:
                *t++ = *s++;
                break;
        }
    }
    *t = '\0';
    return 0;
}

int translate(char *s, char *t){
    while (*s){
        if (*s=='\\'){
            switch (*++s){
                case 't':
                    *t++ = '\t';
                    s++;
                    break;
                case 'n':
                    *t++ = '\n';
                    s++;
                    break;
                case '\\': 
                case '\'': 
                case '\"':
                default:
                    *t++ = *s++;
                    break;
            }
        } else {
            *t++ = *s++;
        }
    }
    *t = '\0';
    return 0;
}

int main(){
    size_t MAXLINE = 1000;
    char *line;
    size_t len;
    len = getline(&line, &MAXLINE, stdin);
    if (len<0)
        return -1;
    char *escape_line;
    escape_line = (char *)malloc(2*MAXLINE*sizeof(char));
    escape(line, escape_line);
    printf("line: %s", line);
    printf("escape_line: %s\n", escape_line);
    char *translate_line;
    translate_line = (char *)malloc(2*MAXLINE*sizeof(char));
    translate(escape_line, translate_line);
    printf("translate_line: %s\n", translate_line);
    return 0;
}
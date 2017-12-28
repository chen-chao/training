/* Write a program to print a set of files, starting each new one on a
new page, with a title and a running page count for each file */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int width_of_page = 80, lines_of_page = 30, pageno = 1;
char header[MAXLINE], pagemarker[MAXLINE];

void get_pagemarker(char *pagemarker){
    *pagemarker++ = '\n';
    for (int i = 0; i < width_of_page; i++, pagemarker++) {
        *pagemarker = '=';
    }
    *pagemarker++ = '\n';
    *pagemarker++ = '\n';
    *pagemarker = '\0';
}

void get_header(char *header, char *title) {
    int i;
    for (i = 0; *title && i < width_of_page-10; i++, header++, title++) {
        *header = *title;
    }
    for (; i < width_of_page-10; i++, header++) {
        *header = ' ';
    }
    *header = '\0';
}

int print_page(FILE *f) {
    if (f == NULL)
        return -1;

    char line[MAXLINE];
    char *linepos;
    int i = 0, lino = 1;
    printf("%s%10d\n\n", header, pageno);
    lino += 2;
    while ((fgets(line, MAXLINE, f)) != NULL) {
        for (linepos = line; *linepos; linepos++, i++) {
            if (i == width_of_page && *linepos != '\n') {
                lino++;
                i = 0;
                putchar('\n');
            } 
            if (*linepos == '\n') {
                lino++;
                i = 0;
                putchar('\n');
            }
            if (lino == lines_of_page) {
                printf("%s", pagemarker);
                pageno++;
                lino = 3;
                printf("%s%10d\n\n", header, pageno);
            }
            if (*linepos != '\n') {
                putchar(*linepos);
            }
        }
    }
    return pageno;
}

int main(int argc, char *argv[]) {
    int c;
    while (--argc > 0 && (*++argv)[0] == '-') {
        switch ((c=*++argv[0])) {
            case 'l':
                lines_of_page = atoi(*++argv);
                --argc;
                break;
            case 'w':
                width_of_page = atoi(*++argv);
                --argc;
                break;
            default:
                fprintf(stderr, "Unknown option %c, ignored\n", c);
                break;
        }
    }

    get_pagemarker(pagemarker);
    FILE *f = NULL;
    if (argc == 0) {
        f = stdin;
        get_header(header, "\0");
    }
    char *fname;
    do {
        if (f == NULL){
            if (argc-- > 0 && (f = fopen(fname=*argv++, "r")) == NULL) {
                fprintf(stderr, "Error opening file %s\n", fname);
            } else {
                get_header(header, fname);
            }
        }

        if (f != NULL) {
            print_page(f);
        }
    } while (argc > 0);

    return pageno;
}
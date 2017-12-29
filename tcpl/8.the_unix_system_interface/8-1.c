#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/* This is a little faster than the getc version */
void copy_file(int fd, int dest) {
    char buf[BUFSIZ];
    int n;
    while ((n = read(fd, buf, BUFSIZ)) > 0) {
        if (write(dest, buf, n) != n) {
            fprintf(stderr, "copy_file: Error on writing destination %d.\n", dest);
        }
    }
}

int main(int argc, char *argv[]) {
    int fd;
    if (argc == 1) {
        copy_file(0, 1);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                fprintf(stderr, "Can not open file %s\n", *argv);
                return 1;
            } else {
                copy_file(fd, 1);
                close(fd);
            }
        }
    }

    return 0;
}

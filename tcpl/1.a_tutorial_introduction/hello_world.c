#include <stdio.h>

main() {
    printf("hello world.\n");
/* \c would get a warning of unrecognized escape sequence */
/* and use the letter instead */
    printf("\\c: \c");
    printf("\\d: \d");
    printf("\\e: \e");
    printf("\\f: \f");
    printf("\\g: \g");
    // printf("\\x: \x");
    printf("\\z: \z");
}

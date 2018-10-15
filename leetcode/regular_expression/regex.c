/* Simple regular expression matcher by Rob Pike from A Regular Expression
   Matcher written by Brian Kernighan. Really simple and elegant by not
   efficient. */


#include <stdio.h>


int match(char *, char *);
int matchhere(char *, char *);
int matchstar(int, char *, char *);


/* match: search for regexp anywhere in text */
int match(char *regexp, char *text)
{
  if (regexp[0] == '^')
    return matchhere(regexp+1, text);
  do {    /* must look even if string is empty */
    if (matchhere(regexp, text))
      return 1;
  } while (*text++ != '\0');
  return 0;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text)
{
  printf("call matchhere, re: %c, text: %c\n", *regexp, *text);
  if (regexp[0] == '\0')
    return 1;
  if (regexp[1] == '*')
    return matchstar(regexp[0], regexp+2, text);
  if (regexp[0] == '$' && regexp[1] == '\0')
    return *text == '\0';
  if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
    return matchhere(regexp+1, text+1);
  return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar(int c, char *regexp, char *text)
{
  printf("call matchstar, re: %c, text: %c\n", *regexp, *text);
  do {    /* a * matches zero or more instances */
    if (matchhere(regexp, text))
      return 1;
  } while (*text != '\0' && (*text++ == c || c == '.'));
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: regex pattern string\n");
    return 1;
  }
  if (match(argv[1], argv[2])) {
    printf("Match!");
  } else {
    printf("Oops~");
  }
}

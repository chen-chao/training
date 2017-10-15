#define NUMBER '0'
#define UNKNOWN_FUNC 'u'


/* extern const char *funclist; */


void push(double);
double pop(void);
int getop(char []);
int getch(void);
void ungetch(int);


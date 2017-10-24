#define NUMBER '0'
#define VARFUNC '1'


void push(double);
double pop(void);

int getop(char []);

int getch(void);
void ungetch(int);
void ungets(char []);

void set_var(char, float);
float get_var(char);
void unset_var(char);
void print_var();



#include <stdio.h>
/* #define MAXVARS 100 */
/* #define MAXVARNAME 100 */

/* char var_names[MAXVARS][MAXVARNAME]; */
/* double var_val[MAXVARS]; */


double var_az[26] = {0.};


void set_var(char name, double value){
        var_az[name-'a'] = value;
}

double get_var(char name){
        return var_az[name-'a'];
}

void unset_var(char name){
        var_az[name-'a'] = 0.;
}

void print_var(){
        for (int i=0; i<26; i++){
                printf("%.6g\n", var_az[i]);
        }
}



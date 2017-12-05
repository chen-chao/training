#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 1000

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day){
    if (month < 0 || month > 12 || day<1)
        return -1;
    int leap = (year%100==0) ? (year%400==0) : (year%4==0);
    if (day > daytab[leap][month])
        return -1;
    for (int i = 0; i < month; i++)
        day += daytab[leap][i];
    return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday){
    if (yearday < 1)
        return -1;
    int leap = (year%100 == 0)? (year%400==0) : (year%4==0);
    if (yearday > ((leap == 1)? 366: 365))
        return -1;
    int i; 
    for (i=1; yearday>daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday; 
    return 0;
}

int main(int argc, char *argv[]){
    char c;
    int year=0, month=0, day=0, yearday=0;
    int status = 0;
    while (argc > 1  && (*++argv)[0] == '-'){
            switch(c = *++argv[0]) {
            case 'y':
                year = atoi(*++argv);
                argc -= 2;
                break;
            case 'm':
                month = atoi(*++argv);
                argc -= 2;
                break;
            case 'd':
                day = atoi(*++argv);
                argc -= 2;
                break;
            case 'a':
                yearday = atoi(*++argv);
                argc -= 2;
                break;
            default:
                printf("monthday: illegal option %c\n", c);
                argc = 0;
                break;
            }
        }
    
    if (argc != 1){
        printf("Usage monthday -y year [-m month] [-d day] [-a yearday]\n");
        return -1;
    } else if (yearday == 0){
        yearday = day_of_year(year, month, day);
        if (yearday <= 0)
            return -1;
    } else {
        status = month_day(year, yearday, &month, &day);
        if (status != 0)
            return status;
    }
    printf("month %d, day %d of year %d is overall day %d\n",
                        month, day, year, yearday); 
    return 0;
}
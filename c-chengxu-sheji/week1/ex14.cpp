// Next day for the input date: yyyy-mm-dd

#include <iostream>
#include <string>
using namespace std;

int monthDays[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int monthDaysLeapYear[12]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year){
        if (year%400==0)
                return true;
        if (year%100==0)
                return false;
        if (year%4==0)
                return true;
}

int next_day(int year, int month, int day){
        int *monthdays;

        if (is_leap_year(year) ){
                monthdays = monthDaysLeapYear;
        } else {
                monthdays = monthDays;
        }
        day++;

        if (day > monthdays[month-1]){
                day = 1;
                month++;
        }

        if (month > 12){
                month = 1;
                year++;
        }
        printf("%4d-%02d-%02d\n",year, month, day );
}

int main(){
        string date;
        int year, month, day;
        cin >> date;
        year = stoi(date.substr(0,4) );
        month = stoi(date.substr(5,2) );
        day = stoi(date.substr(8,2) );
        next_day(year, month, day);
        return 0;
}

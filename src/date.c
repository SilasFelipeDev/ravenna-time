#include "date.h"

static int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static int bissexto(long year){
    if (year % 4 == 0 && (
        year % 100 != 0 || 
        year % 400 == 0)){
            return 1;
        }
    return 0;
}

static short int howDays(short int month, long year){
    short int days = monthDays[month - 1];

    if (month == 2 && bissexto(year)){
        days += 1;
    }

    return days;
}

int dateValid(Date data){
    if (data.second < 0   || data.second > 59) return 0;
    if (data.minute < 0   || data.minute > 59) return 0;
    if (data.hour   < 0   || data.hour   > 23) return 0;
    if (data.month  < 1   || data.month  > 12) return 0;
    if (data.day    < 1   || data.day    >   
        howDays(data.month, data.year))        return 0;
    if (data.year   < 1) return 0;

    return 1;
}
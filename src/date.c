#include "date.h"

static int bissexto(long year){
    if (year % 4 == 0 && (
        year % 100 != 0 || 
        year % 400 == 0)){
            return 1;
        }
    return 0;
}

int dateValid(Date data){
    if (data.second < 0   || data.second > 59) return 0;
    if (data.minute < 0   || data.minute > 59) return 0;
    if (data.hour   < 0   || data.hour   > 23) return 0;
    if (data.day    < 1   || data.day    > 31) return 0;
    if (data.month  < 1   || data.month  > 12) return 0;
    if (data.year   < 1) return 0;

    return 1;
}
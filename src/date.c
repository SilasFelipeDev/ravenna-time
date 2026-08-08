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

static long long absoluteTime(Date data){
    long long secondsYear   = data.year * 31536000;

    long long secondsMonth  = 0;
    for (int i = 0; i < data.month - 1; i++){
        int n = howDays(i + 1, data.year);
        secondsMonth += n;
    }
    secondsMonth *= 86400;

    long long secondsDay = data.day * 86400;
    int  secondsHour     = data.hour * 3600;
    int  secondsMinute   = data.minute * 60;
    short int seconds    = data.second;

    long long total = secondsYear + secondsMonth + secondsDay + 
                      secondsHour + secondsMinute + seconds;
    
    return total;
}

void dateDiff(Date inicio, Date fim, DateDiff *resultado){
    if (absoluteTime(inicio) > absoluteTime(fim)){
        Date aux = inicio;
        inicio = fim;
        fim = aux;
    }

    resultado->second = fim.second - inicio.second;
    if (resultado->second < 0){
        resultado->second += 60;
        fim.minute -= 1;
    }

    resultado->minute = fim.minute - inicio.minute;
    if (resultado->minute < 0){
        resultado->minute += 60;
        fim.hour -= 1;
    }

    resultado->hour   = fim.hour   - inicio.hour;
    if (resultado->hour < 0){
        resultado->hour += 24;
        fim.day -= 1;
    }

    resultado->day    = fim.day    - inicio.day;
    if (resultado->day < 0){
        fim.month -= 1;
        if (fim.month == 0){
            fim.month = 12;
            fim.year -= 1;
        }
        resultado->day += howDays(fim.month, fim.year);
    }

    resultado->month  = fim.month  - inicio.month;
    if(resultado->month < 0){
        resultado->month += 12;
        fim.year -= 1;
    }

    resultado->year   = fim.year   - inicio.year;
}
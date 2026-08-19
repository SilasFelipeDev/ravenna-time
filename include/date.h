#ifndef DATE_H
#define DATE_H

#ifdef __cplusplus
extern "C"{
#endif

// ESTA STRUCT REPRESENTA UMA DATA FIXA NO CALENDÁRIO.
typedef struct{
    short int second;
    short int minute;
    short int hour;
    short int day;
    short int month;
    long year;
} Date;

// ESTA OUTRA STRUCT REPRESENTA APENAS A DISTÂNCIA ENTRE DUAS DATAS.
typedef struct{
    short int second;
    short int minute;
    short int hour;
    short int day;
    short int month;
    int year;
} DateDiff;

int dateValid(Date data);
void dateDiff(Date inicio, Date fim, DateDiff *resultado);

#ifdef __cplusplus
}
#endif
#endif
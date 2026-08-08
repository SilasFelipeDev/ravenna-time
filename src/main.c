#include <stdio.h>
#include "date.h"

int main(void){
    Date inicio;
    Date fim;
    DateDiff resultado;

    do {
        printf("Digite uma Data Inicial: ");
        scanf("%hd/%hd/%ld %hd:%hd:%hd",
              &inicio.day, &inicio.month, &inicio.year, 
              &inicio.hour, &inicio.minute, &inicio.second
        );
        if (dateValid(inicio) == 0){
            printf("Data Invalida! Digite Novamente\n");
        } 
     } while (!dateValid(inicio));
    
    do {
        printf("Digite uma Data Final: ");
        scanf("%hd/%hd/%ld %hd:%hd:%hd", 
              &fim.day, &fim.month, &fim.year,
              &fim.hour, &fim.minute, &fim.second
        );
        if (dateValid(fim) == 0){
            printf("Data Invalida! Digite Novamente\n");
        }
    } while (!dateValid(fim));

    dateDiff(inicio, fim, &resultado);

    printf("Diferenca: %d anos %d meses %d dias, %d horas %d min %d seg\n",
           resultado.year, resultado.month, resultado.day, 
           resultado.hour, resultado.minute, resultado.second
    );

    return 0;
}
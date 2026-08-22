#include <stdio.h>
#include "date.h"

int main(void){
    Date inicio;
    Date fim;
    DateDiff resultado;

    int lidos; 

    do {
        printf("Digite uma Data Inicial (dd/mm/yyyy hh:mm:ss): ");
        lidos = scanf("%hd/%hd/%ld %hd:%hd:%hd",
                      &inicio.day, &inicio.month, &inicio.year, 
                      &inicio.hour, &inicio.minute, &inicio.second
        );

        int c; 
        while ((c = getchar()) != '\n' && c != EOF); // Limpa o resto do Buffer

        if (lidos != 6 || dateValid(inicio) == 0){
            printf("Data Invalida! Digite Novamente\n");
        } 
     } while (lidos != 6 || !dateValid(inicio));
    
    do {
        printf("Digite uma Data Final (dd/mm/yyyy hh:mm:ss): ");
        lidos = scanf("%hd/%hd/%ld %hd:%hd:%hd", 
                      &fim.day, &fim.month, &fim.year,
                      &fim.hour, &fim.minute, &fim.second
        );

        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa o resto do Buffer

        if (lidos != 6 || dateValid(fim) == 0){
            printf("Data Invalida! Digite Novamente\n");
        }
    } while (lidos != 6 || !dateValid(fim));

    dateDiff(inicio, fim, &resultado);

    printf("Diferenca: %d anos %d meses %d dias, %d horas %d min %d seg\n",
           resultado.year, resultado.month, resultado.day, 
           resultado.hour, resultado.minute, resultado.second
    );

    return 0;
}
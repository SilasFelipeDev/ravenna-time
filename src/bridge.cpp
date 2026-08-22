// FORÇA A LIB A **NÃO** USAR `inline`, GARANTINDO QUE A 
// IMPLEMENTAÇÃO VIRE CÓDIGO REAL E "PEGÁVEL" PELO LINKER
#define WEBVIEW_STATIC

// TODA FUNÇÃO DA LIB VAI SER COMPILADA COM NOME SIMPLES
// SEM MANGLING
#define WEBVIEW_API extern "C"

// PUXA O HEADER PRINCIPAL DA LIB
#include "webview/webview.h"

#include <string.h>
#include <stdlib.h>
#include "date.h"
#include "bridge.h"

int parseDateJson(const char* json, Date* date){
    const char* pointer;
    int   value;

    /*
    EXTRAÇÃO DE VALORES JSON PARA INTEIROS
    1. strstr() ACHA A POSIÇÃO DA CHAVE DO CAMPO DENTRO DA STRING JSON
       -> RETORNA NULL SE A CHAVE NÃO FOR ENCONTRADA EM JSON
    2. SE FOR NULL, O CAMPO ESTÁ AUSENTE -> return 1 (CÓDIGO DE ERRO: CAMPO AUSENTE)
    3. strchr() ACHA O ':' LOGO DEPOIS DA CHAVE; +1 AVANÇA O PONTEIRO PARA DEPOIS DELE,
       CAINDO NO PRIMEIRO DÍGITO DO VALOR
    4. strtol() LÊ O NÚMERO A PARTIR DALI, PARANDO AUTOMATICAMENTE NO PRIMEIRO 
       CARACTERE QUE NÃO É DÍGITO (',' ou '}')
    5. O VALOR LIDO É CONVERTIDO PRA SHORT INT (EXCETO year, QUE CONTINUA LONG)
       E GUARDADO NO CAMPO CORRESPONDENTE DA STRUCT Date DE SAÍDA 
    */
    pointer    = strstr(json, "\"year\"");
    if (pointer == NULL) return 1; 
    pointer    = strchr(pointer, ':') + 1;
    value      = strtol(pointer, NULL, 10);
    date->year = value;

    pointer     = strstr(json, "\"month\"");
    if (pointer == NULL) return 1;
    pointer     = strchr(pointer, ':') + 1;
    value       = strtol(pointer, NULL, 10);
    date->month = (short int) value;

    pointer   = strstr(json, "\"day\"");
    if (pointer == NULL) return 1;
    pointer   = strchr(pointer, ':') + 1;
    value     = strtol(pointer, NULL, 10);
    date->day = (short int) value;

    pointer    = strstr(json, "\"hour\"");
    if (pointer == NULL) return 1;
    pointer    = strchr(pointer, ':') + 1;
    value      = strtol(pointer, NULL, 10);
    date->hour = (short int) value;

    pointer      = strstr(json, "\"minute\"");
    if (pointer == NULL) return 1;
    pointer      = strchr(pointer, ':') + 1;
    value        = strtol(pointer, NULL, 10);
    date->minute = (short int) value;

    pointer      = strstr(json, "\"second\"");
    if (pointer == NULL) return 1;
    pointer      = strchr(pointer, ':') + 1;
    value        = strtol(pointer, NULL, 10);
    date->second = (short int) value;

    if (dateValid(*date)){
        return 0;
    } else {
        return 2; // DATA INVÁLIDA 
    }
}

std::string calculateDiff(const std::string& request){
    // PROCURA UMA SUBSTRING 
    // DEVOLVE O ÍNDICE NÚMERO DA POSIÇÃO DA SUBSTRING
    size_t splitPos = request.find("},{");

    // RECORTA A STRING ORIGINAL EM _REQUEST_ 
    // COMEÇA DO ÍNDICE 1 DO ARRAY (CORTANDO O "[") E PEGA OS **splitPos** CARACTERES SEGUINTES
    // REPRESENTA NOSSO PRIMEIRO OBJETO JSON
    std::string startJson = request.substr(1, splitPos);

    // **splitPos** APONTA PARA "}", A CHAVE DE FECHAMENTO DO PRIMEIRO OBJETO JSON
    // **splitPos** + 2, APONTA PARA "{", A CHAVE DE ABERTURA DO SEGUNDO OBJETO JSON
    // request.length() - splitPos - 3, REPRESENTA QUANTOS CARACTERES VAMOS PEGAR
    // request.length É O TAMANHO TOTAL DO OBJETO ORIGINAL (ÚNICO) QUE QUEREMOS DIVIDIR EM DOIS
    // SUBTRAINDO PELA QUANTIDADE DE CARACTERES DA PRIMEIRA PARTIÇÃO (splitPos)
    // E SUBTRAINDO POR 3 QUE REPRESENTA OS CARACTERES "} , ]"
    // TEMOS O TAMANHO TOTAL DO SEGUNDO OBJETO
    std::string endJson   = request.substr(splitPos + 2, request.length() - splitPos - 3);

    /*
    CONVERTER `startJson` E `endJson` PARA const char* 
    CHAMAR `parseDateJson PARA CADA UM 
    VERIFICAR OS CÓDIGOS DE ERRO
    */
   const char* startCSrt = startJson.c_str();
   const char* endCStr   = endJson.c_str();
   Date start, end;

   int startStatus = parseDateJson(startCSrt, &start);
   if (startStatus == 1){
    return "{\"error\":\"missing field\"}";
   } else if (startStatus == 2){
    return "{\"error\":\"invalid start date\"}";
   }

   int endStatus = parseDateJson(endCStr, &end);
   if (endStatus == 1){
    return "{\"error\":\"missing field\"}";
   } else if (endStatus == 2){
    return "{\"error\":\"invalid end date\"}";
   }

    /*
    CHAMAR `dateDiff` COM AS DUAS DATAS RESULTANTES
    */
    DateDiff resultado;
    dateDiff(start, end, &resultado);

    /*
    MONTAR O OBJETO JSON COM A DIFERENÇA ENTRE AS DATAS
    RETORNAR ESSE OBJETO
    */

    char buffer[256];
    snprintf(buffer, sizeof(buffer), 
        "{\"years\":%d,\"months\":%d,\"days\":%d,\"hours\":%d,\"minutes\":%d,\"seconds\":%d}",
        resultado.year, resultado.month, resultado.day,
        resultado.hour, resultado.minute, resultado.second);
    
    return std::string(buffer);
}
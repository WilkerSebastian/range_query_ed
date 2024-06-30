#include "ui.h"

#include <stdio.h>
#include <stdlib.h>

int8_t main_menu() {

    int8_t op = 0;

    printf("1) realizar query\n0) Sair\nescolha uma opção: ");
    scanf("%hhd", &op);

    while (op < EXIT || op > QUERY) {
        clear();
        printf("opção inválida\n");
        printf("1) realizar query\n0) Sair\nescolha uma opção: ");
        scanf("%hhd", &op);
    }

    clear();

    return op;

}

Query *query_menu() {

    int op = 0;
    Query *query = (Query*)malloc(sizeof(Query));
    query->maxCodigo_uf = NULL;
    query->minCodigo_uf = NULL;
    query->maxDdd = NULL;
    query->minDdd = NULL;
    query->maxLatitude = NULL;
    query->minLatitude = NULL;
    query->maxLongitude = NULL;
    query->minLongitude = NULL;
    query->maxNome = NULL;
    query->minNome = NULL;

    op = insert_query("nome");

    if (op == YES) { 

        void **array = min_max("nome", STRING);

        query->minNome = (char*)(*array);
        query->maxNome = (char*)(*(array + 1));

        free(array);

    }


    op = insert_query("latitude");

    if (op == YES) {

        void **array = min_max("latitude", FLOAT);

        query->minLatitude = (double*)(*array);
        query->maxLatitude = (double*)(*(array + 1));

        free(array);

    }

    op = insert_query("longitude");

    if (op == YES) {

        void **array = min_max("longitude", FLOAT);

        query->minLongitude = (double*)(*array);
        query->maxLongitude = (double*)(*(array + 1));

        free(array);

    }

    op = insert_query("codigo_uf");

    if (op == YES) {

        void **array = min_max("codigo_uf", SMALL_INT);

        query->minCodigo_uf = (uint8_t*)(*array);
        query->maxCodigo_uf = (uint8_t*)(*(array + 1));

        free(array);

    }

    op = insert_query("ddd");

    if (op == YES) {

        void **array = min_max("ddd", SMALL_INT);

        query->minDdd = (uint8_t*)(*array);
        query->maxDdd = (uint8_t*)(*(array + 1));

        free(array);

    }

    return query;

}

int8_t insert_query(const char *name) {

    int8_t op = 0;

    printf("Você deseja inserir %s na sua query(1 = SIM, 0 = NÃO): ", name);
    scanf("%hhd", &op);

    while (op < EXIT || op > QUERY) {

        clear();
        printf("opção inválida\n");
        printf("Você deseja inserir %s na sua query(1 = SIM, 0 = NÃO): ", name);
        scanf("%hhd", &op);

    }

    return op;

}

void** min_max(const char *name, int8_t TYPE) {

    void *min = NULL;
    void *max = NULL;

    void **array = malloc(2 * sizeof(void*));

    switch (TYPE) {
    
        case SMALL_INT:

            min = (uint8_t*)malloc(sizeof(uint8_t));

            max = (uint8_t*)malloc(sizeof(uint8_t));

            printf("Qual valor minimo que deseja que %s tenha na sua query: ", name);
            scanf("%hhd", (uint8_t*)min);

            printf("Qual valor maximo que deseja que %s tenha na sua query: ", name);
            scanf("%hhd", (uint8_t*)max);

            break;
        case FLOAT:

            min = (double*)malloc(sizeof(double));

            max = (double*)malloc(sizeof(double));

            printf("Qual valor minimo que deseja que %s tenha na sua query: ", name);
            scanf("%lf", (double*)min);

            printf("Qual valor maximo que deseja que %s tenha na sua query: ", name);
            scanf("%lf", (double*)max);

            break;
        case STRING:

            getchar();
            printf("Qual valor minimo que deseja que %s tenha na sua query: ", name);
            min = readLine();

            printf("Qual valor maximo que deseja que %s tenha na sua query: ", name);
            max = readLine();

            break;
    
    }

    *array = min;
    *(array + 1) = max;

    printf("\n");

    return array;

}

// Função para ler a string de entrada com tamanho dinamico
char* readLine() {

    char *buffer = NULL;  
    size_t buffer_size = 0;  
    size_t length = 0; 

    buffer_size = 16;
    buffer = (char*)malloc(buffer_size * sizeof(char));

    if (buffer == NULL)
        return buffer;

    char ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        
        if (length >= buffer_size) {

            buffer_size *= 2;

            buffer = (char*)realloc(buffer, buffer_size * sizeof(char));

            if (buffer == NULL)
                return NULL;
            
        }

        buffer[length++] = ch;

    }

    *(buffer + length) = '\0';

    return buffer;

}

void clear() {
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

}
#include "ui.h"

#include <stdio.h>

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

        void **array = min_max("nome", INT);

        query->minNome = (uint32_t*)(*array);
        query->maxNome = (uint32_t*)(*(array + 1));

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

        void **array = min_max("codigo_uf", INT);

        query->minCodigo_uf = (uint32_t*)(*array);
        query->maxCodigo_uf = (uint32_t*)(*(array + 1));

        free(array);

    }

    op = insert_query("ddd");

    if (op == YES) {

        void **array = min_max("ddd", INT);

        query->minDdd = (uint32_t*)(*array);
        query->maxDdd = (uint32_t*)(*(array + 1));

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

    min = malloc(TYPE == INT ? sizeof(uint32_t) : sizeof(double));
    max = malloc(TYPE == INT ? sizeof(uint32_t) : sizeof(double));

    printf("Qual valor minimo que deseja que %s tenha na sua query: ", name);
    TYPE == INT ? scanf("%d", (uint32_t*)min) : scanf("%lf", (double*)min);

    printf("Qual valor maximo que deseja que %s tenha na sua query: ", name);
    TYPE == INT ? scanf("%d", (uint32_t*)max) : scanf("%lf", (double*)max);
    
    *array = min;
    *(array + 1) = max;

    printf("\n");

    return array;

}

void clear() {
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

}
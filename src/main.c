#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#define NOME 0
#define LATITUDE 1
#define LONGITUDE 2
#define CODIGO_UF 3
#define DDD 4

#include "comparators.h"
#include "hash.h"
#include "file.h"
#include "municipio.h"
#include "avl.h"
#include "ui.h"

int main() {

    void loadAvls(tnode *avl, Municipio **municipios, uint32_t size, Comparator comparator, int TYPE);

    Municipio **municipios = NULL;

    uint32_t size_json;

    json_error_t error;
    json_t *root = NULL;

    char *jsonString = readFile("municipios.min.json");

    if (jsonString == NULL) {
        printf("Ocooreu um erro ao ler o municipios.min.json\n");
        return EXIT_FAILURE;
    }
    
    root = json_loads(jsonString, 0, &error);
    free(jsonString); 

    if (root == NULL) {
        printf("Erro ao fazer o parse do JSON: %s\n", error.text);
        return EXIT_FAILURE;
    }

    size_json = json_array_size(root);

    municipios = calloc(size_json, sizeof(Municipio*));

    for (size_t i = 0; i < size_json; i++) {

        json_t *json = json_array_get(root, i);

        *(municipios + i) = createMunicipioFromJson(json);

    }

    if (municipios == NULL) {
        printf("Erro ao criar os municipios\n");
        return EXIT_FAILURE;
    }

    json_decref(root);

    Hashtable *hashTable = createHashTableMunicipio(municipios, size_json, size_json);

    tnode ** avls = (tnode**)calloc(5, sizeof(tnode*));

    for (size_t i = 0; i < 5; i++)
        for (size_t j = 0; j < size_json; j++) {

            Municipio *m = *(municipios + j);

            switch (i) {

                case NOME:

                    avl_insere(&*avls, m->nome, &m->codigo_ibge, comparatorString);
                    break;
                
                case LATITUDE:

                    avl_insere(&*(avls + 1), &m->latitude, &m->codigo_ibge, comparatorDobule);
                    break;
                
                case LONGITUDE:

                    avl_insere(&*(avls + 2), &m->longitude, &m->codigo_ibge, comparatorDobule);
                    break;
                
                case CODIGO_UF:

                    avl_insere(&*(avls + 3), &m->codigo_uf, &m->codigo_ibge, comparatorUnsignedInteger);
                    break;
                
                case DDD:

                    avl_insere(&*(avls + 4), &m->ddd, &m->codigo_ibge, comparatorUnsignedInteger);
                    break;
            }

        };

    int8_t op;

    do {

        op = main_menu();

        if (op == QUERY) {

            Query *query = query_menu();

            if (query == NULL) 
                printf("query informada incorretamente\n");

            else {

                printf("Busca %d %d\n", *query->minNome, *query->maxNome);

                printAVL(*(avls + 3), 0);

                uint32_t size = 0;
                uint32_t *results = searchRange(*avls, query->minNome, query->maxNome, comparatorDobule, &size);

                if (results == NULL) 
                    printf("Nenhum resultado encontrado\n");
                else 
                    for (size_t i = 0; i < size; i++)
                        printf("%d\n", results[i]);

                free(results);

            }

            free(query);

        }

        printf("\n\n\n");

    } while (op != EXIT);

    for (size_t i = 0;i < size_json;i++)
        destroyMunicipio(*(municipios + i));
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#define NOME 1
#define LATITUDE 2
#define LONGITUDE 3
#define CODIGO_UF 4
#define DDD 5

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

    loadAvls(*avls, municipios, size_json, comparatorString, NOME);
    loadAvls(*(avls + 1), municipios, size_json, comparatorDobule, LATITUDE);
    loadAvls(*(avls + 2), municipios, size_json, comparatorDobule, LONGITUDE);
    loadAvls(*(avls + 3), municipios, size_json, comparatorSmallUnsignedInteger, DDD);
    loadAvls(*(avls + 4), municipios, size_json, comparatorSmallUnsignedInteger, CODIGO_UF);

    int8_t op;

    do {

        op = main_menu();

        if (op == QUERY) {

            Query *query = query_menu();

            if (query == NULL) 
                printf("query informada incorretamente\n");

            else {

                

            }

            free(query);

        }

        printf("\n\n\n");

    } while (op != EXIT);

    for (size_t i = 0;i < size_json;i++)
        destroyMunicipio(*(municipios + i));
    
    return EXIT_SUCCESS;
}

void loadAvls(tnode *avl, Municipio **municipios, uint32_t size, Comparator comparator, int TYPE) {

    for (size_t i = 0; i < size; i++) {

        Municipio *m = *(municipios + i);

        if (*(municipios + i) != NULL) {

            switch (TYPE) {

                case NOME:

                    avl_insere(&avl, m->nome, &m->codigo_ibge, comparator);
                    break;
                
                case LATITUDE:

                    avl_insere(&avl, &m->latitude, &m->codigo_ibge, comparator);
                    break;
                
                case LONGITUDE:

                    avl_insere(&avl, &m->longitude, &m->codigo_ibge, comparator);
                    break;
                
                case CODIGO_UF:

                    avl_insere(&avl, &m->codigo_uf, &m->codigo_ibge, comparator);
                    break;
                
                case DDD:

                    avl_insere(&avl, &m->ddd, &m->codigo_ibge, comparator);
                    break;
            }

        } else 
            printf("Erro ao acessar o municipio\n");
        

    }

} 
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "file.h"
#include "municipio.h"
#include "avl.h"
#include "hash.h"

int comparator(titem item1, titem item2) {
    return (*(int *)item1) - (*(int *)item2);
}

void test_file() {
    char *file = readFile("municipios.min.json");
    assert(file != NULL);
    free(file);
}

void test_json() {
    json_error_t error;
    json_t *root = NULL;
    char *jsonString = readFile("municipios.min.json");
    
    root = json_loads(jsonString, 0, &error);
    free(jsonString); 

    assert(root != NULL);
    assert(json_is_array(root));
    assert(json_array_size(root) == 5570);

    json_t *city = json_array_get(root, 0);
    assert(city != NULL);
    assert(json_integer_value(json_object_get(city, "codigo_ibge")) == 5200050);
    assert(json_real_value(json_object_get(city, "latitude")) == -16.7573);
    assert(json_real_value(json_object_get(city, "longitude")) == -49.4412);
    assert(json_integer_value(json_object_get(city, "capital")) == 0);
    assert(json_integer_value(json_object_get(city, "codigo_uf")) == 52);
    assert(json_integer_value(json_object_get(city, "siafi_id")) == 1050);
    assert(json_integer_value(json_object_get(city, "ddd")) == 62);
    assert(strcmp(json_string_value(json_object_get(city, "nome")), "Abadia de Goiás") == 0);
    assert(strcmp(json_string_value(json_object_get(city, "fuso_horario")), "America/Sao_Paulo") == 0);

    json_decref(root);
}

void test_municipio() {
    json_error_t error;
    json_t *root = NULL;
    char *jsonString = readFile("municipios.min.json");
    
    root = json_loads(jsonString, 0, &error);
    free(jsonString);

    Municipio *municipio1 = createMunicipioFromJson(json_array_get(root, 0));
    Municipio *municipio2 = createMunicipioFromJson(json_array_get(root, 5569));

    json_decref(root);

    assert(municipio1 != NULL);
    assert(municipio2 != NULL);

    assert(municipio1->codigo_ibge == 5200050);
    assert(municipio1->latitude == -16.7573);
    assert(municipio1->longitude == -49.4412);
    assert(municipio1->capital == 0);
    assert(municipio1->codigo_uf == 52);
    assert(municipio1->siafi_id == 1050);
    assert(municipio1->ddd == 62);
    assert(strcmp(municipio1->nome, "Abadia de Goiás") == 0);
    assert(strcmp(municipio1->fuso_horario, "America/Sao_Paulo") == 0);

    assert(municipio2->codigo_ibge == 4219853);
    assert(municipio2->latitude == -27.4521);
    assert(municipio2->longitude == -51.552);
    assert(municipio2->capital == 0);
    assert(municipio2->codigo_uf == 42);
    assert(municipio2->siafi_id == 950);
    assert(municipio2->ddd == 49);
    assert(strcmp(municipio2->nome, "Zortéa") == 0);
    assert(strcmp(municipio2->fuso_horario, "America/Sao_Paulo") == 0);

    char distance[9];
    sprintf(distance, "%.6f", distanceMunicipios(municipio1, municipio2));
    assert(strcmp(distance, "10.901111") == 0);

    destroyMunicipio(municipio1);
    destroyMunicipio(municipio2);
}

void test_hash() {

    json_error_t error;
    json_t *root = NULL;
    char *jsonString = readFile("municipios.min.json");
    
    root = json_loads(jsonString, 0, &error);
    free(jsonString);

    Municipio **municipios = calloc(json_array_size(root), sizeof(Municipio*));
    *municipios  = createMunicipioFromJson(json_array_get(root, 0));
    *(municipios + 1) = createMunicipioFromJson(json_array_get(root, 5569));

    json_decref(root);

    Hashtable *hashTable = createHashTableMunicipio(municipios, 2, 2);

    assert(hashTable != NULL);
    assert(hashTable->length == 2);
    assert(hashTable->max == 2);

    assert(getValueByKey(hashTable, 5200050) != NULL);
    assert(getValueByKey(hashTable, 4219853) != NULL);

    destroyHashTable(hashTable);

}

void test_insere() {
    int v10 = 10;
    int v15 = 15;
    int v20 = 20;
    int v50 = 50;
    int v23 = 23;
    int v30 = 30;
    int v5 = 5;
    int v7 = 7;
    int v25 = 25;
    tnode *arv;
    arv = NULL;
    assert(arv == NULL);
    
    avl_insere(&arv, &v10, comparator);    
    avl_insere(&arv, &v15, comparator);
    avl_insere(&arv, &v20, comparator);
    assert(*(int*)(arv->items->item) == 15);
    assert(*(int*)(arv->esq->items->item) == 10);
    assert(*(int*)(arv->dir->items->item) == 20);

    avl_insere(&arv, &v50, comparator);
    avl_insere(&arv, &v23, comparator);
    assert(*(int*)(arv->items->item) == 15);
    assert(*(int*)(arv->esq->items->item) == 10);
    assert(*(int*)(arv->dir->items->item) == 23);
    assert(*(int*)(arv->dir->esq->items->item) == 20);
    assert(*(int*)(arv->dir->dir->items->item) == 50);

    avl_insere(&arv, &v5, comparator);
    avl_insere(&arv, &v30, comparator);
    avl_insere(&arv, &v25, comparator);
    assert(*(int*)(arv->items->item) == 15);
    assert(*(int*)(arv->esq->items->item) == 10);
    assert(*(int*)(arv->esq->esq->items->item) == 5);
    assert(*(int*)(arv->dir->items->item) == 23);
    assert(*(int*)(arv->dir->esq->items->item) == 20);
    assert(*(int*)(arv->dir->dir->items->item) == 30);
    assert(*(int*)(arv->dir->dir->esq->items->item) == 25);
    assert(*(int*)(arv->dir->dir->dir->items->item) == 50);

    avl_insere(&arv, &v7, comparator);
    assert(*(int*)(arv->items->item) == 15);
    assert(*(int*)(arv->esq->items->item) == 7);
    assert(*(int*)(arv->esq->esq->items->item) == 5);
    assert(*(int*)(arv->esq->dir->items->item) == 10);
    assert(*(int*)(arv->dir->items->item) == 23);
    assert(*(int*)(arv->dir->esq->items->item) == 20);
    assert(*(int*)(arv->dir->dir->items->item) == 30);
    assert(*(int*)(arv->dir->dir->dir->items->item) == 50);
    assert(*(int*)(arv->dir->dir->esq->items->item) == 25);

    avl_destroi(arv);
}

int main() {
    test_file();
    test_json();
    test_municipio();
    test_hash();
    test_insere();

    return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "file.h"
#include "municipio.h"
#include "avl.h"

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

void test_rotacao() {
    tnode *x;
    tnode *y;
    tnode *a;
    tnode *b;
    tnode *c;
    tnode *arv;
    arv = NULL;
    assert(arv == NULL);
    x = malloc(sizeof(tnode));
    y = malloc(sizeof(tnode));
    a = malloc(sizeof(tnode));
    b = malloc(sizeof(tnode));
    c = malloc(sizeof(tnode));
    x->items = malloc(sizeof(LinkedList));
    y->items = malloc(sizeof(LinkedList));
    a->items = malloc(sizeof(LinkedList));
    b->items = malloc(sizeof(LinkedList));
    c->items = malloc(sizeof(LinkedList));
    x->items->item = 5;
    y->items->item = 10;
    a->items->item = 3;
    b->items->item = 7;
    c->items->item = 12;
    x->esq = a;
    x->dir = b;
    y->esq = x;
    y->dir = c;
    arv = y;
    _rd(&arv);
    assert(arv->items->item == 5);
    assert(arv->esq->items->item == 3);
    assert(arv->dir->items->item == 10);
    assert(arv->dir->dir->items->item == 12);
    assert(arv->dir->esq->items->item == 7);
    _re(&arv);
    assert(arv->items->item == 10);
    assert(arv->esq->items->item == 5);
    assert(arv->dir->items->item == 12);
    assert(arv->esq->dir->items->item == 7);
    assert(arv->esq->esq->items->item == 3);

    avl_destroi(arv);
}

void test_insere() {
    tnode *arv;
    arv = NULL;
    assert(arv == NULL);
    
    avl_insere(&arv, 10);    
    avl_insere(&arv, 15);
    avl_insere(&arv, 20);
    assert(arv->items->item == 15);
    assert(arv->esq->items->item == 10);
    assert(arv->dir->items->item == 20);

    avl_insere(&arv, 50);
    avl_insere(&arv, 23);
    assert(arv->items->item == 15);
    assert(arv->esq->items->item == 10);
    assert(arv->dir->items->item == 23);
    assert(arv->dir->esq->items->item == 20);
    assert(arv->dir->dir->items->item == 50);

    avl_insere(&arv, 5);
    avl_insere(&arv, 30);
    avl_insere(&arv, 25);
    assert(arv->items->item == 15);
    assert(arv->esq->items->item == 10);
    assert(arv->esq->esq->items->item == 5);
    assert(arv->dir->items->item == 23);
    assert(arv->dir->esq->items->item == 20);
    assert(arv->dir->dir->items->item == 30);
    assert(arv->dir->dir->esq->items->item == 25);
    assert(arv->dir->dir->dir->items->item == 50);

    avl_insere(&arv, 7);
    assert(arv->items->item == 15);
    assert(arv->esq->items->item == 7);
    assert(arv->esq->esq->items->item == 5);
    assert(arv->esq->dir->items->item == 10);
    assert(arv->dir->items->item == 23);
    assert(arv->dir->esq->items->item == 20);
    assert(arv->dir->dir->items->item == 30);
    assert(arv->dir->dir->dir->items->item == 50);
    assert(arv->dir->dir->esq->items->item == 25);

    avl_destroi(arv);
}

void test_remove() {
    tnode *arv;
    arv = NULL;
    assert(arv == NULL);
    avl_insere(&arv, 10);    
    avl_insere(&arv, 15);
    avl_insere(&arv, 20);
    avl_insere(&arv, 50);
    avl_insere(&arv, 23);
    avl_insere(&arv, 5);
    avl_insere(&arv, 30);
    avl_insere(&arv, 25);
    
    avl_remove(&arv, 15);
    assert(arv->items->item == 20);
    assert(arv->dir->items->item == 30);
    assert(arv->esq->items->item == 10);
    
    assert(arv->esq->esq->items->item == 5);

    assert(arv->dir->dir->items->item == 50);
    assert(arv->dir->esq->items->item == 23);
    assert(arv->dir->esq->dir->items->item == 25);

    avl_remove(&arv, 20);
    assert(arv->items->item == 23);
    assert(arv->dir->items->item == 30);
    assert(arv->esq->items->item == 10);
    
    assert(arv->esq->esq->items->item == 5);

    assert(arv->dir->dir->items->item == 50);
    assert(arv->dir->esq->items->item == 25);

    avl_remove(&arv, 10);
    assert(arv->items->item == 23);
    assert(arv->dir->items->item == 30);
    assert(arv->esq->items->item == 5);
    assert(arv->dir->dir->items->item == 50);
    assert(arv->dir->esq->items->item == 25);

    avl_destroi(arv);
}

void test_avl() {

    test_insere();
    test_remove(); 
    test_rotacao();

}

int main() {

    test_file();
    test_json();
    test_municipio();
    test_avl();

    return EXIT_SUCCESS;
}
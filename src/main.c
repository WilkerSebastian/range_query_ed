#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#include "file.h"
#include "municipio.h"

int main() {

    uint32_t size_json;

    json_error_t error;
    json_t *root = NULL;

    Municipio **municipios = NULL;

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

    json_decref(root);

    for (size_t i = 0;i < size_json;i++)
        destroyMunicipio(*(municipios + i));
    
    return EXIT_SUCCESS;
}
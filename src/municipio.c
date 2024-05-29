#include "municipio.h"

#include <string.h>
#include <math.h>

/* Aloca um municipio e passa os valores do json para municipio, retorna o endereço do municipio alocado */
Municipio *createMunicipioFromJson(const json_t *object) {

    Municipio *municipio = (Municipio*)malloc(sizeof(Municipio));

    municipio->codigo_ibge = (uint32_t)json_integer_value(json_object_get(object, "codigo_ibge"));
    municipio->latitude = json_real_value(json_object_get(object, "latitude"));
    municipio->longitude = json_real_value(json_object_get(object, "longitude"));
    municipio->capital = (uint8_t)json_integer_value(json_object_get(object, "capital"));
    municipio->codigo_uf = (uint8_t)json_integer_value(json_object_get(object, "codigo_uf"));
    municipio->siafi_id = (uint16_t)json_integer_value(json_object_get(object, "siafi_id"));
    municipio->ddd = (uint8_t)json_integer_value(json_object_get(object, "ddd"));

    municipio->nome = (char*)malloc(json_string_length(json_object_get(object, "nome")) + 1);
    municipio->fuso_horario = (char*)malloc(json_string_length(json_object_get(object, "fuso_horario")) + 1);

    strcpy(municipio->nome, json_string_value(json_object_get(object, "nome")));
    strcpy(municipio->fuso_horario, json_string_value(json_object_get(object, "fuso_horario")));

    return municipio;

}

/* imprime no stdout os valores do municipio */
void printMunicipio(const Municipio *municipio) {

    printf("Código IBGE: %d\n", municipio->codigo_ibge);
    printf("Nome: %s\n", municipio->nome);
    printf("Latitude: %f\n", municipio->latitude);
    printf("Longitude: %f\n", municipio->longitude);
    printf("Capital: %s\n", municipio->capital ? "SIM" : "NÃO");
    printf("Código UF: %d\n", municipio->codigo_uf);
    printf("Siafi ID: %d\n", municipio->siafi_id);
    printf("DDD: %d\n", municipio->ddd);
    printf("Fuso Horário: %s\n", municipio->fuso_horario);
    printf("\n");

}

/* desaloca o municipio da memoria */
void destroyMunicipio(Municipio *municipio) {

    if (municipio == NULL)
        return;

    if (municipio->nome != NULL)
        free(municipio->nome);
    
    if (municipio != NULL)
        free(municipio->fuso_horario);

    free(municipio);

}

/* calcula a distancia entre dois municipios */
double distanceMunicipios(Municipio *m1, Municipio *m2) {

    // disntacia entre dois pontos sqrt( (x2 - x1)² + (y2 - y1)² ) 
    return sqrt(pow((m2->longitude - m1->longitude), 2) + pow((m2->latitude - m1->latitude), 2));

}
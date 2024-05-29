#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <jansson.h>

typedef struct {
    
    uint32_t codigo_ibge;
    char *nome;
    double latitude;
    double longitude;
    bool capital;
    uint8_t codigo_uf;
    uint16_t siafi_id;
    uint8_t ddd;
    char *fuso_horario;

} Municipio;

Municipio *createMunicipioFromJson(const json_t *object);

void printMunicipio(const Municipio *municipio);

void destroyMunicipio(Municipio *municipio);

double distanceMunicipios(Municipio *m1, Municipio *m2);
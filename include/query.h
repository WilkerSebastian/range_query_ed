#pragma once

#include "municipio.h"
#include "avl.h"

typedef struct {
    char *minNome;
    char *maxNome;
    double *minLatitude;
    double *maxLatitude;
    double *minLongitude;
    double *maxLongitude;
    uint8_t *minCodigo_uf;
    uint8_t *maxCodigo_uf;
    uint8_t *minDdd;
    uint8_t *maxDdd;
} Query;

uint32_t *query(Query requires);
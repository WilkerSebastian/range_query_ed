#pragma once

#include "municipio.h"

typedef struct {
    uint32_t *minNome;
    uint32_t *maxNome;
    double *minLatitude;
    double *maxLatitude;
    double *minLongitude;
    double *maxLongitude;
    uint32_t *minCodigo_uf;
    uint32_t *maxCodigo_uf;
    uint32_t *minDdd;
    uint32_t *maxDdd;
} Query;

Municipio *query(Query requires);
#pragma once

#include "municipio.h"

typedef struct {
    char *nome;
    double minLatitude;
    double maxLatitude;
    double minLongitude;
    double maxLongitude;
    double minCodigo_uf;
    double maxCodigo_uf;
    uint8_t minDdd;
    uint8_t maxDdd;
} Query;

Municipio *query(Query requires);
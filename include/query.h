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

uint32_t *query(Query *requires, tnode **avls, uint32_t *size);

uint32_t *removeDuplicates(uint32_t *arr, uint32_t *size);
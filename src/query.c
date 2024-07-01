#include "query.h"
#include "comparators.h"

uint32_t *query(Query *requires, tnode **avls, uint32_t *size) {

    uint32_t resultSize[] = {0, 0, 0, 0, 0};
    uint32_t **results = (uint32_t **)calloc(5, sizeof(uint32_t *));

    if (requires->minNome != NULL && requires->maxNome != NULL)
        results[0] = searchRange(avls[0], requires->minNome, requires->maxNome, comparatorString, &resultSize[0]);

    if (requires->minLatitude != NULL && requires->maxLatitude != NULL)
        results[1] = searchRange(avls[1], requires->minLatitude, requires->maxLatitude, comparatorDouble, &resultSize[1]);

    if (requires->minLongitude != NULL && requires->maxLongitude != NULL)
        results[2] = searchRange(avls[2], requires->minLongitude, requires->maxLongitude, comparatorDouble, &resultSize[2]);

    if (requires->minCodigo_uf != NULL && requires->maxCodigo_uf != NULL)
        results[3] = searchRange(avls[3], requires->minCodigo_uf, requires->maxCodigo_uf, comparatorSmallUnsignedInteger, &resultSize[3]);

    if (requires->minDdd != NULL && requires->maxDdd != NULL)
        results[4] = searchRange(avls[4], requires->minDdd, requires->maxDdd, comparatorSmallUnsignedInteger, &resultSize[4]);

    uint32_t totalSize = 0;
    for (int i = 0; i < 5; i++) 
        totalSize += resultSize[i];

    uint32_t *tempArray = (uint32_t *)malloc(sizeof(uint32_t) * totalSize);
    uint32_t index = 0;

    for (uint32_t i = 0; i < 5; i++) 
        if (resultSize[i] > 0) 
            for (uint32_t j = 0; j < resultSize[i]; j++) 
                tempArray[index++] = results[i][j];

    tempArray = removeDuplicates(tempArray, &totalSize);

    *size = totalSize;

    free(results);

    return tempArray;
}

uint32_t *removeDuplicates(uint32_t *arr, uint32_t *size) {
    
    if (*size == 0) 
        return arr;

    // Ordenar o array usando qsort do stdlib
    qsort(arr, *size, sizeof(uint32_t), comparatorUnsignedInteger);

    uint32_t *temp = (uint32_t *)malloc(sizeof(uint32_t) * (*size));
    uint32_t j = 0;

    for (uint32_t i = 0; i < *size - 1; i++) 
        if (arr[i] != arr[i + 1]) 
            temp[j++] = arr[i];
     
    temp[j++] = arr[*size - 1];

    // Atualizar o tamanho do array resultante
    *size = j;

    // Realocar o array para o tamanho correto e liberar memória
    arr = (uint32_t *)realloc(arr, sizeof(uint32_t) * (*size));
    for (uint32_t i = 0; i < *size; i++)
        arr[i] = temp[i];

    free(temp);

    return arr;
}

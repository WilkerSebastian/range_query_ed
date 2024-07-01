#include "comparators.h"

#include <string.h>
#include <stdint.h>

int comparatorDouble(titem item1, titem item2) {

    double diff = *(double*)item1 - *(double*)item2;
    
    if (diff < 0) 
        return -1;
    
    if (diff > 0) 
        return 1;

    return 0;

}

int comparatorString(titem item1, titem item2) {
    return strcmp((char *) item1, (char *) item2);
}

int comparatorSmallUnsignedInteger(titem item1, titem item2) {
    return (*(uint8_t*)item1) - (*(uint8_t*)item2);
}

// esse vai ser usado para a função qsort
int comparatorUnsignedInteger(const void *a, const void *b) {
    return (*(uint32_t *)a - *(uint32_t *)b);
}
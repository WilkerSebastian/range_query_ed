#include "comparators.h"

#include <string.h>
#include <stdint.h>

int comparatorUnsignedInteger(titem item1, titem item2) {
    return (*(uint32_t*)item1) - (*(uint32_t*)item2);
}

int comparatorDobule(titem item1, titem item2) {
    return (*(double*)item1) - (*(double*)item2);
}

int comparatorString(titem item1, titem item2) {
    return strcmp((char*)item1, (char*)item2);
}

int comparatorSmallUnsignedInteger(titem item1, titem item2) {
    return (*(uint8_t*)item1) - (*(uint8_t*)item2);
}
#pragma once

#include <stdint.h>
#include <municipio.h>

// Irei implementar uma hash table com lista encadeada

typedef struct hashNode {
    uint32_t key;
    Municipio *value;
    struct hashNode *next;
} NodeHash;

typedef struct {
    NodeHash **table;
    uint32_t max;
    uint32_t length;
} Hashtable;

Hashtable *createHashTableMunicipio(Municipio **municipios, uint32_t n, uint32_t MAX_ZISE);

NodeHash *createNodeHash(uint32_t key, Municipio* value);

void setKeyValue(Hashtable *hashTable, uint32_t key, Municipio* value);

Municipio *getValueByKey(Hashtable *hashTable, uint32_t key);

uint64_t hashDJB2(uint32_t key);

uint32_t indexHash(uint32_t key, uint32_t size);

void destroyHashTable(Hashtable *hashTable);
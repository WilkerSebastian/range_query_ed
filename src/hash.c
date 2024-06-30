#include "hash.h"

Hashtable *createHashTableMunicipio(Municipio **municipios, uint32_t n, uint32_t MAX_ZISE) {

    Hashtable *hashTable = (Hashtable*)malloc(sizeof(Hashtable));

    hashTable->max = MAX_ZISE;
    hashTable->length = 0;
    hashTable->table = (NodeHash**)calloc(hashTable->max, sizeof(NodeHash*));

    if (municipios != NULL) {
        for (uint32_t i = 0; i < n; i++) {
            Municipio *municipio = *(municipios + i);
            setKeyValue(hashTable, municipio->codigo_ibge, municipio);
        }
    }
    
    return hashTable;

}

NodeHash *createNodeHash(uint32_t key, Municipio* value) {

    NodeHash *node = (NodeHash*)malloc(sizeof(NodeHash));
    node->key = key;
    node->value = value;
    node->next = NULL;

    return node;

}

void setKeyValue(Hashtable *hashTable, uint32_t key, Municipio* value) {

    uint32_t index = indexHash(key, hashTable->max);
    NodeHash *fisrt = *(hashTable->table + index);
    NodeHash *current = createNodeHash(key, value);

    current->next = fisrt;
    *(hashTable->table + index) = current;

    hashTable->length++;

}

Municipio *getValueByKey(Hashtable *hashTable, uint32_t key) {

    uint32_t index = indexHash(key, hashTable->max);
    NodeHash *current = hashTable->table[index];

    while (current != NULL) {
        if (current->key == key)
            return current->value; 
        
        current = current->next;
    }
    return NULL;

}

uint64_t hashDJB2(uint32_t key) {

    uint64_t hash = 5381;
    hash = ((hash << 5) + hash) + key; 
    return hash;

}

uint32_t indexHash(uint32_t key, uint32_t size) {

    uint64_t hash = hashDJB2(key);

    return hash % size;

}

void destroyHashTable(Hashtable *hashTable) {

    if (hashTable == NULL) 
        return;

    if (hashTable->table != NULL) {
        for (uint32_t i = 0; i < hashTable->max; i++) {
            NodeHash *current = *(hashTable->table + i);
            while (current != NULL) {
                NodeHash *tmp = current;
                current = current->next;
                free(tmp);
            }
        }
        free(hashTable->table);
    }

    free(hashTable);

}
#pragma once

#include <stdint.h>
#include "query.h"
#include "hash.h"

#define YES 1
#define NO 0

#define EXIT 0
#define QUERY 1

#define SMALL_INT 1
#define FLOAT 2
#define STRING 3

int8_t main_menu();

Query *query_menu();

int8_t insert_query(const char *name);

void** min_max(const char *name, int8_t TYPE);

char* readLine();

void printResult(Hashtable *table, uint32_t *result, uint32_t size);

void clear();
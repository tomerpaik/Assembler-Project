#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "general_functions.h"
#define MAX_MACRO_NAME_LENGTH 100
#define MAX_MACRO_BODY 100

typedef struct HashNode {
    char key[MAX_MACRO_NAME_LENGTH];
    char *value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode** buckets;
    size_t size;
} HashTable;

HashTable* create_hash_table(size_t size);
void insert_table(HashTable* table, const char* key, const char* value);
char* search_table(HashTable* table, const char* key);
void free_hash_table(HashTable* table);
int in_table(HashTable* table, const char* value);

#endif

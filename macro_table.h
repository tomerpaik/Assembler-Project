#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H
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
} Macro_Table;

Macro_Table* create_macro_table(size_t size);
void insert_macro_table(Macro_Table* table, const char* key, const char* value);
char* search_macro_table(Macro_Table* table, const char* key);
void free_macro_table(Macro_Table* table);
int is_in_macro_table(Macro_Table* table, const char* value);

#endif

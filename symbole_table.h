#ifndef SYMBOLE_TABLE_H
#define SYMBOLE_TABLE_H
#include "globals.h"
#include "general_functions.h"
typedef struct label_address {
    char label_name[MAX_LABEL_LENGTH];
    int assembly_line;
    int is_data_line;
} label_address;

typedef struct SymbolNode {
    label_address label;
    struct SymbolNode* next;
} SymbolNode;

typedef struct {
    SymbolNode** buckets;
    int size;
} symbol_table;

unsigned int hash(const char* key, int size);

symbol_table* create_symbol_table();
void free_symbol_table(symbol_table* table);
void insert_label(symbol_table* table, const char* label_name, int assembly_line, int is_data_line);
label_address* search_label(symbol_table* table, const char* label_name);
unsigned int hash(const char* str, int table_size);

#endif
#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H
#define MAX_MACRO_NAME_LENGTH 32
#define MAX_MACRO_BODY 100
#include "globals.h"
#include "linked_list.h"

typedef Node hash_table[TABLE_SIZE];

unsigned int hash(const char* key);
void insert_table(hash_table table, char* key, void* value);
void* search_table(hash_table table, char* key);
int is_in_table(hash_table table, char* key);
void print_table(hash_table table);
void free_table(hash_table table);
#endif

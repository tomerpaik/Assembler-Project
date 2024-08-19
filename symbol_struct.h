#ifndef SYMBOL_STRUCT_H
#define SYMBOL_STRUCT_H

#include "first_pass.h"

enum symbol_flag {
    DATA_FLAG,
    OPCODE_FLAG,
    EXTERN_FLAG,
    ENTRY_FLAG_DATA,
    ENTRY_FLAG_OPCODE
} ;
typedef struct symbol{
    int count;
    enum symbol_flag flag;
}*Symbol;


enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table);

void print_symbol_table(hash_table table);
enum symbol_flag get_symbol_flag(hash_table symbol_table, char *symbol_name);
void update_symbol_flag(hash_table symbol_table, char *symbol_name, enum symbol_flag new_symbol_flag);
char* get_flag_name(enum symbol_flag flag);
enum symbol_flag get_symbol_count(hash_table symbol_table, char *symbol_name);

void print_symbol_table(hash_table table);
void print_array(short arr[], int size);
#endif

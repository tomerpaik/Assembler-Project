#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "hash_table.h"
#include "general_functions.h"
#include "errors_handle.h"
#include "lexer.h"

extern int DC;
extern int IC;

enum symbol_flag {
    DATA_FLAG,
    CODE_FLAG,
    EXTERN_FLAG,
    ENTRY_FLAG
} ;
typedef struct symbol{
    int count;
    enum symbol_flag flag;
}*Symbol;

short code_image[MAX_MEMORY_SPACE];
short data_image[MAX_MEMORY_SPACE];

int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table);
enum project_error valid_symbol(char *word, hash_table macro_table);
enum project_error valid_data(char *line);
enum project_error valid_string(char *line);
enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table);
enum project_error encode_data(char* data_argument);
#endif

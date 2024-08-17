#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "hash_table.h"
#include "general_functions.h"
#include "errors_handle.h"
#include "colors.h"
#include "lexer.h"
#include "encode.h"
#include "validation.h"

extern int DC;
extern int IC;

enum symbol_flag {
    DATA_FLAG,
    OPCODE_FLAG,
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
enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table);

void print_symbol_table(hash_table table);
enum project_error valid_opcode(char *opcode_operands, char* opcode_name, hash_table symbol_table, hash_table macro_table);
enum symbol_flag get_symbol_flag(hash_table symbol_table, char *symbol_name);

int find_addressing_method(char* operand, hash_table symbol_table);
void print_symbol_table(hash_table table);
#endif

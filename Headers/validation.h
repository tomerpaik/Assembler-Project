#ifndef VALIDATION_H
#define VALIDATION_H
#include "first_pass.h"

typedef struct {
    char *first_word;
    char *line;
    int offset;
    int line_num;
    char *am_path;
} * EntryExternContent;


enum project_error valid_symbol(char *symbol_name, hash_table macro_table);
enum project_error valid_data(char *line);
enum project_error valid_string(char *string);
EntryExternContent init_entry_extern_context(char *first_word, char *line, int offset, int line_num, char *am_path);
int handel_entry_extern(EntryExternContent context, hash_table symbol_table, hash_table macro_tabel);
void free_entry_extern_context(EntryExternContent context);
int find_addressing_method(char* operand);
enum project_error handel_opcode(char *opcode_operands, char* opcode_name, hash_table symbol_table, char * symbol_name, int symbol_flag);
#endif

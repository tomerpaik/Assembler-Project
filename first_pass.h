#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "hash_table.h"
#include "general_functions.h"
#include "errors_handle.h"
#include "colors.h"
#include "lexer.h"

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

typedef struct {
    char *first_word;
    char *line;
    int offset;
    int line_num;
    char *am_path;
} * EntryExternContent;

short code_image[MAX_MEMORY_SPACE];
short data_image[MAX_MEMORY_SPACE];

int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table);
enum project_error valid_symbol(char *symbol_name, hash_table macro_table);
enum project_error valid_data(char *line);
enum project_error valid_string(char *string);
enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table);
enum project_error encode_data(char* data_arguments);
enum project_error encode_string(char* string_argument);
void print_symbol_table(hash_table table);
enum project_error valid_opcode(char *opcode_line, hash_table symbol_table);
enum symbol_flag get_symbol_flag(hash_table symbol_table, char *symbol_name);
EntryExternContent init_entry_extern_context(char *first_word, char *line, int offset, int line_num, char *am_path);
int handle_entry_extern_context(EntryExternContent context, hash_table symbol_table, hash_table macro_tabel);
int append_to_code_image(short encoded_value);
void free_entry_extern_context(EntryExternContent context);
int find_addressing_method(char* operand, hash_table symbol_table);
/**
 * Appends an encoded short value to the global data_image array.
 * @param encoded_value The short value to append.
 * @return 0 if successful, or -1 if there is not enough space.
 */
int append_to_data_image(short encoded_value);
void print_symbol_table(hash_table table);
#endif

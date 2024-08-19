#ifndef SECOND_PASS_
#define SECOND_PASS_H
#include "hash_table.h"
#include "finish_encode.h"
#include "errors_handle.h"
#include "first_pass.h"

int second_pass(char * am_path, hash_table symbol_table);
void create_object_file(char * file_name);
void update_symbol_table_values(hash_table symbol_table);
enum project_error handle_operand_symbol(char *operands, hash_table symbol_table, char * file_name);
void append_to_ext_ent_file(char *filename, char * ending, char *symbol_name, int line_number);


#endif
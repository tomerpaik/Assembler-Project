#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#include "hash_table.h"
#include "finish_encode.h"
#include "errors_handle.h"
#include "symbol_struct.h"
#include "encode.h"
int second_pass(char * am_path, hash_table symbol_table);
void create_object_file(char * file_name);
enum project_error handle_operand_symbol(char *operands, hash_table symbol_table);
void update_symbol_table_values(hash_table symbol_table);


#endif
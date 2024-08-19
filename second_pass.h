#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#include "hash_table.h"
#include "finish_encode.h"
#include "errors_handle.h"
#include "encode.h"
int second_pass(char * am_path, hash_table symbol_table);
enum project_error handle_operand_symbol(char *operands, hash_table symbol_table);



#endif
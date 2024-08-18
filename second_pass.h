#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#include "hash_table.h"
#include "errors_handle.h"
#include "encode.h"
int second_pass(char * am_path, hash_table symbol_table);
void encode_symbol(hash_table symbol_table, char * symbol_name);
enum project_error find_symbol_check(char *opcode_operands, char* opcode_name, hash_table symbol_table, char * symbol_name);
#endif
#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "hash_table.h"
#include "general_functions.h"
#include "errors_handle.h"
#include "lexer.h"
int first_pass(char * am_path, hash_table macro_table);
enum project_error valid_symbol(char *word, hash_table macro_table);
enum project_error is_data_string(char *word);
#endif

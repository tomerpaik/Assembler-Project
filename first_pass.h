#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "hash_table.h"
#include "general_functions.h"
#include "errors.h"
#include "lexer.h"
int first_pass(char * am_path, hash_table macro_table);
int is_symbol(char *word, int *error, hash_table macro_table);
#endif

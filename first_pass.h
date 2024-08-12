#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "general_functions.h"
#include "errors.h"
#include "lexer.h"
#include "hash_table.h"
int first_pass(char * am_path);
int is_symbol(const char *word, int *error);
#endif

#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "hash_table.h"
#include "lexer.h"
#include "validation.h"
#include "general_functions.h"
#include "errors_handle.h"
#include "encode.h"
#include "symbol_struct.h"

extern int DC;
extern int IC;



short code_image[MAX_MEMORY_SPACE];
short data_image[MAX_MEMORY_SPACE];

int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table);

#endif

#ifndef MACRO_DEFINER_H
#define MACRO_DEFINER_H
#include "hash_table.h"
#include "general_functions.h"
#include "globals.h"
#include "lexer.h"

/* Function to combine two strings */
int pre_assembler(char * file_name, hash_table macro_table);
int process_macros(FILE * inputFile, FILE * outputFile, char * file_name, hash_table macroTable);
int is_empty_after_key(char *line);
int is_valid_macro_name(char *name, int line_num, char * file_name);
void add_to_macro_body(hash_table macro_table, char * line, char * macroName, int * macro_len);
void set_body_value(hash_table table, char *macroName, char *new_macro_val);
#endif /* MACRO_DEFINER_H */

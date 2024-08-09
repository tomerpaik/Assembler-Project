#ifndef MACRO_DEFINER_H
#define MACRO_DEFINER_H
#include "hash_table.h"
#include "general_functions.h"

/* Function to combine two strings */
int pre_assembler(char * as_file);
const char* combineFilePath(const char* basePath, const char* extension);
int process_macros(FILE * inputFile, FILE * outputFile, HashTable* macroTable);

int is_macro_additional_after_endmacr(char *line, int offset);
int is_additional_text_after_macro_name(char *line, int total_offset);
int is_valid_macro_name(char *name);

int is_macr(char *line);
int is_endmacr(char *line);

int get_macro_name(const char *line, char *macroName, int macr_offset);

#endif /* MACRO_DEFINER_H */

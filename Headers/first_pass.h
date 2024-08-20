#ifndef FIRST_PASS_H
#define FIRST_PASS_H

/**
 * @file first_pass.h
 * @brief Handles the first pass of the assembler process.
 *
 * This file contains declarations for functions and global variables used
 * during the first pass of the assembler. The first pass involves parsing
 * the assembly file, handling symbols, and encoding data.
 */

#include "hash_table.h"
#include "lexer.h"
#include "validation.h"
#include "general_functions.h"
#include "errors_handle.h"
#include "encode.h"
#include "symbol_struct.h"

/* Global counters for Data Counter (DC) and Instruction Counter (IC) */
extern int DC;
extern int IC;

/* Memory space for the code and data images */
short code_image[MAX_MEMORY_SPACE];
short data_image[MAX_MEMORY_SPACE];

/**
 * @brief Executes the first pass of the assembly process.
 *
 * This function reads the assembly file generated after the macro expansion
 * (with `.am` extension) and processes it line by line. It handles symbol
 * definitions, data encoding, and checks for errors in the assembly code.
 *
 * @param am_path The path to the assembly file with the `.am` extension.
 * @param macro_table The hash table containing the macros.
 * @param symbol_table The hash table for storing symbols encountered during the first pass.
 * @return 1 if errors were found during the first pass, 0 otherwise.
 */
int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table);

#endif /* FIRST_PASS_H */

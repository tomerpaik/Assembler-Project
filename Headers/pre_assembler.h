#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

/**
 * @file pre_assembler.h
 * @brief Pre-assembler functions for handling macros in assembly files.
 *
 * This file contains declarations of functions used to handle macros in assembly files.
 * The pre-assembler processes macro definitions and calls, storing them in a hash table.
 * It then generates an output file with all macros expanded.
 */

#include "hash_table.h"
#include "lexer.h"
#include "general_functions.h"

/**
 * @brief Processes an assembly file to handle macros.
 *
 * This function opens the specified assembly file, processes its macros,
 * and writes the expanded macros to a new file.
 *
 * @param file_name The name of the assembly file (without extension).
 * @param macro_table The hash table to store macros.
 * @return 1 if processing was successful, 0 if there were errors.
 */
int pre_assembler(char * file_name, hash_table macro_table);

/**
 * @brief Processes macros within the input assembly file.
 *
 * This function reads the input file line by line, identifies macro definitions and calls,
 * and handles them appropriately. The processed content is written to the output file.
 *
 * @param inputFile The file pointer to the input assembly file.
 * @param outputFile The file pointer to the output file where macros are expanded.
 * @param file_name The name of the original assembly file.
 * @param macroTable The hash table storing the macros.
 * @return 1 if processing was successful, 0 if there were errors.
 */
int process_macros(FILE * inputFile, FILE * outputFile, char * file_name, hash_table macroTable);

/**
 * @brief Validates a macro name.
 *
 * This function checks if a given macro name is valid according to the rules defined.
 * It ensures that the name is not an instruction, register, or opcode, and meets other criteria.
 *
 * @param name The macro name to validate.
 * @param line_num The line number in the file for error reporting.
 * @param file_name The name of the file being processed.
 * @return 1 if the macro name is valid, 0 otherwise.
 */
int is_valid_macro_name(char *name, int line_num, char * file_name);

/**
 * @brief Adds a line to a macro's body in the hash table.
 *
 * This function appends a line of text to the body of an existing macro stored in the hash table.
 * The macro body is dynamically resized to accommodate new lines.
 *
 * @param macro_table The hash table containing the macro.
 * @param line The line of text to add to the macro's body.
 * @param macroName The name of the macro being updated.
 * @param macro_len Pointer to an integer tracking the current length of the macro's body.
 */
void add_to_macro_body(hash_table macro_table, char * line, char * macroName, int *macro_len);

/**
 * @brief Prints the contents of the macro table.
 *
 * This function prints all macros stored in the hash table, displaying their names and bodies.
 * The output is formatted in a table structure for clarity.
 *
 * @param table The hash table containing the macros.
 */
void print_macro_table(hash_table table);

/**
 * @brief Updates the value of a key in the hash table.
 *
 * This function updates the value associated with a given key in the hash table.
 * It is typically used to replace or modify the content of a macro.
 *
 * @param table The hash table to update.
 * @param key The key (macro name) to update.
 * @param new_value The new value (macro body) to associate with the key.
 */
void update_table_value(hash_table table, char* key, char* new_value);

#endif /* PRE_ASSEMBLER_H */
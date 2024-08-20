#ifndef SECOND_PASS_H
#define SECOND_PASS_H

/**
 * @file second_pass.h
 * @brief Functions for the second pass of the assembly process.
 *
 * This file contains declarations for functions used during the second pass of the assembler.
 * The second pass resolves symbols, handles `.entry` and `.extern` directives, and generates
 * the final object file.
 */

#include "hash_table.h"
#include "finish_encode.h"
#include "errors_handle.h"
#include "first_pass.h"

/**
 * @brief Executes the second pass of the assembly process.
 *
 * This function processes the assembly file for the second time, resolving symbols,
 * handling `.entry` and `.extern` directives, and finalizing the encoding. It also
 * generates the object file and any required external and entry files.
 *
 * @param am_path The path to the assembly file with the `.am` extension.
 * @param symbol_table The hash table containing symbols from the first pass.
 * @return 1 if errors were found during the second pass, 0 otherwise.
 */
int second_pass(char * am_path, hash_table symbol_table);

/**
 * @brief Creates the object file from the encoded code and data images.
 *
 * This function generates the object file (`.ob` extension) by writing the encoded
 * instructions and data to the file. It includes the instruction and data counters
 * at the top of the file.
 *
 * @param file_name The base name of the file (without extension).
 */
void create_object_file(char * file_name);

/**
 * @brief Updates symbol table values based on instruction counter adjustments.
 *
 * This function adjusts the values of symbols marked as data or entry data by adding
 * the instruction counter (IC) to their current value, accounting for the code section size.
 *
 * @param symbol_table The hash table containing symbols to update.
 */
void update_symbol_table_values(hash_table symbol_table);

/**
 * @brief Handles operand symbols during the second pass.
 *
 * This function processes symbols in operand positions during the second pass,
 * ensuring they are correctly encoded and resolving any errors related to their usage.
 *
 * @param operands The operand string containing the symbols to process.
 * @param symbol_table The hash table containing symbols.
 * @param file_name The name of the assembly file being processed.
 * @return An error code if a symbol-related error is found, or `Error_Success` if successful.
 */
enum project_error handle_operand_symbol(char *operands, hash_table symbol_table, char * file_name);

/**
 * @brief Appends symbol information to an external or entry file.
 *
 * This function writes the symbol name and its address to the appropriate file
 * (either `.ext` for external symbols or `.ent` for entry symbols).
 *
 * @param filename The base name of the file (without extension).
 * @param ending The file extension to use (e.g., ".ext" or ".ent").
 * @param symbol_name The name of the symbol to write.
 * @param line_number The line number or address associated with the symbol.
 */
void append_to_ext_ent_file(char *filename, char * ending, char *symbol_name, int line_number);

#endif /* SECOND_PASS_H */

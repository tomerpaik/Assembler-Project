#ifndef VALIDATION_H
#define VALIDATION_H

/**
 * @file validation.h
 * @brief Functions for validating assembly code and processing symbols, data, and opcodes.
 *
 * This file contains function declarations for validating different components
 * of the assembly code, such as symbols, data, and strings. It also includes
 * functions for handling `.entry` and `.extern` directives and processing opcodes.
 */

#include "first_pass.h"

/* Structure to store context information for handling entry and extern symbols */
typedef struct {
    char *first_word;  /**< The first word in the line (e.g., ".entry" or ".extern") */
    char *line;        /**< The full line being processed */
    int offset;        /**< The offset to the current position in the line */
    int line_num;      /**< The current line number in the assembly file */
    char *am_path;     /**< The path to the assembly file */
} * EntryExternContent;

/**
 * @brief Validates a symbol name.
 *
 * This function checks if a given symbol name is valid according to the assembly language rules.
 * It ensures the symbol is not an instruction, opcode, register, or macro name, and adheres to naming conventions.
 *
 * @param symbol_name The symbol name to validate.
 * @param macro_table The hash table containing macro names to avoid conflicts.
 * @return An error code if the symbol is invalid, or `Error_Success` if it is valid.
 */
enum project_error valid_symbol(char *symbol_name, hash_table macro_table);

/**
 * @brief Validates the `.data` directive in an assembly line.
 *
 * This function checks if the data values following the `.data` directive are valid.
 * It verifies that the values are within the allowed range and properly formatted.
 *
 * @param line The line containing the `.data` directive and its values.
 * @return An error code if the data is invalid, or `Error_Success` if it is valid.
 */
enum project_error valid_data(char *line);

/**
 * @brief Validates the `.string` directive in an assembly line.
 *
 * This function checks if the string following the `.string` directive is properly formatted
 * with quotes and contains printable characters.
 *
 * @param string The line containing the `.string` directive and its string value.
 * @return An error code if the string is invalid, or `Error_Success` if it is valid.
 */
enum project_error valid_string(char *string);

/**
 * @brief Initializes a context structure for handling `.entry` and `.extern` directives.
 *
 * This function creates and initializes a context structure with the relevant information
 * from the line containing the `.entry` or `.extern` directive.
 *
 * @param first_word The directive (either `.entry` or `.extern`).
 * @param line The line containing the directive.
 * @param offset The offset to the current position in the line.
 * @param line_num The current line number in the assembly file.
 * @param am_path The path to the assembly file.
 * @return A pointer to the initialized context structure.
 */
EntryExternContent init_entry_extern_context(char *first_word, char *line, int offset, int line_num, char *am_path);

/**
 * @brief Handles the processing of `.entry` and `.extern` directives.
 *
 * This function validates and processes the symbol following an `.entry` or `.extern` directive.
 * It checks for errors and updates the symbol table accordingly.
 *
 * @param context The context structure containing the directive and related information.
 * @param symbol_table The hash table containing symbols.
 * @param macro_table The hash table containing macro names.
 * @return 1 if processing is successful, 0 if there are errors.
 */
int handel_entry_extern(EntryExternContent context, hash_table symbol_table, hash_table macro_table);

/**
 * @brief Frees the memory allocated for an `EntryExternContent` structure.
 *
 * This function releases the memory used by the context structure after processing is complete.
 *
 * @param context The context structure to free.
 */
void free_entry_extern_context(EntryExternContent context);

/**
 * @brief Determines the addressing method of an operand.
 *
 * This function identifies the addressing method used by an operand in an instruction.
 * The method is returned as an integer value corresponding to the addressing type.
 *
 * @param operand The operand whose addressing method is to be determined.
 * @return An integer representing the addressing method.
 */
int find_addressing_method(char* operand);

/**
 * @brief Handles the processing of an opcode and its operands.
 *
 * This function validates and encodes an opcode and its operands in the assembly code.
 * It checks for correct addressing methods and updates the symbol table if needed.
 *
 * @param opcode_operands The operands of the opcode.
 * @param opcode_name The name of the opcode.
 * @param symbol_table The hash table containing symbols.
 * @param symbol_name The name of the symbol if defined.
 * @param symbol_flag A flag indicating if the symbol is being defined.
 * @return An error code if the opcode or operands are invalid, or `Error_Success` if they are valid.
 */
enum project_error handel_opcode(char *opcode_operands, char* opcode_name, hash_table symbol_table, char * symbol_name, int symbol_flag);

char* process_operand(char** operand_str, int* addressing_metho);
#endif /* VALIDATION_H */

#ifndef SYMBOL_STRUCT_H
#define SYMBOL_STRUCT_H

/**
 * @file symbol_struct.h
 * @brief Functions and structures for managing symbols in the assembler.
 *
 * This file contains declarations for functions and structures used to manage
 * symbols during the assembly process. It includes symbol creation, retrieval,
 * and updates within the symbol table.
 */

#include "first_pass.h"

/* Enumeration to represent different types of symbol flags */
enum symbol_flag {
    DATA_FLAG,         /**< Indicates a data symbol */
    OPCODE_FLAG,       /**< Indicates an opcode symbol */
    EXTERN_FLAG,       /**< Indicates an external symbol */
    ENTRY_FLAG_DATA,   /**< Indicates a data symbol marked as entry */
    ENTRY_FLAG_OPCODE  /**< Indicates an opcode symbol marked as entry */
};

/* Structure to represent a symbol with its associated attributes */
typedef struct symbol {
    int count;                   /**< The address or value associated with the symbol */
    enum symbol_flag flag;       /**< The flag indicating the type of the symbol */
} *Symbol;

/**
 * @brief Adds a new symbol to the symbol table.
 *
 * This function creates a new symbol with the specified name and flag,
 * and inserts it into the symbol table. If the symbol name is already
 * taken, it returns an error.
 *
 * @param symbol_name The name of the symbol to add.
 * @param type_flag The flag indicating the type of the symbol (e.g., data, opcode).
 * @param symbol_table The hash table where the symbol will be stored.
 * @return An error code if the symbol name is already taken, or `Error_Success` if successful.
 */
enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table);

/**
 * @brief Retrieves the flag associated with a symbol.
 *
 * This function looks up a symbol in the symbol table and returns its associated flag.
 *
 * @param symbol_table The hash table containing symbols.
 * @param symbol_name The name of the symbol to retrieve.
 * @return The flag associated with the symbol, or -1 if the symbol is not found.
 */
enum symbol_flag get_symbol_flag(hash_table symbol_table, char *symbol_name);

/**
 * @brief Retrieves the count associated with a symbol.
 *
 * This function looks up a symbol in the symbol table and returns its count value.
 *
 * @param symbol_table The hash table containing symbols.
 * @param symbol_name The name of the symbol to retrieve.
 * @return The count associated with the symbol, or -1 if the symbol is not found.
 */
enum symbol_flag get_symbol_count(hash_table symbol_table, char *symbol_name);

/**
 * @brief Updates the flag of an existing symbol.
 *
 * This function changes the flag of a specified symbol in the symbol table.
 *
 * @param symbol_table The hash table containing symbols.
 * @param symbol_name The name of the symbol to update.
 * @param new_symbol_flag The new flag to assign to the symbol.
 */
void update_symbol_flag(hash_table symbol_table, char *symbol_name, enum symbol_flag new_symbol_flag);


/**
 * DEBUG
 *
 *
 */
char* get_flag_name(enum symbol_flag flag);
void print_symbol_table(hash_table table);

#endif /* SYMBOL_STRUCT_H */

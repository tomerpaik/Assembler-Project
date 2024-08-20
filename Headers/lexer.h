#ifndef LEXER_H
#define LEXER_H

/**
 * @file lexer.h
 * @brief Functions and structures for parsing assembly language.
 *
 * This file contains declarations of functions and structures used for parsing
 * and processing assembly language commands, including opcode recognition,
 * instruction validation, and handling various assembly components.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "general_functions.h"

/* Represents an operation code with its associated properties */
typedef struct op_code {
    char *opcode;               /**< The opcode string (e.g., "mov", "add") */
    int arg_num;                /**< The number of arguments the opcode requires */
    int source_address[6];      /**< Valid addressing modes for the source operand */
    int destination_address[6]; /**< Valid addressing modes for the destination operand */
} op_code;

/* Represents different parts of a command in the assembly code */
typedef struct command_parts {
    char *label;    /**< The label associated with the command */
    int opcode;     /**< The opcode of the command */
    char *source;   /**< The source operand */
    char *dest;     /**< The destination operand */
} command_parts;

/* Represents different parts of a data line in the assembly code */
typedef struct inst_parts {
    char *label;    /**< The label associated with the instruction */
    short *nums;    /**< An array of short integers representing the instruction data */
    int len;        /**< The length of the data in nums, including '0' at the end of a string */
    char *arg_label;/**< The label associated with an argument, if applicable */
    int is_extern;  /**< Flag indicating whether the instruction is marked as external */
} inst_parts;

/* Declaration of the external OPCODES array that holds the defined opcodes */
extern op_code OPCODES[];

/**
 * @brief Checks if a string matches a known instruction.
 *
 * This function checks if the provided string corresponds to one of the predefined instructions.
 *
 * @param str The string to check.
 * @return 1 if the string is a valid instruction, 0 otherwise.
 */
int is_instruction(char *str);

/**
 * @brief Retrieves the index of an opcode in the predefined list.
 *
 * This function compares the provided string with known opcodes and returns the index
 * of the matching opcode in the `OPCODES` array. If the opcode is not found, it returns -1.
 *
 * @param str The string representing the opcode.
 * @return The index of the opcode in the `OPCODES` array, or -1 if not found.
 */
int opcode_num(char *str);

/**
 * @brief Retrieves the index of a register in the predefined list.
 *
 * This function compares the provided string with known register names and returns the index
 * of the matching register in the `REGS` array. If the register is not found, it returns -1.
 *
 * @param str The string representing the register.
 * @return The index of the register in the `REGS` array, or -1 if not found.
 */
int register_num(char *str);

/**
 * @brief Extracts a substring from a source string.
 *
 * This function creates a new string containing a substring from the source string,
 * starting and ending at the specified positions.
 *
 * @param source The source string.
 * @param start The starting position of the substring.
 * @param end The ending position of the substring.
 * @return A pointer to the newly created substring.
 */
char* substring(char *source, int start, int end);

/**
 * @brief Checks if a line is empty or contains only whitespace.
 *
 * This function determines whether a line is empty or consists solely of whitespace characters.
 *
 * @param line The line of text to check.
 * @return 1 if the line is empty or contains only whitespace, 0 otherwise.
 */
int is_empty_line(const char *line);

/**
 * @brief Removes leading and trailing whitespace from a string.
 *
 * This function trims whitespace from both ends of the string and returns a new string.
 *
 * @param word The string to trim.
 * @return A pointer to the newly created string without leading or trailing whitespace.
 */
char* str_without_spaces(char * word);

/**
 * @brief Checks if a line is a comment or empty.
 *
 * This function determines whether a line is either a comment or empty.
 *
 * @param line The line of text to check.
 * @return 1 if the line is a comment or empty, 0 otherwise.
 */
int is_comment_empty_line(char * line);

#endif /* LEXER_H */

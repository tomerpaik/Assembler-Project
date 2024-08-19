#ifndef C_PROJECT_LEXER_H
#define C_PROJECT_LEXER_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "globals.h"
#include "general_functions.h"

/* Represents an operation code with its associated opcode and argument count */
typedef struct op_code {
    char *opcode;    /* The opcode corresponding to the operation */
    int arg_num;     /* The number of arguments for the operation */
    int source_address[6]; /*possible addressing system for source opernad*/
    int destination_address[6]; /*possible addressing system for target opernad*/
} op_code;
/* Represents different parts of a command */
typedef struct command_parts {
    char *label;     /* The label associated with the command */
    int opcode;      /* The opcode of the command */
    char *source;    /* The source operand of the command */
    char *dest;      /* The destination operand of the command */
} command_parts;

/* Represents different parts of a data line */
typedef struct inst_parts {
    char *label;       /* The label associated with the instruction */
    short *nums;       /* An array of short integers representing instruction data */
    int len;           /* The number of data in *nums including '0' at the end of a string */
    char *arg_label;   /* The label associated with an argument, if applicable */
    int is_extern;     /* Indicates whether the instruction is marked as external */
} inst_parts;

/* Declaration of the external OPCODES array */
extern op_code OPCODES[];

int is_instruction(char *str);


/**
 * @brief This function returns the index of the opcode in the predefined opcode list.
 *
 * It compares the provided string with a list of known opcodes. If a match is found,
 * it returns the index of the matching opcode in the `OPCODES` array. If no match is
 * found or the string is NULL, it returns -1.
 *
 * @param str A pointer to a character string representing the opcode to check.
 *
 * @return Returns an integer representing the index of the opcode in the `OPCODES` array.
 *         If the string does not match any opcode or is NULL, it returns -1.
 **/
int opcode_num(char *str);


/**
 * @brief This function returns the index of the register in the predefined register list.
 *
 * It compares the provided string with a list of known registers. If a match is found,
 * it returns the index of the matching register in the `REGS` array. If no match is
 * found or the string is NULL, it returns -1.
 *
 * @param str A pointer to a character string representing the register to check.
 *
 * @return Returns an integer representing the index of the register in the `REGS` array.
 *         If the string does not match any register or is NULL, it returns -1.
**/
int register_num(char *str);

int get_first_word(char * line, char * first_word);

int is_comment(char * line);

int legal_label(char *str, int *error_code);

char* substring(char *source, int start, int end);

int is_valid_ascci(char c);

int is_empty_line(const char *line);

char* str_without_spaces(char * word);

int is_comment_empty_line(char * line);

/**
 * Function to find a character in a string.
 * @param str The string to search within.
 * @param ch The character to search for.
 * @return 1 if the character is found, 0 if not found.
 */
int find_int_in_array(int *array, int length, int value);

#endif
#ifndef C_PROJECT_LEXER_H
#define C_PROJECT_LEXER_H

/* Represents an operation code with its associated opcode and argument count */
typedef struct op_code {
    char *opcode;    /* The opcode corresponding to the operation */
    int arg_num;     /* The number of arguments for the operation */
    char * source_address; /*possible addressing system for source opernad*/
    char * destination_address; /*possible addressing system for target opernad*/

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


/**
 * @brief Reads an entry or extern directive from a string.
 *
 * The function reads an entry or extern directive from a given string. It tokenizes the string, extracts
 * relevant information, and populates an inst_parts structure with the parsed data. The function handles
 * memory allocation for the inst_parts structure and returns a pointer to it. It also updates the error_code
 * in case of errors.
 *
 * @param str: The input string containing an entry or extern directive.
 * @param error_code: A pointer to an integer to hold the error code if an error occurs.
 * @return Returns a pointer to an inst_parts structure containing the parsed data, or NULL on error.
 */
inst_parts *read_entry_or_extern(char *str ,int *error_code);


/**
 * @brief This function checks whether any line in the provided file exceeds the maximum length limit.
 *
 * It scans through each line of the file, and if it encounters a line longer than `MAX_LINE_LENGTH`,
 * it prints an external error using `ERROR_CODE_30` and sets a flag indicating a long line was found.
 *
 * @param file_name A pointer to a character string representing the file name.
 *
 * @return Returns an integer. If any line in the file exceeds `MAX_LINE_LENGTH`, it returns 1.
 *         Otherwise, it returns 0 indicating all lines are within the limit.
 *
 */
int lines_too_long(char *file_name);


/**
 * @brief Checks if the provided string is an instruction.
 *
 * This function compares the provided string with a list of known instructions.
 * If a match is found, the function will return 1, indicating that the string is an instruction.
 * If no match is found, it returns 0.
 *
 * @param str A pointer to a character string representing the instruction to check.
 *
 * @return Returns an integer. If the string matches one of the known instructions, it returns 1.
 *         Otherwise, if the string does not match any instruction or is NULL, it returns 0.
 */
int is_instr(char *str);


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
int what_opcode(char *str);


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
int what_reg(char *str);

void get_first_word(char * line, char * first_word);

int is_comment(char * line);

int legal_label(char *str, int *error_code);

#endif
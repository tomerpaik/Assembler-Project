#ifndef LABRATORY_C_FINAL_PROJECT_ERRORS_H
#define LABRATORY_C_FINAL_PROJECT_ERRORS_H

/**
 * @file errors_handle.h
 * @brief Defines error codes and error handling functions for the assembler project.
 *
 * This file contains the definitions of various error codes used throughout the
 * assembler program, along with functions to handle, display, and log errors
 * encountered during the assembly process.
 */

#include "../Headers/colors.h"

/**
 * @enum project_error
 * @brief Enumerates the possible error codes used in the assembler.
 *
 * This enumeration lists all the error codes that can be encountered
 * during the assembly process. Each error code corresponds to a specific
 * type of error, ranging from general errors to specific issues related
 * to macros, symbols, data, strings, extern/entry commands, and more.
 */
enum project_error {
    /* General errors */
    GENERIC_NO_E,                       /**< No Error */
    GENERIC_LINE_OOR,                   /**< Line was too long, not all the content was caught */
    GENERIC_Allocation_Faild,           /**< Failed to dynamically allocate memory */
    GENERIC_Line_TooLONG,               /**< The Line is too long */
    GENERIC_Faild_OpenFile_W,           /**< Failed to open new file for writing */
    GENERIC_Faild_OpenFile_R,           /**< Failed to open file for reading */

    /* Macro-related errors */
    Macro_Without_Name,                 /**< Macro without name definition */
    Macro_ETA_MacroName,                /**< Extra text after macro name definition */
    macro_name_MACR_ENDMACR,            /**< Macro name is called like macro definition (macr/endmacr) */
    Macro_ETA_endmacr,                  /**< endmacr with extra text */
    Macro_double_define,                /**< Macro has more than one definition */
    Macro_ETA_MacroCall,                /**< Macro call with extra text */
    Macro_nameis_Reg_Op_Inst,           /**< Illegal name for a macro */
    Macro_namestart_with_numbers,       /**< Macro name starts with numbers */
    Macro_nameis_oor,                   /**< Macro Name is out of range */

    Error_Success,                      /**< No Error Found */

    /* Symbol-related errors */
    firstPassError_symbol_iliigal_characters, /**< Symbol name contains illegal characters */
    firstPassError_symbol_invalid_name_starts_with_numbers, /**< Symbol name starting with number */
    firstPassError_symbol_invalid_name_is_inst, /**< Symbol name is an instruction */
    firstPassError_symbol_invalid_name_is_reg, /**< Invalid symbol name is a register */
    firstPassError_symbol_invalid_name_is_opcode, /**< Invalid symbol name is an opcode */
    firstPassError_symbol_name_taken, /**< A symbol with this name already exists */
    firstPassError_symbol_macro_name, /**< Can't define a symbol with the same name as a macro */
    firstPassError_symbol_invalid_length, /**< Symbol name is too long */
    firstPassError_symbol_empty_line,

    /* .data-related errors */
    firstPassError_data_nan, /**< Arguments of a data instruction must be immediate numbers or constants */
    firstPassError_data_comma_expected, /**< Comma expected between arguments */
    firstPassError_data_const_not_found, /**< Constant was not found */
    firstPassError_data_argument_expected, /**< Argument expected in .data */
    firstPassError_data_oor, /**< Data argument out of range for a byte */
    firstPassError_data_empty_line, /**< Data instruction is empty */
    firstPassError_data_argument_out_of_range, /**< Data argument is out of range of 15 */

    /* .string-related errors */
    firstPassError_string_expected_quotes, /**< Expected '"' to start the string */
    firstPassError_string_expected_end_quotes, /**< Expected '"' to terminate the string */
    firstPassError_string_extra_chars, /**< Extra characters after closing '"' */
    firstPassError_string_not_printable, /**< String contains non-printable characters */
    firstPassError_string_empty_line, /**< String instruction is empty */

    /* .extern/.entry-related errors */
    firstPassError_extern_entry_in_same_file, /**< Symbol is defined as both .extern and .entry in the same file */
    firstPassError_extern_entry_without_symbol, /**< No symbol name found after .extern or .entry */
    firstPassError_extern_symbol_exists, /**< The symbol is already defined in the file */
    firstPassError_extern_exists, /**< This symbol was already declared as extern */
    firstPassError_extern_symbol_in_file, /**< Extern symbol is declared in the file */

    /* Command-related errors */
    firstPassError_command_not_found, /**< Invalid command */
    firstPassError_command_too_many_operands, /**< Too many operators in command */
    firstPassError_command_invalid_source_adress, /**< Source operand addressing method is not available for opcode */
    firstPassError_command_invalid_dest_adress, /**< Destination operand addressing method is not available for opcode */
    firstPassError_command_no_operand_expected, /**< Opcode should not receive operands */
    firstPassError_command_expected_operand, /**< Opcode should receive operands */
    firstPassError_command_expected_more_operand, /**< Opcode should receive operands */
    firstPassError_command_invalid_operand, /**< Opcode received invalid operands */
    firstPassError_command_code_image_oor, /**< IC is out of MAX computer range */
    firstPassError_command_code_number_oor, /**< Immediate addressing method number is out of range */
    firstPassError_command_command_arg,
    firstPassError_command_expected_reg,

    SECOND_PASS_ERROR_COMMAND_SYMBOL_OPERAND_NEXIST, /**< Symbol operand does not exist in the second pass */
    SECOND_PASS_ERROR_ENTRY_SYMBOL_NEXSIT, /**< .Entry Symbol is not defined in the file */
    SECOND_PASS_ERROR_OPCODE_SYMBOL /**< OPCODE Symbol cannot be a command operand */
};

/**
 * @struct project_errors
 * @brief Struct that associates error codes with their corresponding messages.
 *
 * This struct is used to map error codes defined in the `project_error` enum
 * to their descriptive error messages.
 */
typedef struct {
    enum project_error code; /**< The error code */
    char *message; /**< The error message */
} project_errors;

/* Function Prototypes */

/**
 * @brief Prints an error message based on the error code, line number, and file name.
 *
 * @param code The error code.
 * @param srcline The line number where the error occurred.
 * @param srcfile The name of the file where the error occurred.
 */
void print_error(enum project_error code, int srcline, char srcfile[]);

/**
 * @brief Prints a generic error message based on the error code.
 *
 * @param code The error code.
 */
void print_generic_error(enum project_error code);

/**
 * @brief Prints a warning message based on the error code, line number, and file name.
 *
 * @param code The error code.
 * @param srcline The line number where the warning occurred.
 * @param srcfile The name of the file where the warning occurred.
 */
void print_warning(enum project_error code, int srcline, char srcfile[]);

/**
 * @brief Prints an error message with additional custom information.
 *
 * @param code The error code.
 * @param srcline The line number where the error occurred.
 * @param srcfile The name of the file where the error occurred.
 * @param additional_msg Additional custom message to include in the error output.
 */
void print_error_custom_message(enum project_error code, int srcline, char srcfile[], char* additional_msg);

#endif /* LABRATORY_C_FINAL_PROJECT_ERRORS_H */
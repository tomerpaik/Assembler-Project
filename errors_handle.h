#ifndef LABRATORY_C_FINAL_PROJECT_ERRORS_H
#define LABRATORY_C_FINAL_PROJECT_ERRORS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colors.h"

enum  project_error {
     GENERIC_NO_E,
     GENERIC_LINE_OOR,
     GENERIC_Allocation_Faild,
     GENERIC_Line_TooLONG,
     GENERIC_Faild_OpenFile_W,
     GENERIC_Faild_OpenFile_R,
     Macro_Without_Name,
     Macro_ETA_MacroName,
     macro_name_MACR_ENDMACR,
     Macro_ETA_endmacr,
     Macro_double_define,
     Macro_ETA_MacroCall,
     Macro_nameis_Reg_Op_Inst,
     Macro_namestart_with_numbers,
     Macro_nameis_oor,

     firstPassError_success,   /* no error */
    /* label errors */
     /* invalid label name */

     firstPassError_symbol_iliigal_characters,   /* invalid label name */
     firstPassError_symbol_invalid_name_starts_with_numbers,   /*label name starting with number */
     firstPassError_symbol_invalid_name_is_inst,   /* label name is insruction */
     firstPassError_symbol_invalid_name_is_reg,   /* invalid label name is reg*/
     firstPassError_symbol_invalid_name_is_opcode,   /* invalid label name is reg*/
     firstPassError_symbol_name_taken, /* name of label taken */
     firstPassError_symbol_macro_name, /* there's a macro with the same name as the label */
     firstPassError_symbol_invalid_length, /*label is too long*/

    /* .data errors */
     firstPassError_data_nan, /* .data argument is not a number */
     firstPassError_data_comma_expected,  /* comma expected between arguments */
     firstPassError_data_const_not_found, /* constant referenced was not found */
     firstPassError_data_argument_expected,   /* argument expected in data */
     firstPassError_data_oor, /* the data argument was out of range for a byte */
     firstPassError_data_empty_line, /*after .data line is empty */
     firstPassError_data_argument_out_of_range,

    /* .string errors */
     firstPassError_string_expected_quotes,   /* quotes missing after .string */
     firstPassError_string_expected_end_quotes,   /* quotes missing at end of .string definition */
     firstPassError_string_extra_chars,   /* extra characters after closing quotes */
     firstPassError_string_not_printable, /* a character in the string is not printable */
     firstPassError_string_empty_line, /*after .string line is empty */

    /* .extern errors */
    firstPassError_extern_entry_in_same_file,
    firstPassError_extern_entry_without_symbol,
    firstPassError_extern_symbol_exists,  /* the label is already defined in the file */
    firstPassError_extern_exists, /* this label was already declared as extern (warning) */
    /* .entry errors */

    /* command errors */
     firstPassError_command_not_found,  /* invalid operator name */
     firstPassError_command_too_many_operands, /*"too many operators in command"*/
     firstPassError_command_invalid_source_adress,
     firstPassError_command_invalid_dest_adress,
     firstPassError_command_no_operand_expected,
     firstPassError_command_expected_operand,
     firstPassError_command_invalid_operand,
     firstPassError_command_code_image_oor,
     firstPassError_command_code_number_oor

};
typedef struct {
 enum project_error code;
 char *message;
} project_errors;

/* Represents an error with an associated error ID and error message */
typedef struct Error {
    int error_id;     /* Unique identifier for the error */
    char *error_msg;  /* Error message associated with the error */
} Error;

void print_error(enum project_error code, int srcline, char srcfile[]);
void print_generic_error(enum project_error code);
void print_warning(enum project_error code, int srcline, char srcfile[]);
void print_error_custom_message(enum project_error code, int srcline, char srcfile[], char* additional_msg);
#endif
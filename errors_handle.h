#ifndef LABRATORY_C_FINAL_PROJECT_ERRORS_H
#define LABRATORY_C_FINAL_PROJECT_ERRORS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum  project_error {
     GENERIC_NO_E,
     GENERIC_Allocation_Faild,
     ERROR_CODE_2,
     ERROR_CODE_3,
     GENERIC_File_NEXIST,
     GENERIC_Line_TooLONG,
     GENERIC_Faild_OpenFile_W,
     GENERIC_Faild_OpenFile_R,
     Macro_Without_Name,
     Macro_ETA_MacroName,
     macro_name_MACR,
     Macro_ETA_endmacr,
     Macro_double_define,
     ERROR_CODE_15,
     Macro_ETA_MacroCall,
     Macro_nameis_Reg_Op_Inst,
     Macro_nameis_oor,

     firstPassError_success,   /* no error */
    /* label errors */
     firstPassError_label_invalid_name,   /* invalid label name */
     firstPassError_label_const_definition,   /* constant defined in a label */
     firstPassError_label_saved_keyword,  /* the label's name is a saved keyword */
     firstPassError_label_name_taken, /* name of label taken */
     firstPassError_label_empty_line, /* label defined on an empty line */
     firstPassError_label_macro_name, /* there's a macro with the same name as the label */
     firstPassError_label_no_whitespace, /* missing space after label declaration */

    /* .data errors */
     firstPassError_data_nan, /* .data argument is not a number */
     firstPassError_data_comma_expected,  /* comma expected between arguments */
     firstPassError_data_const_not_found, /* constant referenced was not found */
     firstPassError_data_argument_expected,   /* argument expected in data */
     firstPassError_data_oor, /* the data argument was out of range for a byte */

    /* .string errors */
     firstPassError_string_expected_quotes,   /* quotes missing after .string */
     firstPassError_string_expected_end_quotes,   /* quotes missing at end of .string definition */
     firstPassError_string_extra_chars,   /* extra characters after closing quotes */
     firstPassError_string_not_printable, /* a character in the string is not printable */

    /* .extern errors */
     firstPassError_extern_argument_expected, /* missing argument */
     firstPassError_extern_invalid_lbl_name,  /* the .extern parameter is not a valid name for a label */
     firstPassError_extern_extra_chars,   /* extra characters at the end of an extern instruction */
     firstPassError_extern_label_exists,  /* the label is already defined in the file */
     firstPassError_extern_saved_keyword, /* extern label is a saved keyword */
     firstPassError_extern_define_label,  /* a label is defined in the beginning of an extern instruction (warning) */
     firstPassError_extern_exists, /* this label was already declared as extern (warning) */
     firstPassError_extern_macro_name,    /* there's a macro with the same name as the .extern argument */

    /* .entry errors */
     firstPassError_entry_argument_expected, /* missing argument */
     firstPassError_entry_invalid_lbl_name,   /* the .entry argument is not a valid name for a label */
     firstPassError_entry_saved_keyword, /* argument name is a system keyword */
     firstPassError_entry_macro_name, /* entry argument is a macro name */
     firstPassError_entry_extra_chars,    /* extra characters at the end of an entry instruction */
     firstPassError_entry_define_label,   /* a label is defined in the beginning of an entry instruction (warning) */

    /* command errors */
     firstPassError_command_not_found,  /* invalid operator name */
     firstPassError_command_expected_operand,   /* expected an operand */
     firstPassError_command_invalid_immediate,  /* the immediate operand was invalid */
     firstPassError_command_expected_closing_sqr_bracks,    /* expected closing square brackets */
     firstPassError_command_expected_index, /* index was not found between square brackets */
     firstPassError_command_invalid_index,  /* the given index (in square brackets) was invalid */
     firstPassError_command_invalid_label_name, /* label name in operand has an invalid name */
     firstPassError_command_invalid_addr_method,    /* invalid addressing method */
     firstPassError_command_invalid_operand,    /* operand expected for command */
     firstPassError_command_expected_comma, /* expected comma to seperate operands */
     firstPassError_command_immediate_oor,  /* immediate operand was out of range */
     firstPassError_command_index_oor,  /* constant index was out of range */
     firstPassError_command_too_many_operands, /* too many operands for an command */
     firstPassError_command_extra_chars,    /* extra characters at the end of the line */
     firstPassError_command_operand_number, /* a number operand that doesn't follow # */
     firstPassError_command_operand_macro,   /* a macro was used as an operand */
     firstPassError_command_operand_saved,   /* cannot be a saved keyword */

     /* .define errors */
     firstPassError_define_name_expected, /* name expected */
     firstPassError_define_unexpected_chars,  /* unexpected chars at the end of a define statement */
     firstPassError_define_expected_equal_sign,   /* expected after constant name */
     firstPassError_define_value_expected,    /* expected value for constant */
     firstPassError_define_invalid_name,  /* the constant's name was invalid */
     firstPassError_define_saved_keyword, /* the constant's name is a saved keyword */
     firstPassError_define_name_taken,    /* name of constant taken */
     firstPassError_define_value_nan, /* value is not a number */
     firstPassError_define_macro_name    /* there's a macro with the same name as the constant */
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
#endif
#include "errors_handle.h"


project_errors errors[] = {
    {GENERIC_NO_E,  "No Error"},
    {GENERIC_Allocation_Faild,  "Failed to dynamically allocate memory"},
    {ERROR_CODE_2,  ".as files name is missing"},
    {ERROR_CODE_3,  "The file name is too long"},
    {GENERIC_File_NEXIST,  "The provided file name is not exist"},
    {GENERIC_Line_TooLONG,  "The Line is too long"},
    {GENERIC_Faild_OpenFile_W,  "Failed to open new file for writing"},
    {GENERIC_Faild_OpenFile_R,  "Failed to open file for reading"},
    {Macro_Without_Name,  "Error - macro without name definition"},
    {Macro_ETA_MacroName, "Error - extra text after macro name definition"},
    {macro_name_MACR_ENDMACR, "Macro name is called like macro defenition -macr-/-endmacr"},
    {Macro_ETA_endmacr, "endmacr with extra text"},
    {Macro_double_define, "Macro has more than one definition"},
    {ERROR_CODE_15, "Macros expansion in an .as file failed"},
    {Macro_ETA_MacroCall, "Macro call with extra text"},
    {Macro_nameis_Reg_Op_Inst, "Illegal name for a macro"},
    {Macro_namestart_with_numbers, "Macro name starts with numbers"},
    {Macro_nameis_oor, "Macro Name is out of range"},
    {firstPassError_success, "No Error Found"},
    /*label errors*/
    {firstPassError_label_invalid_name, "invalid name for a label"},
    {firstPassError_label_invalid_name_starts_with_numbers, "label name starting with number"},
    {firstPassError_label_invalid_name_is_inst, "label name is insruction"},
    {firstPassError_label_invalid_name_is_reg, "invalid label name is reg"},
    {firstPassError_label_invalid_name_is_opcode, "invalid label name is opcode"},
    {firstPassError_label_const_definition, "can't define a constant in the same line as a label"},
    {firstPassError_label_saved_keyword, "can't use a saved keyword as a label's name"},
    {firstPassError_label_name_taken, "a symbol with this name already exists"},
    {firstPassError_label_empty_line, "can't define a label on an empty line"},
    {firstPassError_label_macro_name, "can't define a label with the same name as a macro"},
    {firstPassError_label_no_whitespace, "missing a space after label definition"},
    {firstPassError_label_invalid_length, "label long is out off range"},
    /*.data errors*/
    {firstPassError_data_nan, "arguments of a data instruction must be immediate numbers or constants"},
    {firstPassError_data_comma_expected, "comma expected between arguments"},
    {firstPassError_data_const_not_found, "constant was not found"},
    {firstPassError_data_argument_expected, "argument expected"},
    {firstPassError_data_oor, "data argument out of range for a byte"},
    {firstPassError_data_empty_line, "data instuction is empty"},
    {firstPassError_data_argument_out_of_range, "data argument is out of range of 15"},
    /*.string errors*/
    {firstPassError_string_expected_quotes, "expected '\"' to start the string"},
    {firstPassError_string_expected_end_quotes, "expected '\"' to terminate the string"},
    {firstPassError_string_extra_chars, "extra characters after closing '\"'"},
    {firstPassError_string_not_printable, "string is not printable"},
    {firstPassError_string_empty_line, "string instuction is empty"},
    /*.extern/entry errors*/
    {firstPassError_extern_invalid_lbl_name, "the .extern label is not a valid name for a label"},
    {firstPassError_extern_label_exists, "the label is already defined in the file"},
    {firstPassError_extern_exists, "this label was already declared as extern (warning)"},/*TODO: warning*/

    /*commands errors*/
    {firstPassError_command_not_found, "invalid command"},
    {firstPassError_command_too_many_operands, "too many operators in command"},
    { firstPassError_command_invalid_operands_number, "invalid operands number for the command"}

};


/*
 * prints error message
 * takes message to display, line of error, and file the error was found in
 */
void print_error(enum project_error code, int srcline, char srcfile[]) {
    printf(""RED"Error in %s, line: %d says: ---[%s]---\n"RESET"", srcfile, srcline, errors[code].message);
}

void print_generic_error(enum project_error code) {
    printf("GENERIC %s\n", errors[code].message);
}

void print_error_custom_message(enum project_error code, int srcline, char srcfile[], char* additional_msg) {
    printf(""RED"Error in %s, line: %d says: ---[%s: %s]---\n"RESET"", srcfile, srcline, errors[code].message, additional_msg);
}
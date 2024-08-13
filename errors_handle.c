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
    {macro_name_MACR, "Macro name is called like macro defenition -macr-"},
    {Macro_ETA_endmacr, "endmacr with extra text"},
    {Macro_double_define, "Macro has more than one definition"},
    {ERROR_CODE_15, "Macros expansion in an .as file failed"},
    {Macro_ETA_MacroCall, "Macro call with extra text"},
    {Macro_nameis_Reg_Op_Inst, "Illegal name for a macro"}, /*TODO: seperate to either reg_op_etc*/
    {Macro_nameis_oor, "Macro Name is out of range"},
    {firstPassError_success, "No Error Found"},
    /*label errors*/
    {firstPassError_label_invalid_name, "invalid name for a label"},
    {firstPassError_label_const_definition, "can't define a constant in the same line as a label"},
    {firstPassError_label_saved_keyword, "can't use a saved keyword as a label's name"},
    {firstPassError_label_name_taken, "a symbol with this name already exists"},
    {firstPassError_label_empty_line, "can't define a label on an empty line"},
    {firstPassError_label_macro_name, "can't define a label with the same name as a macro"},
    {firstPassError_label_no_whitespace, "missing a space after label definition"},
    /*.data errors*/
    {firstPassError_data_nan, "arguments of a data instruction must be immediate numbers or constants"},
    {firstPassError_data_comma_expected, "comma expected between arguments"},
    {firstPassError_data_const_not_found, "constant was not found"},
    {firstPassError_data_argument_expected, "argument expected"},
    {firstPassError_data_oor, "data argument out of range for a byte"},
    /*.string errors*/
    {firstPassError_string_expected_quotes, "expected '\"' to start the string"},
    {firstPassError_string_expected_end_quotes, "expected '\"' to terminate the string"},
    {firstPassError_string_extra_chars, "extra characters after closing '\"'"},
    {firstPassError_string_not_printable, "string is not printable"},
    /*.extern/entry errors*/
    {firstPassError_extern_argument_expected, "missing argument"},
    {firstPassError_extern_invalid_lbl_name, "invalid label name for extern argument"},
    {firstPassError_extern_extra_chars, "extra characters following .extern argument"},
    {firstPassError_extern_label_exists, "a symbol with this name already exists in this file"},
    {firstPassError_extern_saved_keyword, "can't use .extern on a saved keyword"},
    {firstPassError_extern_macro_name, ".extern argument has the same name as a macro"},
    {firstPassError_entry_argument_expected, "missing argument"},
    {firstPassError_entry_invalid_lbl_name, "invalid label name for entry argument"},
    {firstPassError_entry_extra_chars, "extra characters following .entry argument"},
    {firstPassError_entry_define_label, "-----------------------"},
    /*commands errors*/
    {firstPassError_command_not_found, "invalid command"},
    {firstPassError_command_expected_operand, "operand expected"},
    {firstPassError_command_invalid_immediate, "immediate operand must be a number or constant"},
    {firstPassError_command_expected_closing_sqr_bracks, "expected closing square brackets"},
    {firstPassError_command_expected_index, "index expected inside square brackets"},
    {firstPassError_command_invalid_index, "index must be a number or constant"},
    {firstPassError_command_invalid_label_name, "operand has an invalid label name"},
    {firstPassError_command_invalid_addr_method, "addressing methods don't match command"},
    {firstPassError_command_invalid_operand, "illegal operand"},
    {firstPassError_command_expected_comma, "comma expected to separate operands"},
    {firstPassError_command_immediate_oor, "immediate operand is out of range"},
    {firstPassError_command_index_oor, "index is out of range"},
    {firstPassError_command_too_many_operands, "too many operands"},
    {firstPassError_command_extra_chars, "extra characters at the end of the line"},
    {firstPassError_command_operand_number, "a number operand has to follow a #"},
    {firstPassError_command_operand_macro, "macro can't be used as an operand"},
    {firstPassError_command_operand_saved, "operand cannot be a saved keyword"},
    /*.define errors*/
    {firstPassError_define_name_expected, "constant name expected"},
    {firstPassError_define_unexpected_chars, "unexpected characters at end of line"},
    {firstPassError_define_expected_equal_sign, "equal sign expected"},
    {firstPassError_define_value_expected, "constant value expected"},
    {firstPassError_define_invalid_name, "invalid name for a constant"},
    {firstPassError_define_saved_keyword, "can't use a saved keyword as a constant's name"},
    {firstPassError_define_name_taken, "the constant's name is already used"},
    {firstPassError_define_value_nan, "constant value must be an immediate whole number"},
    {firstPassError_define_macro_name, "can't define a constant with the same name as a macro"},

};


/*
 * prints error message
 * takes message to display, line of error, and file the error was found in
 */
void print_error(enum project_error code, int srcline, char srcfile[]) {
    printf("Error in %s, line: %d says: ---[%s]---\n", srcfile, srcline, errors[code].message);
}

void print_generic_error(enum project_error code) {
    printf("%s\n", errors[code].message);
}


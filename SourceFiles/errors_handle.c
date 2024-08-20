#include "../Headers/errors_handle.h"
#include <stdio.h>


project_errors errors[] = {
    {GENERIC_NO_E,  "No Error"},
    {GENERIC_LINE_OOR,  "Line was too long, not all the content was caught"},
    {GENERIC_Allocation_Faild,  "Failed to dynamically allocate memory"},
    {GENERIC_Line_TooLONG,  "The Line is too long"},
    {GENERIC_Faild_OpenFile_W,  "Failed to open new file for writing"},
    {GENERIC_Faild_OpenFile_R,  "Failed to open file for reading"},
    {Macro_Without_Name,  "Macro without name definition"},
    {Macro_ETA_MacroName, "Extra text after macro name definition"},
    {macro_name_MACR_ENDMACR, "Macro name is called like macro defenition -macr-/-endmacr"},
    {Macro_ETA_endmacr, "endmacr with extra text"},
    {Macro_double_define, "Macro has more than one definition"},
    {Macro_ETA_MacroCall, "Macro call with extra text"},
    {Macro_nameis_Reg_Op_Inst, "Illegal name for a macro"},
    {Macro_namestart_with_numbers, "Macro name starts with numbers"},
    {Macro_nameis_oor, "Macro Name is out of range"},
    {Error_Success, "No Error Found"},
    /*symbol errors*/
    {firstPassError_symbol_iliigal_characters, "symbol name contains illigal characters"},
    {firstPassError_symbol_invalid_name_starts_with_numbers, "symbol name starting with number"},
    {firstPassError_symbol_invalid_name_is_inst, "symbol name is insruction"},
    {firstPassError_symbol_invalid_name_is_reg, "invalid symbol name is reg"},
    {firstPassError_symbol_invalid_name_is_opcode, "invalid symbol name is opcode"},
    {firstPassError_symbol_name_taken, "a symbol with this name already exists"},
    {firstPassError_symbol_macro_name, "can't define a symbol with the same name as a macro"},
    {firstPassError_symbol_invalid_length, "symbol long is out off range"},
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
    {firstPassError_extern_entry_in_same_file, "symbol Is Defined As An (.extern) and (.entry) In The Same File"},
    {firstPassError_extern_entry_without_symbol, "No Symbol Name Was Found After "},
    {firstPassError_extern_symbol_exists, "trying to handel extern - the symbol is already defined in the file"},
    {firstPassError_extern_exists, "this symbol was already declared as extern"},
    {firstPassError_extern_symbol_in_file, "extern symbol is declered in the file"},

    /*commands errors*/
    {firstPassError_command_not_found, "invalid command"},
    {firstPassError_command_too_many_operands, "too many operators in command"},
    { firstPassError_command_invalid_source_adress, "soucre operand adressing method is not availible for opcode"},
    { firstPassError_command_invalid_dest_adress, "destination operand adressing method is not availible for opcode"},
    { firstPassError_command_no_operand_expected, "opcode should get no operands"},
    { firstPassError_command_expected_operand, "opcode should get operands"},
    { firstPassError_command_invalid_operand, "opcode should get operands"},
    { firstPassError_command_code_image_oor, "IC is out of MAX computer range"},
    { firstPassError_command_code_number_oor, "Immidiate addressing method number is out of range"},

    { SECOND_PASS_ERROR_COMMAND_SYMBOL_OPERAND_NEXIST, "After Defining all the Symboles in the first pass it is not exist in the file"},
    { SECOND_PASS_ERROR_ENTRY_SYMBOL_NEXSIT, ".Entry Symbol Is not defined in the file"},
    { SECOND_PASS_ERROR_OPCODE_SYMBOL, "OPCODE Symbol Can Not be command operand"}

};


/*
 * prints error message
 * takes message to display, line of error, and file the error was found in
 */
void print_error(enum project_error code, int srcline, char srcfile[]) {
    printf(""RED"Error in %s, line: %d says: ---[%s]---\n"RESET"", srcfile, srcline, errors[code].message);
}
void print_warning(enum project_error code, int srcline, char srcfile[]) {
    printf(""YELLOW"Warning in %s, line: %d says: ---[%s]---\n"RESET"", srcfile, srcline, errors[code].message);
}
void print_generic_error(enum project_error code) {
    printf("GENERIC %s\n", errors[code].message);
}
void print_error_custom_message(enum project_error code, int srcline, char srcfile[], char* additional_msg) {
    printf(""RED"Error in %s, line: %d says: ---[%s: %s]---\n"RESET"", srcfile, srcline, errors[code].message, additional_msg);
}
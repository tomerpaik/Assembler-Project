#include "../Headers/validation.h"

enum project_error valid_symbol(char *symbol_name, hash_table macro_table) {
    int i;
    int symbol_name_len;
    symbol_name_len = strlen(symbol_name);

    /*check valid len*/
    if(symbol_name_len > 32) return firstPassError_symbol_invalid_length;
    if(is_instruction(symbol_name)) return firstPassError_symbol_invalid_name_is_inst;
    if (!isalpha(symbol_name[0])) return firstPassError_symbol_invalid_name_starts_with_numbers;
    for (i = 1; i < symbol_name_len - 1; i++) {
        if (!isalnum(symbol_name[i]) && symbol_name[i] != '_') {
            return firstPassError_symbol_iliigal_characters;
        }
    }
    if(opcode_num(symbol_name)>=0) return firstPassError_symbol_invalid_name_is_opcode;
    if(register_num(symbol_name)>=0) return firstPassError_symbol_invalid_name_is_reg;
    if (is_in_table(macro_table, symbol_name)) return firstPassError_symbol_macro_name;
    return Error_Success;
}

enum project_error valid_data(char *line){
    const char *ptr = line;
    if(is_empty_line(line)) return firstPassError_data_empty_line;

    if (atoi(line) >= (1 << 11) || atoi(line) < -(1 << 11)) {
        return firstPassError_data_oor;
    }

    while (*ptr) {  /* Loop to check all the numbers after ".data" */
        while (isspace(*ptr)) ptr++;    /* Skip any whitespace */
        if (*ptr == '+' || *ptr == '-') ptr++; /* Check if the first character is a digit or an optional +/- sign */
        if (!isdigit(*ptr)) return firstPassError_data_nan; /* Ensure the current character is a digit */

        while (isdigit(*ptr)) ptr++;    /* Continue scanning digits */
        while (isspace(*ptr)) ptr++;    /* Skip any whitespace */
        if (*ptr == ',') {  /* If a comma is found, move to the next number */
            ptr++;
            while (isspace(*ptr)) ptr++;     /* Ensure there's a number after the comma */
            if (!isdigit(*ptr) && *ptr != '+' && *ptr != '-') return firstPassError_data_argument_expected; /* Check if the next character is a digit or a sign */
        } else if (*ptr != '\0') return firstPassError_data_comma_expected; /* Invalid if there's any other character */

    }
    return Error_Success;; /* Valid instruction */
}

enum project_error valid_string(char *string) {
    char * string_without_spaces, *start_quote, *end_quote;
    if(is_empty_line(string)) return firstPassError_string_empty_line;
    string_without_spaces = str_without_spaces(string);

    start_quote = string_without_spaces, end_quote = string_without_spaces+strlen(string_without_spaces)-1;

    if (*start_quote != '\"') return firstPassError_string_expected_quotes;
    if (*end_quote != '\"') return firstPassError_string_expected_end_quotes;

    while (start_quote < end_quote) {
        if (!isprint(*start_quote)) return firstPassError_string_not_printable;
        start_quote ++;
    }

    free(string_without_spaces);
    free(end_quote);
    return Error_Success;
}

int handel_entry_extern(EntryExternContent context, hash_table symbol_table, hash_table macro_tabel){
    char *after_entry_extern_symbol_name;
    enum project_error current_error;

    after_entry_extern_symbol_name = str_without_spaces(context->line + context->offset);

    if (is_empty_line(context->line + context->offset)) {
        print_error_custom_message(firstPassError_extern_entry_without_symbol, context->line_num, context->am_path, context->first_word);
        return 0;
    }

    if ((current_error = valid_symbol(after_entry_extern_symbol_name, macro_tabel)) != Error_Success) {
        print_error_custom_message(current_error, context->line_num, context->am_path, context->first_word);
        return 0;
    }

    if (is_in_table(symbol_table, after_entry_extern_symbol_name)) {
        if (get_symbol_flag(symbol_table, after_entry_extern_symbol_name) == EXTERN_FLAG) {
            if (strcmp(context->first_word, ".entry") == 0) {
                print_error(firstPassError_extern_entry_in_same_file, context->line_num, context->am_path);
                return 0;
            } else {
                print_warning(firstPassError_extern_exists, context->line_num, context->am_path);
                return 1; /* Not an error, so return 0 */
            }
        }
        if (strcmp(context->first_word, ".extern") == 0) {
            print_error_custom_message(firstPassError_extern_symbol_exists, context->line_num, context->am_path, context->first_word);
        }
        if (strcmp(context->first_word, ".extern") == 0) {
            print_error(firstPassError_extern_symbol_in_file, context->line_num, context->am_path);
            return 0;
        }
    }

    if (strcmp(context->first_word, ".extern") == 0) {
        add_symbol(after_entry_extern_symbol_name, EXTERN_FLAG, symbol_table);
    }

    return 1;
}
EntryExternContent init_entry_extern_context(char *first_word, char *line, int offset, int line_num, char *am_path) {
    EntryExternContent context = handel_malloc(sizeof(*context));
    /* Initialize the context with the relevant values */
    context->first_word = first_word;
    context->line = line;
    context->offset = offset;
    context->line_num = line_num;
    context->am_path = am_path;
    return context;
}

void free_entry_extern_context(EntryExternContent context) {
    if (context != NULL) {
        free(context);
    }
}


enum project_error handel_opcode(char *opcode_operands, char* opcode_name, hash_table symbol_table, char * symbol_name, int symbol_flag) {
    op_code current_op_code;
    char *source_operand = "NULL", *dest_operand = "NULL";
    int source_addressing_method = 4, dest_addressing_method = 4; /*RESET addressing_method TO BE NO_METHOD*/

    if (opcode_num(opcode_name) == -1) return firstPassError_command_not_found;
    current_op_code = OPCODES[opcode_num(opcode_name)]; /* Find the opcode in the OPCODES array */

    if (is_empty_line(opcode_operands) && current_op_code.arg_num > 0)  return firstPassError_command_expected_operand; /*opcode that needs to get operands arg_num > 0*/

    if (current_op_code.arg_num == 2) {
        source_operand = strtok(opcode_operands, ","); /* Tokenize the operands using comma as a delimiter */
        if (source_operand != NULL) {
            source_operand = str_without_spaces(source_operand);  /* Remove spaces around operand1 */
            dest_operand = str_without_spaces(strtok(NULL, ","));
            if (strtok(NULL, ",") != NULL) return firstPassError_command_too_many_operands;
        } else {
            source_operand = "NULL", dest_operand = "NULL";
        }
    } else if (current_op_code.arg_num == 1) {
        dest_operand = str_without_spaces(opcode_operands);
    }
    else if (current_op_code.arg_num == 0 && !is_empty_line(opcode_operands)) return firstPassError_command_no_operand_expected; /* Handle cases where the opcode expects no operands but arguments are present */

    if (strcmp(source_operand, "NULL") != 0) {
        source_addressing_method = find_addressing_method(source_operand);
    }
    if (strcmp(dest_operand, "NULL") != 0) {
        dest_addressing_method = find_addressing_method(dest_operand);
    }
    /* Check if the source addressing method is allowed */
    if (current_op_code.source_address[source_addressing_method] == 0) return firstPassError_command_invalid_source_adress;

    /* Check if the destination addressing method is allowed */
    if (current_op_code.destination_address[dest_addressing_method] == 0) return firstPassError_command_invalid_dest_adress;

    if (source_addressing_method == 0) {
        if (atoi(source_operand + 1) < -(1 << 11) || atoi(source_operand + 1) >= (1 << 11)) {
            return firstPassError_command_code_number_oor;
        }
    }
    if (dest_addressing_method == 0) {
        if (atoi(source_operand + 1) < -(1 << 11) || atoi(source_operand + 1) >= (1 << 11)) {
            return firstPassError_command_code_number_oor;
        }
    }
    if (symbol_flag) {
        add_symbol(symbol_name, OPCODE_FLAG, symbol_table);
    }

    encode_opcode(opcode_name, source_operand, dest_operand, source_addressing_method, dest_addressing_method);

    if (source_operand != NULL && source_operand != opcode_operands) {
        free(source_operand);
    }
    if (dest_operand != NULL && dest_operand != opcode_operands) {
        free(dest_operand);
    }
    return Error_Success;

}

/* Function to find addressing method as an integer */
int find_addressing_method(char* operand) {
    if (operand[0] == '#') {
        int i = 1;
        if (operand[i] == '-' || operand[i] == '+') {
            i++;
        }
        while (isdigit(operand[i])) {
            i++;
        }
        if (operand[i] == '\0') {
            return 0; /* Immediate addressing method */
        }
    }
    if (operand[0] == '*') {
        if (register_num(operand+1) > -1) {
            return 2; /* Register indirect addressing method */
        }
    }
    if (register_num(operand) > -1) {
        return 3; /* Register direct addressing method */
    }
    return 1; /* Direct addressing method (symbol) */
}



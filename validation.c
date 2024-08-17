#include "validation.h"

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
    return firstPassError_success;
}

enum project_error valid_data(char *line){
    const char *ptr = line;
    if(is_empty_line(line)) return firstPassError_data_empty_line;

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
    return firstPassError_success;; /* Valid instruction */
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
    return firstPassError_success;
}

int handel_entry_extern(EntryExternContent context, hash_table symbol_table, hash_table macro_tabel){
    char *after_entry_extern_symbol_name;
    enum project_error current_error;

    after_entry_extern_symbol_name = str_without_spaces(context->line + context->offset);

    if (is_empty_line(context->line + context->offset)) {
        print_error_custom_message(firstPassError_extern_entry_without_symbol, context->line_num, context->am_path, context->first_word);
        return 0;
    }

    if ((current_error = valid_symbol(after_entry_extern_symbol_name, macro_tabel)) != firstPassError_success) {
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
        return 0;
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

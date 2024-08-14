#include "first_pass.h"
int DC = 0;
int IC = 0;

int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table) {
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH], symbol_name[MAX_LABEL_LENGTH];
    int error_found = 0;
    enum project_error current_error;
    int symbol_flag = 0, offset = 0, after_label_offset = 0;
    int line_num = 0;

    am_file = open_new_file(am_path, ".am", "r");
    /* Initialize  symbol table */
    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num++;
        /*printf("line number: %d line is: %s", line_num, line);*/

        /*initial variables*/
        symbol_flag = 0;
        offset = 0;

        sscanf(line, "%s%n", first_word, &offset);

        printf("line: %d, first word: %s\n", line_num, first_word);
        /*check if word is a symbol*/
        if (first_word[strlen(first_word) - 1] == ':') {
            strcpy(symbol_name, substring(my_strdup(first_word), 0, strlen(first_word)-1));
            if((current_error = valid_symbol(first_word, macro_table)) != firstPassError_success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;
            }

            symbol_flag = 1;
            sscanf(line + offset, "%s%n", first_word, &after_label_offset);
            offset += after_label_offset;
        }

        /*DATA IMAGE SECTION*/
        if((strcmp(first_word, ".data") == 0)){
            if((current_error = valid_data(line + offset)) != firstPassError_success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;;
            }
            /*printf("line: %d, added data\n", line_num);*/
            /*add data to datalist*/
            if(symbol_flag){
                add_symbol(symbol_name, DATA_FLAG, symbol_table);

            }


        }
        if(strcmp(first_word, ".string") == 0){
            if((current_error = valid_string(line + offset)) != firstPassError_success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
            }
            /*add string to datalist*/

            if(symbol_flag){
                add_symbol(symbol_name, DATA_FLAG, symbol_table);
            }
        }


        /* TODO
        current_error = firstPassError_label_empty_line;
        */

        /*CODE IMAGE SECTION*/
    }
    fclose(am_file);
    /* At this point, the symbol table should be filled with all labels and their addresses. */
    /* You might want to print the symbol table for debugging purposes.
    print_symbol_table(sym_table);
    destroy_symbol_table(sym_table);*/

    return error_found;

}

enum project_error valid_symbol(char *symbol_name, hash_table macro_table) {
    int word_len = strlen(symbol_name);
    int i;
    /*check valid len*/
    if(word_len > 32) return firstPassError_label_invalid_length;
    if(is_instruction(symbol_name)) return firstPassError_label_invalid_name_is_inst;
    if (!isalpha(symbol_name[0])) return firstPassError_label_invalid_name_starts_with_numbers;
    for (i = 1; i < word_len - 1; i++) {
        if (!isalnum(symbol_name[i]) && symbol_name[i] != '_') {
            return firstPassError_label_invalid_name;
        }
    }
    if(opcode_num(symbol_name)>=0) return firstPassError_label_invalid_name_is_opcode;
    if(register_num(symbol_name)>=0) return firstPassError_label_invalid_name_is_reg;
    if (is_in_table(macro_table, symbol_name)) return firstPassError_label_macro_name;
    return firstPassError_success;
}

enum project_error valid_data(char *line){
    const char *ptr = line;
    if(is_empty_line(line)) return firstPassError_string_empty_line;

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

enum project_error valid_string(char *line) {
    char *start_ptr = line;
    char *end_ptr = line+strlen(line)-1;

    if(is_empty_line(line)) return firstPassError_string_empty_line;

    while (isspace(*start_ptr)) start_ptr++;
    while (isspace(*end_ptr)) end_ptr--;

    if (*start_ptr != '\"') return firstPassError_string_expected_quotes;
    if (*end_ptr != '\"') return firstPassError_string_expected_end_quotes;

    while (start_ptr < end_ptr) {
        if (!isprint(*start_ptr)) return firstPassError_string_not_printable;
        start_ptr ++;
    }
    return firstPassError_success;
}

enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table) {
    Symbol new_symbol;
    new_symbol = (Symbol)handle_malloc(sizeof(struct symbol));

    if (is_in_table(symbol_table, symbol_name)) return firstPassError_label_name_taken;

    new_symbol -> count = DC;
    new_symbol -> flag = type_flag;

    insert_table(symbol_table, symbol_name, new_symbol);

    return firstPassError_success;

}

enum project_error encode_data(char* data_argument) {

    return firstPassError_success;
}
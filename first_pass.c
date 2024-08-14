#include "first_pass.h"

int first_pass(char * am_path, hash_table macro_table) {
    FILE * am_file;
    int DC, IC;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH], symbol_name[MAX_LINE_LENGTH];
    int old_error = 0;
    int error_found = 0;
    enum project_error current_error;
    int symbol_flag = 0, offset = 0;
    int line_num = 0;
    am_file = open_new_file(am_path, ".am", "r");
    /* Initialize  symbol table */
    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num++;
        /*printf("line number: %d line is: %s", line_num, line);*/

        /*initial variables*/
        symbol_flag = 0;
        old_error = 0;

        sscanf(line, "%s%n", first_word, &offset);

        printf("line: %d, first word: %s\n", line_num, first_word);
        /*check if word is a symbol*/
        if (first_word[strlen(first_word) - 1] == ':') {
            if((current_error = valid_symbol(first_word, macro_table)) != firstPassError_success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;
            }
            symbol_flag = 1;
        }
        if (first_word[0] == '.') { /*word is starting with "." so it can be .string/.data/.extern/.entry*/
            if ((current_error = is_data_string(first_word)) != firstPassError_success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
            }
        }

    }

    fclose(am_file);
    /* At this point, the symbol table should be filled with all labels and their addresses. */
    /* You might want to print the symbol table for debugging purposes.
    print_symbol_table(sym_table);
    destroy_symbol_table(sym_table);*/

    return error_found;

}

enum project_error valid_symbol(char *word, hash_table macro_table) {
    int word_len = strlen(word);
    char *symbol_name = substring(my_strdup(word), 0, word_len-1);
    int i;
    /*check valid len*/
    if(word_len > 32) return firstPassError_label_invalid_length;
    if(is_instruction(symbol_name)) return firstPassError_label_invalid_name_is_inst;
    if (!isalpha(word[0])) return firstPassError_label_invalid_name_starts_with_numbers;
    for (i = 1; i < word_len - 1; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return firstPassError_label_invalid_name;
        }
    }
    if(opcode_num(symbol_name)>=0) return firstPassError_label_invalid_name_is_opcode;
    if(register_num(symbol_name)>=0) return firstPassError_label_invalid_name_is_reg;
    if (is_in_table(macro_table, symbol_name)) return firstPassError_label_macro_name;
    return firstPassError_success;
}

enum project_error is_data_string(char *word) {
    return firstPassError_success;
}
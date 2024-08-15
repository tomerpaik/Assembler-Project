#include "first_pass.h"
int DC = 0;
int IC = 0;

int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table) {
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH], symbol_name[MAX_LABEL_LENGTH];
    int error_found = 0;
    enum project_error current_error = 0;
    int symbol_flag, offset, after_label_offset, line_num = 0;

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
            if((current_error = valid_symbol(symbol_name, macro_table)) != firstPassError_success) {
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
                continue;
            }

            if(symbol_flag){
                add_symbol(symbol_name, DATA_FLAG, symbol_table);

            }


            if((current_error = encode_data(line + offset)) != firstPassError_success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;
            }

        }
        else if(strcmp(first_word, ".string") == 0){
            if((current_error = valid_string(line + offset)) != firstPassError_success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;
            }
            /*add string to datalist*/

            if(symbol_flag){
                add_symbol(symbol_name, DATA_FLAG, symbol_table);
            }

            encode_string(line + offset);
        }


        /*CODE IMAGE SECTION*/
        else if(opcode_num(first_word) == -1) {
            current_error = firstPassError_command_not_found;
            print_error(current_error, line_num, am_path);
            error_found = 1;
        }else {

        }

        /*if((current_error = valid_opcode(line + offset - after_label_offset)) != firstPassError_success) {
            print_error(current_error, line_num, am_path);
            error_found = 1;
            continue;
        }*/

    }
    print_symbol_table(symbol_table);
    fclose(am_file);

    return error_found;

}

enum project_error valid_symbol(char *symbol_name, hash_table macro_table) {
    int i;
    int symbol_name_len;
    symbol_name_len = strlen(symbol_name);

    /*check valid len*/
    if(symbol_name_len > 32) return firstPassError_label_invalid_length;
    if(is_instruction(symbol_name)) return firstPassError_label_invalid_name_is_inst;
    if (!isalpha(symbol_name[0])) return firstPassError_label_invalid_name_starts_with_numbers;
    for (i = 1; i < symbol_name_len - 1; i++) {
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

enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table) {
    Symbol new_symbol;
    new_symbol = (Symbol)handle_malloc(sizeof(struct symbol));

    if (is_in_table(symbol_table, symbol_name)) return firstPassError_label_name_taken;

    if (type_flag == DATA_FLAG) {
        new_symbol->count = DC;
    }
    if (type_flag == OPCODE_FLAG) {
        new_symbol->count = IC;
    }
    /*TODO: extern / entry*/
    new_symbol->flag = type_flag;

    printf("Adding Symbol: %s, Count: %d, Flag: %d\n", symbol_name, new_symbol->count, new_symbol->flag);

    insert_table(symbol_table, symbol_name, new_symbol);

    return firstPassError_success;
}

enum project_error encode_data(char* data_arguments) {
    short data_encoded = 0;
    char *number_token;
    char *argument_copy;
    long num_value;
    char* data_short_is_binary;
    argument_copy = my_strdup(data_arguments);
    number_token = strtok(argument_copy, ","); /* Use strtok to split the data_argument by commas */

    while (number_token != NULL) {
        num_value = strtol(number_token, NULL, 10);         /* Convert the number string to a long integer */
        if (num_value < -16384 || num_value > 16383) {         /* Validate the number to ensure it fits within 15 bits (-16384 to 16383) */
            free(argument_copy);
            return firstPassError_data_argument_out_of_range;
        }

        data_encoded = convert_to_15bit_binary(num_value);         /* Use the convert_to_15bit_binary function to encode the number */

        data_short_is_binary = short_to_binary_string(data_encoded);
        append_to_data_image(data_encoded); /*Adds the new short to the data image array*/
        DC++; /*updates the data counter*/
        printf(""CYAN"number %s\ndata encoded: -------%s-------\n" RESET " ",number_token, data_short_is_binary);
        number_token = strtok(NULL, ","); /* Get the next argument */
    }

    free(argument_copy);
    return firstPassError_success;  /* Return success if arguments are found and processed */
}

enum project_error encode_string(char* string) {
    char *string_without_spaces, *string_arguments;
    short encoded_char;
    int i;

    string_without_spaces = str_without_spaces(string);
    string_arguments = substring(string_without_spaces, 1, strlen(string_without_spaces) - 2);


    for (i = 0; i < strlen(string_arguments); i++) {
        encoded_char = (short)string_arguments[i]; /* Convert character to its ASCII value */
        append_to_data_image(encoded_char); /* Add the ASCII value to the data image */
        DC++; /* Update the data counter */
        printf(""CYAN"Character: %c, Encoded ASCII: %s\n" RESET, string_arguments[i], short_to_binary_string(encoded_char));
    }

    /* Add the null terminator '\0' at the end of the string */
    encoded_char = 0;
    append_to_data_image(encoded_char);
    DC++;
    printf(""CYAN"Null terminator added: Encoded ASCII: %s\n" RESET, short_to_binary_string(encoded_char));

    free(string_arguments);
    return firstPassError_success;
}


int append_to_data_image(short encoded_value) {
    if (DC >= MAX_MEMORY_SPACE) {
        return -1;
    }
    data_image[DC++] = encoded_value;
    return 0;
}

/*enum project_error valid_opcode(char * opcode_line) {
    op_code current_op_code; int opcode_offset = 0;
    char * opcode_name = NULL, * opcode_arguments;
    opcode_offset = get_first_word(opcode_line, opcode_name);

    current_op_code = OPCODES[opcode_num(opcode_name)];

    /*valid arg num #1#
    opcode_arguments = str_without_spaces(opcode_line + opcode_offset);

    /*operand does not fit to #1#


    /*#1#
    /*#1#
    /*#1#
    /*#1#
    return firstPassError_success;
}*/


void print_symbol_table(hash_table table) { /*TODO: sort the table?*/
    int i;
    Node current;

    printf("| %-11s | %-5s | %-4s |\n", "Symbol Name", "Count", "Flag");
    printf("|-------------|-------|------|\n");

    for (i = 0; i < TABLE_SIZE; i++) {
        current = table[i];
        while (current != NULL) {
            Symbol sym = (Symbol)current->value;
            printf("| " BOLD GREEN "%-11s" RESET " | " BOLD BLUE "%-5d" RESET " | " BOLD MAGENTA "%-4d" RESET " |\n",
                   current->key,
                   sym->count,
                   sym->flag);
            current = current->next;
        }
    }
}

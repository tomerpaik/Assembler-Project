#include "first_pass.h"
int DC = 0;
int IC = 0;

int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table) {
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH], symbol_name[MAX_LABEL_LENGTH];
    int error_found = 0;
    enum project_error current_error = 0;
    int symbol_flag, offset, after_label_offset=0, line_num = 0;
    EntryExternContent content;
    am_file = open_new_file(am_path, ".am", "r");
    /* Initialize  symbol table */
    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num++;
        if (is_comment_empty_line(line)) continue; /*IF line is a comment or a empty sentence SKIP to the next line*/
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
            encode_data(line + offset);
            continue;
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
            continue;
        }
        /*ENTRY/EXTERN SECTION*/
        else if(strcmp(first_word, ".entry") == 0 || strcmp(first_word, ".extern") == 0) {
            content = init_entry_extern_context(first_word, line, offset, line_num, am_path);
            if(!handel_entry_extern(content, symbol_table, macro_table)) {
                free_entry_extern_context(content);
                error_found = 1;
                continue;
            }
            free_entry_extern_context(content);
            continue;
        }

        /*CODE SECTION*/
        else if (symbol_flag) {
            if(is_in_table(symbol_table, symbol_name)) {
                print_error(GENERIC_NO_E, line_num, am_path);  /*TODO: find right error to asign*/
                error_found = 1;
                continue;
            }
            add_symbol(symbol_name, OPCODE_FLAG, symbol_table);
        }
        if ((current_error = valid_opcode(line + offset, first_word, symbol_table, macro_table)) != firstPassError_success) {
            print_error(current_error, line_num, am_path);
            error_found = 1;
            continue;
        }else {
            /*encode*/
        }

    }
    /*DEBUG:*/
    print_symbol_table(symbol_table);
    fclose(am_file);

    return error_found;

}

enum project_error valid_opcode(char *opcode_operands, char* opcode_name, hash_table symbol_table, hash_table macro_table) {
    op_code current_op_code;
    char *source_operand = "NULL", *dest_operand = "NULL";
    int source_addressing_method = 4, dest_addressing_method = 4; /*RESET addressing_method TO BE NO_METHOD*/
    int can_encode_flag = 1;

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
        source_addressing_method = find_addressing_method(source_operand, symbol_table);
    }
    if (strcmp(dest_operand, "NULL") != 0) {
        dest_addressing_method = find_addressing_method(dest_operand, symbol_table);
    }
    /* Check if the source addressing method is allowed */
    if (current_op_code.source_address[source_addressing_method] == 0) return firstPassError_command_invalid_source_adress;

    /* Check if the destination addressing method is allowed */
    if (current_op_code.destination_address[dest_addressing_method] == 0) return firstPassError_command_invalid_dest_adress;

    if(source_addressing_method == 1) {
        if (is_in_table(symbol_table, source_operand)) {
            can_encode_flag = 1;
        } else {
            if(valid_symbol(source_operand, macro_table) != firstPassError_success) return firstPassError_command_invalid_operand;
            /*TODO: add to struct*/
            can_encode_flag = 0;
        }
    }
    if(dest_addressing_method == 1) {

    }

    return firstPassError_success;
}

/* Function to find addressing method as an integer */
int find_addressing_method(char* operand, hash_table symbol_table) {
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




enum project_error add_symbol(char* symbol_name, enum symbol_flag type_flag, hash_table symbol_table) {
    Symbol new_symbol;
    new_symbol = (Symbol)handel_malloc(sizeof(struct symbol));

    if ((is_in_table(symbol_table, symbol_name) && new_symbol->count == 0)) return firstPassError_symbol_name_taken;

    if (type_flag == DATA_FLAG) {
        new_symbol->count = DC;
    }
    if (type_flag == OPCODE_FLAG) {
        new_symbol->count = IC+100;
    }
    if (type_flag == EXTERN_FLAG || type_flag == ENTRY_FLAG) {
        new_symbol->count = 0;
    }
    new_symbol->flag = type_flag;

    insert_table(symbol_table, symbol_name, new_symbol);

    return firstPassError_success;
}





enum symbol_flag get_symbol_flag(hash_table symbol_table, char *symbol_name) {
    Symbol symbol = search_table(symbol_table, symbol_name);
    if (symbol != NULL) {
        return symbol->flag;
    }
    return -1;
}


void print_symbol_table(hash_table table) {
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


#include "second_pass.h"
int second_pass(char * am_path, hash_table symbol_table) {
    IC = 0;
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH]; char * symbol_name = 0;
    char * opcode_line;
    int error_found = 0;
    enum project_error current_error = 0;
    int offset, after_label_offset=0, line_num = 0;
    am_file = open_new_file(am_path, ".am", "r");
    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num++;
        if (is_comment_empty_line(line)) continue; /*IF line is a comment or a empty sentence SKIP to the next line*/

        sscanf(line, "%s%n", first_word, &offset);

        if (first_word[strlen(first_word) - 1] == ':') {
            sscanf(line + offset, "%s%n", first_word, &after_label_offset);

            offset += after_label_offset;
        }

        if(strcmp(first_word, ".data") == 0 || strcmp(first_word, ".string") == 0 || strcmp(first_word, ".extern") == 0) {
            continue;
        }
        if(strcmp(first_word, ".entry") == 0) {
            symbol_name = line + after_label_offset;
            if(is_in_table(symbol_table, symbol_name)) {
                if (get_symbol_flag(symbol_table, symbol_name) == DATA_FLAG) {
                    update_symbol_flag(symbol_table, symbol_name, ENTRY_FLAG_DATA);
                    continue;
                }
                if (get_symbol_flag(symbol_table, symbol_name) == OPCODE_FLAG) {
                    update_symbol_flag(symbol_table, symbol_name, ENTRY_FLAG_OPCODE);
                }else { /*extern*/
                    error_found = 1;
                    print_error(firstPassError_extern_entry_in_same_file, line_num, am_path);
                }
            } else {

                error_found = 1;
                return GENERIC_NO_E; /*TODO: entry is not defined in the file and it shoud be */
            }
        } else {
            /*finish encoding*/
            IC++;
            printf("opcodename: %s operands: %s", first_word, line+offset);
            if ((current_error = find_symbol_check(line + offset, first_word, symbol_table, symbol_name)) != Error_Success) {
                error_found = 1;
                return current_error;
            }
        }
    }

    if (symbol_name != 0) {
        free(symbol_name);
    }
    return error_found;
}

void encode_symbol(hash_table symbol_table, char * symbol_name) {
    printf("symbol to encode %s\n", symbol_name);
    short encoded_word = 0;
    short encoded_symbol_address = 0;
    encoded_symbol_address = get_symbol_count(symbol_table, symbol_name) << 3;
    if (get_symbol_flag(symbol_table, symbol_name) == EXTERN_FLAG) {
        encoded_word = encoded_symbol_address | EXTERNAL;
    }
    if (get_symbol_flag(symbol_table, symbol_name) == ENTRY_FLAG_DATA) {
        encoded_word = encoded_symbol_address | RELOCATABLE;
    }else {
        encoded_word = encoded_symbol_address | ABSOLUTE;
    }
    append_to_code_image(encoded_word); /*without i++ in order to override current 0000... default value*/
    IC++;
}



enum project_error find_symbol_check(char *opcode_operands, char* opcode_name, hash_table symbol_table, char * symbol_name) {
    op_code current_op_code;
    char *source_operand = "NULL", *dest_operand = "NULL";
    int source_addressing_method = 4, dest_addressing_method = 4; /*RESET addressing_method TO BE NO_METHOD*/
    current_op_code = OPCODES[opcode_num(opcode_name)]; /* Find the opcode in the OPCODES array */

    if (current_op_code.arg_num == 2) {
        source_operand = strtok(opcode_operands, ","); /* Tokenize the operands using comma as a delimiter */
        if (source_operand != NULL) {
            source_operand = str_without_spaces(source_operand);  /* Remove spaces around operand1 */
            dest_operand = str_without_spaces(strtok(NULL, ","));
        } else {
            source_operand = "NULL", dest_operand = "NULL";
        }
    } else if (current_op_code.arg_num == 1) {
        dest_operand = str_without_spaces(opcode_operands);
    }
    if (strcmp(source_operand, "NULL") != 0) {
        source_addressing_method = find_addressing_method(source_operand);
    }
    if (strcmp(dest_operand, "NULL") != 0) {
        dest_addressing_method = find_addressing_method(dest_operand);
    }

    printf("source_addressing_method %d\n", source_addressing_method);
    printf("dest_addressing_method %d\n", dest_addressing_method);

    if (source_addressing_method == 1) {
        if(!is_in_table(symbol_table, source_operand)) {
            return GENERIC_NO_E; /*TODO: label is not defined in the file*/
        }
        if(is_in_table(symbol_table, source_operand) && (get_symbol_flag(symbol_table, source_operand) == OPCODE_FLAG || get_symbol_flag(symbol_table, source_operand) == ENTRY_FLAG_OPCODE)) {
            return GENERIC_NO_E; /*TODO: label that defined as a command operand can not be in type OPCODE Symbol*/
        }
        encode_symbol(symbol_table, source_operand);
    }else {
        IC++;
    }
    if (dest_addressing_method == 1) {
        if(!is_in_table(symbol_table, dest_operand)) {
            return GENERIC_NO_E; /*TODO: label is not defined in the file*/
        }
        if(is_in_table(symbol_table, dest_operand) && (get_symbol_flag(symbol_table, dest_operand) == OPCODE_FLAG || get_symbol_flag(symbol_table, dest_operand) == ENTRY_FLAG_OPCODE)) {
            return GENERIC_NO_E; /*TODO: label that defined as a command operand can not be in type OPCODE Symbol*/
        }
        encode_symbol(symbol_table, dest_operand);
    }else {
        IC++;
    }
    return Error_Success;
}
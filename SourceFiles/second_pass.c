#include "../Headers/second_pass.h"
int second_pass(char * am_path, hash_table symbol_table) {
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH]; char * symbol_name = 0;
    int error_found = 0; int creat_ext = 0; int create_ent = 0; enum project_error current_error = 0;
    int offset, after_label_offset=0, line_num = 0;
    am_file = open_new_file(am_path, ".am", "r");
    update_symbol_table_values(symbol_table);
    IC = 0;
    while (fgets(line, MAX_LINE_LENGTH, am_file)) {
        line_num++;
        if (is_comment_empty_line(line)) continue; /*IF line is a comment or a empty sentence SKIP to the next line*/
        sscanf(line, "%s%n", first_word, &offset);

        if (first_word[strlen(first_word) - 1] == ':') {
            sscanf(line + offset, "%s%n", first_word, &after_label_offset);

            offset += after_label_offset;
        }
        if(strcmp(first_word, ".data") == 0 || strcmp(first_word, ".string") == 0) {
            continue;
        }
        if ((strcmp(first_word, ".extern") == 0) && !creat_ext) {
            open_new_file(am_path, ".ext", "w");
            creat_ext = 1;
            continue;
        }

        if(strcmp(first_word, ".entry") == 0) {
            if (!create_ent) {
                open_new_file(am_path, ".ent", "w");
                create_ent = 1;
            }
            symbol_name = str_without_spaces(line + offset);
            if(is_in_table(symbol_table, symbol_name)) {
                append_to_ext_ent_file(am_path, ".ent", symbol_name, get_symbol_count(symbol_table, symbol_name));
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
                print_error(SECOND_PASS_ERROR_ENTRY_SYMBOL_NEXSIT, line_num, am_path);
            }
        } else {
            /*finish encoding*/
            if ((current_error = handle_operand_symbol(line+offset, symbol_table, am_path)) != Error_Success) {
                error_found = 1;
                print_error(current_error, line_num, am_path);
            }
        }
    }
    create_object_file(am_path);


    if (symbol_name != 0) {
        free(symbol_name);
    }
    return error_found;
}



void update_symbol_table_values(hash_table symbol_table) {
    int i;
    Node current;
    Symbol sym;
    printf("UPDATING DATA VALUES\n");


    for (i = 0; i < TABLE_SIZE; i++) {
        current = symbol_table[i];

        while (current != NULL) {
            sym = (Symbol)current->value;

            if (get_symbol_flag(symbol_table, current->key) == DATA_FLAG || get_symbol_flag(symbol_table, current->key) == ENTRY_FLAG_DATA) {
                sym->count += IC + 100;
            }

            current = current->next; /* Move to the next node */
        }
    }
}

void create_object_file(char * file_name) {
    unsigned short positive_value ;
    FILE *file = open_new_file(file_name, ".ob","w");
    int i;
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    fprintf(file, "   %d %d\n", IC, DC);
    for (i = 0; i < IC; i++) {
        positive_value = code_image[i] & 0x7FFF;
        fprintf(file, "%04d %05o\n", i+100, positive_value);
    }
    for (i = 0; i < DC; i++) {
        positive_value = data_image[i] & 0x7FFF;
        fprintf(file, "%04d %05o\n", IC+i+100, positive_value);
    }
    fclose(file);

}
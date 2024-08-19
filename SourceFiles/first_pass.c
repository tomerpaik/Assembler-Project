#include "../Headers/first_pass.h"

#include <stdio.h>
#include <string.h>
int DC = 0;
int IC = 0;

int first_pass(char * am_path, hash_table macro_table, hash_table symbol_table) {
    FILE * am_file;
    char line[MAX_LINE_LENGTH], first_word[MAX_LINE_LENGTH], symbol_name[MAX_LABEL_LENGTH];
    int error_found = 0;
    enum project_error current_error = 0;
    int symbol_flag, offset, after_label_offset=0, line_num = 0;
    char * first_word_copy = 0;
    char * substring_symbol_copy = 0;
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

        if (first_word[strlen(first_word) - 1] == ':') { /*found optional symbol define*/
            first_word_copy = my_strdup(first_word);
            substring_symbol_copy = substring(first_word_copy, 0, strlen(first_word)-1);
            strcpy(symbol_name, substring_symbol_copy);
            if((current_error = valid_symbol(symbol_name, macro_table)) != Error_Success) {
                print_error(current_error, line_num, am_path);
                error_found = 1;
                continue;
            }

            symbol_flag = 1;
            sscanf(line + offset, "%s%n", first_word, &after_label_offset); /*update first word to point the word after label*/
            offset += after_label_offset; /*updating rest of the world to point the word after label*/
        }

        /*DATA IMAGE SECTION*/
        if((strcmp(first_word, ".data") == 0)){ /*found optional .data instuction*/
            if((current_error = valid_data(line + offset)) != Error_Success) {
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
        else if(strcmp(first_word, ".string") == 0){ /*found optional .data instuction*/
            if((current_error = valid_string(line + offset)) != Error_Success) {
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
        if ((current_error = handel_opcode(line + offset, first_word, symbol_table, symbol_name, symbol_flag)) != Error_Success) {
            print_error(current_error, line_num, am_path);
            error_found = 1;
        }
    }
    fclose(am_file);
    if (first_word_copy != NULL) {
        free(first_word_copy);
        first_word_copy = NULL;
    }
    if (substring_symbol_copy != NULL) {
        free(substring_symbol_copy);
        substring_symbol_copy = NULL;
    }
    return error_found;
}




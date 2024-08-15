#include "pre_assembler.h"

#include "first_pass.h"

int pre_assembler(char * file_name, hash_table macro_table) {
    FILE *as_file , *am_file;
    /*error handleing trouble opening the file*/
    as_file = open_new_file(file_name, ".as", "r");
    if (as_file == NULL) {
        return 0;
    }
    am_file = open_new_file(file_name, ".am", "w");

    if (process_macros(as_file, am_file, file_name, macro_table)) {
        /*free_table(macro_table);*/    /*free_macro_table(macroTable);*/
        return 1;
    }
    fclose(as_file);
    fclose(am_file);
    return 0;
}
int process_macros(FILE * inputFile, FILE * outputFile,char * file_name, hash_table macroTable){
    /*Initialize Varibals*/
    char line[MAX_LINE_LENGTH], word[MAX_LINE_LENGTH], macroName[MAX_MACRO_NAME_LENGTH], *helpful_empty_str = NULL;
    int inMacroFlag = 0,  line_num = 0, total_body_length = 0, error_found = 0;
    /*check macro*/
    int macro_name_offset = 0, offset = 0;
    /*running on the file */
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        line_num++;
        if(!line_length_valid(line, line_num)) {
            continue;
        }
        /*TODO: if no word was found sscanf will return 0 we wiil continue to the next line*/
        sscanf(line, "%s%n", word, &offset);
        if (!strcmp(word, MACRO_START)) {
            inMacroFlag = 1;
            if (!sscanf(line + offset, "%s%n", macroName, &macro_name_offset)) { /*scanf returns 0 means no name was found*/
                print_error(Macro_Without_Name, line_num, file_name);
                error_found  = 1;
                inMacroFlag = 0;
                continue;
            }
            if (!is_empty_after_key(line + macro_name_offset + offset)) { /*more text after macro name*/
                print_error(Macro_ETA_MacroName, line_num, file_name);
                error_found  = 1;
                inMacroFlag = 0;
                continue;
            }
            if (!is_valid_macro_name(macroName, line_num, file_name)) {
                error_found  = 1;
                inMacroFlag = 0;
                continue;
            }
            if (search_table(macroTable, macroName) == 0) {
                total_body_length = 0;
                helpful_empty_str = my_strdup("");
                insert_table(macroTable, macroName, (char*)(helpful_empty_str));
            }else {
                print_error(Macro_double_define, line_num, file_name);
                error_found  = 1;
                inMacroFlag = 0;
            }
        }
        else if (!strcmp(word, MACRO_END)) {
            inMacroFlag = 0;
            if (!is_empty_after_key(line + offset)) {
                print_error(Macro_ETA_endmacr, line_num, file_name);
                error_found  = 1;
            }
        }
        else if (inMacroFlag){
            add_to_macro_body(macroTable, line, macroName, &total_body_length);
        }
        else if(search_table(macroTable, word)){ /*check if first word is macro call*/
            if (!is_empty_after_key(line + offset)) {
                print_error(Macro_ETA_MacroCall, line_num, file_name);
                error_found  = 1;
                continue;
            }
            fputs((char*)search_table(macroTable, word), outputFile);
        }else {
            fputs(line, outputFile);
        }
    }
    free(helpful_empty_str);
    fclose(inputFile);
    fclose(outputFile);
    return !error_found;
}
int is_valid_macro_name(char *name, int line_num, char * file_name) {
    if(is_instruction(name) || opcode_num(name) >= 0 || register_num(name) >=0) {
        print_error(Macro_nameis_Reg_Op_Inst, line_num, file_name); /*TODO: shoud be external print*/
        return 0;
    }
    if (!strcmp(name, MACRO_START) && !strcmp(name, MACRO_END)) {
        print_error(macro_name_MACR_ENDMACR, line_num, file_name);
        return 0;
    }
    if (isdigit(name[0])) print_error(Macro_namestart_with_numbers, line_num, file_name);
    if(strlen(name) > MAX_MACRO_NAME_LENGTH) {
        print_error(Macro_nameis_oor, line_num, file_name);
        return 0;
    }
    return 1;
}

void add_to_macro_body(hash_table table, char *line, char *macroName, int *macro_len) {
    char *macro_val, *after_realloc_body;  int new_len;
    macro_val = (char*)search_table(table, macroName);
    if (macro_val == NULL) {
        printf("Error: Macro not found\n");
        return;
    }

    new_len = *macro_len + strlen(line) + 1;
    after_realloc_body = realloc(macro_val, new_len);
    if (after_realloc_body == NULL) {
        printf("Error: Realloc failed\n");
        return;
    }

    strcat(after_realloc_body, line);
    *macro_len = new_len;

    update_table_value(table, macroName, after_realloc_body);
}

void print_macro_table(hash_table table) {
    /*TODO: sort the table?*/
    int i;
    Node current;

    printf("| %-11s | %-5s |\n", "Macro Name", "Body");
    printf("|-------------|-------|\n");

    for (i = 0; i < TABLE_SIZE; i++) {
        current = table[i];
        while (current != NULL) {
            printf("| " BOLD GREEN "%-11s" RESET " | " BOLD BLUE "%-5s" RESET " |\n",
                   current->key,
                   (char*)current->value);
            current = current->next;
        }
    }
}
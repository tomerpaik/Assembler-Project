#include "../Headers/main.h"

/***************************************************
 * Project: FINAL - ASSEMBLER
 * Authors: ROY KAGAN ID: 327077988, TOMER PAIKOWSKEY ID: 329816060
 * Course: LABORATORY "MAABADA" 20465, Fall Semester: 2024b
 * University: OPEN UNIVERSITY
 *
 *        INPUT: .AS FILE -->
 * PRE-ASSEMBLER: EXPANDS MACROS --> .AM FILE
 * FIRST PASS: VALIDATES INPUT CONTENT AND PERFORMS INITIAL ENCODING FOR DATA, FIRST COMMAND WORD
 * SECOND PASS: COMPLETES ENCODING (RESOLVES SYMBOLS USED AS COMMAND OPERANDS)
 *              --> OUTPUT: .ENT FILE, .EXT FILE, .OB FILE
 *
 * Additional Instructions:
 * Valid test cases are included in the folder `final_tests_valid`.
 * These files demonstrate the assembler's capabilities and can be run for validation.
 *
 * Thank you very much, Roni. It was a great experience
 ***************************************************/


int main(int argc, char *argv[]) {
    char *am_path;
    char *filePath;

    while (--argc > 0) {
        hash_table macro_table = {0};
        hash_table symbol_table = {0};

        am_path = argv[argc];

        printf(""BOLD"********* Starting Pre-Proccesor %s ********* \n"RESET"", argv[argc]);
        if (!pre_assembler(argv[argc], macro_table)){
            /*If it failed, remove .am.*/
            filePath = add_new_file(argv[argc], ".am");
            remove(filePath);
            free(filePath);

            free_table(macro_table);
            free_table(symbol_table);
            printf(""ORANGE"********* Removed .am File After Pre-Assembler Faild %s ********* \n"RESET"", argv[argc]);
            continue;
        }

        printf(""BOLD"********* Starting First Pass %s *********\n"RESET"", argv[argc]);
        /* Generate a new file with the ".am" extension by adding it to the input filename.*/

        /*Execute the first pass, and then the second on the ".am" file.*/
        if (first_pass(am_path, macro_table, symbol_table)) {
            /*If it failed, move to the next file.*/
            free_table(macro_table);
            free_table(symbol_table);
            printf(""ORANGE"********* First Pass Faild %s ********* \n"RESET"", argv[argc]);
            continue;
        }

        printf(""BOLD"********* Start Second Pass %s *********\n"RESET"", argv[argc]);

        if (second_pass(am_path, symbol_table)) {
            /*If it failed, move to the next file.*/
            free_table(macro_table);
            free_table(symbol_table);
            printf(""ORANGE"********* Second Pass Faild %s ********* \n"RESET"", argv[argc]);
            continue;
        }

        free_table(macro_table);
        free_table(symbol_table);
        printf(""BOLD"********* Done Assembling %s ********* \n\n"RESET"", argv[argc]);
    }

    printf(""BOLD"********* End-Assembler ********* \n"RESET"");
    return 0;
}
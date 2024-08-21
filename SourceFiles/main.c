#include "../Headers/main.h"

/**
 * This is the main function that processes the input files.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return Returns 0 on successful completion.
 */

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
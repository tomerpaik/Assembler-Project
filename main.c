#include "main.h"

/**
 * This is the main function that processes the input files.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return Returns 0 on successful completion.
 */

int main(int argc, char *argv[]) {
    char *am_path;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 0;
    }

    while (--argc > 0) {
        /* Generate a new file with the ".as" extension by adding it to the input filename.*/
        printf("Start pre-proc %s\n", argv[argc]);

        hash_table macro_table = {0};
        /*Execute the macro preprocessor on the ".as" file.*/
        if (!pre_assembler(argv[argc], macro_table)){
            /*If it failed, move to the next file.*/
            const char *filePath = combineFilePath(argv[argc], ".am");
            remove(filePath);
            print_internal_error(ERROR_CODE_15);
            continue;
        }

        printf("Start first pass %s\n", argv[argc]);
        /* Generate a new file with the ".am" extension by adding it to the input filename.*/
        am_path = argv[argc];

        /*Execute the first pass, and then the second on the ".am" file.*/
        if (first_pass(am_path)) {
            /*If it failed, move to the next file.*/
            continue;
        }

        /*Free allocated memory*/
        free(am_path);
    }
    printf("end\n");
    return 0;
}
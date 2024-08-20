#include "../Headers/general_functions.h"

void cleanup() {
    /*TODO: func that frees all alocated vars (shoud get malloc list)*/
}

void *handel_malloc(long object_size) {
    void *object_ptr = malloc(object_size);
    if (object_ptr == NULL) {
        print_generic_error(GENERIC_Allocation_Faild);
        exit(1);
    }
    return object_ptr;
}

char *add_new_file(char *file_name, char *ending) {
    char *c, *new_file_name;
    new_file_name = handel_malloc(MAX_LINE_LENGTH * sizeof(char));
    strcpy(new_file_name, file_name);
    /* deleting the file name if a '.' exists and forth */
    if ((c = strchr(new_file_name, '.')) != NULL) {
        *c = '\0';
    }
    /* adds the ending of the new file name */
    strcat(new_file_name, ending);
    return new_file_name;
}

FILE * open_new_file(char *file_name, char *ending, char * mode) {
    char *c, *new_file_name;
    FILE * file;
    new_file_name = handel_malloc(MAX_LINE_LENGTH * sizeof(char));
    strcpy(new_file_name, file_name);
    /* deleting the file name if a '.' exists and forth */
    if ((c = strchr(new_file_name, '.')) != NULL) {
        *c = '\0';
    }
    /* adds the ending of the new file name */
    strcat(new_file_name, ending);
    file = fopen(new_file_name, mode);
    free(new_file_name);
    if (file == NULL) {
        if (!strcmp(mode, "r")) {
            print_generic_error(GENERIC_Faild_OpenFile_R);
        }else {
            print_generic_error(GENERIC_Faild_OpenFile_W);
        }
        return NULL;
    }
    return file;
}


/**
 * Duplicates a string by allocating memory and copying the original string's content.
 *
 * @param src The source string to duplicate.
 * @return A pointer to the newly allocated string containing a copy of the source string.
 *         Returns NULL if memory allocation fails.
 */
void * my_strdup(const char* src) {
    char* dup;
    size_t len;
    /* Calculate the length of the source string, including the null terminator */
    len = strlen(src) + 1;
    /* Allocate memory for the duplicated string */
    dup = (char*)handel_malloc(len);
    /* Copy the content of the source string to the newly allocated memory */
    strcpy(dup, src);
    return dup; /* Return the duplicated string */
}

int line_length_valid(char* line) {
    int is_valid = 1;
    if(strlen(line) >= MAX_LINE_LENGTH-1) {
        is_valid = 0;

    }

    return is_valid;
}

int is_empty_after_key(const char *str) {
    while (isspace(*str)) {
        str++;
    }
    if (*str == '\0' || *str == '\n') {
        return 1;
    }
    return 0;
}

/** Converts an integer to a 15-bit binary representation using a 16-bit short */
short convert_to_15bit_binary(int number) {
    if (number >= (1 << 14) || number < -(1 << 14)) {
        return 0;
    }
    return (short)number;
}

/** Converts a 16-bit short to a binary string representation */
char* short_to_binary_string(short value) {
    int i;
    char* binary_str = (char*)handel_malloc(17);
    binary_str[16] = '\0';
    for (i = 15; i >= 0; i--) {
        binary_str[15 - i] = (value & (1 << i)) ? '1' : '0';
    }

    return binary_str;
}
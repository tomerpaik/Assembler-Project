#include "general_functions.h"
#include "errors.h"


void cleanup() {
    /*TODO: func that frees all alocated vars (shoud get malloc list)*/
}

void *handle_malloc(long object_size) {
    void *object_ptr = malloc(object_size);
    if (object_ptr == NULL) {
        print_internal_error(ERROR_CODE_1);
    }
    return object_ptr;
}

char *add_new_file(char *file_name, char *ending) {
    char *c, *new_file_name;
    new_file_name = handle_malloc(MAX_LINE_LENGTH * sizeof(char));
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
    new_file_name = handle_malloc(MAX_LINE_LENGTH * sizeof(char));
    strcpy(new_file_name, file_name);
    /* deleting the file name if a '.' exists and forth */
    if ((c = strchr(new_file_name, '.')) != NULL) {
        *c = '\0';
    }
    /* adds the ending of the new file name */
    strcat(new_file_name, ending);
    file = fopen(new_file_name, mode);
    if (file == NULL) {
        if (!strcmp(mode, "r")) {
            print_internal_error(ERROR_CODE_8);
        }else {
            print_internal_error(ERROR_CODE_7);
        }
        return NULL;
    }
    return file;
}

const char* combineFilePath(const char* basePath, const char* extension) {
    char* combinedPath;
    const size_t basePathLen = strlen(basePath);
    const size_t extensionLen = strlen(extension);
    combinedPath = handle_malloc(basePathLen + extensionLen + 1);

    strcpy(combinedPath, basePath);
    strcat(combinedPath, extension);

    return combinedPath;
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
    dup = (char*)handle_malloc(len);
    /* Copy the content of the source string to the newly allocated memory */
    strcpy(dup, src);
    return dup; /* Return the duplicated string */
}

int line_length_valid(char* line, int line_num) {
    int is_valid = 1;
    if(strlen(line) > MAX_LINE_LENGTH) {
        is_valid = 0;
        printf("In File: Line %d exceeds the maximum allowed length of characters.\n", line_num);
    }

    return is_valid;
}

int is_empty_after_key(char *str) {
    while (isspace(*str)) {
        str++;
    }
    if (*str == '\0' || *str == '\n') {
        return 1;
    }
    return 0;
}
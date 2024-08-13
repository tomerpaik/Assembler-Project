#ifndef BASIC_H
#define BASIC_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "errors_handle.h"
#include "globals.h"

typedef enum {
    false,
    true
}bool;

int line_length_valid(char* line, int line_num);
void *handle_malloc(long object_size);
const char* combineFilePath(const char* basePath, const char* extension);
FILE *open_new_file(char *file_name,char *ending, char *mode);
char *add_new_file(char *file_name, char *ending);
void* my_strdup(const char* src);
int is_empty_after_key(char *str);
#endif

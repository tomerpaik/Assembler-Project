#ifndef BASIC_H
#define BASIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#define MAX_LINE_LENGTH 82
#define INPUT_EXTENSION ".as"
#define OUTPUT_EXTENSION ".am"
#define MACRO_START "macr"
#define MACRO_END "endmacr"
#define TABLE_SIZE 100

void *handle_malloc(long object_size);
const char* combineFilePath(const char* basePath, const char* extension);
FILE *open_new_file(char *file_name,char *ending, char *mode);
char *add_new_file(char *file_name, char *ending);
#endif

#ifndef BASIC_H
#define BASIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "globals.h"

void *handle_malloc(long object_size);
const char* combineFilePath(const char* basePath, const char* extension);
FILE *open_new_file(char *file_name,char *ending, char *mode);
char *add_new_file(char *file_name, char *ending);
void* my_strdup(const char* src);
#endif

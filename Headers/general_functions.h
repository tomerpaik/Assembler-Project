#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

/**
 * @file general_functions.h
 * @brief General utility functions for handling memory, files, and conversions.
 *
 * This file contains declarations for various utility functions used throughout the project.
 * These include memory management, file handling, string manipulation, and conversion utilities.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "errors_handle.h"
#include "globals.h"

/* Definition of a boolean type for better readability */
typedef enum {
    false,
    true
} bool;

/**
 * @brief Validates the length of a line.
 *
 * This function checks if the length of the provided line exceeds the maximum allowed length.
 *
 * @param line The line to validate.
 * @return 1 if the line length is valid, 0 if it exceeds the maximum length.
 */
int line_length_valid(char* line);

/**
 * @brief Allocates memory and handles allocation errors.
 *
 * This function allocates memory for an object of the specified size and
 * checks if the allocation was successful. If not, it prints an error and exits.
 *
 * @param object_size The size of the object to allocate.
 * @return A pointer to the allocated memory.
 */
void *handel_malloc(long object_size);

/**
 * @brief Opens a new file with the specified name and mode.
 *
 * This function creates a new file name by appending the given extension
 * to the base file name and opens the file in the specified mode.
 *
 * @param file_name The base name of the file.
 * @param ending The file extension to add.
 * @param mode The mode in which to open the file (e.g., "r" for read, "w" for write).
 * @return A pointer to the opened file, or NULL if the file could not be opened.
 */
FILE *open_new_file(char *file_name, char *ending, char *mode);

/**
 * @brief Creates a new file name by appending an extension.
 *
 * This function generates a new file name by adding the specified extension
 * to the base file name, replacing any existing extension.
 *
 * @param file_name The base name of the file.
 * @param ending The file extension to add.
 * @return A pointer to the newly created file name string.
 */
char *add_new_file(char *file_name, char *ending);

/**
 * @brief Duplicates a string by allocating memory and copying the original string's content.
 *
 * This function creates a new string by duplicating the provided source string,
 * allocating the necessary memory to hold the copy.
 *
 * @param src The source string to duplicate.
 * @return A pointer to the newly allocated string containing a copy of the source string.
 */
void* my_strdup(const char* src);

/**
 * @brief Checks if a string is empty or contains only whitespace after a key.
 *
 * This function determines if there are any non-whitespace characters
 * remaining in a string after a key or command.
 *
 * @param str The string to check.
 * @return 1 if the string is empty or contains only whitespace, 0 otherwise.
 */
int is_empty_after_key(const char *str);

/**
 * @brief Converts an integer to a 15-bit binary representation.
 *
 * This function converts an integer to a 15-bit binary representation using a 16-bit short.
 * The function returns 0 if the integer is out of the 15-bit range.
 *
 * @param number The integer to convert.
 * @return The 15-bit binary representation as a short.
 */
short convert_to_15bit_binary(int number);

/**
 * @brief Converts a 16-bit short to a binary string representation.
 *
 * This function generates a binary string representation of a 16-bit short value.
 *
 * @param value The 16-bit short to convert.
 * @return A pointer to the binary string representation.
 */
char* short_to_binary_string(short value);

#endif /* GENERAL_FUNCTIONS_H */

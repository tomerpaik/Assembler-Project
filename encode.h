#ifndef ENCODE_H
#define ENCODE_H
#include "globals.h"
#include "first_pass.h"

enum project_error encode_data(char* data_arguments);
enum project_error encode_string(char* string_argument);
/**
 * Appends an encoded short value to the global data_image array.
 * @param encoded_value The short value to append.
 * @return 0 if successful, or -1 if there is not enough space.
 */
int append_to_data_image(short encoded_value);
int append_to_code_image(short encoded_value);
#endif

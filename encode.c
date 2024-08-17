#include "encode.h"


enum project_error encode_data(char* data_arguments) {
    short data_encoded = 0;
    char *number_token;
    char *argument_copy;
    long num_value;
    char* data_short_is_binary;
    argument_copy = my_strdup(data_arguments);
    number_token = strtok(argument_copy, ","); /* Use strtok to split the data_argument by commas */

    while (number_token != NULL) {
        num_value = strtol(number_token, NULL, 10);         /* Convert the number string to a long integer */
        data_encoded = convert_to_15bit_binary(num_value);         /* Use the convert_to_15bit_binary function to encode the number */

        data_short_is_binary = short_to_binary_string(data_encoded);
        append_to_data_image(data_encoded); /*Adds the new short to the data image array*/
        DC++; /*updates the data counter*/
        printf(""CYAN"number %s\ndata encoded: -------%s-------\n" RESET " ",number_token, data_short_is_binary);
        number_token = strtok(NULL, ","); /* Get the next argument */
    }

    free(argument_copy);
    return firstPassError_success;  /* Return success if arguments are found and processed */
}

enum project_error encode_string(char* string) {
    char *string_without_spaces, *string_arguments;
    short encoded_char;
    int i;

    string_without_spaces = str_without_spaces(string);
    string_arguments = substring(string_without_spaces, 1, strlen(string_without_spaces) - 2);


    for (i = 0; i < strlen(string_arguments); i++) {
        encoded_char = (short)string_arguments[i]; /* Convert character to its ASCII value */
        append_to_data_image(encoded_char); /* Add the ASCII value to the data image */
        DC++; /* Update the data counter */
        printf(""CYAN"Character: %c, Encoded ASCII: %s\n" RESET, string_arguments[i], short_to_binary_string(encoded_char));
    }

    /* Add the null terminator '\0' at the end of the string */
    encoded_char = 0;
    append_to_data_image(encoded_char);
    DC++;
    printf(""CYAN"Null terminator added: Encoded ASCII: %s\n" RESET, short_to_binary_string(encoded_char));

    free(string_arguments);
    return firstPassError_success;
}

int append_to_data_image(short encoded_value) {
    if (IC + DC >= MAX_MEMORY_SPACE-100) {
        return -1;
    }
    data_image[DC+1] = encoded_value;
    return 0;
}


int append_to_code_image(short encoded_value) {
    if (IC + DC >= MAX_MEMORY_SPACE-100) {
        return -1;
    }
    data_image[IC+1] = encoded_value;
    return 0;
}


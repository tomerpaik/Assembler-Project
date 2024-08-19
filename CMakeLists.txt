cmake_minimum_required(VERSION 3.28)
project(assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(assembler "SourceFiles/pre_assembler.c"
        Headers/pre_assembler.h
        Headers/linked_list.h
        "SourceFiles/linked_list.c"
        "SourceFiles/hash_table.c"
        Headers/hash_table.h
        "SourceFiles/first_pass.c"
        Headers/first_pass.h
        "SourceFiles/main.c"
        Headers/main.h
        Headers/general_functions.h
        "SourceFiles/general_functions.c"
        "SourceFiles/lexer.c"
        Headers/lexer.h
        Headers/globals.h
        Headers/pre_assembler.h
        Headers/lexer.h
        Headers/linked_list.h
        Headers/main.h
        Headers/hash_table.h
        Headers/globals.h
        Headers/general_functions.h
        Headers/first_pass.h
        "SourceFiles/errors_handle.c"
        "SourceFiles/second_pass.c"
        Headers/second_pass.h
        "SourceFiles/encode.c"
        Headers/encode.h
        "SourceFiles/validation.c"
        Headers/validation.h
        "SourceFiles/finish_encode.c"
        Headers/finish_encode.h
        "SourceFiles/symbol_struct.c"
        Headers/symbol_struct.h
)

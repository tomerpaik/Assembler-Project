cmake_minimum_required(VERSION 3.28)
project(assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(assembler pre_assembler.c
        pre_assembler.h
        linked_list.h
        linked_list.c
        hash_table.c
        hash_table.h
        first_pass.c
        first_pass.h
        main.c
        main.h
        general_functions.h
        general_functions.c
        errors.c
        errors.h
        lexer.c
        lexer.h
        globals.h
        pre_assembler.h
        lexer.h
        linked_list.h
        main.h
        hash_table.h
        globals.h
        general_functions.h
        first_pass.h
        errors.h
        symbole_table.c
        symbole_table.h
)

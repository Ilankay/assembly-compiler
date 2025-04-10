
#ifndef PRE_PROC_H
#define PRE_PROC_H

/**
 * @file pre_proc.h
 * @brief [Add a short description of this header file's purpose]
 * 
 * Detailed description:
 * [Provide detailed explanation of the module, usage, and purpose]
 * 
 * @author
 * @date
 */

#include "../headers/table.h"
#include "../headers/util.h"

#define LINE_SIZE 80
#define MAX_FILENAME 100

#define INSTRUCTION_LIST "mov","cmp","add","sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"
#define INSTRUCTION_AMNT  16

#define DECORATOR_LIST ".data", ".string", ".entry", ".extern"
#define DECORATOR_AMNT 4

#define MACRO_START "mcro"
#define MACRO_END "endmcro"

/**
 * @brief Checks if a given word is a valid macro name.
 * 
 * @param word The word to check.
 * @return int TRUE if valid, FALSE otherwise.
 */
int is_valid_macro(const char* word);

/**
 * @brief Adds a macro definition to the macro table.
 * 
 * @param macro_table The macro table to add to.
 * @param line_list Linked list of macro lines.
 * @param line_count Number of lines in the macro.
 * @param name The name of the macro.
 */
void add_macro(Table macro_table, Node* line_list, int line_count, char* name);

/**
 * @brief Performs preprocessing on an assembly file (.as), expanding macros into a new file (.am).
 * 
 * @param filename The path to the .as file.
 * @return int 0 on success, non-zero on failure.
 */
int pre_proc(const char* filename);

#endif // PRE_PROC_H

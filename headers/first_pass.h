#ifndef FIRST_PASS_H
#define FIRST_PASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "util.h"
#include "pre_proc.h"
#include "ins_parse.h"
/**
 * Struct to hold the results of the first pass over an assembly file.
 */
typedef struct FirstPassPack {
    Table symbol_table;        /** Symbol table of labels and their addresses*/
    Node* data_list;           /** Linked list containing data segment*/
    Node* instruction_list;    /** Linked list containing instruction segment*/
    int ICF;                   /** Instruction Counter Final*/
    int DCF;                   /** Data Counter Final*/
} FirstPassPack;

/**
 * Checks if a given word is a valid symbol (label).
 * A valid symbol ends with ':' and does not match any reserved keyword.
 * 
 * @param word The word to check.
 * @return 1 if valid, 0 otherwise.
 */
int is_valid_symbol(const char* word);

/**
 * Stores a parsed instruction and its arguments into the instruction list.
 * Converts the instruction and its arguments to binary format.
 * 
 * @param instruction_list Pointer to the instruction list.
 * @param IC Current instruction counter.
 * @param inst Instruction mnemonic.
 * @param arg1 First argument.
 * @param arg2 Second argument.
 * @return Updated instruction counter after storing the instruction.
 */
int store_instruction(Node* instruction_list, int IC, char* inst, char* arg1, char* arg2,int line_number);

/**
 * Parses and stores data values from a .data directive line into the data list.
 * 
 * @param data_list Pointer to the data list.
 * @param line Full line of code containing the .data directive.
 * @param DC Current data counter.
 * @return Updated data counter after storing the data.
 */
int store_data(Node* data_list, char* line, int DC);

/**
 * Parses and stores characters from a .string directive line into the data list.
 * 
 * @param data_list Pointer to the data list.
 * @param line Full line of code containing the .string directive.
 * @param DC Current data counter.
 * @return Updated data counter after storing the string.
 */
int store_string(Node* data_list, char* line, int DC);

/**
 * Adds a symbol (label) to the symbol table.
 * 
 * @param t Symbol table to update.
 * @param symbol Symbol name.
 * @param IC Address to associate with the symbol.
 * @param type Section type (e.g., .data, .code, .external).
 */
void store_symbol(Table t, char* symbol, int IC, char* type,int line_num);

/**
 * Performs the first pass over an assembly source file.
 * Builds the symbol table, and separates the data and instruction memory images.
 * 
 * @param filename Name of the preprocessed assembly file.
 * @return Struct containing results of the first pass.
 */
FirstPassPack first_pass(char* filename);

#endif /** FIRST_PASS_H*/

#include "../headers/table.h"
#ifndef INS_PARSE_H
#define INS_PARSE_H

/**
 * @file ins_parse.h
 * @brief this is a module for converting assembly instructions into machine code.
 *
 * Detailed description:
 * I divided the instruction parsing into three main functions:
 * build first word - which builds the first word which definitly exists for every instruction.
 * build arg word first - which builds the words for immmidiate arguments or tells the assembler to save a spot for the second pass.
 * build arg word second - which builds the words for arguments that can only be built in the second pass.
 *
 * @author Ilan Kayesar
 * @date 1.4.25
 */

/** --- Character Identifiers ---*/
#define IMM_ID '#'      /** Immediate addressing*/
#define REL_ID '&'      /** Relative addressing*/
#define REG_ID 'r'      /** Register addressing*/

/** --- Addressing Types ---*/
#define IMM 0           /** Immediate*/
#define DIR 1           /** Direct*/
#define REL 2           /** Relative*/
#define REG 3           /** Register*/

/** --- ASCII Characters ---*/
#define NUM_START '0'
#define NUM_END '9'
#define NUM_7 '7'
#define PLUS '+'
#define MINUS '-'
#define CHAR_ONE '1'
#define CHAR_ZERO '0'

/** --- Utility Constants ---*/
#define ZERO 0
#define ONE 1
#define TWO 2
#define MINUS_ONE -1

#define TRUE 1
#define FALSE 0

/** --- Sizes and Limits ---*/
#define REG_SIZE 2
#define LINESIZE 80
#define INSTRUCTION_SIZE 24
#define OPECODE_SIZE 6
#define FUNCT_SIZE 5
#define FUNCT_INDEX 16
#define REG1_INDEX 6
#define INS_REG_SIZE 5
#define REG_VAL_SIZE 3
#define OPERATION_SIZE 2
#define IMM_SIZE 21

/** --- Instruction Structure ---*/
typedef struct Instruction {
  const char* name;
  int opecode;
  int funct;
  int origin[4];
  int dest[4];
} Instruction;

/** --- Instruction Set (16 Instructions Total) ---*/
#define INSTRUCTION_AMNT 16
#define INSTRUCTIONS \
  {"mov",0,0,{1,1,0,1},{0,1,0,1}}, \
  {"cmp",1,0,{1,1,0,1},{1,1,0,1}}, \
  {"add",2,1,{1,1,0,1},{0,1,0,1}}, \
  {"sub",2,2,{1,1,0,1},{0,1,0,1}}, \
  {"lea",4,0,{0,1,0,1},{0,1,0,1}}, \
  {"clr",5,1,{0,0,0,0},{0,1,0,1}}, \
  {"not",5,2,{0,0,0,0},{0,1,0,1}}, \
  {"inc",5,3,{0,0,0,0},{0,1,0,1}}, \
  {"dec",5,4,{0,0,0,0},{0,1,0,1}}, \
  {"jmp",9,1,{0,0,0,0},{0,1,1,0}}, \
  {"bne",9,2,{0,0,0,0},{0,1,1,0}}, \
  {"jsr",9,3,{0,0,0,0},{0,1,1,0}}, \
  {"red",12,0,{0,0,0,0},{0,1,0,1}}, \
  {"prn",13,0,{0,0,0,0},{1,1,0,1}}, \
  {"rts",14,0,{0,0,0,0},{0,0,0,0}}, \
  {"stop",15,0,{0,0,0,0},{0,0,0,0}}


/** --- Function Declarations --- */

/**
 * @brief Determines the addressing method of a given argument string.
 * @param arg The argument string to analyze.
 * @return One of IMM, DIR, REL, or REG.
 */
int get_operator(char* arg);

/**
 * @brief Converts a value to its binary representation and stores it in a char array.
 * @param array The target array to hold binary digits as characters.
 * @param val The integer value to convert.
 * @param len Number of bits to represent.
 */
void convert_to_bits(char *array, int val, int len);

/**
 * @brief Converts a register character (e.g., 'r3') to binary representation.
 * @param array Target array to store the binary representation.
 * @param reg Register character to convert (expects second character of "rX").
 */
void convert_register(char* array, char reg);

/**
 * @brief Fills an array with -1 values (used to indicate uninitialized bits).
 * @param arr The array to fill.
 * @param len Number of elements to fill.
 */
void fill_minus_one(char* arr, int len);

/**
 * @brief Fills the first 'amnt' characters of an array with ASCII '0'.
 * @param arr The array to fill.
 * @param amnt Number of characters to set to '0'.
 */
void fill_zeros(char* arr, int amnt);

/**
 * @brief Creates the first binary word (instruction word) for a given command and arguments.
 * @param command The instruction name.
 * @param arg1 The first operand.
 * @param arg2 The second operand.
 * @return A newly allocated string representing the instruction word in binary.
 */
char* create_first_word(char* command, char* arg1, char* arg2,int line_number,int* continue_flag);

/**
 * @brief Creates a word for an argument in the first pass(for immediate addressing).
 * @param arg The argument string.
 * @return A binary string or "0" if no word is needed, or "" if unresolved.
 */
char* create_arg_word_first(char* arg);

/**
 * @brief determine whether a word is a valid instruction or not.
 * @param ins the instruction string.
 * @return boolean value of 1 if the word is an instruction and 0 if not
 */
int is_instruction(char* inst);

/**
 * @brief creates the word for an argument in the second pass
 * @param arg the argument string;
 * @param IC the instruction counter
 * @param symbol_table the symbol table 
 * @param line_number the current line number
 * @return A newly allocated string representing the instruction word in binary.
 */
char* create_arg_word_second(char* arg, int IC, Table symbol_table, int line_number,int* continue_flag);

#endif 

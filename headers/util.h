#ifndef UTIL_H
#define UTIL_H
//general constants
#define ZERO 0
#define ONE 1
#define TWO 2

#define TRUE 1
#define FALSE 0

// ASCII Values
#define NUM_START '0'
#define NUM_END '9'
#define NUM_7 '7'
#define PLUS '+'
#define MINUS '-'
#define CHAR_ZERO '0'
#define CHAR_ONE '1'

#define STRING ".string"
#define DATA ".data"
#define CODE ".code"
#define EXTERN ".extern"
#define ENTRY ".entry"

char* get_word(char* inst, int ind);

void convert_to_bits(char *array, int val, int len);
#endif



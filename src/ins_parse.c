#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/ins_parse.h"
#include "../headers/table.h"

int get_operator(char* arg){
  int i;
  char* num_str;
  switch (arg[ZERO]){
    case IMM_ID:
      if(isdigit(arg[ONE]) || arg[ONE]==MINUS || arg[ONE]==PLUS){
        num_str=&arg[TWO];
      }
      else{
        break;
      }

      for (i=ZERO;i<strlen(num_str);i++){
        if(isdigit(num_str[i])==0){
          return DIR; 
        }
      }

      return IMM;
    case REL_ID:
      return REL;
    case REG_ID:
      if (strlen(arg)>TWO){
        return DIR;
      }
      for (i = ONE; i<strlen(arg);i++){
        if(arg[i]>NUM_7 || arg[i]<NUM_START){
          return DIR; 
        }
      }     
      return REG;
    default:
      return DIR;
    
  }
}

void convert_to_bits(char *array, int val, int len){
  int i;
  for (i = len-ONE; i >= ZERO; i--) {
    array[len-ONE-i]=(val & (ONE << i)) ? CHAR_ONE : CHAR_ZERO;
  }
}

void convert_register(char* array, char reg){
  int reg_num;
  int i;
  reg_num = reg-NUM_START;
  printf("%d\n",reg_num);
  for (i = REG_VAL_SIZE-ONE; i >= ZERO; i--) {
    array[REG_VAL_SIZE-ONE-i]=(reg_num & (ONE << i)) ? CHAR_ONE : CHAR_ZERO;
  }
}

void fill_minus_one(char* arr,int len){
  int i;
  for (i=0;i<len;i++){
    arr[i]=MINUS_ONE;
  }
  return;
}

void fill_zeros(char* arr, int amnt){
  int i;
  for(i=0;i<amnt;i++){
    arr[i]=CHAR_ZERO;
  }
  return;
}

char* create_first_word(char* command,char* arg1,char* arg2){
  char* instruction;
  int opecode;
  int i;
  int oparg1;
  int oparg2;
  Instruction ins_list[INSTRUCTION_AMNT] = {INSTRUCTIONS};
  instruction = calloc(INSTRUCTION_SIZE+1,sizeof(char));
  /**
   * generic for all commands
  */
  fill_zeros(instruction,INSTRUCTION_SIZE);
  opecode=-1;
  for(i=0;i<INSTRUCTION_AMNT;i++){
    if(strcmp(ins_list[i].name,command)==0){
      opecode = ins_list[i].opecode;
    }
  }
  if(opecode==-1){
    return instruction;
  }
  convert_to_bits(instruction, opecode,OPECODE_SIZE);

  convert_to_bits(&instruction[FUNCT_INDEX],ins_list[opecode].funct,FUNCT_SIZE);

  instruction[INSTRUCTION_SIZE-ONE]=CHAR_ZERO+ONE;
  instruction[INSTRUCTION_SIZE-ONE-ONE]=CHAR_ZERO;
  instruction[INSTRUCTION_SIZE-ONE-ONE-ONE]=CHAR_ZERO;
  /**
   * handle arguments
  */
  if(strlen(arg1)==0){
    return instruction;
  }
  oparg1 = get_operator(arg1);
  convert_to_bits(&instruction[REG1_INDEX],oparg1,OPERATION_SIZE);
  if(oparg1==3){
    convert_register(&instruction[REG1_INDEX+OPERATION_SIZE], arg1[ONE]);
  }

  if(strlen(arg2)==0){
    return instruction;
  }
  oparg2 = get_operator(arg2);
  convert_to_bits(&instruction[REG1_INDEX+INS_REG_SIZE],oparg2,OPERATION_SIZE);
  if(oparg2==3){
    convert_register(&instruction[REG1_INDEX+INS_REG_SIZE+OPERATION_SIZE], arg2[ONE]);
  }
  return instruction;
}
char* create_arg_word_first(char* arg){
  /**
    * in case not needed return "0"
    * in case needed return either an empty string or the instruction
  */
  char* instruction;
  int oparg1;
  const char* num_string;
  int num;

  if (strlen(arg)==0){
    return "0";
  }
  instruction = calloc(INSTRUCTION_SIZE+1,sizeof(char));
  fill_zeros(instruction,INSTRUCTION_SIZE);
  oparg1 = get_operator(arg);
  switch(oparg1){
    case IMM:
      instruction[INSTRUCTION_SIZE-ONE]=CHAR_ZERO+ONE;
      instruction[INSTRUCTION_SIZE-ONE-ONE]=CHAR_ZERO;
      instruction[INSTRUCTION_SIZE-ONE-ONE-ONE]=CHAR_ZERO;
      num = atoi(&arg[1]);
      convert_to_bits(instruction,num,IMM_SIZE);
      return instruction;
    case REG:
      return "0";
    default:
      return "";
  }


  
  return instruction;
}
int is_instruction(char* inst){
  Instruction ins_list[INSTRUCTION_AMNT] = {INSTRUCTIONS};
  int i;
  for(i=0; i<INSTRUCTION_AMNT; i++){
    if(strcmp(ins_list[i].name,inst)==0){
      return TRUE;
    }
  }
  return FALSE;
}


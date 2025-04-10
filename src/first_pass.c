#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/first_pass.h"
#include "../headers/table.h"
#include "../headers/util.h"
#include "../headers/pre_proc.h"
#include "../headers/ins_parse.h"

int is_valid_symbol(const char* word){
  int i;
  const char* invalid_names[INSTRUCTION_AMNT+DECORATOR_AMNT+2] =  {INSTRUCTION_LIST,DECORATOR_LIST,MACRO_START,MACRO_END};
  
  for(i=0; i<INSTRUCTION_AMNT+DECORATOR_AMNT;i++){
    if(strcmp(word, invalid_names[i])==0){
      return FALSE;
    }
  }
  if(word[strlen(word)-ONE]!=':'){
    return FALSE;
  }
  return TRUE;
}

int store_instruction(Node* instruction_list, int IC, char* inst, char* arg1, char* arg2){
  char* instruction;
  char* argline1;
  char* argline2;
  TableVal tv;

  instruction = create_first_word(inst, arg1, arg2);
  tv.address = IC;
  tv.key = "";
  tv.val = instruction;
  add_node(instruction_list,tv);
  
  IC++;

  argline1 = create_arg_word_first(arg1);
  if(strlen(argline1)==ZERO){
    tv.address = IC;
    tv.key = "";
    tv.val = arg1;
    add_node(instruction_list,tv);
    IC++;
  }
  else if(strlen(argline1)!=ONE){
    tv.address = IC;
    tv.key = "";
    tv.val = argline1;
    IC++;
  }

  argline2 = create_arg_word_first(arg2);
  if(strlen(argline2)==ZERO){
    tv.address = IC;
    tv.key = "";
    tv.val = arg2;
    add_node(instruction_list,tv);
  }
  else if(strlen(argline2)!=ONE){
    tv.address = IC;
    tv.key = "";
    tv.val = argline2;
  }
  free(argline1);
  free(argline2);
  return IC;
}

int store_data(Node* data_list, char* line, int DC){
  char* word;
  int word_count;
  char num_bits[INSTRUCTION_SIZE+1];
  TableVal tv;

  word_count = 0;
  word = get_word(line,word_count);
  if(strcmp(word,DATA)==1){
    word_count++;
  }
  word_count++;

  while(strlen((word=get_word(line, word_count)))!=0){
    convert_to_bits(num_bits,atoi(word),INSTRUCTION_SIZE);
    tv.address = DC;
    tv.key = "",
    tv.val=num_bits;
    add_node(data_list,tv);
    word_count++;
    DC++;
  }
  return DC;
}

int store_string(Node* data_list, char* line, int DC){
  char c;
  int i=0;
  char num_bits[INSTRUCTION_SIZE+1];
  TableVal tv;
  
  while((c=line[i])!='"'){
    i++;
  }
  i++;
  while((c=line[i])!='"'){
    convert_to_bits(num_bits,(int) c,INSTRUCTION_SIZE);
    tv.address = DC;
    tv.key = "",
    tv.val=num_bits;
    add_node(data_list,tv);
    DC++;
  }
  return DC;
}

void store_symbol(Table t, char* symbol, int IC, char* type){
  table_add(t, symbol, type, IC);
}

FirstPassPack first_pass(char* filename){
  Node *instruction_list;
  Node *data_list;
  Table symbol_table;
  FILE *am_file;
  int IC;
  int DC;
  int word_count;
  TableVal tv;
  char line[LINE_SIZE];
  int is_symbol;
  char* word;
  char* symbol = "";
  char* arg1;
  char* arg2;
  FirstPassPack fpp;

  IC = 100;
  DC = 0;
  is_symbol = FALSE;
  am_file = fopen(filename,"r");
  tv.val="";
  tv.key="";
  tv.address=0;
  symbol_table = create_table();

  data_list = create_node(tv);
  instruction_list = create_node(tv);
  
  while (fgets(line, sizeof(line), am_file)) {
    word_count=ZERO;
    word = get_word(line, word_count);
    if(strlen(word)==0){
      continue;
    }
    if(is_valid_symbol(word)){
      strcpy(symbol, word);
      symbol[strlen(symbol)-ONE]='\0';
      word_count++;
      is_symbol = TRUE;
    }
    word = get_word(line, word_count);
    if(strcmp(word,DATA)==0){
      if(is_symbol){
        store_symbol(symbol_table, symbol, DC, DATA);
      }
      DC = store_data(data_list, line,DC);
      word_count = ZERO;
      continue;
    }
    if(strcmp(word,STRING)==0){
      if(is_symbol){
        store_symbol(symbol_table, symbol, DC, DATA);
      }
      DC = store_string(data_list,line,DC);
      word_count = ZERO;
      continue;
    }
    if(strcmp(word,EXTERN)==0){
      word_count++;
      strcpy(symbol,get_word(line, word_count));
      store_symbol(symbol_table, symbol, ZERO, EXTERN);
      word_count = ZERO;
      continue;
    }
    if(is_symbol){
      store_symbol(symbol_table,symbol,IC,CODE); // add error if exists
    }
    if(!is_instruction(word)){
      printf("line %d: not a valid instruction",IC);
      
    }
    word_count++;
    arg1 = get_word(line, word_count);
    word_count++;
    arg2 = get_word(line,word_count);

    IC = store_instruction(instruction_list,IC,word,arg1,arg2);

  }
  fpp.instruction_list=instruction_list;
  fpp.symbol_table=symbol_table;
  fpp.data_list=data_list;
  fpp.ICF=IC;
  fpp.DCF=DC;
  return fpp;
}



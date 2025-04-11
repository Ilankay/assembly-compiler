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

int store_instruction(Node* instruction_list, int IC, char* inst, char* arg1, char* arg2,int line_number,int* continue_flag){
  char* instruction;
  char* argline1;
  char* argline2;
  TableVal tv;

  instruction = create_first_word(inst, arg1, arg2,line_number,continue_flag);
  tv.address = IC;
  tv.key = "";
  tv.val = instruction;
  tv.line_num = line_number;
  add_node(instruction_list,tv);
  
  IC++;

  argline1 = create_arg_word_first(arg1);
  if(strlen(argline1)==ZERO){
    tv.address = IC;
    tv.key = "";
    tv.val = arg1;
    tv.line_num = line_number;
    add_node(instruction_list,tv);
    IC++;
  }
  else if(strlen(argline1)!=ONE){
    tv.address = IC;
    tv.key = "";
    tv.val = argline1;
    tv.line_num = line_number;
    add_node(instruction_list,tv);
    IC++;
  }

  argline2 = create_arg_word_first(arg2);
  if(strlen(argline2)==ZERO){
    tv.address = IC;
    tv.key = "";
    tv.val = arg2;
    tv.line_num = line_number;
    add_node(instruction_list,tv);
    IC++;
  }
  else if(strlen(argline2)!=ONE){
    tv.address = IC;
    tv.key = "";
    tv.val = argline2;
    tv.line_num = line_number;
    add_node(instruction_list,tv);
    IC++;
  }

  return IC;
}

int store_data(Node* data_list, char* line, int DC){
  char* word;
  int word_count;
  char num_bits[INSTRUCTION_SIZE+1];
  TableVal tv;
  
  num_bits[INSTRUCTION_SIZE] = '\0';
  word_count = 0;
  word = get_word(line,word_count);
  if(is_valid_symbol(word)){
    word_count++;
  }
  if(strcmp(word,DATA)==1){
    word_count++;
  }
  word_count= word_count+1;

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
  TableVal tv;
  int i=0;
  char num_bits[INSTRUCTION_SIZE+1];
  int max = LINE_SIZE;
  num_bits[INSTRUCTION_SIZE]='\0'; 
  while((c=line[i])!='"' && i<max){
    i++;
  }
  i++;
  while((c=line[i])!='"' && i<max){
    convert_to_bits(num_bits,(int) c,INSTRUCTION_SIZE);
    tv.address = DC;
    tv.key = "",
    tv.val=num_bits;
    add_node(data_list,tv);
    DC++;
    i++;
  }
  convert_to_bits(num_bits,ZERO,INSTRUCTION_SIZE);
  tv.address = DC;
  tv.key = "",
  tv.val=num_bits;
  add_node(data_list,tv);
  DC++;
  i++;
  return DC;
}

void store_symbol(Table t, char* symbol, int IC, char* type,int line_num, int* continue_flag){
  if(table_add_line_number(t, symbol, type, IC,line_num)==0){
    printf("Line %d, Error: symbol already defined\n",line_num);
    *continue_flag = FALSE;
  }
}

FirstPassPack first_pass(char* filename, int* continue_flag){
  Node *instruction_list;
  Node *data_list;
  Table symbol_table;
  char am_filename[MAX_FILENAME];
  FILE *am_file;
  int IC;
  int DC;
  int word_count;
  TableVal tv;
  char line[LINE_SIZE];
  int is_symbol;
  char* word;
  char symbol[LINE_SIZE];
  char* arg1;
  char* arg2;
  FirstPassPack fpp;
  int line_number = 0;
  Node* curr;
  int i;
  
  IC = 100;
  DC = 0;
  is_symbol = FALSE;
  strcpy(am_filename,filename);
  strcat(am_filename,".am");
  am_file = fopen(am_filename,"r");
  tv.val="";
  tv.key="";
  tv.address=0;
  symbol_table = create_table();
  data_list = create_node(tv);
  instruction_list = create_node(tv);
  
  while (fgets(line, sizeof(line), am_file)) {
    line_number++;
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
        store_symbol(symbol_table, symbol, DC, DATA,line_number, continue_flag);
        is_symbol=FALSE;
      }
      DC = store_data(data_list, line,DC);
      word_count = ZERO;
      continue;
    }
    if(strcmp(word,ENTRY)==0){
      continue;
    }
    if(strcmp(word,STRING)==0){
      if(is_symbol){
        store_symbol(symbol_table, symbol, DC, DATA,line_number, continue_flag);
        is_symbol=FALSE;
      }
      DC = store_string(data_list,line,DC);
      word_count = ZERO;
      continue;
    }
    if(strcmp(word,EXTERN)==0){
      word_count++;
      strcpy(symbol,get_word(line, word_count));
      store_symbol(symbol_table, symbol, ZERO, EXTERN,line_number, continue_flag);
      is_symbol=FALSE;
      word_count = ZERO;
      continue;
    }
    if(is_symbol){
      store_symbol(symbol_table,symbol,IC,CODE,line_number, continue_flag); 
      is_symbol=FALSE;
    }
    if(!is_instruction(word)){
      printf("Line %d, Error: not a valid instruction\n",line_number);
      *continue_flag=FALSE;
    }
    word_count++;
    arg1 = get_word(line, word_count);
    word_count++;
    arg2 = get_word(line,word_count);

    IC = store_instruction(instruction_list,IC,word,arg1,arg2,line_number,continue_flag);

  }
  fpp.instruction_list=instruction_list;
  fpp.symbol_table=symbol_table;
  /*
    * adding FIC to all the data
  */
  for(i=0;i<DEFAULT_TABLE_SIZE;i++){
    curr = symbol_table[i];
    while (curr != NULL){
      if(strcmp(curr->val.val,DATA)==0){
        curr->val.address = curr->val.address+IC;
      }
      curr = curr->next;
    }
  } 
  ll_add_address(data_list,IC);
  fpp.data_list=data_list;
  fpp.ICF=IC;
  fpp.DCF=DC;
  return fpp;
}



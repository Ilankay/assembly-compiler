#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/first_pass.h"
#include "../headers/table.h"
#include "../headers/util.h"
#include "../headers/pre_proc.h"
#include "../headers/ins_parse.h"
#include "../headers/first_pass.h"

typedef struct SecondPassPack{
  Node* instruction_list;
  Node* external_list;
  Node* data_list;
  Node* entry_list;
  int ICF;
  int DCF;
} SecondPassPack;

SecondPassPack second_pass(FirstPassPack fpp,char* filename){
  char* instruction;
  char am_filename[MAX_FILENAME];
  FILE *am_file;
  char* word;
  int address;
  char line[LINE_SIZE];
  TableVal tv;
  Node* entry_list;
  Node* external_list;
  Node* curr;
  SecondPassPack spp;
  int i;
  tv.val="";
  tv.key="";
  tv.address=0;

  entry_list = create_node(tv);
  external_list = create_node(tv);
  i = 0;
  strcpy(am_filename,filename);
  strcat(am_filename,".am");
  am_file = fopen(am_filename,"r");
  while (fgets(line, sizeof(line), am_file)) {
    word = get_word(line, ZERO);
    if (strcmp(word,ENTRY)==0){
      address = table_get_address(fpp.symbol_table, get_word(line, ONE));
      if (address<0){
        printf("Line: %d, Error: not a valid symbol\n",i);
      }
      else{
        tv.val = get_word(line,ONE);
        tv.key = "";
        tv.address = address;
        add_node(entry_list,tv);
      }
    }
  }
  free(word);
  curr = fpp.instruction_list;
  while(curr->next != NULL){
    if(strlen(curr->val.val) != INSTRUCTION_SIZE){
      instruction = create_arg_word_second(curr->val.val,curr->val.address,fpp.symbol_table,curr->val.line_num);
      if(instruction[INSTRUCTION_SIZE-1]=='1'){
        tv.val = (curr->val.val);
        tv.address = curr->val.address;
        add_node(external_list,tv);
      }
      curr->val.val = instruction;

    }
    curr = curr->next;
  }
  spp.external_list = external_list;
  spp.entry_list = entry_list;
  spp.instruction_list = fpp.instruction_list;
  spp.data_list = fpp.data_list;
  spp.DCF = fpp.DCF;
  spp.ICF = fpp.ICF;
  return spp;
}


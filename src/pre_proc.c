#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/util.h"
#include "../headers/table.h"
#include "../headers/pre_proc.h"

int is_valid_macro(const char* word){
  int i;
  const char* invalid_names[INSTRUCTION_AMNT+DECORATOR_AMNT+2] =  {INSTRUCTION_LIST,DECORATOR_LIST,MACRO_START,MACRO_END};
  
  for(i=0; i<INSTRUCTION_AMNT+DECORATOR_AMNT;i++){
    if(strcmp(word, invalid_names[i])==0){
      return FALSE;
    }
  }
  return TRUE;
}

void add_macro(Table macro_table, Node* line_list,int line_count, char* name){
  char* full_string;
  Node* curr;
  full_string = calloc(line_count,LINE_SIZE);
  curr = line_list;
  while(curr->next != NULL){
    strcat(full_string,curr->val.val);
    curr = curr->next;
  }
  strcat(full_string,curr->val.val);

  table_add(macro_table,name,full_string,0);
}

int pre_proc(const char* filename){
  FILE *as_file;
  FILE *am_file;
  char line[LINE_SIZE];
  char am_filename[MAX_FILENAME];
  char* word0;
  char* macro_name;
  char* word2;
  int macro_flag;
  int len;

  int line_count;
  Node* line_list;
  TableVal line_val; 

  Table macro_table;
  //alter the name of the file
  strncpy(am_filename, filename, sizeof(am_filename)-1);
  am_filename[sizeof(am_filename)-1] = '\0';

  len = strlen(am_filename);
  if (len >= 3 && strcmp(am_filename + len - 3, ".as") == 0) {
    am_filename[len-1] = 'm';
  } else {
    if (len + 3 < sizeof(am_filename))
      strcat(am_filename, ".am");
  }
  // open files
  as_file = fopen(filename,"r");
  if (as_file == NULL){
    printf("failiure");//add error handling
  }
  am_file = fopen(am_filename,"w");
  if (am_file == NULL){
    printf("failiure");//add error handling
  }
  //start loop
  macro_flag = FALSE;
  macro_table = create_table();
  line_count=0;
  while (fgets(line, sizeof(line), as_file)) {
    word0 = get_word(line,0);
    if(strlen(table_get(macro_table,word0))!=0){
      fputs(table_get(macro_table,word0),am_file);
      continue;
    }
    if(strcmp(word0,"")==0){
      continue;
    }
    else if(strcmp(word0,MACRO_START)==0 && strcmp(macro_name=get_word(line,1),"")!=0 && strcmp(word2=get_word(line,2),"")==0){
      line_count=1;
      macro_flag=TRUE;
      line_val.val = "";
      line_val.key = NULL;
      line_list = create_node(line_val);
    }

    else if(strcmp(word0,MACRO_END)==0 && macro_flag){
      macro_flag=FALSE;
      add_macro(macro_table,line_list,line_count,macro_name);
      ll_free(line_list);
    }
    else if(macro_flag){
      line_count++;
      line_val.val = malloc(strlen(line) + 1); 

      strcpy(line_val.val,line);

      line_val.key = NULL;
      add_node(line_list,line_val);
    }
    else{
      fputs(line,am_file);
    }



  }
  free(word0);
  free(macro_name);
  free(word2);
  fclose(am_file);
  fclose(as_file); 
  return 0;
}



#include "../headers/first_pass.h"
#include "../headers/pre_proc.h"
#include "../headers/second_pass.h"
#include <string.h>

#define HEX_SIZE 24

char *binary_to_hex(const char *binary) {
  int i;
  int j;
  char *hex = (char *)malloc(HEX_SIZE+ONE);     
  
  for (i = 0; i < 6; i++) {
    int value = 0;
    for (j = 0; j < 4; j++) {
      value = value * 2 + (binary[i * 4 + j] - '0');
    }
    hex[i] = (value < 10) ? ('0' + value) : ('A' + (value - 10));
  }
  hex[HEX_SIZE] = '\0'; 
  return hex;
}
void create_ob_file(char* filename, Node* instruction_list, Node* data_list, int ICF, int DCF){
  char ob_filename[MAX_FILENAME];
  FILE* ob_file;
  Node* curr;

  strcpy(ob_filename,filename);
  strcat(ob_filename,".ob");
  ob_file = fopen(ob_filename,"w");
  fprintf(ob_file,"%d       %d\n",ICF-100,DCF);
  curr = instruction_list->next;
  if (curr != NULL){
    while(curr != NULL){
      fprintf(ob_file,"%d    %s\n",curr->val.address,binary_to_hex(curr->val.val));
      curr= curr->next;
    }
  }
  curr = data_list->next;
  if(curr != NULL){
    while(curr != NULL){
      fprintf(ob_file,"%d    %s\n",curr->val.address,binary_to_hex(curr->val.val));
      curr= curr->next;
    }
  }
}
void create_ext_file(char* filename, Node* external_list){
  char ext_filename[MAX_FILENAME];
  FILE* ext_file;
  Node* curr;

  curr =external_list->next;
  if (curr != NULL){
    strcpy(ext_filename,filename);
    strcat(ext_filename,".ext");
    ext_file = fopen(ext_filename,"w");
    while(curr != NULL){
      fprintf(ext_file,"%s    %d\n",curr->val.val,curr->val.address);
      curr= curr->next;
    }
  }
}

void create_entry_file(char* filename, Node* entry_list){
  char ent_filename[MAX_FILENAME];
  FILE* ent_file;
  Node* curr;


  curr = entry_list->next;
  if (curr != NULL){
    strcpy(ent_filename,filename);
    strcat(ent_filename,".ent");
    ent_file = fopen(ent_filename,"w");
    while(curr != NULL){
      fprintf(ent_file,"%s    %d\n",curr->val.val,curr->val.address);
      curr= curr->next;
    }
  }
}

void assemble(char* filename){
  FirstPassPack fpp;
  SecondPassPack spp;
  int preproc_flag;
  preproc_flag=pre_proc(filename);
  if(!preproc_flag){
    return;
  }
  fpp = first_pass(filename);
  spp = second_pass(fpp, filename); 
  create_ob_file(filename,spp.instruction_list,spp.data_list,spp.ICF,spp.DCF);
  create_ext_file(filename, spp.external_list);
  create_entry_file(filename,spp.entry_list);
}

int main(int argc, char *argv[]) {
  int i;
  for (i = 1; i < argc; i++) {
    assemble(argv[i]);
  }
  return 0;
}


#include "../headers/util.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_seperator(char c){

  if(isspace(c) || c == ','){
    return TRUE;
  }
  return FALSE;
}
void convert_to_bits(char *array, int val, int len){
  int i;
  for (i = len-ONE; i >= ZERO; i--) {
    array[len-ONE-i]=(val & (ONE << i)) ? CHAR_ONE : CHAR_ZERO;
  }
}


char* get_word(char* inst,int ind){
  int curr = ZERO;
  int i = ZERO;
  int flag = FALSE;
  char* word;
  int start_ind;
  int end_ind;
  int len;

  while(i<strlen(inst)){
    if(!is_seperator(inst[i])){
      break;
    }
    i++;
  }
  
  while (curr<ind && i<strlen(inst)){
    if (is_seperator(inst[i])) {
        flag = TRUE;
    } else if (flag) {
        curr++;
        flag = FALSE;
        if(curr>=ind){
        i--;
      }
    }
    i++;
  }
  start_ind = i;
  while (i<strlen(inst)&&!(is_seperator(inst[i]))){
    i++;
  }
  end_ind = i;
  len = end_ind-start_ind;
  word = (char*)calloc(len+1,sizeof(char)); 
  for(i=start_ind;i<end_ind;i++){
    word[i-start_ind] = inst[i];
  }
  return word;
}


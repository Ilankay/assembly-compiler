#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/table.h"

Node* create_node(TableVal val){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val.address = val.address;
    strcpy(new_node->val.val,val.val);
    strcpy(new_node->val.key,val.key);
    new_node->next = NULL;
    return new_node;
}
void add_node(Node* head,TableVal val){
  
    Node* n = create_node(val);  
    Node* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = n;  

}

const char* ll_get(Node* head, const char* key){

  Node* curr = head;

  while (curr != NULL) {
    if (strcmp(key, curr->val.key) == 0) {
      return curr->val.val;
    }
    curr = curr->next;
  }

  return "";

}

void ll_free(Node* head){
  Node* curr = head;
  Node* nextnode=NULL;
   while(curr->next != NULL){
    nextnode = curr->next;
    free(curr);
    curr = nextnode;
  } 
}

// table code
unsigned long djb2_hash(const char *str) {
  unsigned long hash = DEFAULT_SEED;
  int c;

  while ((c = *str++))
    hash = ((hash << DEFAULT_MULTIPLIER) + hash) + c;

  return hash;
}

Table create_table(){
  Node **t;
  t = (Node**)calloc(DEFAULT_TABLE_SIZE,sizeof(Node*));
  int i;
  for(i=0;i<DEFAULT_TABLE_SIZE;i++){
    t[i]=NULL;
  }
  return t;
}

void table_add(Table t, char* key, char* val, int address){
  TableVal table_val;
  unsigned long hash;
  int index;
  table_val.key = key;
  table_val.val = val;
  table_val.address = address;
  hash = djb2_hash(table_val.key);
  index = (int) (hash%DEFAULT_TABLE_SIZE);
  if (t[index] == NULL){
    Node* n = create_node(table_val);
    t[index] = n;
  }
  else{
    add_node(t[index], table_val);
  }
}

const char* table_get(Table t, const char* key){
  unsigned long hash = djb2_hash(key);
  int index = (int) (hash%DEFAULT_TABLE_SIZE);
  return ll_get(t[index],key);
}

// int main(){
//   Table t = create_table();
//   table_add(t,"hello","world");
//   table_add(t,"hey","ilan");
//   printf("the result is: %s\n",table_get(t,"arge"));
// }


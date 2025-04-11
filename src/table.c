#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/table.h"
#include "../headers/util.h"

Node* create_node(TableVal val){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val.line_num=val.line_num;
    new_node->val.address = val.address;
    new_node->val.val = (char*)malloc(strlen(val.val) + 1);
    strcpy(new_node->val.val,val.val);
    new_node->val.key = (char*)malloc(strlen(val.key) + 1);
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
int ll_get_address(Node* head, const char* key){

  Node* curr = head;

  while (curr != NULL) {
    if (strcmp(key, curr->val.key) == 0) {
      return curr->val.address;
    }
    curr = curr->next;
  }

  return -1;

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

void ll_add_address(Node* head, int n){
  Node* curr = head;

  while (curr != NULL) {
    curr->val.address= curr->val.address+n;
    curr = curr->next;
  }
}
/**
* table code
*/
unsigned long djb2_hash(const char *str) {
  unsigned long hash = DEFAULT_SEED;
  int c;

  while ((c = *str++))
    hash = ((hash << DEFAULT_MULTIPLIER) + hash) + c;

  return hash;
}

Table create_table(void){
  Node **t;
  int i;
  t = (Node**)calloc(DEFAULT_TABLE_SIZE,sizeof(Node*));
  for(i=0;i<DEFAULT_TABLE_SIZE;i++){
    t[i]=NULL;
  }
  return t;
}

int table_add(Table t, char* key, char* val, int address){
  TableVal table_val;
  unsigned long hash;
  int index;
  if(strlen(table_get(t,key))!=0){
    return 0;
  }
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
  return ONE;
}
int table_add_line_number(Table t, char* key, char* val, int address, int line_num){
  TableVal table_val;
  unsigned long hash;
  int index;
  if(strlen(table_get(t,key))!=0){
    return 0;
  }
  table_val.key = key;
  table_val.val = val;
  table_val.address = address;
  table_val.line_num = line_num;
  hash = djb2_hash(table_val.key);
  index = (int) (hash%DEFAULT_TABLE_SIZE);
  if (t[index] == NULL){
    Node* n = create_node(table_val);
    t[index] = n;
  }
  else{
    add_node(t[index], table_val);
  }
  return ONE;
}

const char* table_get(Table t, const char* key){
  unsigned long hash = djb2_hash(key);
  int index = (int) (hash%DEFAULT_TABLE_SIZE);
  return ll_get(t[index],key);
}

int table_get_address(Table t, const char* key){
  unsigned long hash = djb2_hash(key);
  int index = (int) (hash%DEFAULT_TABLE_SIZE);
  return ll_get_address(t[index],key);
}


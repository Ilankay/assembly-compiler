#include "../headers/first_pass.h"
#include "../headers/pre_proc.h"

void assemble(char* filename){
  pre_proc(filename);
}

int main(int argc, char *argv[]) {
  int i;
  for (i = 1; i < argc; i++) {
    assemble(argv[i]);
  }
  return 0;
}


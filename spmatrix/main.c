#include <stdio.h>
#include "spmatrix.h"


int main(int argv, char**argc) {
  for(int i=0; i<argv; i++) {
    printf("%s ", argc[i]);
  }
  printf("\n");
  return 0;
}

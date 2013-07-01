#include <stdio.h>
#include "spmatrix.h"


int main(int argv, char**argc) {
  for(int i=0; i<argv; i++) {
    printf("%s ", argc[i]);
  }
  printf("\n");
  a_test_function(20);
  return 0;
}

#include <stdint.h>
#include <stdio.h>
#include "spmatrix.h"


int main(void){
  MatrixRef M = matrix_init(1000,1000);
  matrix_free(&M);
  return 0;
}

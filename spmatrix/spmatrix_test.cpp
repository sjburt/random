#include <iostream>
extern "C" {
#include "spmatrix.h"
}

int main(){
  std::cout << "hi" << std::endl;
  a_test_function(77);
  return 0;
}

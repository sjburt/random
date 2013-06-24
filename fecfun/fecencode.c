
#include <stdint.h>
#include <string.h>
#include "fecencode.h"



typedef struct {
  uint32_t blocks_generated;
  uint8_t * data;
  uint8_t blocksize;

} fecencoder;


#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "fecencode.h"

#define Q (3)
#define eps (.02)

typedef struct fecencoder {
  uint32_t blocks_generated;
  uint8_t * data;
  uint16_t blocksize;
  uint32_t length;
} fecencoder;

fecRef_t fenc_create(uint8_t* data, uint32_t len, uint16_t block_size){
  fecRef_t newFec;
  newFec = malloc(sizeof(fecencoder));

  newFec->data = data;
  newFec->length = len;
  newFec->blocksize=block_size;
  return newFec;
}



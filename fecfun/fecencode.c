#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "fecencode.h"

typedef struct fecencoder {
  uint32_t blocks_generated;
  uint8_t * data;
  uint16_t blocksize;
  uint32_t length;
} fecencoder;

static void
gen_block_list(const int seqnum, uint8_t* count, uint16_t blocklist[]);



fecRef_t fenc_create(uint8_t* data, uint32_t len, uint16_t block_size){
  fecRef_t newFec = NULL;
  newFec = (fecRef_t)malloc(sizeof(fecencoder));

  newFec->data = data;
  newFec->length = len;
  newFec->blocksize=block_size;
  return newFec;
}



/* fecencode.h 
 * just a test file to play around with some fec ideas
 *
 *
 * data structure:
 *
 */


typedef struct fecencoder* fecRef_t;

typedef struct {
  uint8_t * data;
  uint32_t seqnum;
} fecBlock_t;

fecRef_t fenc_create(uint8_t* data, uint32_t len, uint16_t block_size);
int fenc_init(fecRef_t fec);
int fenc_genBlock(fecRef_t fec, fecBlock_t * fecBlock);



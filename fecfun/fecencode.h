/* fecencode.h 
 * just a test file to play around with some fec ideas
 *
 *
 * data structure:
 *
 */

typedef fecencoder* fecRef_t;

typedef struct {
  uint8_t * data;
  uint32_t seqnum;
} fecBlock_t;

fecRef_t fenc_create(const char* data, int len, int block_size);
int fenc_init(fecRef fec);
int fenc_genBlock(fecRef fec, fecBlock_t * fecBlock);



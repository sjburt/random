/* Sparse matrix lib
 *
 * For 2x2 matrices; indexed both by row and column
 */

typedef struct Matrix* MatrixRef;

MatrixRef matrix_init(int16_t rows, int16_t columns);
void matrix_free(MatrixRef* M);

int matrix_add(MatrixRef M, int16_t row, int16_t column);
int matrix_rem(MatrixRef M, int16_t row, int16_t column);

int matrix_get(MatrixRef M, int16_t row, int16_t column);

void matrix_xor(MatrixRef M, int16_t row, int16_t column, int val);

MatrixRef matrix_transpose(MatrixRef M);
void matrix_print(FILE* out, MatrixRef M);


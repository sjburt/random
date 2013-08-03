#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "set.h"
#include "spmatrix.h"

typedef struct Matrix {
  int16_t rows;
  int16_t columns;
  SetRef* rdata;
  SetRef* cdata;
} Matrix;


MatrixRef matrix_init(int16_t rows, int16_t columns) {

  MatrixRef M = malloc(sizeof(Matrix));

  M->rdata = calloc(sizeof(SetRef*),rows);
  M->cdata = calloc(sizeof(SetRef*),columns);

  for(int r = 0; r < rows; r++) {
    M->rdata[r] = newSet();
  }
  for(int c = 0; c < rows; c++) {
    M->cdata[c] = newSet();
  }
  M->rows = rows;
  M->columns = columns;

  return M;
}

void matrix_free(MatrixRef* M) {
  for (int i = 0; i < (*M)->rows; i++) {
    freeSet(&(*M)->rdata[i]);
  }

  for (int i = 0; i < (*M)->columns; i++) {
    freeSet(&(*M)->cdata[i]);
  }
  free(*M);
  M=NULL;
}

int matrix_get(MatrixRef M, int16_t r, int16_t c) {
  return hasMember(M->rdata[r],c);
}

void matrix_print(FILE* out, MatrixRef M) {
  fprintf(out, "%i rows, %i columns\n", M->rows, M->columns);
  for (int ri = 0; ri < M->rows; ri++) {
    for (int ci = 0; ci < M->columns; ci++) {
      fprintf(out, "%01i ", hasMember(M->rdata[ri], ci));
    }
    fprintf(out, "\n");
  }


}

void matrix_add(MatrixRef M, int16_t row, int16_t column) {
  Insert(M->rdata[row], column);
  Insert(M->cdata[column], row);
}

void matrix_rem(MatrixRef M, int16_t row, int16_t column) {
  Remove(M->rdata[row], column);
  Remove(M->cdata[column], row);
}

MatrixRef matrix_transpose(MatrixRef M) {
  MatrixRef N = matrix_init(M->columns, M->rows);

  return N;

}

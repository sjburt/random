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

typedef struct Set Row;


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
  
  free((*M)->rdata);
  free((*M)->cdata);


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

int matrix_add(MatrixRef M, int16_t row, int16_t column) {
  if (row >= M->rows) return -1;
  if (column >= M->columns) return -1;

  Insert(M->rdata[row], column);
  Insert(M->cdata[column], row);

  return 0;
}

int matrix_rem(MatrixRef M, int16_t row, int16_t column) {
  if (row >= M->rows) return -1;
  if (column >= M->columns) return -1;

  Remove(M->rdata[row], column);
  Remove(M->cdata[column], row);

  return 0;
}

MatrixRef matrix_transpose(MatrixRef M) {
  MatrixRef N = matrix_init(M->columns, M->rows);

  for (int ri = 0; ri < N->rows; ri++) {
    freeSet(&N->rdata[ri]);
    N->rdata[ri] = copySet(M->cdata[ri]);
  }
  for (int ci = 0; ci < N->columns; ci++) {
    freeSet(&N->cdata[ci]);
    N->cdata[ci] = copySet(M->rdata[ci]);
  }
  return N;
}

RowRef copy_row(MatrixRef M, uint16_t row) {
  if (row >= M->rows) return NULL;

  RowRef R = (RowRef)copySet(M->rdata[row]);

  return R;
}

SetRef row_xor(const SetRef A, const SetRef B) {
  SetRef R = newSet();


  return R;
}

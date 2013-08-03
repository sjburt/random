#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "set.h"

#define DEFAULT_SET_SIZE 10

typedef struct Set {
  int count;
  int16_t *data;
  int size_of_array; // use to determine when we
                     // need to adjust size
} Set;
static int16_t findEl(SetRef S, int16_t E);

SetRef
newSet() {
  SetRef S = malloc(sizeof(Set));
  if (S==NULL){
    fprintf(stderr,"malloc failed");
    exit(1);
  }
  S->count = 0;
  S->size_of_array = DEFAULT_SET_SIZE;
  S->data = malloc(sizeof(*S->data) * S->size_of_array);
  return S;
}

void freeSet(SetRef* pS) {
  free((*pS)->data);
  free(*pS);
  *pS = NULL;
  pS = NULL;
}

int isEmpty(SetRef S) {
  if (NULL == S) {
    fprintf(stderr, "Error, NULL pointer passed to isEmpty");
    return -1;
  }
  return 1;
}

int hasMember(SetRef S, int16_t E) {
  if (S==NULL) return -1;
  return (findEl(S,E)==-1) ? 0 : 1;
}

int getCount(SetRef S) {
  if (S==NULL) return -1;
  return S->count;
}


static void resize(SetRef S) {
  if (S==NULL) return;
  if (S->count == S->size_of_array) {
    S->size_of_array *=2;
    S->data = realloc(S->data, sizeof(*S->data) * S->size_of_array);
    printf("embiggened to %i\n", S->size_of_array);
  } else if ((S->count < S->size_of_array / 4) && S->size_of_array > DEFAULT_SET_SIZE) {
  // shrink array back down
    S->size_of_array = S->size_of_array / 2;
    S->data = realloc(S->data, sizeof(*S->data) * S->size_of_array);
    printf("ensmallered to %i\n", S->size_of_array);
  }
}

static int cmp_int(const void* a, const void* b){
  const int16_t * A = a;
  const int16_t * B = b;

  if (*A < *B) return -1;
  if (*A == *B) return 0;
  return 1;
}

static int16_t findEl(SetRef S, int16_t E) {
  int16_t * Eref;
  Eref = bsearch(&E, S->data, S->count, sizeof(*S->data), cmp_int);
  if (NULL!=Eref) {
    return (Eref - S->data);
  }
  return -1;
}

void Insert(SetRef S, int16_t E) {
  if (S == NULL) S = newSet();
  if (findEl(S,E) != -1) return;
  S->count++;

  resize(S);
  S->data[S->count-1] = E;
  // todo: actually insert instead of this junk!
  qsort(S->data, S->count, sizeof(*S->data), &cmp_int);
}

void Remove(SetRef S, int16_t E) {
  int16_t addr;
  if ((addr = findEl(S,E)) == -1 ) return;
  memmove(&S->data[addr],&S->data[addr+1], (S->count - addr)*sizeof(*S->data));
  S->count--;
  resize(S);
}

int Equals(SetRef A, SetRef B) {
  for (int i = 0; i < A->count; i++) {
    if (!hasMember(B,A->data[i])) {
      return 0;
    }
  }
  for (int i = 0; i < B->count; i++) {
    if (!hasMember(A,B->data[i])) {
      return 0;
    }
  }
  return 1;
}

SetRef Intersection(SetRef A, SetRef B) {
  SetRef C = newSet();
  for (int i = 0; i < A->count; i++) {
    if (hasMember(B,A->data[i])) {
      Insert(C, A->data[i]);
    } else {
    }
  }
  return C;
}

SetRef Union(SetRef A, SetRef B) {
  SetRef C = newSet();
  for (int i = 0; i < A->count; i++) {
    Insert(C, A->data[i]);
  }
  for (int i = 0; i < B->count; i++) {
    Insert(C, B->data[i]);
  }
  return C;
}

SetRef copySet(SetRef S) {
  SetRef R = newSet();

  for (int i = 0; i < S->count; i++) {
    Insert(R, S->data[i]);
  }
  return R;
}


void printMembers(FILE* out, SetRef S) {
  fprintf(out, "(");
  for(int i = 0; i < S->count; ++i){
    fprintf(out, "%i, ", S->data[i]);
  }
  fprintf(out, "\b\b)\n");
}


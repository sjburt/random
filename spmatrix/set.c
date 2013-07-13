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
}

int isEmpty(SetRef S) {
  if (NULL == S) {
    fprintf(stderr, "Error, NULL pointer passed to isEmpty");
    return -1;
  }
  printf("%d ",S->count);
  return 1;
}

static void resize(SetRef S) {
  if (S->count == S->size_of_array) {
    S->size_of_array *=2;
    S->data = realloc(S->data, sizeof(*S->data) * S->size_of_array);
    printf("embiggened to %i", S->size_of_array);
  } else if ((S->count < S->size_of_array / 4) && S->size_of_array > DEFAULT_SET_SIZE) {
  // shrink array back down
    S->size_of_array = S->size_of_array / 2;
    S->data = realloc(S->data, sizeof(*S->data) * S->size_of_array);
    printf("ensmallered to %i", S->size_of_array);
  }
}

int cmp_int(const void* a, const void* b){
  const int16_t * A = a;
  const int16_t * B = b;

  if (*A < *B) return -1;
  if (*A == *B) return 0;
  return 1;
}

void Insert(SetRef S, int16_t E) {
  S->count++;
  resize(S);
  S->data[S->count-1] = E;
  qsort(S->data, S->count, sizeof(*S->data), &cmp_int);
}

void printMembers(FILE* out, SetRef S) {
  fprintf(out, "(");
  for(int i = 0; i < S->count; ++i){
    fprintf(out, "%i, ", S->data[i]);
  }
  fprintf(out, "\b\b)\n");
}

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "set.h"

#define DEFAULT_SET_SIZE 50

typedef struct Set {
  int count;
  uint16_t *data;
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
  int cs = S->size_of_array;
  int c = S->count;
  printf("%i\n",sizeof(*S->data));
  if (c == cs) {
    S->data = realloc(S->data, sizeof(*S->data) * c * 2);
  } else if (c < cs / 4 && cs > 200) {
  // shrink array back down
    S->data = realloc(S->data, sizeof(*S->data) * c / 2);
  }
}

void Insert(SetRef S, int E) {
  S->count++;
  resize(S);
  S->data[S->count-1] = E;
}

void printMembers(FILE* out, SetRef S) {
  fprintf(out, "(");
  for(int i = 0; i < S->count; ++i){
    fprintf(out, "%i, ", S->data[i]);
  }
  fprintf(out, ")\n");
}

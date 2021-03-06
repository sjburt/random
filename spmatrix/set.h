/* set.h
 *
 * implements a set
 *
 */

#ifndef SET_H
#define SET_H

typedef struct Set* SetRef;

SetRef newSet(void);
void freeSet(SetRef* pS);

int isEmpty(SetRef S);
int hasMember(SetRef S, int16_t E);
int getCount(SetRef S);
int Equals(SetRef A, SetRef B);

void makeEmpty(SetRef S);
void Insert(SetRef S, int16_t E);
void Remove(SetRef S, int16_t E);

SetRef Intersection(SetRef A, SetRef B);
SetRef Union(SetRef A, SetRef B);

void printMembers(FILE* out, SetRef S);
SetRef copySet(SetRef S);

#endif // SET_H

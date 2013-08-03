#include <iostream>
#include <stdio.h>
#include <stdint.h>
extern "C" {
#include "set.h"
}
#define BOOST_TEST_DYN_LINK 1
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE( my_test) {
  SetRef S = newSet();
  printf(" %p\n", S);
  freeSet(&S);
  printf(" %p\n", S);
}

BOOST_AUTO_TEST_CASE(isitempty) {
  SetRef S = newSet();
  BOOST_REQUIRE_EQUAL(1,isEmpty(S));
  freeSet(&S);
  BOOST_REQUIRE_EQUAL(-1,isEmpty(S));
}

BOOST_AUTO_TEST_CASE(insert) {
  SetRef S = newSet();
  BOOST_REQUIRE_EQUAL(1,isEmpty(S));
  Insert(S,  20);
  Insert(S,  12);
  Insert(S,  1);
  Insert(S,  3);
  printMembers(stdout,S);
  Insert(S,  3);
  printMembers(stdout,S);
  freeSet(&S);
}

BOOST_AUTO_TEST_CASE(insertandresize) {
  SetRef S = newSet();
  for (int i=0; i<300; ++i) {
    Insert(S,i);
  }
  
  for (int i=10; i<300; ++i) {
    Remove(S,i);
  }
  
  //  printMembers(stdout,S);
  freeSet(&S);
}

BOOST_AUTO_TEST_CASE(remove_test) {
  SetRef S = newSet();
  BOOST_REQUIRE_EQUAL(1,isEmpty(S));
  Insert(S,  20);
  Insert(S,  12);
  Insert(S,  1);
  Insert(S,  3);
  printMembers(stdout,S);
  Remove(S,  3);
  Remove(S,  3);
  Remove(S,  20);
  printMembers(stdout,S);

  freeSet(&S);
}

BOOST_AUTO_TEST_CASE(test_equals) {

  SetRef S = newSet();
  SetRef R = newSet();

  BOOST_REQUIRE_EQUAL(1,Equals(S,R));

  Insert(S, 20);


  BOOST_REQUIRE_EQUAL(1,Equals(S,S));
  BOOST_REQUIRE_EQUAL(0,Equals(S,R));
  Insert(R, 20);
  BOOST_REQUIRE_EQUAL(1,Equals(S,R));

  freeSet(&R);
  for(int i =0; i<50; i++) {
    Insert(S, rand()%50);
  }
  R = copySet(S);

  BOOST_REQUIRE_EQUAL(1,Equals(S,R));

}

BOOST_AUTO_TEST_CASE(union_of_two_sets) {
  SetRef S = newSet();
  SetRef R = newSet();

  Insert(S,  20);
  Insert(S,  22);
  Insert(S,  13);
  Insert(S,  3);
  
  Insert(R,  20);
  Insert(R,  12);
  Insert(R,  1);
  Insert(R,  3);

  SetRef Q = Union(S,R);

  printMembers(stdout,S);
  printMembers(stdout,R);
  printMembers(stdout,Q);

  freeSet(&Q);
  Q = Intersection(S,R);

  printMembers(stdout,Q);
  freeSet(&S);
  freeSet(&R);
  freeSet(&Q);

}

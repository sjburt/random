#include <iostream>
#include <stdio.h>
#include <stdint.h>
extern "C" {
#include "set.h"
}
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


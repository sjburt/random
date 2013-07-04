#include <iostream>
#include <stdio.h>
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

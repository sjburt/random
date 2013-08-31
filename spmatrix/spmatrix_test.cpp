#include <iostream>
extern "C" {
#include "spmatrix.h"
}
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE( my_test) {
  MatrixRef M = matrix_init(10,10);
  matrix_free(&M);
}

BOOST_AUTO_TEST_CASE(add_stuff) {

  MatrixRef M = matrix_init(2,2);
  matrix_print(stdout, M);
  matrix_add(M,0,0);
  matrix_print(stdout, M);
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,0,0));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,1,0));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,0,1));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,1,1));
// try adding to another place
  matrix_add(M,1,0);
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,0,0));
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,1,0));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,0,1));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,1,1));
// try adding to same place
  matrix_add(M,0,0);
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,0,0));
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,1,0));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,0,1));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,1,1));
// try adding to another column.
  matrix_add(M,0,1);
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,0,0));
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,1,0));
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,0,1));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,1,1));
// adding outside of range should fail gracefully;
  BOOST_REQUIRE_EQUAL(-1,matrix_add(M,2,1));

  matrix_free(&M);
}

BOOST_AUTO_TEST_CASE(add_n_remove) {
  MatrixRef M = matrix_init(3,3);

  BOOST_REQUIRE_EQUAL(0, matrix_add(M,1,1));

  BOOST_REQUIRE_EQUAL(-1, matrix_rem(M,4,1));
  BOOST_REQUIRE_EQUAL(-1, matrix_rem(M,1,4));
  BOOST_REQUIRE(matrix_get(M,1,1));

  BOOST_REQUIRE_EQUAL(0, matrix_rem(M,1,1));
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,1,1));
  matrix_free(&M);
}
BOOST_AUTO_TEST_CASE(transpose) {
  MatrixRef M = matrix_init(3,3);

  BOOST_REQUIRE_EQUAL(0, matrix_add(M,2,1));
  BOOST_REQUIRE_EQUAL(1, matrix_get(M,2,1));

  MatrixRef N = matrix_transpose(M);
  matrix_print(stdout, M);
  matrix_print(stdout, N);

  matrix_free(&M);

  BOOST_REQUIRE_EQUAL(1, matrix_get(N,1,2));
  BOOST_REQUIRE_EQUAL(0, matrix_get(N,2,1));
  matrix_free(&N);
}

BOOST_AUTO_TEST_CASE(big_matrix){
  MatrixRef M = matrix_init(10000,10000);
  BOOST_REQUIRE_EQUAL(0, matrix_get(M,4555,4333));
  matrix_free(&M);

}

#include <iostream>
extern "C" {
#include "spmatrix.h"
}
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE( my_test) {

  BOOST_CHECK_EQUAL(0, a_test_function(10));

}

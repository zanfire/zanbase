#include "zStringTest.h"


zStringTest::zStringTest(void) {

}


zStringTest::~zStringTest(void) {

}


bool zStringTest::execute(int index) {
  bool ret = false;
  if (index == 0) ret = test_all_ctor();
  return ret;
}


int zStringTest::get_number_of_tests(void) {
  return 1;
}


char const* zStringTest::get_name(void) {
  return "zString tests";
}


char const* zStringTest::get_description(void) {
  return "Tests for zString class";
}


char const* zStringTest::get_test_name(int index) {
  if (index == 0) return "Constructors test";
  return "??";
}


char const* zStringTest::get_test_description(int index) {
  if (index == 0) return "Test all ctor of zString classes.";
  return "??";
}


bool zStringTest::test_all_ctor(void) {
  return true;
}


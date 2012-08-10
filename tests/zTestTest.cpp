#include "zTestTest.h"

#include "zLogger.h"

zTestTest::zTestTest(void) {
  //logger_ = zLogger::get_logger("test");
}


zTestTest::~zTestTest(void) {
}


bool zTestTest::execute(int index) {
  switch(index) {
    case 0: return test_one();
    default: return false;
  }
  return false;
}


int zTestTest::get_num_tests(void) {
  return 1;
}


char const* zTestTest::get_name(void) {
  return "zTest reference";
}


char const* zTestTest::get_description(void) {
  return "Test example";
}


char const* zTestTest::get_test_name(int index) {
  switch(index) {
    case 0: return "test one";
    default: return "??";
  }
  return "??";

}


char const* zTestTest::get_test_description(int index) {
  return "??";
}


bool zTestTest::test_one(void) {
  // Test impl.
  // return false; test failed.
  return true;
}


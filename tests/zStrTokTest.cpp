#include "zStrTokTest.h"

#include "zStringTokenizer.h"
#include "zLogger.h"

zStrTokTest::zStrTokTest(void) {
  logger_ = zLogger::get_logger("test");
}


zStrTokTest::~zStrTokTest(void) {

}


bool zStrTokTest::execute(int index) {
  switch(index) {
    case 0: return test_simple_case();
    default: return false;
  }
  return false;
}


int zStrTokTest::get_num_tests(void) {
  return 1;
}


char const* zStrTokTest::get_name(void) {
  return "zStringTokenizer tests";
}


char const* zStrTokTest::get_description(void) {
  return "Test example";
}


char const* zStrTokTest::get_test_name(int index) {
  switch(index) {
    case 0: return "simple case";
    default: return "??";
  }
  return "??";

}


char const* zStrTokTest::get_test_description(int index) {
  return "??";
}


bool zStrTokTest::test_simple_case(void) {
  
  zStringTokenizer token("1 2", " ", false);

  int count = 0;
  while(token.has_more_tokens()) {
    token.next();
    count++;
  }
  if (count != 2) return false;

  return true;
}


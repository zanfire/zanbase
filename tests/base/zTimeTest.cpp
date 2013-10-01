#include "zTimeTest.h"

#include "zLogger.h"
#include "zTime.h"
#include "zThread.h"

#include <memory.h>

zTimeTest::zTimeTest(void) {
}


zTimeTest::~zTimeTest(void) {
}


bool zTimeTest::execute(int index) {
  switch(index) {
    case 0: return test_one();
    default: return false;
  }
  return false;
}


int zTimeTest::get_num_tests(void) {
  return 1;
}


char const* zTimeTest::get_name(void) {
  return "zTime tests";
}


char const* zTimeTest::get_description(void) {
  return "zTime test set.";
}


char const* zTimeTest::get_test_name(int index) {
  switch(index) {
    case 0: return "1 secs";
    default: return "??";
  }
  return "??";

}


char const* zTimeTest::get_test_description(int index) {
  return "??";
}


bool zTimeTest::test_one(void) {
  uint64_t t1 = zTime::current_millis();
  zThread::sleep(1000);
  uint64_t t2 = zTime::current_millis();
  
  int s = 1000 - abs((t2 - t1));
  return (s < 3); // In this test is expected an high accuracy.
}

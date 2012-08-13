#include "zArrayTest.h"

#include "zLogger.h"
#include "zArray.h"

zArrayTest::zArrayTest(void) {
}


zArrayTest::~zArrayTest(void) {
}


bool zArrayTest::execute(int index) {
  switch(index) {
    case 0: return test_ctor();
    case 1: return test_resize();
    case 2: return test_memory();
    default: return false;
  }
  return false;
}


int zArrayTest::get_num_tests(void) {
  return 3;
}


char const* zArrayTest::get_name(void) {
  return "zArray tests";
}


char const* zArrayTest::get_description(void) {
  return "zArray test set.";
}


char const* zArrayTest::get_test_name(int index) {
  switch(index) {
    case 0: return "ctor";
    case 1: return "resize";
    case 2: return "memory";
    default: return "??";
  }
  return "??";

}


char const* zArrayTest::get_test_description(int index) {
  return "??";
}


bool zArrayTest::test_ctor(void) {

  {
    zArray<int>* array = new zArray<int>(NO, 1024, -1);
    array->append(0);
    if (array->get_count() != 1) return false;
    delete array;
  }
  {
    zArray<int>* array = new zArray<int>(YES, 0, -1);
    array->append(0);
    if (array->get_count() != 1) return false;
    delete array;
  }
  return true;
}


bool zArrayTest::test_resize(void) {
  zArray<int> arr(YES, 5, -1);
  int size = 10000 * 1024;
  for (int i = 0; i < size; i++) {
    arr.append(i);
  }
  for(int i = 0; i < size; i++) {
    int tmp = -2;
    arr.remove(0, &tmp);
    // Is expected the same order.
    if (tmp != i) return false;
  }

  return true;
}


bool zArrayTest::test_memory(void) {

  
  return false;
}


#include "zTester.h"

#include "zArray.h"


zTester::zTester(void) {
  _tests_unprocessed = new zArray(YES, sizeof(void*), 32);
  _tests_processed = new zArray(YES, sizeof(void*), 32);
}


zTester::~zTester(void) {
  delete _tests_unprocessed;
  delete _tests_processed;
}

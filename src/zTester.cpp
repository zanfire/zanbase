#include "zTester.h"

#include "zVector.h"


zTester::zTester(void) {
  _testSetUnprocessed = new zVector(true, 32);
  _testSetProcessed = new zVector(true, 32);
}


zTester::~zTester(void) {
  delete _testSetUnprocessed;
  delete _testSetProcessed;
}

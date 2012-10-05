#include "zGetOptTest.h"

#include "zLogger.h"

zGetOptTest::zGetOptTest(void) {
}


zGetOptTest::~zGetOptTest(void) {
}


bool zGetOptTest::execute(int index) {
  switch(index) {
    case 0: return test_base();
    default: return false;
  }
  return false;
}


int zGetOptTest::get_num_tests(void) {
  return 1;
}


char const* zGetOptTest::get_name(void) {
  return "zTest reference";
}


char const* zGetOptTest::get_description(void) {
  return "Test example";
}


char const* zGetOptTest::get_test_name(int index) {
  switch(index) {
    case 0: return "test one";
    default: return "??";
  }
  return "??";

}


char const* zGetOptTest::get_test_description(int index) {
  return "??";
}


bool zGetOptTest::test_base(void) {
  // Test impl.
  
  /*

  zGetOpt opt(argv, argc);
  opt.addMandatoryFlag("v", "verbose");
  opt.addMandatoryParamater("v", "verbose", String|Numeric);

  opt.isValid() // Check if mandatory paramaters are available.

  while(opt.hasMoreArgs()) {
    opt.getArg
    has.getParam
    shortArg opt.next();
    get
  }
  */


  return true;
}


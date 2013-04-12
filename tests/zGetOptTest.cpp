#include "zGetOptTest.h"

#include "zLogger.h"
#include "zGetOpt.h"

zGetOptTest::zGetOptTest(void) {
}


zGetOptTest::~zGetOptTest(void) {
}


bool zGetOptTest::execute(int index) {
  switch(index) {
    case 0: return test_param();
    case 1: return test_arguments();
    case 2: return test_unknown_args();
    case 3: return test_missing_param();
    case 4: return test_help_message();
    default: return false;
  }
  return false;
}


int zGetOptTest::get_num_tests(void) {
  return 5;
}


char const* zGetOptTest::get_name(void) {
  return "zGetOptTest test suite";
}


char const* zGetOptTest::get_description(void) {
  return "A set of test for the zGetOpt class.";
}


char const* zGetOptTest::get_test_name(int index) {
  switch(index) {
    case 0: return "param";
    case 1: return "arguments";
    case 2: return "unknown_args";
    case 3: return "missing_mandatory";
    case 4: return "missing_param";
    case 5: return "help_message";
    default: return "??";
  }
  return "??";

}


char const* zGetOptTest::get_test_description(int index) {
  return "??";
}


bool zGetOptTest::test_param(void) {
  char const* argv[] = { "c:\\path\\executable.exe", "--file", "C:\\out.txt"};
  int argc = 3;
  
  zGetOpt opt(argc, argv);
  opt.add_arg('v', "verbose", false, "Enable verbose logging");
  opt.add_arg('h', "help", false, "Show help");
  opt.add_arg('f', "file", true, "Input file");
  zGetOpt::Argument const* arg = NULL;
  while ((arg = opt.next()) != NULL) {
    if (!arg->arg != 'f')
    if (!arg->param.equals("C:\\out.txt")) {
      return false;
    }
  }

  return true;
}
 

bool zGetOptTest::test_arguments(void) {
  return false;
}


bool zGetOptTest::test_unknown_args(void) {
  char const* argv[] = { "c:\\path\\executable.exe", "--file", "C:\\out.txt"};
  int argc = 3;
  
  zGetOpt opt(argc, argv);
  opt.add_arg('v', "verbose", false, "Enable verbose logging");
  opt.add_arg('h', "help", false, "Show help");
  //zGetOpt::Argument const* arg = NULL;
  if (opt.next() != NULL) {
    return false;
  }
  if (opt.get_error() != zGetOpt::ERR_UNKNOWN_ARG) {
    return false;
  }

  return true;
}


bool zGetOptTest::test_missing_param(void) {
  return false;
}


#include <stdio.h>

bool zGetOptTest::test_help_message(void) {
  zGetOpt opt(0, NULL);

  opt.add_arg('h', "help", false, "Show help message.");
  opt.add_arg('v', "version", false, "Show the version.");
  opt.add_arg('f', "file", false, "Specify the input file.", "file");
  
  if (opt.get_help_message().is_empty()) return false;
  return true;
}

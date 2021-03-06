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
    case 5: return test_usage_message();
    default: return false;
  }
  return false;
}


int zGetOptTest::get_num_tests(void) {
  return 6;
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
    case 3: return "missing_param";
    case 4: return "help_message";
    case 5: return "test_usage_message";
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
    if (arg->arg != 'f')
    if (!arg->param.equals("C:\\out.txt")) {
      return false;
    }
  }
  // Check no error.
  if (opt.get_error() != zGetOpt::ERR_NO_ERROR) return false;

  return true;
}
 

bool zGetOptTest::test_arguments(void) {
  char const* argv[] = { "c:\\path\\executable.exe", "-hv", "-f"};
  int argc = 3;
  
  zGetOpt opt(argc, argv);
  opt.add_arg('v', "verbose", false, "Enable verbose logging");
  opt.add_arg('h', "help", false, "Show help");
  opt.add_arg('f', "file", false, "Input file");
  zGetOpt::Argument const* arg = NULL;
  bool have_v = false;
  bool have_h = false;
  bool have_f = false;
  while ((arg = opt.next()) != NULL) {
    if (arg->arg == 'v') {
      have_v = true;
    }
    else if (arg->arg == 'h') {
      have_h = true;
    }
    else if (arg->arg == 'f') {
      have_f = true;
    }
  }
  // Check no error.
  if (opt.get_error() != zGetOpt::ERR_NO_ERROR) return false;
  // DEtect if one arg is missing.
  if (!have_v || !have_h || !have_f) return false;

  return true;
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

#include <stdio.h>

bool zGetOptTest::test_missing_param(void) {
  char const* argv[] = { "c:\\path\\executable.exe", "-f"};
  int argc = 2;
  
  zGetOpt opt(argc, argv);
  opt.add_arg('f', "file", true, "Input file", "input.txt");
  zGetOpt::Argument const* arg = NULL;
  if (opt.next() != NULL) return false;
  // Check no error.
  if (opt.get_error() != zGetOpt::ERR_MISSING_PARAM) return false;

  zString msg = opt.get_error_message();

  return true;
}


bool zGetOptTest::test_help_message(void) {
  char const* argv[] = { "c:\\path\\executable.exe", "--file", "C:\\out.txt"};
  int argc = 3;
  
  zGetOpt opt(argc, argv);
  opt.add_arg('h', "help", false, "Show help message.");
  opt.add_arg('v', "version", false, "Show the version.");
  opt.add_arg('f', "file", false, "Specify the input file.", "file");
  
  if (opt.get_help_message().is_empty()) return false;
  return true;
}


bool zGetOptTest::test_usage_message(void) {
  char const* argv[] = { "c:/path/executable.exe", "--file", "C:\\out.txt"};
  int argc = 3;
  
  zGetOpt opt(argc, argv);
  opt.add_arg('h', "help", false, "Show help message.");
  opt.add_arg('v', "version", false, "Show the version.");
  opt.add_arg('f', "file", false, "Specify the input file.", "file");
  
  if (opt.get_usage_message().is_empty()) return false;
  return true;
}

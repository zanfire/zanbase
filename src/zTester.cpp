#include "zTester.h"

#include "zStringBuilder.h"
#include "zTest.h"
#include "zConsole.h"

#include <stdio.h>

zTester::zTester(void) : _tests(YES, 32) {
  // 
}


zTester::~zTester(void) {
  // TODO: Handle clear.
}


void zTester::add(zTest* test) {
  _tests.append(test);
}


zTest* zTester::remove(int index) {
  zTest* t = NULL;
  if (_tests.remove(index, &t)) {
    return t;
  }
  else {
    return NULL;
  }
}


bool zTester::process(void) {
  bool ret = true;
  for (int i = 0; i < _tests.get_count(); i++) {
    zTest* test = NULL;
    _tests.get(i, &test);
    if (test != NULL) {
      printf("%d )  %s\n", (i + 1), test->get_name());
      for (int x = 0; x < test->get_num_tests(); x++) {
        bool result = execute(test, x);
        ret = (ret && result);
      }
    }
  }
  return ret;
}


bool zTester::process_interactive(void) {

  bool res = true;
  // Main loop
  while (true) {
    for (int i = 0; i < _tests.get_count(); i++) {
      zStringBuilder strb;
      strb.append("  ");
      strb.append(i);
      strb.append(" - ");

      zTest* test = NULL;
      _tests.get(i, &test);
      if (test != NULL) {
        strb.append(test->get_name());
      }
      else {
        strb.append(" test invalid.");
      }
      printf("%s\n", strb.to_string().get_buffer());
    }

    printf("Insert a test number or quit: ");

    zStringBuilder commandBuf;
    char c = 0;
    while ((c = (char)getchar()) != '\n') {
      commandBuf.append(c);
    }
    zString command = commandBuf.to_string().to_lowercase();

    if (command.equals("quit")) {
      break;
    }
    if (command.is_num()) {
      int index = command.to_int();

      zTest* test = NULL;
      _tests.get(index, &test);
      if (test != NULL) {

        printf("Executing test: %s\n", test->get_name());

        for (int i = 0; i < test->get_num_tests(); i++) {
          bool result = execute(test, i);
          res = (res && result);
        }
      }
    }
  }
  return res;
}


bool zTester::execute(zTest* test, int index) {
  // Build nice string.
  zStringBuilder strb;
  strb.appendf("\t- %s, result: ", test->get_test_name(index));
  while (strb.get_length() <= 64) {
    strb.append('.');
  }

  printf("%s", strb.to_string().get_buffer());
  bool result = test->execute(index);

  if (result) {
    zConsole::setColor(zConsole::FG_COLOR_GREEN);
  } 
  else {
     zConsole::setColor(zConsole::FG_COLOR_RED);
  }
  printf("%s", (result) ? "passed" : "failed");
  
  zConsole::clearColor();


  printf("\n");
  return result;
}

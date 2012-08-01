#include "zTester.h"

#include "zStringBuilder.h"
#include "zTest.h"

#include <stdio.h>

zTester::zTester(void) : _tests_unprocessed(YES, 32), _tests_processed(YES, 32) {
  // 
}


zTester::~zTester(void) {
  // TODO: Handle clear.
}


void zTester::add(zTest* test) {
  _tests_unprocessed.append(test);
}


bool zTester::process(void) {
  return true;
}


bool zTester::process_interactive(void) {
  printf("Tester is running in the interactive mode.\n");

  // Main loop
  while (true) {
    // List unporcessed test.
    for (int i = 0; i < _tests_unprocessed.get_count(); i++) {
      zStringBuilder strb;
      strb.append(i);
      strb.append(") ");

      zTest* test = NULL;
      _tests_unprocessed.get(i, &test);
      if (test != NULL) {
        strb.append(test->get_name());
      }
      else {
        strb.append(" test invalid.");
      }

      printf("%s\n", strb.to_string().get_buffer());
    }

    break;
  }

  printf("Tester terminated.\n");
  return true;
}


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
  bool ret = true;
  for (int i = 0; i < _tests_unprocessed.get_count(); i++) {
    zTest* test = NULL;
    _tests_unprocessed.get(i, &test);
    if (test != NULL) {
      printf("%d )  %s\n", (i + 1), test->get_name());
      for (int x = 0; x < test->get_num_tests(); x++) {
        // Build nice string.
        zStringBuilder strb;
        strb.appendf("\t- %s, result: ", test->get_test_name(x));
        while (strb.get_length() <= 64) {
          strb.append('.');
        }

        bool result = test->execute(x);
        printf("%s", strb.to_string().get_buffer());

        #define BRIGHT 1
        #define RED 31
        #define GREEN 32
        #define BG_BLACK 4

        if (result) {
          printf("%c[%d;%d;%dmpassed", 0x1B, BRIGHT, GREEN, BG_BLACK);
        } 
        else {
           printf("%c[%d;%d;%dmfailed", 0x1B, BRIGHT, RED, BG_BLACK);
        }

        // Reset color and next line
        printf("\n%c[%dm", 0x1B, 0);
        ret = (ret && result);
      }
    }
  }
  return ret;
}


bool zTester::process_interactive(void) {

  printf("Select a test:\n");
  bool res = true;
  // Main loop
  while (true) {
    // List unporcessed test.
    for (int i = 0; i < _tests_unprocessed.get_count(); i++) {
      zStringBuilder strb;
      strb.append("\t");
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
      printf("%s\n> ", strb.to_string().get_buffer());
    }

    zStringBuilder commandBuf;
    char c = 0;
    while ((c = getchar()) != '\n') {
      commandBuf.append(c);
    }
    zString command = commandBuf.to_string().to_lowercase();

    if (command.equals("quit")) {
      break;
    }
    if (command.is_num()) {
      int index = command.to_int();

      zTest* test = NULL;
      _tests_unprocessed.get(index, &test);
      if (test != NULL) {
        
        printf("Running test %s\n", test->get_name());

        for (int i = 0; i < test->get_num_tests(); i++) {
          printf(" - %s, result: ", test->get_test_name(i));
          bool result = test->execute(i);
          printf("%s\n", result ? "passed" : "failed");
          res = (res && result);
        }
      }
    }
  }
  return res;
}


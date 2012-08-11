/******************************************************************************
 * Copyright 2009-2011 Matteo Valdina
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include "zLogger.h"

#include "zTester.h"
#include "zStringTest.h"
#include "zTestTest.h"
#include "zStrTokTest.h"

#if defined(ENABLED_DMALLOC)
#  include <dmalloc.h>
#endif

zLogger* g_logger = NULL;

void showCopyright(char* programName);
void showHelp(char* programName);
void handleInvalidArg(char* programName, char invalidArg);

int main(int argc, char** argv) {

  g_logger = zLogger::get_logger("zanbase_test_runner");
  
  int opt = 0;
  bool interactive = false;

  while ((opt = getopt(argc, argv, "hvi")) != -1) {
    switch (opt) {
    case 'h':
      showHelp(argv[0]);
      exit(EXIT_SUCCESS);
      break;
    case 'v':
      showCopyright(argv[0]);
      exit(EXIT_SUCCESS);
      break;
    case 'i':
      interactive = true;
      break;
    default:
      handleInvalidArg(argv[0], opt);
      exit(EXIT_FAILURE);
    }
  }

  showCopyright(argv[0]);

  // Initialize tests.
  zTester* tester = new zTester();
  tester->add(new zTestTest());
  tester->add(new zStrTokTest());
  tester->add(new zStringTest());

  // Execute tests.
  bool result = false;
  if (interactive) {
    result = tester->process_interactive();
  }
  else {
    result = tester->process();
  }

  // Cleanup.
  while (tester->get_count() > 0) {
    zTest* test = tester->remove(0);
    if (test != NULL) delete test;
  }
  delete tester;

  g_logger->shutdown();
  g_logger->release_reference();

  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}


void showCopyright(char* programName) {
  printf("%s version %s\n", programName, PACKAGE_VERSION);
  printf("Copyright 2009-2012 Matteo Valdina (bugs: %s)\n", PACKAGE_BUGREPORT);
  printf("\n");
}


void handleInvalidArg(char* programName, char invalidArg) {
  printf("Try '%s -h' for more information.\n", programName);
}


void showHelp(char* programName) {
  printf("Usage: %s [OPTION]...\n", programName);
  printf("This program executes a set of tests for the zanbase library.\n");
  printf("  -v          show version information and exit\n");
  printf("  -i          interactive mode\n");
  printf("\n");
  printf("Report %s bugs to %s.\n", programName, PACKAGE_BUGREPORT);
}


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
#include "zFile.h"
#include "zStringBuilder.h"

#include "zTester.h"
#include "zStringTest.h"
#include "zTestTest.h"
#include "zArrayTest.h"
#include "zStrTokTest.h"
#include "zThreadTest.h"
#include "zFileTest.h"

#if defined(ENABLED_DMALLOC)
#  include <dmalloc.h>
#endif

zLogger* g_logger = NULL;

void showCopyright(char* programName);
void showHelp(char* programName);
void handleInvalidArg(char* programName, char invalidArg);

void  dmalloc_track_function(const char *file, const unsigned int line, 
                            const int func_id,
                            const DMALLOC_SIZE byte_size,
                            const DMALLOC_SIZE alignment,
                            const DMALLOC_PNT old_addr,
                            const DMALLOC_PNT new_addr) {
  if (byte_size == 0) {
    // For some reason deletes are invoked with byte_size == 0.
    //printf("op %d file %s line %u size = 0\n", func_id, file, line);
  }
}
                                         


int main(int argc, char** argv) {

  
  int opt = 0;
  bool interactive = false;
  bool use_dmalloc = false;

  while ((opt = getopt(argc, argv, "hvid")) != -1) {
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
    case 'd':
      use_dmalloc = true;
      break;
    default:
      handleInvalidArg(argv[0], opt);
      exit(EXIT_FAILURE);
    }
  }

  showCopyright(argv[0]);

#if defined(DMALLOC)
   if (use_dmalloc) {
     // Configure dmalloc to the high logging level and to log in the current directory.
     // log file: $PWD/dmalloc.log
     zStringBuilder debugstr;
     debugstr.append("debug=0x4f4ed03,log=");
     zString dir = zFile::get_current_directory();
     debugstr.append(dir);
     debugstr.append("/dmalloc.log");
     dmalloc_debug_setup(debugstr.to_string().get_buffer());

     printf("dmalloc library configured with \"%s\".\n\n", debugstr.to_string().get_buffer());

     dmalloc_track(&dmalloc_track_function);
   }
#endif

  g_logger = zLogger::get_logger("zanbase_test_runner");

  // Initialize tests.
  zTester* tester = new zTester();
  tester->add(new zTestTest());
  tester->add(new zStrTokTest());
  tester->add(new zStringTest());
  tester->add(new zArrayTest());
  tester->add(new zThreadTest());
  tester->add(new zFileTest());

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
  printf("  -v          show version information and exit.\n");
  printf("  -i          interactive mode.\n");
#if defined(DMALLOC)
  printf("  -d          debug memory with dmalloc.\n");
#endif
  printf("\n");
  printf("Report %s bugs to %s.\n", programName, PACKAGE_BUGREPORT);
}


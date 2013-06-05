/******************************************************************************
 * Copyright 2009-2013 Matteo Valdina
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

#include "zCommon.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>


#include "zRect.h"

#if HAVE_UNISTD_H
# include <unistd.h>
#endif

#include "zGetOpt.h"
#include "zLogger.h"
#include "zFile.h"
#include "zStringBuilder.h"

#include "zTester.h"
#include "base/zStringTest.h"
#include "base/zTestTest.h"
#include "base/zArrayTest.h"
#include "base/zStrTokTest.h"
#include "base/zThreadTest.h"
#include "base/zFileTest.h"
#include "base/zBufferTest.h"
#include "base/zGetOptTest.h"

#if defined(ENABLED_DMALLOC)
#  include <dmalloc.h>
#endif

#if defined(WIN32) && defined(DEBUG)
# define _CRTDBG_MAP_ALLOC
# include <stdlib.h>
# include <crtdbg.h>
#endif


zLogger* g_logger = NULL;

void showCopyright(char const* programName);
void showHelp(char const* programName, zGetOpt* getopt);

#if defined(DMALLOC)
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
#endif                                    


int main(int argc, char const** argv) {

  zGetOpt* getopt = new zGetOpt(argc, argv);
  getopt->add_arg('h', "help", false, "Show this message.");
  getopt->add_arg('v', "version", false, "Show version information and exit..");
  getopt->add_arg('i', "interactive", false, "Enable the interactive mode.");
#if defined(DMALLOC)
  getopt->add_arg('d', "debugmem", false, "Debug memory (with dmalloc).");
#endif
  
  
  zGetOpt::Argument const* arg = NULL;
  bool interactive = false;
  bool use_dmalloc = false;

  while ((arg = getopt->next()) != NULL) {
    switch (arg->arg) {
    case 'h':
      showHelp(argv[0], getopt);
      exit(EXIT_SUCCESS);
      break;
    case 'v':
      showCopyright(getopt->get_program_name().get_buffer());
      exit(EXIT_SUCCESS);
      break;
    case 'i':
      interactive = true;
      break;
    case 'd':
      use_dmalloc = true;
      break;
    }
  }
  showCopyright(getopt->get_program_name().get_buffer());

  if (getopt->get_error() != zGetOpt::ERR_NO_ERROR) {
    printf("%s\n", getopt->get_error_message().get_buffer());
    printf("Try '%s -h' for more information.\n", getopt->get_program_name().get_buffer());
    exit(EXIT_FAILURE);
  }

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
  tester->add(new zThreadTest());
  tester->add(new zArrayTest());
  tester->add(new zFileTest());
  tester->add(new zBufferTest());
  tester->add(new zGetOptTest());

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
  delete getopt;

#if defined(_CRTDBG_MAP_ALLOC)
  if (_CrtDumpMemoryLeaks()) {
    DebugBreak();
  }
#endif

  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}


void showCopyright(char const* programName) {
  bool debug = false;
#if defined(DEBUG)
  debug = true;
#endif
  printf("%s version %s %s\n", programName, PACKAGE_VERSION, (debug ? "Debug" : "Release"));
  printf("Copyright 2009-2012 Matteo Valdina (bugs: %s)\n", /*PACKAGE_BUGREPORT*/ "tmp@nodomain.XXX");
  printf("\n");
}


void showHelp(char const* programName, zGetOpt* opt) {
  //printf("Usage: %s [OPTION]...\n", programName);
  printf("%s\n", opt->get_usage_message().get_buffer());
  printf("This program executes a set of tests for the zanbase library.\n");
  printf("%s\n", opt->get_help_message().get_buffer());
  printf("Report %s bugs to %s.\n", programName, /*PACKAGE_BUGREPORT*/ "tmp@nodomain.XXX");
}


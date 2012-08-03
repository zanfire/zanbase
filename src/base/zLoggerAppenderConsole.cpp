#include "zLoggerAppenderConsole.h"

#include <stdio.h>


zLoggerAppenderConsole::zLoggerAppenderConsole() : zLoggerAppender() {
}


zLoggerAppenderConsole::~zLoggerAppenderConsole() {
}


void zLoggerAppenderConsole::line(char const* line) {
  printf("%s\n", line);
}


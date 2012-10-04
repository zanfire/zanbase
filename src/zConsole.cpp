#include "zConsole.h"

// TODO: todo...
#define BRIGHT 1

zConsole::zConsole(void) {}


zConsole::~zConsole(void) {}


void zConsole::setColor(FgColor fg, BgColor bg) {
#if defined(WIN32)
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
#else
  printf("%c[%d;%d;%dm", 0x1B, BRIGHT, (int)fg, (int)bg);
#endif
}


void zConsole::clearColor(void) {
#if defined(WIN32)
#else
  printf("%c[%dm", 0x1B, 0);
#endif
}
  
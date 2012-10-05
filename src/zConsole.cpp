#include "zConsole.h"

// TODO: todo...
#define BRIGHT 1

zConsole::zConsole(void) {}


zConsole::~zConsole(void) {}


void zConsole::setColor(FgColor fg) {
#if defined(WIN32)
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(fg) | FOREGROUND_INTENSITY);
#else
  printf("%c[%d;%d;%dm", 0x1B, BRIGHT, (int)fg, 4);
#endif
}


void zConsole::clearColor(void) {
#if defined(WIN32)
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
#else
  printf("%c[%dm", 0x1B, 0);
#endif
}
  
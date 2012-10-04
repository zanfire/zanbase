#include "zStringBuilder.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>


zStringBuilder::zStringBuilder(void) :  _strings(YES, 32, NULL) {
}


zStringBuilder::~zStringBuilder(void) {
  while(_strings.get_count() > 0) {
    zString* tmp = NULL;
    if (_strings.remove(0, &tmp)) {
      if (tmp != NULL) delete tmp;
      tmp = NULL;
    }
  }
}


int zStringBuilder::get_length(void) const {
  int l = 0;
  for (int i = 0; i < _strings.get_count(); i++) {
    zString* tmp;
    _strings.get(i, &tmp);
    l += tmp->get_length();
  }
  return l;
}


void zStringBuilder::append(zString const& str) {
  append(str.get_buffer(), str.get_length());
}


void zStringBuilder::append(char const* str) {
  append(str, strlen(str));
}


void zStringBuilder::append(char const* str, int len) {
  zString* zstr = new zString(str, len); 
  _strings.append(zstr); 
}


void zStringBuilder::append(char c) {
  append(&c, 1);
}

void zStringBuilder::appendf(char const* format, ...) {
  // TODO: This is a bug. Limiting the format!!!!
  char line[1024 * 4];
  line[0] = '\n';

  va_list args;
  va_start(args, format);
  vsnprintf_s(line, sizeof(line), format, args);
  va_end(args);

  append(line);
}


void zStringBuilder::append(int value) {
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%d", value);
  append(buffer);
}


void zStringBuilder::append(unsigned int value) {
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%u", value);
  append(buffer);
}


zString zStringBuilder::to_string() const {
  return zString(this);
}


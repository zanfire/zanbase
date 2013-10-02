#include "zTime.h"


zTime::zTime(void) {
}


zTime::~zTime(void) {
}


uint64_t zTime::current_millis(void) {
  return current_nanos() / 10e9;
}


uint64_t zTime::current_micros(void) {
  return current_nanos() / 10e6;
}
  

uint64_t zTime::current_nanos(void) {
  uint64_t res = 0;
#if _POSIX_C_SOURCE >= 199309L
  timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);

  res = t.tv_sec * 10e12 + t.tv_nsec;
#else
  // TODO: Impl.
#endif
  return res;
}

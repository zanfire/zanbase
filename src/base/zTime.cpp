#include "zTime.h"


zTime::zTime(void) {
}


zTime::~zTime(void) {
}


uint64_t zTime::current_millis(void) {
  return 0;
}


uint64_t zTime::current_micros(void) {
  return 0;
}
  

uint64_t zTime::current_nanos(void) {
  uint64_t res = 0;
#if _POSIX_C_SOURCE >= 199309L
  timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);

  res = t.tv_sec * 10e9 + t.tv_nsec;
#else
  // TODO: Impl.
#endif
  return res;
}

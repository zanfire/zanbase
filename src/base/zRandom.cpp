#include "zRandom.h"

#include "zMutex.h"
#include "zLogger.h"

#include <time.h>

#if HAVE_SYS_TIME_H
# include <sys/time.h>
#endif


zRandom::zRandom(void) {
  // initstate_r(t.tv_sec, (char*)(&_randstate), sizeof(_randstate), &_randdata);
  //CHECK_FATAL(ret, "initstate_r");
}


zRandom::~zRandom(void) {
  // nop
}


int zRandom::nextInt(void) {
  //int32_t result;
  //int ret = random_r(&_randdata, &result);
  //if (ret == -1) {
    //CHECK_FATAL(errno, "random_r");
  //}
  //return result;
  return 0;
}


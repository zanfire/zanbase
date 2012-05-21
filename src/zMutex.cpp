#include "zMutex.h"

#include "zLogger.h"

#include <stdio.h>
zMutex::zMutex(void) {
  _lockedCount = 0;
  _isDestroying = false;

#if defined(_WIN32)
  _cs = new CRITICAL_SECTION;
  InitializeMutexAndSpinCount((LPCRITICAL_SECTION)_cs, 500);
#else
  pthread_mutexattr_t mutexAttr;

  int res = pthread_mutexattr_init(&mutexAttr);
  CHECK_FATAL(res, "pthread_mutexattr_init");

  res = pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE);
  CHECK_FATAL(res, "pthread_mutexattr_settype PTHREAD_MUTEX_RECURSIVE");

  res = pthread_mutex_init(&_mutex, &mutexAttr);
  CHECK_FATAL(res, "pthread_mutex_init");

  res = pthread_mutexattr_destroy(&mutexAttr);
  CHECK_FATAL(res, "pthread_mutexattr_destroy");
#endif
}


zMutex::~zMutex() {
  sync();

#if defined(_WIN32)
  DeleteMutex((LPCRITICAL_SECTION)_cs);
  delete (CRITICAL_SECTION*)_cs;
#else
  int res = pthread_mutex_destroy(&_mutex);
  CHECK_FATAL(res, "pthread_mutex_destroy");
#endif
}


void zMutex::lock() {
#if defined(_WIN32)
  EnterMutex((LPCRITICAL_SECTION)_cs);
#else
  int res = pthread_mutex_lock(&_mutex);
  CHECK_FATAL(res, "pthread_mutex_lock");
#endif
  _lockedCount++;
}


void zMutex::unlock() {
  _lockedCount--;
#if defined(_WIN32)
  LeaveMutex((LPCRITICAL_SECTION)_cs);
#else
  int res = pthread_mutex_unlock(&_mutex);
  CHECK_FATAL(res, "pthread_mutex_unlock");
#endif
}


bool zMutex::isLocked(void) const {
  return _lockedCount > 0;
}

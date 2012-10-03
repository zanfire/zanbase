#include "zMutex.h"

#include "zLogger.h"

zMutex::zMutex(void) {
  _locked_count = 0;
#if defined(_WIN32)
  // TODO: Check initialization values (500).
  InitializeCriticalSectionAndSpinCount(&_mutex, 500);
#else
  pthread_mutexattr_t mutexAttr;
  pthread_mutexattr_init(&mutexAttr);
  pthread_mutexattr_settype(&mutexAttr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&_mutex, &mutexAttr);
  pthread_mutexattr_destroy(&mutexAttr);
#endif
}


zMutex::~zMutex() {
  sync();

#if defined(_WIN32)
  DeleteCriticalSection(&_mutex);
#else
  pthread_mutex_destroy(&_mutex);
#endif
}


void zMutex::lock() {
#if defined(_WIN32)
  EnterCriticalSection(&_mutex);
#else
  pthread_mutex_lock(&_mutex);
#endif
  _locked_count++;
}


void zMutex::unlock() {
  _locked_count--;
#if defined(_WIN32)
  LeaveCriticalSection(&_mutex);
#else
  pthread_mutex_unlock(&_mutex);
#endif
}


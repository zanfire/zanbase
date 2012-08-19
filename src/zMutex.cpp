#include "zMutex.h"

#include "zLogger.h"

zMutex::zMutex(void) {
#if defined(_WIN32)
  _cs = new CRITICAL_SECTION;
  InitializeMutexAndSpinCount((LPCRITICAL_SECTION)_cs, 500);
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
  DeleteMutex((LPCRITICAL_SECTION)_cs);
  delete (CRITICAL_SECTION*)_cs;
#else
  pthread_mutex_destroy(&_mutex);
#endif
}


void zMutex::lock() {
#if defined(_WIN32)
  EnterMutex((LPCRITICAL_SECTION)_cs);
#else
  pthread_mutex_lock(&_mutex);
#endif
}


void zMutex::unlock() {
#if defined(_WIN32)
  LeaveMutex((LPCRITICAL_SECTION)_cs);
#else
  pthread_mutex_unlock(&_mutex);
#endif
}


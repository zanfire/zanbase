#include "zMutex.h"

#include "zLogger.h"

zMutex::zMutex(void) {
#if defined(_WIN32)
  _mutex = new CRITICAL_SECTION;
  // TODO: Check initialization values (500).
  InitializeCriticalSectionAndSpinCount((LPCRITICAL_SECTION)_mutex, 500);
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
  DeleteCriticalSection((LPCRITICAL_SECTION)_mutex);
  delete (CRITICAL_SECTION*)_mutex;
#else
  pthread_mutex_destroy(&_mutex);
#endif
}


void zMutex::lock() {
#if defined(_WIN32)
  EnterCriticalSection((LPCRITICAL_SECTION)_mutex);
#else
  pthread_mutex_lock(&_mutex);
#endif
}


void zMutex::unlock() {
#if defined(_WIN32)
  LeaveCriticalSection((LPCRITICAL_SECTION)_mutex);
#else
  pthread_mutex_unlock(&_mutex);
#endif
}


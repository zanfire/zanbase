#include "zEvent.h"

zEvent::zEvent(void) {
#if defined(_WIN32)
  _event = INVALID_HANDLE_VALUE;
  _event = CreateEvent(NULL, true, false, NULL); 
#elif HAVE_PTHREAD_H
  int success = sem_init(&_event, 0, 0);
  assert_perror(success);
#endif
}


zEvent::~zEvent(void) {
#if defined(_WIN32)
  if(_event != NULL) {
    CloseHandle(_event);
    _event = NULL;
  }
#else
  int success = sem_destroy(&_event);
  assert_perror(success);
#endif
}


void zEvent::wait(int timeoutMillis) {
#if defined(_WIN32)
  DWORD res = WaitForSingleObject( _event, timeoutMillis);
#else
  int success = 0;
  if (timeoutMillis < 0) {
    success = sem_wait(&_event);
  }
  else {
    timespec request_time;

    request_time.tv_sec = (int)(timeoutMillis / 1000);
    request_time.tv_nsec = (int)(timeoutMillis % 1000) * 1000;
    success = sem_timedwait(&_event, &request_time);
  }
  assert_perror(success);
#endif
}


void zEvent::signal(void) {
#if defined(_WIN32)
  SetEvent(_event);
#else
  int success = sem_post(&_event);
  assert_perror(success);
#endif
}


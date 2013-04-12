#include "zEvent.h"

zEvent::zEvent(void) {
#if defined(_WIN32)
  _event = INVALID_HANDLE_VALUE;
  _event = CreateEvent(NULL, true, false, NULL); 
#elif HAVE_PTHREAD_H
  sem_init(&_event, 0, 0);
#endif
}


zEvent::~zEvent(void) {
#if defined(_WIN32)
  if(_event != NULL) {
    CloseHandle(_event);
    _event = NULL;
  }
#else
  sem_destroy(&_event);
#endif
}


void zEvent::wait(int timeoutMillis) {
#if defined(_WIN32)
  WaitForSingleObject( _event, timeoutMillis);
#else
  if (timeoutMillis < 0) {
    sem_wait(&_event);
  }
  else {
    timespec request_time;

    request_time.tv_sec = (int)(timeoutMillis / 1000);
    request_time.tv_nsec = (int)(timeoutMillis % 1000) * 1000;
    sem_timedwait(&_event, &request_time);
  }
#endif
}


void zEvent::signal(void) {
#if defined(_WIN32)
  SetEvent(_event);
#else
  sem_post(&_event);
#endif
}


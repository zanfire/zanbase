#include "zRunnable.h"

#include "zEvent.h"
#include "zThread.h"


zRunnable::zRunnable(void) {
}


zRunnable::~zRunnable(void) {
}



zRunnableLoop::zRunnableLoop(void) {
  _must_continue = true;
  _loop_timeout_ms = -1; 
  _continue = new zEvent();
}


zRunnableLoop::~zRunnableLoop(void) {
  delete _continue;
}


void zRunnableLoop::set_loop_timeout(int ms) {
  _loop_timeout_ms = ms;
}


void zRunnableLoop::signal_continue(void) {
  _continue->signal();
}


void zRunnableLoop::stop(bool sync) {
  _must_continue = false;
  if (_threadID != zThread::get_current_thread_id()) {
    if (sync) {
      _continue->signal();
    }
  }
}


int zRunnableLoop::run(void* param) {
  _threadID = zThread::get_current_thread_id();
  int ret = 0;
  while (_must_continue) {
    ret = execute(param);
     if (_loop_timeout_ms != 0) {
      _continue->wait(_loop_timeout_ms);
    }
  }
  return ret;
}


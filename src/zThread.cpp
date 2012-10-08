#include "zThread.h"
#include "zRunnable.h"

#include <stdio.h>
#include <time.h>

#if defined(_WIN32)
  #include <windows.h>
  #include <Process.h>
#else
# include <pthread.h>
# include <unistd.h>
# include <sys/syscall.h>
#endif

class zThreadMain {
public:
  zThreadMain(void) {}
  virtual ~zThreadMain(void) {}

  void main(zThread* th) {
    th->_mtx_running.lock();
    th->_id = zThread::get_current_thread_id();
    th->_is_running = true;
    // Init finished.
    th->_ev_start.signal();
    th->_result = th->_runnable->run(th->_app_param);
    th->_is_running = false;
    th->_mtx_running.unlock();
    // After this the th instance can be destroied. Pay attention.
  }
};


/// Internal namespace.
namespace Protected  {

///
/// The thread entry point for the platform API.
///

#if defined(_WIN32)
  unsigned __stdcall ThreadEntry(void* arg) {
#else
  void* ThreadEntry(void* arg) {
#endif
    zThreadMain th;
    th.main((zThread*)arg);
    return NULL;
  }
}


zThread::zThread(zRunnable* runnable, int stack_size) : zObject() {
  _result = 0;
  _runnable = runnable;
  _app_param = NULL;
  _is_running = false;
  // IF invalid stack_size set default 2 MB.
  if (stack_size <= 0) _stack_size = 1024 * 2048;
  _stack_size = stack_size;

  _thread = 0;
  _id = INVALID_THREAD_ID;
}


zThread::~zThread(void) {
  // Join to the main thread to avoid race-condition with internal data.
  join();
}


void zThread::sleep(int ms) {
#if defined(WIN32)
	// TODO: Check if it is precise.
	Sleep(ms);
#else
  timespec rentime;
  timespec reqtime;

  reqtime.tv_sec = (int)(ms / 1000);
  reqtime.tv_nsec = (int)(ms % 1000) * 1000;

  int success = nanosleep(&reqtime, &rentime);
  assert_perror(success);
#endif
}


bool zThread::start(void* param) {
  if (_is_running) return false;
  if (_runnable == NULL) return false;

  // Store the application param to be passed to the running thread via zThread instance.
  _app_param = param;

#if defined(WIN32)
  // READ DOCs because this cast is quite hazard.
  _thread = (HANDLE)_beginthreadex(NULL, 0, &(Protected::ThreadEntry), this, 0, &_id);
  // hThread = (HANDLE)_beginthreadex( NULL, 0, &SecondThreadFunc, NULL, 0, &threadID );

#else // POSIX

  pthread_attr_t attr;
  // Initialize attribute.
  int result = pthread_attr_init(&attr);
  assert_perror(result);
  // The library doesn't use the pthread_join method. Creates a detached thread that release system resources when thread terminate.
  result = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  assert_perror(result);
  // Set stack size.
  result = pthread_attr_setstacksize(&attr, _stack_size);
  assert_perror(result);

  // Create the thread,
  result = pthread_create(&_thread, &attr, &(Protected::ThreadEntry), this);
  assert_perror(result);
  // Destroy attributes.
  pthread_attr_destroy(&attr);
#endif
  // Wait for the running thread.
  _ev_start.wait();
  return true;
}


int zThread::join(void) { 
  _mtx_running.sync();
  return _result;
}


THREAD_ID zThread::get_current_thread_id(void) {
#if defined(_WIN32) 
	return GetCurrentThreadId();
#else
  return syscall(SYS_gettid);
#endif
}


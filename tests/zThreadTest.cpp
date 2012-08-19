#include "zThreadTest.h"

#include "zLogger.h"
#include "zThread.h"
#include "zRunnable.h"

zThreadTest::zThreadTest(void) {
}


zThreadTest::~zThreadTest(void) {
}


bool zThreadTest::execute(int index) {
  switch(index) {
    case 0: return test_join();
    case 1: return test_memory();
    case 2: return test_threadid();
    case 3: return test_startfail();
    default: return false;
  }
  return false;
}


int zThreadTest::get_num_tests(void) {
  return 4;
}


char const* zThreadTest::get_name(void) {
  return "zThread tests";
}


char const* zThreadTest::get_description(void) {
  return "A tests set for zThread class.";
}


char const* zThreadTest::get_test_name(int index) {
  switch(index) {
    case 0: return "join";
    case 1: return "memory";
    case 2: return "threadid";
    case 3: return "start fail";
    default: return "??";
  }
  return "??";
}


char const* zThreadTest::get_test_description(int index) {
  return "??";
}


class ThreadTest : public zRunnable {
  public:
    int run(void* param) {
      int sleep = *((int*)param);
      if (sleep > 0) { 
        zThread::sleep(sleep);
        return sleep * 2;
      }
      else {
        return zThread::get_current_thread_id();
      }
    }
};


bool zThreadTest::test_join(void) {
  // Create threads.
  ThreadTest impl;
  zArray<zThread*> array(NO, 5, NULL);
  int sleep = 500;
  for (int i = 0; i < 50; i++) {
    zThread* thread = new zThread(&impl);
    array.append(thread);
    thread->start(&sleep);
  }
  // Joins
  for (int i = 0; i < 50; i++) {
    zThread* thread = NULL;
    array.get(i, &thread);
    int result = thread->join();
    if (result != sleep * 2) return false;
  }

  // Delete threads.
  while (array.get_count() > 0) {
    zThread* th = NULL;
    array.remove(0, &th);
    th->release_reference();
  }
  return true;

}


bool zThreadTest::test_memory(void) {
  ThreadTest impl;

  zArray<zThread*> array(YES, 10, NULL);
  int sleep = 100;
  for (int i = 0; i < 5; i++) {
    zThread* thread = new zThread(&impl);
    array.append(thread);
    thread->start(&sleep);
  }

  while (array.get_count() > 0) {
    zThread* th = NULL;
    array.remove(0, &th);
    th->release_reference();
  }

  return true;
}


bool zThreadTest::test_threadid(void) {
  ThreadTest impl;

  int sleep = 0;
  zThread* thread = new zThread(&impl);
  thread->start(&sleep);
  THREAD_ID tid = thread->get_thread_id();
  
  THREAD_ID ret = thread->join();

  if (ret != tid) return false;

  thread->release_reference();
 
  return true;
}


bool zThreadTest::test_startfail(void) {
  
  zThread* thread = new zThread(NULL);
  if (thread->start()) return false;
  thread->release_reference();

  ThreadTest impl;
  int sleep = 1000;
  thread = new zThread(&impl);
  thread->start(&sleep);
  if (thread->start(&sleep)) return false;

  thread->release_reference();
 
  return true;
}



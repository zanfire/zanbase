#include "zArrayTest.h"

#include "zLogger.h"
#include "zArray.h"
#include "zThread.h"
#include "zRunnable.h"
#include "zReference.h"

zArrayTest::zArrayTest(void) {
}


zArrayTest::~zArrayTest(void) {
}


bool zArrayTest::execute(int index) {
  switch(index) {
    case 0: return test_ctor();
    case 1: return test_resize();
    case 2: return test_memory();
    case 3: return test_multithread();
    case 4: return test_get();
    default: return false;
  }
  return false;
}


int zArrayTest::get_num_tests(void) {
  return 5;
}


char const* zArrayTest::get_name(void) {
  return "zArray tests";
}


char const* zArrayTest::get_description(void) {
  return "zArray test set.";
}


char const* zArrayTest::get_test_name(int index) {
  switch(index) {
    case 0: return "ctor";
    case 1: return "resize";
    case 2: return "memory";
    case 3: return "multithread";
    case 4: return "get";
    default: return "??";
  }
  return "??";

}


char const* zArrayTest::get_test_description(int index) {
  return "??";
}


bool zArrayTest::test_ctor(void) {

  {
    zArray<int>* array = new zArray<int>(NO, 1024, -1);
    array->append(0);
    if (array->get_count() != 1) return false;
    delete array;
  }
  {
    zArray<int>* array = new zArray<int>(YES, 0, -1);
    array->append(0);
    if (array->get_count() != 1) return false;
    delete array;
  }
  return true;
}


bool zArrayTest::test_resize(void) {
  zArray<int> arr(YES, 5, -1);
  int size = 16 * 1024;
  for (int i = 0; i < size; i++) {
    arr.append(i);
  }
  for(int i = 0; i < size; i++) {
    int tmp = -2;
    arr.remove(0, &tmp);
    // Is expected the same order.
    if (tmp != i) return false;
  }
  for (int i = 0; i < size; i++) {
    arr.append(i);
  }
  for(int i = 0; i < size; i++) {
    int tmp = -2;
    arr.remove(0, &tmp);
    // Is expected the same order.
    if (tmp != i) return false;
  }



  return true;
}


bool zArrayTest::test_memory(void) {
  zArray<void*>* array = new zArray<void*>(NO, 1, NULL);

  delete array;
  
  return true;
}


class MultithreadTest : public zRunnable {
  public:
    zArray<zref_t>* array;
    zReference* ref;
    int run(void* param) {
      
      for (int i = 0; i < 5000; i++) {
        array->lock();
        zref_t r = ref->increment();
        array->append(r);
        array->unlock();
      }
      return 0;
    }
};


bool zArrayTest::test_multithread(void) {
  MultithreadTest* impl = new MultithreadTest();
  zThread* thread1 = new zThread(impl);
  zThread* thread2 = new zThread(impl);

  zArray<zref_t>* arr = new zArray<zref_t>(YES, 10, 0);
  zReference* ref = new zReference();

  impl->array = arr;
  impl->ref = ref;


  thread1->start(NULL);
  thread2->start(NULL);

  thread1->join();
  thread2->join();

  // Check data
  for (int i = 0; i < arr->get_count(); i++) {
    zref_t r = 0;
    arr->get(i, &r);
    if (r != (i +1)) return false;
  }

  // Delete
  thread1->release_reference();
  thread2->release_reference();

  delete impl;
  delete ref;
  delete arr;


  return true;
}


bool zArrayTest::test_get(void) {
  zArray<char> array(NO, 1, 0);
  // Test on failing get.
  char tmp = 'a';
  if (array.get(0, &tmp) || tmp != 'a') return false;
  // Test ok.
  array.append('c');
  if (!array.get(0, &tmp) || tmp != 'c') return false;

  return true;
}




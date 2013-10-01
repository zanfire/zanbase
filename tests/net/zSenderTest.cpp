#include "zSenderTest.h"

#include "zLogger.h"
#include "zThread.h"
#include "zRunnable.h"
#include "zTime.h"
#include "zSender.h"
#include "zSocketUDP.h"

#include "zSocketAddressIPv4.h"

zSenderTest::zSenderTest(void) {
}


zSenderTest::~zSenderTest(void) {
}


bool zSenderTest::execute(int index) {
  switch(index) {
    case 0: return test_benckmark();
    default: return false;
  }
  return false;
}


int zSenderTest::get_num_tests(void) {
  return 1;
}


char const* zSenderTest::get_name(void) {
  return "zSender tests";
}


char const* zSenderTest::get_description(void) {
  return "A tests set for zSender class.";
}


char const* zSenderTest::get_test_name(int index) {
  switch(index) {
    case 0: return "benchmark";
    default: return "??";
  }
  return "??";
}


char const* zSenderTest::get_test_description(int index) {
  return "??";
}


#include <stdio.h>


class SenderThreadTest : public zRunnable {
  public:
    zSender* _sender;
    zSocketUDP* _sock; 
    unsigned char _buffer[1500];

    int run(void* param) {
      zSocketAddressIPv4 dest("127.0.0.1", 50001);
      unsigned int start = zTime::current_millis();
      while ((zTime::current_millis() - start) < (60 * 1000)) {
        _sender->send(_sock, dest.get_address(), dest.get_port(), &_buffer[0], 1500, 0);
        zThread::sleep(5);
      }
      return 0;
    }
};


bool zSenderTest::test_benckmark(void) {

  zSender* sender = new zSender();
  zSocketUDP* sock = new zSocketUDP();
  sock->bindTo(zSocketAddressIPv4("127.0.0.1", 50000));
  sock->set_non_blocking(false);

  sender->start();

  // Create threads.
  SenderThreadTest impl;
  impl._sender = sender;
  impl._sock = sock;
  int c = 5;
  zArray<zThread*> array(NO, c);
  for (int i = 0; i < c; i++) {
    zThread* thread = new zThread(&impl);
    array.append(thread);
    thread->start();
  }

  printf("Started ... \n");

  // Joins
  for (int i = 0; i < c; i++) {
    zThread* thread = NULL;
    array.get(i, &thread);
    thread->join();
  }

  printf("Joined all ...\n");

  // Delete threads.
  while (array.get_count() > 0) {
    zThread* th = NULL;
    array.remove(0, &th);
    th->release_reference();
  }
  delete sender;
  return true;

}

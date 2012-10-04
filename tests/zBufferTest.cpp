#include "zBufferTest.h"

#include "zBuffer.h"

zBufferTest::zBufferTest(void) {
}


zBufferTest::~zBufferTest(void) {
}


bool zBufferTest::execute(int index) {
  switch(index) {
    case 0: return test_ctor();
    case 1: return test_resize();
    case 2: return test_set();
    case 3: return test_append();
    default: return false;
  }
  return false;
}


int zBufferTest::get_num_tests(void) {
  return 4;
}


char const* zBufferTest::get_name(void) {
  return "zBuffer test";
}


char const* zBufferTest::get_description(void) {
  return "zBuffer test set.";
}


char const* zBufferTest::get_test_name(int index) {
  switch(index) {
    case 0: return "ctor";
    case 1: return "resize";
    case 2: return "set";
    case 3: return "append";
    default: return "??";
  }
  return "??";

}


char const* zBufferTest::get_test_description(int index) {
  return "??";
}


bool zBufferTest::test_ctor(void) {
  zBuffer* buffer = new zBuffer(0);
  if (buffer->get_size() != 0) return false;
  if (buffer->get_buffer() != NULL) return false;
  buffer->release_reference();

  buffer = new zBuffer(-1);
  if (buffer->get_size() != 0) return false;
  if (buffer->get_buffer() != NULL) return false;
  buffer->release_reference();

  int size = 1024 * 1024 * 2;
  buffer = new zBuffer(size); // 2 MB
  if (buffer->get_size() != size) return false;
  if (buffer->get_buffer() == NULL) return false;
  buffer->release_reference();

  return true;
}


bool zBufferTest::test_resize(void) {
  zBuffer* buffer = new zBuffer(0);
  buffer->resize(1024);
  if (buffer->get_size() != 1024) return false;
  if (buffer->get_buffer() == NULL) return false;


  buffer->resize(0);
  if (buffer->get_size() != 0) return false;
  if (buffer->get_buffer() != NULL) return false;

  buffer->resize(1024);
  if (buffer->get_size() != 1024) return false;
  if (buffer->get_buffer() == NULL) return false;
  buffer->release_reference();

  return true;
}


bool zBufferTest::test_append(void) {
  unsigned char tmp[] = { 0xAA, 0xAB, 0xAC, 0xAD};
  zBuffer* buffer = new zBuffer(1024);
<<<<<<< HEAD
  buffer->set(0xFB);
  if (buffer->append(NULL, 15) != false) return false;
  if (buffer->append((unsigned char*)&tmp, -1) != false) return false;
  if (buffer->append((unsigned char*)&tmp, 4) != true) return false;
  if (buffer->get_size() != 1028) return false;

  unsigned char* buf = buffer->get_buffer();
  for (int i = 0; i < 1028 ; i++) {
    if (i < 1024) {
      if (buf[i] != 0xFB) return false;
    }
    else if (i == 1024) {
      if (buf[i] != 0xAA) return false;
    }
    else if (i == 1025) {
      if (buf[i] != 0xAB) return false;
    }
    else if (i == 1026) {
      if (buf[i] != 0xAC) return false;
    }
    else if (i == 1027) {
      if (buf[i] != 0xAD) return false;
    }
  }

=======
  buffer->set(0);
>>>>>>> Update ignore list.
  buffer->release_reference();

  return true;
}


bool zBufferTest::test_set(void) {
  zBuffer* buffer = new zBuffer(1024);
  buffer->set(0xfa);
  for (int i = 0; i < buffer->get_size(); i++) {
    if (buffer->get_buffer()[i] != 0xfa) return false;
  }
  buffer->resize(128 * 1024);
  buffer->set(0xfb);
  for (int i = 0; i < buffer->get_size(); i++) {
    if (buffer->get_buffer()[i] != 0xfb) return false;
  }


  buffer->release_reference();

  return true;
}


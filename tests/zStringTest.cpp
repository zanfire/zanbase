#include "zStringTest.h"

#include "zString.h"
#include "zBuffer.h"
#include "zLogger.h"

#include <string.h>

zStringTest::zStringTest(void) {
  logger_ = zLogger::get_logger("test");
}


zStringTest::~zStringTest(void) {

}


bool zStringTest::execute(int index) {
  bool ret = false;
  if (index == 0) ret = test_all_ctor();
  return ret;
}


int zStringTest::get_num_tests(void) {
  return 1;
}


char const* zStringTest::get_name(void) {
  return "zString tests";
}


char const* zStringTest::get_description(void) {
  return "Tests for zString class";
}


char const* zStringTest::get_test_name(int index) {
  if (index == 0) return "Constructors test";
  return "??";
}


char const* zStringTest::get_test_description(int index) {
  if (index == 0) return "Test all ctor of zString classes.";
  return "??";
}


bool zStringTest::test_all_ctor(void) {
  // Test empty string.
  zString empty;
  if (empty.get_length() != 0 || strlen(empty.get_buffer()) != 0) {
    logger_->error("Failed ctor test of empty string.");
    return false;
  }

  // Test buffer.
  zBuffer* zbuf = new zBuffer(1024);
  char*  buf = (char*)zbuf->get_buffer();
  buf[0] = 'c';
  buf[1] = 'a';
  buf[2] = 'i';
  buf[3] = 0;
  zString stringBuf(zbuf);
  if (stringBuf.get_length() != (int)strlen(buf) || memcmp(stringBuf.get_buffer(), buf, strlen(buf))) {
    logger_->error("Failed ctor test of string with zBuffer.");
    return false;
  }
  zbuf->release_reference();

  zString stringChar('c');
  if (stringChar.get_length() != 1 || strlen(stringChar.get_buffer()) != 1 || (stringChar.get_buffer())[0] != 'c') {
    logger_->error("Failed ctor test of string with char");
    return false;
  }
  {
    zString stringStr("12345");
    if (stringStr.get_length() != 5 || strlen(stringStr.get_buffer()) != 5 || (strcmp(stringStr.get_buffer(), "12345") != 0)) {
      logger_->error("Failed ctor test of string with string");
      return false;
    }
  }

  {
    zString stringStrl("123456789ABCDEF", 10);
    if (stringStrl.get_length() != 10 || strlen(stringStrl.get_buffer()) != 10 || (strcmp(stringStrl.get_buffer(), "123456789A") != 0)) {
      return false;
    }
  }

  {
    zString stringStrl("12345", 10);
    if (stringStrl.get_length() != 5 || strlen(stringStrl.get_buffer()) != 5 || (strcmp(stringStrl.get_buffer(), "12345") != 0)) {
      return false;
    }
  }

  {
    zString stringStrl(NULL, 10);
    if (stringStrl.get_length() != 0 || strlen(stringStrl.get_buffer()) != 0 || (strcmp(stringStrl.get_buffer(), "") != 0)) {
      return false;
    }
  }

  {
    zString stringStrl((zBuffer*)NULL);
    if (stringStrl.get_length() != 0 || strlen(stringStrl.get_buffer()) != 0 || (strcmp(stringStrl.get_buffer(), "") != 0)) {
      return false;
    }
  }

  {
    zString stringStrl((char const*)NULL);
    if (stringStrl.get_length() != 0 || strlen(stringStrl.get_buffer()) != 0 || (strcmp(stringStrl.get_buffer(), "") != 0)) {
      return false;
    }
  }

  {
    zString stringStrl((zStringBuilder*)NULL);
    if (stringStrl.get_length() != 0 || strlen(stringStrl.get_buffer()) != 0 || (strcmp(stringStrl.get_buffer(), "") != 0)) {
      return false;
    }
  }

  return true;
}


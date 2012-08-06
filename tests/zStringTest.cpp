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
  switch(index) {
    case 0: return test_all_ctor();
    case 1: return test_substring();
    case 2: return test_index_of();
    case 3: return test_last_index_of();
    case 4: return test_to_cases();
    case 5: return false;
    default: return false;
  }
  return false;
}


int zStringTest::get_num_tests(void) {
  return 5;
}


char const* zStringTest::get_name(void) {
  return "zString tests";
}


char const* zStringTest::get_description(void) {
  return "Tests for zString class";
}


char const* zStringTest::get_test_name(int index) {
  switch(index) {
    case 0: return "Constructors test";
    case 1: return "Substring";
    case 2: return "test";
    case 3: return "test";
    case 4: return "test";
    case 5: return "test";
    default: return "??";
  }
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
    // Test NULL ctor.
    zString stringStrl((char const*)NULL);
    if (stringStrl.get_length() != 0 || strlen(stringStrl.get_buffer()) != 0 || (strcmp(stringStrl.get_buffer(), "") != 0)) {
      return false;
    }
  }

  {
    // Test NULL ctor.
    zString stringStrl((zStringBuilder*)NULL);
    if (stringStrl.get_length() != 0 || strlen(stringStrl.get_buffer()) != 0 || (strcmp(stringStrl.get_buffer(), "") != 0)) {
      return false;
    }
  }

  {
    // Test copy constructor.
    zString str("12345");

    zString strc = str;
    if (strc.get_length() != 5 || strlen(strc.get_buffer()) != 5 || (strcmp(strc.get_buffer(), "12345") != 0)) {
      return false;
    }
  }



  {
    // Test copy constructor.
    zString strc = "12345";
    if (strc.get_length() != 5 || strlen(strc.get_buffer()) != 5 || (strcmp(strc.get_buffer(), "12345") != 0)) {
      return false;
    }
  }



  {
    // Test with a BIG buffer.
    zBuffer* buf = new zBuffer(128 * 1024);
    buf->set('a');
    char* strbuf = (char*)buf->get_buffer();
    strbuf[128 * 1024 - 1] = '\0';

    zString str(strbuf);
    if (str.get_length() != (128 * 1024 - 1) || strlen(str.get_buffer()) != (128 * 1024 - 1) || (strcmp(str.get_buffer(), strbuf) != 0)) {
      return false;
    }
    buf->release_reference();
  }

  return true;
}


bool zStringTest::test_substring() {
  zString target = "0123456789ABCDEF";

  zString sub = target.substring(5, 5);
  if (!sub.equals("56789")) {
    return false;
  }

  sub = target.substring(0, 64);
  if (!sub.equals(target)) {
    return false;
  }

  sub = target.substring(-1, 64);
  if (!sub.equals(target)) {
    return false;
  }

  sub = target.substring(0, -1);
  if (!sub.is_empty()) {
    return false;
  }


  sub = target.substring(64, 64);
  if (!sub.is_empty()) {
    return false;
  }

  sub = target.substring(64, -1);
  if (!sub.is_empty()) {
    return false;
  }

  return true;
}


bool zStringTest::test_index_of(void) {
  return false;
}


bool zStringTest::test_last_index_of(void) {
  return false;
}


bool zStringTest::test_to_cases(void) {
  return false;
}


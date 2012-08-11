#include "zStringTest.h"

#include "zString.h"
#include "zBuffer.h"
#include "zLogger.h"

#include <string.h>

zStringTest::zStringTest(void) {
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
    case 5: return test_numeric();
    case 6: return test_comparison();
    case 7: return test_split();
    case 8: return test_memory();
    default: return false;
  }
  return false;
}


int zStringTest::get_num_tests(void) {
  return 9;
}


char const* zStringTest::get_name(void) {
  return "zString tests";
}


char const* zStringTest::get_description(void) {
  return "Tests for zString class";
}


char const* zStringTest::get_test_name(int index) {
  switch(index) {
    case 0: return "ctor";
    case 1: return "substring";
    case 2: return "index of";
    case 3: return "last index of";
    case 4: return "to cases";
    case 5: return "numeric";
    case 6: return "comparison";
    case 7: return "split";
    case 8: return "memory";
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
  // Test varius substring combination.
  // 

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
  if (!sub.equals(target)) return false;

  sub = target.substring(0, -1);
  if (!sub.is_empty()) return false;

  sub = target.substring(64, 64);
  if (!sub.is_empty()) return false;

  sub = target.substring(64, -1);
  if (!sub.is_empty()) return false;

  target = "";
  sub = target.substring(0, 1);
  if (!sub.is_empty()) return false;

  return true;
}


bool zStringTest::test_index_of(void) {
  //             0123456789_11_14_17_20_23_26_29
  zString str = "123456789ABCDEF 123456789ABCDEF";

  if (str.index_of("1", 0) != 0) return false;
  if (str.index_of("1", 1) != 16) return false;
  if (str.index_of("123", 0) != 0) return false;
  if (str.index_of("FEDC", 0) != -1) return false;
  if (str.index_of("23", 0) != 1) return false;
  if (str.index_of("1", 128)  != -1) return false;
  if (str.index_of("", 0) != -1) return false;
  if (str.index_of("EF", 18) != 29) return false;
  if (str.index_of("F", 18) != 30) return false;
  if (str.index_of("", 0) != -1) return false;

  str = "";
  if (str.index_of("1", 0) != -1) return false;

  return true;
}


bool zStringTest::test_last_index_of(void) {
  //             0123456789_11_14_17_20_23_26_29
  zString str = "123456789ABCDEF 123456789ABCDEF";

  if (str.last_index_of("1",    str.get_length()) != 16) return false;
  if (str.last_index_of("1",    10) != 0) return false;
  if (str.last_index_of("123",  str.get_length()) != 16) return false;
  if (str.last_index_of("FEDC", str.get_length()) != -1) return false;
  if (str.last_index_of("23",   str.get_length()) != 17) return false;
  if (str.last_index_of("1",    -1)  != -1) return false;
  if (str.last_index_of("",     0) != -1) return false;
  if (str.last_index_of("EF",   str.get_length()) != 29) return false;
  if (str.last_index_of("F",    str.get_length()) != 30) return false;
  if (str.last_index_of("",     str.get_length()) != -1) return false;

  str = "";
  if (str.last_index_of("1", 64) != -1) return false;

  return true;
}


bool zStringTest::test_to_cases(void) {
  zString empty = "";
  zString from_empty = empty.to_lowercase();
  if (!from_empty.is_empty())  return false;

  zString lower = "abcdef@123-";
  zString upper = "ABCDEF@123-";

  zString from_lower = lower.to_uppercase();
  if (!upper.equals(from_lower)) return false;

  zString from_upper = upper.to_lowercase();
  if (!lower.equals(from_upper)) return false;

  return true;
}


bool zStringTest::test_numeric(void) {

  // TEST is_num
  zString str = "";
  if (str.is_num()) return false;

  str = "0";
  if (!str.is_num()) return false;

  str = "12a";
  if (str.is_num()) return false;

  str = " 12 ";
  if (str.is_num()) return false;

  str = "-12";
  if (str.is_num()) return false;

  str = "45555355252353464634535645354645334664645332436585663434656867654767543215687543233465877654313234567877543234657877867534231";
  if (!str.is_num()) return false;

  // TEST to_int
  
  str = "12";
  if (str.to_int() != 12)  return false;

  str = "";
  if (str.to_int() != 0) return false;

  str = "a13";
  if (str.to_int() != 0) return false;

  str = "12345678087657000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
  if (str.to_int() != 0) return false;

  return true;
}


bool zStringTest::test_comparison(void) {
  zString str = "123456789";

  // TEST equals
  if (!str.equals("123456789")) return false;
  if (str.equals("12")) return false;
  if (str.equals("223456789")) return false;
  if (str.equals("")) return false;

  // TEST compare
  str = "abc";
  if (str.compare("abc") != 0) return false;

  if (str.compare("ABC") != 1) return false;
  if (str.compare("bbc") != -1) return false;

  return true;
}


bool zStringTest::test_split(void) {
  {
    // Simple case.
    zString str = "1 2";
    zArray<zString> arr = str.split(" ", true);
    if (arr.get_count() != 2) return false;
    zString tmp;
    arr.get(0, &tmp);
    if (!tmp.equals("1")) return false;
    arr.get(1, &tmp);
    if (!tmp.equals("2")) return false;
  }

  {
    // Simple case, with an and space..
    zString str = "1 2 ";
    zArray<zString> arr = str.split(" ", true);
    if (arr.get_count() != 2) return false;
    zString tmp;
    arr.get(0, &tmp);
    if (!tmp.equals("1")) return false;
    arr.get(1, &tmp);
    if (!tmp.equals("2")) return false;
  }


  {
    // Simple case with multiple token.
    zString str = "1  2";
    zArray<zString> arr = str.split(" ", true);
    if (arr.get_count() != 2) return false;
    zString tmp;
    arr.get(0, &tmp);
    if (!tmp.equals("1")) return false;
    arr.get(1, &tmp);
    if (!tmp.equals("2")) return false;
  }

  {
    zString str = "0 1 2  3 4 59 ";

    zArray<zString> arr = str.split(" ", true);

    if (arr.get_count() != 6) return false;

    zString tmp;

    arr.get(0, &tmp);
    if (!tmp.equals("0")) return false;
    arr.get(1, &tmp);
    if (!tmp.equals("1")) return false;
    arr.get(2, &tmp);
    if (!tmp.equals("2")) return false;
    arr.get(3, &tmp);
    if (!tmp.equals("3")) return false;
    arr.get(4, &tmp);
    if (!tmp.equals("4")) return false;
    arr.get(5, &tmp);
    if (!tmp.equals("59")) return false;
  }

  {
    // Simple case with multiple token.
    zString str = "ad1adad2adad";
    zArray<zString> arr = str.split("ad", true);
    if (arr.get_count() != 2) return false;
    zString tmp;
    arr.get(0, &tmp);
    if (!tmp.equals("1")) return false;
    arr.get(1, &tmp);
    if (!tmp.equals("2")) return false;
  }

  {
    zString str = "";
    zArray<zString> arr = str.split("ab", true);
    if (arr.get_count() != 0) return false;
  }

  return true;
}


bool zStringTest::test_memory(void) {
  zBuffer* buf = new zBuffer(1024 * 16);
  buf->set('a');
  
  // Check memory.
  
  for (int i = 0; i <= 1000; i++) {
    zString* tmp1 = new zString("ciao");
    zString* tmp2 = new zString((char*)buf->get_buffer(), buf->get_size() - 1);

    *tmp2 = *tmp1;

    delete tmp1;
    delete tmp2;
  }

  // Check memory.

  buf->release_reference();

  return false;
}


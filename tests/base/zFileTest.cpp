#include "zFileTest.h"

#include "zLogger.h"
#include "zFile.h"

#include <memory.h>

zFileTest::zFileTest(void) {
}


zFileTest::~zFileTest(void) {
}


bool zFileTest::execute(int index) {
  switch(index) {
    case 0: return test_open();
    case 1: return test_wr();
    default: return false;
  }
  return false;
}


int zFileTest::get_num_tests(void) {
  return 2;
}


char const* zFileTest::get_name(void) {
  return "zFile tests";
}


char const* zFileTest::get_description(void) {
  return "zFile test set.";
}


char const* zFileTest::get_test_name(int index) {
  switch(index) {
    case 0: return "open";
    case 1: return "write and read";
    default: return "??";
  }
  return "??";

}


char const* zFileTest::get_test_description(int index) {
  return "??";
}


bool zFileTest::test_open(void) {
  // Fail to open a file.
  zFile* file = zFile::open("not existing location");
  if (file != NULL) return false;

  // Create a file.
  file = zFile::create("file.txt");
  if (file == NULL) return false;
  file->close();
  zFile::remove("file.txt");
  file->release_reference();

  return true;
}


bool zFileTest::test_wr(void) {
  zFile* file = zFile::create("testfile.txt");

  int buffer_w[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  int bytes_w = file->write((unsigned char*)&buffer_w, sizeof(buffer_w));
  if (bytes_w != sizeof(buffer_w)) return false;

  file->seek(0);

  char buffer_r[1024];
  int bytes_r = file->read((unsigned char*)&buffer_r, sizeof(buffer_r));
  if (bytes_r != bytes_w) return false;
  if (memcmp(buffer_w, buffer_r, bytes_w) != 0) return false;

  file->close();
  file->release_reference();

  zFile::remove("testfile.txt");

  return true;
}


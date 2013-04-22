#include "zFile.h"

#include "zLogger.h"
#include "zStringBuilder.h"

#if HAVE_UNISTD_H
# include <unistd.h>
#endif
// TODO: Add GUARD.
#include <errno.h>

zFile::zFile(FILE* file, zString const& path) : zStream(), zObject() {
  _file = file;
  _path = path;
  //_flags = flags;
}


zFile::~zFile(void) {
  close();
}


zFile* zFile::create(zString const& path) {
  FILE* fd = NULL;
  fd = fopen(path.get_buffer(), "w+");
  if (fd != NULL) {
    return new zFile(fd, path);
  }
  else {
    LOG_DEBUG("Failed to open file. system reports error: %d - %s", errno, strerror(errno));
  }
  return NULL;
}



zFile* zFile::open(zString const& path) {
  FILE* fd = NULL;
  fd = fopen(path.get_buffer(), "r+");
  if (fd != NULL) {
    return new zFile(fd, path);
  }
  else {
    LOG_DEBUG("Failed to open file. system reports error: %d - %s", errno, strerror(errno));
  }
  return NULL;
}


zFile* zFile::append(zString const& path) {
  FILE* fd = NULL;
  fd = fopen(path.get_buffer(), "a+");
  if (fd != NULL) {
    return new zFile(fd, path);
  }
  else {
    LOG_DEBUG("Failed to open file. system reports error: %d - %s", errno, strerror(errno));
  }
  return NULL;
}


int zFile::read(unsigned char* buffer, int size) {
  if (buffer == NULL) return -1;
  if (size <= 0) return -1;
  if (_file == NULL) return -1;

  return fread(buffer, 1, size, _file);
}


int zFile::write(unsigned char* buffer, int size) {
  if (buffer == NULL) return -1;
  if (size <= 0) return -1;
  if (_file == NULL) return -1;

  return fwrite(buffer, 1, size, _file);
}


int zFile::seek(int pos) {
  if (_file == NULL) return -1;

  return fseek(_file, pos, SEEK_SET);
}

bool zFile::is_eof(void) const {
  return (feof(_file) != 0);
}


bool zFile::get_error(void) const {
  // TODO: Convert error!
  return (ferror(_file) != 0);
}


void zFile::close(void) {
  if (_file == NULL) return;
  ::fclose(_file);
  _file = NULL;
}


zString zFile::get_current_directory(void) {
  char buf[1024];
#if defined(WIN32)
  // Remarks: The GetCurrentDirectroy should not used in a multi-threaded program.
  int result = GetCurrentDirectoryA(sizeof(buf), buf);
  if (result <= 0) {
    // Failed get the current directory.
  }
  else if (result > sizeof(buf)) {
    // The path of current directory is longer of buf. 
    char* pBuf = (char*)malloc(sizeof(char) * result);
    int result2 = GetCurrentDirectoryA(sizeof(char) * result, pBuf);
    zString currentDir(pBuf, sizeof(char) * result);       
    // Should never happen.
    assert(result == result2);
    free(pBuf);
    return currentDir;
  }
  else {
    return zString(buf, sizeof(char) * result);
  }
#else
  char* path = getcwd(buf, sizeof(buf));
  int buff_size = 1024 * 64;
  while (path == NULL && errno == ERANGE) {
    // Ok, buffer is to small. Try with a bigger one.
    char* pbuff = (char*)malloc(buff_size);
    path = getcwd(pbuff, buff_size);
    free(pbuff);
    buff_size *= 2;
  }
  // If path is NULL an empty string is returned.
  return zString(path);
#endif
  return zString();
}


bool zFile::remove(zString const& path) {
  // TODO: Linux should use the C++ conformant unlink function. Check this.
  int res = unlink(path.get_buffer());
  return res == 0;
}

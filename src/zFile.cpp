/******************************************************************************
 * Copyright 2009-2011 Matteo Valdina
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "zFile.h"


zFile::zFile(FILE* file, zString const& path) : zObject() {
  _file = file;
  _path = path;
}


zFile::~zFile(void) {
  close();
}

zFile* zFile::open(zString const& path, OpenMode mode) {
  char const* fmode;
  if (mode == OPEN_MODE_READ) {
    fmode = "r";
  }
  if (mode == OPEN_MODE_WRITE) {
    fmode = "w";
  }
  if (mode == OPEN_MODE_READ_WRITE) {
    fmode = "rw";
  }
  if (mode == OPEN_MODE_APPEND) {
    fmode = "a";
  }

  FILE* fd = fopen(path.get_buffer(), fmode);
  if (fd != NULL) {
    return new zFile(fd, path);
  }
  return NULL;
}


int zFile::readBytes(unsigned char* buffer, int bufferSize) {
  if (buffer == NULL) return -1;
  if (bufferSize < 0) return -1;
  if (_file == NULL) return -1;

  return fread(buffer, 1, bufferSize, _file);
}


int zFile::writeBytes(unsigned char* buffer, int bufferSize) {
  if (buffer == NULL) return -1;
  if (bufferSize < 0) return -1;
  if (_file == NULL) return -1;

  return fwrite(buffer, 1, bufferSize, _file);
}


bool zFile::isEOF(void) const {
  return (feof(_file) != 0);
}


bool zFile::isError(void) const {
  return (ferror(_file) != 0);
}


void zFile::close(void) {
  if (_file == NULL) return;
  ::fclose(_file);
  _file = NULL;
}

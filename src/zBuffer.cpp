/******************************************************************************
 * Copyright 2009 Matteo Valdina
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

#include "zBuffer.h"

#include <stdlib.h>

zBuffer::zBuffer(void) : zObject() {
  buffer_ = NULL;
  size_ = 0;
}

zBuffer::zBuffer(int size) : zObject() {
  buffer_ = (unsigned char*)malloc(sizeof(unsigned char) * size);
  size_ = size;
}


zBuffer::~zBuffer(void) {
  // Clean up memory, because this buffer can contains some sensible data.
  memset(buffer_, 0x00, size_);
  free(buffer_);
}


void zBuffer::resize(int size) {
  buffer_ = (unsigned char*)realloc(buffer_, (sizeof(unsigned char) * size));
  size_ = size;
}

bool zBuffer::append(unsigned char const* buffer, int bufferSize) {
  if (bufferSize < 0) return false;
  if (buffer == NULL) return false;

  int curSize = getSize();
  resize(curSize + bufferSize);

  memcpy(buffer_ + curSize, buffer, bufferSize);

  return true;
}


bool zBuffer::appendPascalString(zString const& str) {

  int len = str.getLength();
  append((unsigned char*)&len, 4);
  append((unsigned char*)str.getBuffer(), len);

  return false;
}

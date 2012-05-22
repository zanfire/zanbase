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
#include <string.h>

zBuffer::zBuffer(void) : zObject() {
  _buffer = NULL;
  _size = 0;
}

zBuffer::zBuffer(int size) : zObject() {
  _buffer = (unsigned char*)malloc(sizeof(unsigned char) * size);
  _size = size;
}


zBuffer::~zBuffer(void) {
  // Clean up memory, because this buffer can contains some sensible data.
  memset(_buffer, 0x00, _size);
  free(_buffer);
}


void zBuffer::resize(int size) {
  _buffer = (unsigned char*)realloc(_buffer, (sizeof(unsigned char) * size));
  _size = size;
}


bool zBuffer::append(unsigned char const* buffer, int bufferSize) {
  if (bufferSize < 0) return false;
  if (buffer == NULL) return false;

  int curSize = _size;
  resize(curSize + bufferSize);

  memcpy(_buffer + curSize, buffer, bufferSize);

  return true;
}


bool zBuffer::append(zString const* str, zString::StoreFormat format) {
  if (format == zString::PASCAL) {
    int len = str->getLength();
    append((unsigned char*)&len, 4);
    append((unsigned char*)str->getBuffer(), len);
  }
  else {
    // TODO: Ugly hack to copy the term char of str.
    append((unsigned char*)str->getBuffer(), str->getLength() + 1);
  }
  return true;
}


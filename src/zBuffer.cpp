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

#include <stdio.h>

zBuffer::zBuffer(void) : zObject() {
  _buffer = NULL;
  _size = 0;
  _next = NULL;
}

zBuffer::zBuffer(int size) : zObject() {
  if (size > 0) {
    _buffer = (unsigned char*)malloc(sizeof(unsigned char) * size);
    _size = size;
  }
  else {
    _buffer = NULL;
    _size = 0;
  }
}


zBuffer::~zBuffer(void) {
  if (_buffer != NULL) free(_buffer);
  _buffer = NULL;
}


void zBuffer::resize(int size) {
  if (size > 0) {
    _buffer = (unsigned char*)realloc(_buffer, (sizeof(unsigned char) * size));
    _size = size;
  }
  else {
    if (_buffer != NULL) {
      free(_buffer);
      _buffer = NULL;
    }
    _size = 0;
  }
}


bool zBuffer::append(unsigned char const* buffer, int size) {
  if (size <= 0) return false;
  if (buffer == NULL) return false;

  int cur_size = _size;
  resize(cur_size + size);
  memcpy(_buffer + cur_size, buffer, size);
  return true;
}

/*
bool zBuffer::append(zString const* str, zString::StoreFormat format) {
  if (format == zString::PASCAL) {
    int len = str->get_length();
    append((unsigned char*)&len, 4);
    append((unsigned char*)str->get_buffer(), len);
  }
  else {
    // TODO: Ugly hack to copy the term char of str.
    append((unsigned char*)str->get_buffer(), str->get_length() + 1);
  }
  return true;
}
*/

bool zBuffer::set(uint8_t value) {
  if (_size < 0) return false;
  if (_buffer == NULL) return false;

  memset(_buffer, value, _size);
  return true;
}


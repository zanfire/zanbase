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

#include "zString.h"

#include "zStringBuilder.h"
#include "zBuffer.h"
#include "zArray.h"

#include <string.h>
#include <stddef.h>
#include <ctype.h>
// Why?
#include <arpa/inet.h>


zString::zString(void) {
  init(NULL, 0);
}


zString::zString(zString* str) {
  if (str != NULL) {
    init(str->get_buffer(), str->get_length());
  } 
  else {
    init(NULL, 0);
  }
}


zString::zString(char c) {
  init((char const*)&c, 1);
}


zString::zString(char const* str) {
  int len = str != NULL ? strlen(str) : 0;
  init(str, len);
}


zString::zString(char const* str, int length) {
  init(str, length);
}


zString::zString(zStringBuilder const* strb) {
  if (strb != NULL) {
    char* targetBuffer = NULL;
    if (strb->get_length() <= ZSTRING_STATIC_BUFFER_SIZE) {
      targetBuffer = (char*)&_staticBuffer;
      _dynamicBuffer = NULL;
    } 
    else {
      _dynamicBuffer = new zBuffer(strb->get_length() + 1);
      targetBuffer = (char*)_dynamicBuffer->get_buffer();
      _staticBuffer[0] = 0x00;
    }

    int readBytes = 0;
    const zArray<zString*>* strings = &strb->_strings;
    for (int i = 0; i < strings->get_count(); i++) {
      zString* str = NULL;
      if (strings->get(i, &str)) {
        memcpy(targetBuffer + readBytes, str->get_buffer(), str->get_length());
        readBytes +=  str->get_length();
      }
    }
    targetBuffer[readBytes] = 0x00;
    _length =  strb->get_length();
  }
  else {
    init(NULL, 0);
  }
}


zString::zString(zBuffer* buffer) {
  if (buffer != NULL) {
    // NOTE: The length is double checked in the init method.
    init((char const*)buffer->get_buffer(), buffer->get_size());
  }
  else {
    init(NULL, 0);
  }
}
  

zString::zString(const zString& str) {
  copy_from(str);
}


zString::~zString(void) {
  if (_dynamicBuffer != NULL) {
    _dynamicBuffer->release_reference();
  }
}


void zString::init(char const* str, int length) {
  if (str != NULL) {
    length = strnlen(str, length);
    if (str == NULL) {
      _staticBuffer[0] = 0x00;
      _dynamicBuffer = NULL;
    } 
    else if (length <= ZSTRING_STATIC_BUFFER_SIZE) {
      memcpy(_staticBuffer, str, length);
      _staticBuffer[length] = 0x00;
      _dynamicBuffer = NULL;
    } 
    else {
      _dynamicBuffer = new zBuffer(length + 1);
      memcpy(_dynamicBuffer->get_buffer(), str, length);
      _dynamicBuffer->get_buffer()[length] = 0x00;
      _staticBuffer[0] = '\0';
    }
    _length = length;
  }
  else {
    _staticBuffer[0] = '\0';
    _dynamicBuffer = NULL;
    _length = 0;
  }
}


zString& zString::operator=(const zString& rhs) {
  if (this != &rhs) {
    copy_from(rhs);
  }

  return *this;
}

bool zString::equals(zString const& str) const {
  return compare(str) == 0;
}


int zString::compare(zString const& str) const {
  return strcmp(get_buffer(), str.get_buffer());
}

  
char* zString::get_buffer(void) const {
  if (_dynamicBuffer != NULL) {
    return (char*)_dynamicBuffer->get_buffer();
  }
  else {
    return (char*)&_staticBuffer;
  }
}


void zString::copy_from(const zString& str) {
  _length = str._length;
  if(str._dynamicBuffer != NULL) {
    _dynamicBuffer = str._dynamicBuffer;
    _dynamicBuffer->acquire_reference();
  }
  else {
    _dynamicBuffer = NULL;
    memcpy(_staticBuffer, str._staticBuffer, _length);
    _staticBuffer[_length] = 0x00;
  }
}


zString zString::substrig(int startPos, int length) const {
  if (startPos < 0 || startPos > get_length()) return zString();
  if (length < 0 || (startPos + length) > get_length()) return zString();
  return zString(get_buffer() + startPos, length);
}


int zString::index_of(zString& str, int startPos) const {
  char* buffer = get_buffer();
  int l = str.get_length();
  char* strBuf = str.get_buffer();
  for (int i = startPos; i < _length; i += l) {
    // Check size
    if ((_length - i) > l) {
      if (memcmp(buffer + i, strBuf, l) == 0) {
        return i;
      }
    }
  }
  return -1;
}


int zString::last_index_of(zString& str, int endPos) const {
  char* buffer = get_buffer();
  for (int i = get_length() - str.get_length(); i >= endPos; i--) {
    if (memcmp(buffer + i, str.get_buffer(), str.get_length()) == 0) {
      return i;
    }
  }
  return -1;
}


zString zString::to_lowercase(void) const {
  zString str(get_buffer(), get_length());
  char* dst = str.get_buffer();
  char* src = dst;
  for (int i = 0; i < str.get_length(); i++) {
    dst[i] = tolower(src[i]);
  }
  return str;
}


zString zString::to_uppercase(void) const {
  zString str(get_buffer(), get_length());
  char* dst = str.get_buffer();
  char* src = dst;
  for (int i = 0; i < str.get_length(); i++) {
    dst[i] = toupper(src[i]);
  }
  return str;
}


bool zString::is_num(void) const {
  if (get_length() == 0) return false;

  char* str = get_buffer();
  for (int i = 0; i < get_length(); i++) {
    if(!isdigit(str[i])) {
      return false;
    }
  }

  return true;
}


int zString::to_int(void) const {
  if (get_length() == 0 || !is_num()) return 0;
  return atoi(get_buffer());
}


zString zString::from_pascal_string(unsigned char const* pascalString, int bufferSize, bool isInNetworkByteOrder) {
  if (bufferSize < 4) return zString();
  uint32_t length = ((uint32_t*)pascalString)[0];
  length = isInNetworkByteOrder ? ntohl(length) : length;
  if (bufferSize < (int)(length + 4)) return zString();
  return zString((char*)(pascalString + 4), length);
}


/******************************************************************************
 * Copyright 2009 - 2012 Matteo Valdina
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

#ifndef ZBUFFER_H__
#define ZBUFFER_H__

#include "zCommon.h"
#include "zObject.h"
#include "zString.h"
 
/// A buffer wrapper that provides a reference system.
/// NOTE: This class provides a pointer to other instance of zBuffer. ???
/// NOTE: This class is not thread-safe.
/// 
/// @author Matteo Valdina
class zBuffer : public zObject {
protected:
  uint8_t* _buffer;
  int _size;
  zBuffer* _next;
public:
  zBuffer(int size);

  /// Return the pointer to the allocated buffer
  uint8_t* get_buffer(void) const { return _buffer; }
  
  /// Get size of the buffer.
  int get_size(void) const { return _size; }

  /// Resize the buffer
  void resize(int size);

  /// Set a value for each byte in the buffer.
  bool set(uint8_t value);

  bool append(uint8_t const* buffer, int size);
  /// Append a zString in the buffer.
  bool append(zString const* str, zString::StoreFormat store);

  void set_next(zBuffer* b) { _next = b; }
  zBuffer* get_next(void) { return _next; }
protected:
  zBuffer(void);
  virtual ~zBuffer(void);
};


#endif // ZBUFFER_H__


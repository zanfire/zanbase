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

#ifndef ZSTRING_H__
#define ZSTRING_H__

#include "zCommon.h"
#include "zObject.h"


#define ZSTRING_STATIC_BUFFER_SIZE 512

class zBuffer;
class zStringBuilder;

/// Immutable String
/// @author Matteo Valdina
class zString {

public:
  enum StoreFormat {
    C,
    PASCAL
  };

private:
  char _staticBuffer[ZSTRING_STATIC_BUFFER_SIZE];
  zBuffer* _dynamicBuffer;
  int _length;

public:
  /// Ctor
  zString(void);
  zString(zBuffer* buffer);
  zString(zStringBuilder const* strb);
  zString(zString* str);
  zString(char c);
  zString(char const* str);
  zString(char const* str, int length);
  /// Dtor
  virtual ~zString(void);

  /// Copy constructors.
  zString(const zString& obj);
  zString& operator=(const zString& rhs);

  zString substrig(int startPos, int length) const;
  int index_of(zString& str, int startPos) const;
  int last_index_of(zString& str, int endPos) const;

  /// Converts string to lowercase.
  zString to_lowercase(void) const;
  /// Converts string to uppercase.
  zString to_uppercase(void) const;

  /// Returns true if string is a number.
  bool is_num(void) const;
  int to_int(void) const;

  bool equals(zString const& str) const;
  int compare(zString const& str) const;
  
  char* get_buffer(void) const;
  int get_length(void) const { return _length; }

  static zString from_pascal_string(unsigned char const* pascalString, int bufferSize, bool isInNetworkByteOrder = false);

protected:  
  void init(char const* str, int length);
  void copy_from(const zString& str);
};

#endif // ZSTRING_H__


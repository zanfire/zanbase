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
#include "zArray.h"

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
  zString& operator=(char const* rhs);

  /// Returns the substring starting from startPos and with the given length.
  /// if arguments are invalid it returns an empty string.
  /// startPos is less than 0 it will be traited as 0
  /// length greater than string length will be capped to the string length.
  zString substring(int startPos, int length) const;

  /// Returns the fist index of given string.
  /// If string is missing or arguments are invalid it returns -1.
  /// If str is empty, it returns -1.
  /// If startPos is less than 0 it will be traited as 0.
  /// If startPos eis greater than string length it returns -1.
  int index_of(zString const& str, int startPos) const;
  
  /// Returns last index of given string.
  /// If string is missing or aguments are invalid it returns -1.
  /// If str is empty, returns -1.
  /// If endPos is greater than string it will the cap to string length.
  int last_index_of(zString const& str, int endPos) const;

  /// Converts string to lowercase.
  zString to_lowercase(void) const;
  
  /// Converts string to uppercase.
  zString to_uppercase(void) const;
  
  /// Returns true if string is a positive number.
  /// NOTES: Spaces ae not valid.
  bool is_num(void) const;
  
  /// Convert the string value to an integer if it is numeric otherwise returns 0.
  int to_int(void) const;

  /// Convert the string value to the hex form.
  zString to_hex(void);

  /// Returns true if string is equals to the given one.
  bool equals(zString const& str) const;

  /// Compare a string with the given one.
  /// @return 0 if equals, -1 if less or 1 if greater. 
  int compare(zString const& str) const;

  bool is_empty(void) const { return _length == 0; }

  zArray<zString> split(zString const& tokeinze, bool ignore_empty_token) const;
  
  char* get_buffer(void) const;
  int get_length(void) const { return _length; }

  /// Create a string from a pascal format string.
  // MOVE to constructor?
  static zString from_pascal_string(unsigned char const* pascalString, int bufferSize, bool isInNetworkByteOrder = false);

protected:  
  void init(char const* str, int length);
  void copy_from(const zString& str);
};

#endif // ZSTRING_H__


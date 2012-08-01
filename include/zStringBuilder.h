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

#ifndef ZSTRINGBUILDER_H__
#define ZSTRINGBUILDER_H__

#include "zString.h"
#include "zArray.h"

/// A string builder.
/// This class is implemented with an array of string.
/// Disadvantage: memory fragmentation? It is a problem but some trick can 
/// be implemented in the zStringBuilder to avoid this problem.
///
/// @author Matteo Valdina
class zStringBuilder {
  // zString can build a string from the content of zStringBuilder
  //
  friend class zString;

protected:
  zArray<zString*> _strings;

public:
  zStringBuilder(void);
  virtual ~zStringBuilder(void);

  int get_length(void) const;

  void append(zString const& str);
  void append(char const* str);
  void append(char const* str, int len);
  void append(char c);
  void append(short c);
  //void append(unsigned short c);
  void append(int c);
  void append(unsigned int c);
  //void append(long c);
  //void append(unsigned long c);
  // Append formattted.
  void appendf(char const* format, ...);

  zString to_string(void) const;
};

#endif // ZSTRINGBUILDER_H__


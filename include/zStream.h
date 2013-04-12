/******************************************************************************
 * Copyright 2012 Matteo Valdina
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

#ifndef ZSTREAM_H__
#define ZSTREAM_H__

#include "zCommon.h"

/// Interface for read/write operation on a stream.
class zStream {
public:
  enum Error {
    NOT_SUPPORTED = -1,
    INTERNAL_ERROR = -2
  };

public:
  zStream(void) {}
  virtual ~zStream(void) {}
  
  /// Read operation.
  /// Returns the the number of bytes readed or an error code from the enum Error.
  virtual int read(unsigned char* buffer, int size) { return NOT_SUPPORTED; };
  /// Write operation.
  /// Retruns the number of bytes written or an error code from the enum Error.
  virtual int write(unsigned char* buffer, int size) { return NOT_SUPPORTED; };
  /// Seek operation.
  /// 
  virtual int seek(int position) { return NOT_SUPPORTED; }
  //virtual int get_current_pos(void) { return NOT_SUPPORTED; }

  virtual bool is_readable(void) const { return false; }
  virtual bool is_writeable(void) const { return false; }
  virtual bool is_seekable(void) const { return false; }
};

#endif // ZSTREAM_H__


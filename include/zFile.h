/******************************************************************************
 * Copyright 2011 Matteo Valdina
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

#ifndef ZFILE_H__
#define ZFILE_H__

#include "zCommon.h"
#include "zObject.h"
#include "zString.h"
#include "zStream.h"

// For FILE.
#include <stdio.h>

/// This class needs refactoring name.
class zFile : public zStream, public zObject {
public:
  enum Flag {
    FLAG_READ          = 0x01,
    FLAG_WRITE         = 0x02,
    FLAG_APPEND        = 0x04
//  APPEND
//  EXCLUSIVE
//  ??
  };

protected:
  // TODO: Abstract FILE handle.
  FILE* _file;
  zString _path;

public:
  // This strategy is quite simple for the common use (open/create a file in RW).
  // But it is sufficent?
  static zFile* create(zString const& path);
  static zFile* open(zString const& path);
  static zFile* append(zString const& path);

  //
  // zStream implementation.
  //
  int read(unsigned char* buffer, int size);
  int write(unsigned char* buffer, int size);
  int seek(int pos);

  //
  // zFile stuff.
  //

  bool is_eof(void) const;
  bool get_error(void) const;

  /// Flush write cache.
  void flush(void);
  /// Close file and release al internal resources.
  void close(void);

  /// Returns the current directory.
  static zString get_current_directory(void);

  static bool exists(zString const& path);

  /// Remove a file from the FS.
  /// Returns true if file/directory is removed.
  static bool remove(zString const& path);

protected:
  zFile(FILE* fd, zString const& file);
  virtual ~zFile(void);
};


#endif // ZLOGGER_H__

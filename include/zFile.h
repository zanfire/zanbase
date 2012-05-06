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

#include "global.h"
#include "zObject.h"
#include "zString.h"

#include <stdio.h>

/**
 */
class zFile : public zObject {
public:
  enum OpenMode {
    OPEN_MODE_READ          = 0x01,
    OPEN_MODE_WRITE         = 0x02,
    OPEN_MODE_APPEND        = 0x04,
    OPEN_MODE_READ_WRITE    = 0x08
  };

protected:
  FILE* _file;
  zString _path;

public:
  static zFile* open(zString const& path, OpenMode mode);

  int readBytes(unsigned char* buffer, int bufferSize);
  int writeBytes(unsigned char* buffer, int bufferSize);

  bool isEOF(void) const;
  bool isError(void) const;

  void close(void);

protected:
  zFile(FILE* fd, zString const& file);
  virtual ~zFile(void);
};


#endif // ZLOGGER_H__

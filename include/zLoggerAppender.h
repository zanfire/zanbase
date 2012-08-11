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

#ifndef ZLOGGERAPPENDER_H__
#define ZLOGGERAPPENDER_H__

#include "zObject.h"

/// Interface for an logger appender.
/// The implementer of this interface must provides the impl of:
///  void line(char const* line),
/// @author Matteo Valdina
class zLoggerAppender : public zObject {

public:
  zLoggerAppender(void);

  /// The implementor must write as a log line the line argument.
  virtual void line(char const* line) = 0;

protected:
  virtual ~zLoggerAppender(void);
};


#endif // ZLOGGERAPPENDER_H__


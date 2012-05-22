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

#ifndef ZLOGGERAPPENDERCONSOLE_H__
#define ZLOGGERAPPENDERCONSOLE_H__

#include "zLoggerAppender.h"


/// Implementation of zLoggerAppender that write in the
/// console.
/// 
/// @author Matteo Valdina
class zLoggerAppenderConsole : public zLoggerAppender {

public:
  zLoggerAppenderConsole(void);
  virtual ~zLoggerAppenderConsole(void);

  virtual void line(char* line);
};


#endif // ZLOGGERAPPENDERCONSOLE_H__


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

#ifndef ZCONSOLE_H__
#define ZCONSOLE_H__

#include "zCommon.h"
 
/// This class provides a cross-platform facility for the console access.
/// This class does't substitute the system printf syscall but provides a set of static methods to do:
///  - Set console colors
/// 
/// @author Matteo Valdina
class zConsole {
public:

  enum FgColor {
#if defined(WIN32)
    FG_COLOR_BLUE  = FOREGROUND_BLUE,
    FG_COLOR_RED   = FOREGROUND_RED,
    FG_COLOR_GREEN = FOREGROUND_GREEN
#else
    FG_COLOR_BLUE  = 30, // TODO: Untested!!!
    FG_COLOR_RED   = 31,
    FG_COLOR_GREEN = 32
#endif
  };

public:

  static void setColor(FgColor fg);
  static void clearColor(void);
  
protected:
  zConsole(void);
  virtual ~zConsole(void);
};


#endif // ZCONSOLE_H__


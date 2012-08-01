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

#ifndef ZLOGGER_H__
#define ZLOGGER_H__

#include "zString.h"
#include "zArray.h"

#include <stdarg.h>
#include <string.h>
#include <errno.h>

class zLoggerAppender;

/// This class provides the logging facility.
/// 
/// @author Matteo Valdina
class zLogger {

public:
  /// Enum of possible logging level.
  enum LogLevel {
    LOG_LEVEL_NONE      = 0x00,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
  };

protected:
  zString _id;
  zArray<zLoggerAppender*> _appenders;
  LogLevel _level;

public:
  static zLogger* get_logger(char const* id);

  void set_level(LogLevel level) { _level = level; }
  void add_appender(zLoggerAppender* appender);

  void fatal(char const* format, ...);
  void error(char const* format, ...);
  void warn(char const* format, ...);
  void info(char const* format, ...);
  void debug(char const* format, ...);
  // Log
  void log(LogLevel level, char const* format, va_list args);
  void log(LogLevel level, char const* format, ...);

protected:
  /// 
  zLogger(char const* loggerName);
  virtual ~zLogger(void);

  /// Load a configuration from file.
  void load_config(void);
};


#endif // ZLOGGER_H__


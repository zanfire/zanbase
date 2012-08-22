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

#include "zCommon.h"

#include "zObject.h"
#include "zString.h"
#include "zArray.h"


#include <stdarg.h>

class zLoggerAppender;

/// This class provides the logging facility.
/// 
/// @author Matteo Valdina
class zLogger : public zObject {

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
  /// Get an instance of logger by id.
  static zLogger* get_logger(char const* id);

  /// Shutdown the logger facility.
  static void shutdown(void);

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


  static void log(LogLevel level, char const* file, int line, char const* format, va_list args);
  static void log(LogLevel level, char const* file, int line, char const* format, ...);

protected:
  /// 
  zLogger(char const* loggerName);
  virtual ~zLogger(void);

  /// Load a configuration from file.
  void load_config(void);
};

// Useful macro.

#if defined(LOGGING_ENABLED) 
# define LOG_FATAL(format, ...)    zLogger::log(zLogger::LOG_LEVEL_FATAL, __FILE__, __LINE__, format, __VA_ARGS___)
# define LOG_ERROR(format, ...)    zLogger::log(zLogger::LOG_LEVEL_WARN, __FILE__, __LINE__, format, __VA_ARGS__)
# define LOG_WARNING(format, ...)  zLogger::log(zLogger::LOG_LEVEL_WARN, __FILE__, __LINE__, format, __VA_ARGS__)
# define LOG_INFO(format, ...)     zLogger::log(zLogger::LOG_LEVEL_INFO, __FILE__, __LINE__, format, __VA_ARGS__)
# define LOG_DEBUG(format, ...)    zLogger::log(zLogger::LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, __VA_ARGS__)
#else 
# define LOG_FATAL(format, ...)
# define LOG_ERROR(format, ...)
# define LOG_WARNING(format, ...)
# define LOG_INFO(format, ...)
# define LOG_DEBUG(format, ...)
#endif

#endif // ZLOGGER_H__


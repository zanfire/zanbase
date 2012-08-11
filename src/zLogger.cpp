#include "zLogger.h"

#include <stdio.h>


#include "zLoggerAppenderConsole.h"

// TODO: Replace array with an hash table.
static zArray<zLogger*>* g_loggers = new zArray<zLogger*>(YES, 32, NULL);

zLogger::zLogger(char const* loggerName) : zObject(), _appenders(YES, 32, NULL) {
  _id = zString(loggerName);
  _level = LOG_LEVEL_INFO;
}


zLogger::~zLogger(void) {
  while(_appenders.get_count() > 0) {
    zLoggerAppender* appender = 0;
    _appenders.remove(_appenders.get_count() - 1, &appender);
    appender->release_reference();
  }
}


zLogger* zLogger::get_logger(char const* id) {
  if (g_loggers == NULL) return NULL;
  g_loggers->lock();
  for (int i = 0; i < g_loggers->get_count(); i++) {
    zLogger* logger = NULL;
    g_loggers->get(i, &logger);
    if (logger != NULL) {
      if (logger->_id.equals(id)) {
        logger->acquire_reference();
        return logger;
      }
    }
  }
  zLogger* logger = new zLogger(id);
  zLoggerAppender* appender = new zLoggerAppenderConsole();
  logger->add_appender(appender);
  appender->release_reference();
  g_loggers->append(logger);
  g_loggers->unlock();

  logger->acquire_reference();
  return logger;
}


void zLogger::shutdown(void) {
  if (g_loggers == NULL) return;
  g_loggers->lock();

  while (g_loggers->get_count() > 0) {
    zLogger* logger = NULL;
    g_loggers->remove(0, &logger);
    if (logger != NULL) {
      logger->release_reference();
    }
  }
  g_loggers->unlock();

  delete g_loggers;
  g_loggers = NULL;
}


void zLogger::add_appender(zLoggerAppender* appender) {
  if (appender == NULL) return;
  appender->acquire_reference();
  _appenders.append(appender);
}


void zLogger::fatal(char const* format, ...) {
  va_list args;
  va_start(args, format);
  log(LOG_LEVEL_FATAL, format, args);
  va_end(args);
}


void zLogger::error(char const* format, ...) {
  va_list args;
  va_start(args, format);
  log(LOG_LEVEL_ERROR, format, args);
  va_end(args);
}


void zLogger::warn(char const* format, ...) {
  va_list args;
  va_start(args, format);
  log(LOG_LEVEL_WARN, format, args);
  va_end(args);
}


void zLogger::info(char const* format, ...) {
  va_list ap;
  va_start(ap, format);
  log(LOG_LEVEL_INFO, format, ap);
  va_end(ap);
}


void zLogger::debug(char const* format, ...) {
  va_list args;
  va_start(args, format);
  log(LOG_LEVEL_DEBUG, format, args);
  va_end(args);
}


void zLogger::log(LogLevel level, char const* format, ...) {
  va_list args;
  va_start(args, format);
  log(level, format, args);
  va_end(args);
}

void zLogger::log(LogLevel level, char const* format, va_list args) {
  if (level < _level) return;
  //
  char line[1024 * 4];
  line[0] = '\n';

  vsnprintf(line, sizeof(line), format, args);

  for (int i = 0; i < _appenders.get_count(); i++) {
    zLoggerAppender* appender = NULL;
    _appenders.get(i,  &appender);
    if (appender != NULL) {
      appender->line(line);
    }
  }
}

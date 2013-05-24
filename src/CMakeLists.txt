# Build zanbase library.
#

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${zanbase_BINARY_DIR})

add_library(zanbase STATIC
  zObject.cpp
  zReference.cpp
  zTester.cpp
  zLogger.cpp
  zLoggerAppender.cpp
  zLoggerAppenderConsole.cpp
  zMutex.cpp
  zScopeMutex.cpp
  zBuffer.cpp
  zString.cpp
  zStringBuilder.cpp
  zEvent.cpp
  zThread.cpp
  zFile.cpp
  zRandom.cpp
  zGetOpt.cpp
  zConsole.cpp
  zStringTokenizer.cpp
)

install (TARGETS zanbase DESTINATION lib)



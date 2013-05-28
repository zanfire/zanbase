# Build zanbase library.
#

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${zanbase_BINARY_DIR})

add_library(zanbase STATIC
  base/zObject.cpp
  base/zReference.cpp
  base/zTester.cpp
  base/zLogger.cpp
  base/zLoggerAppender.cpp
  base/zLoggerAppenderConsole.cpp
  base/zMutex.cpp
  base/zScopeMutex.cpp
  base/zBuffer.cpp
  base/zString.cpp
  base/zStringBuilder.cpp
  base/zEvent.cpp
  base/zThread.cpp
  base/zFile.cpp
  base/zRandom.cpp
  base/zGetOpt.cpp
  base/zConsole.cpp
  base/zStringTokenizer.cpp
)



AUX_SOURCE_DIRECTORY(net zanbase_net_SOURCES)
add_library(zannet STATIC ${zanbase_net_SOURCES})



install (TARGETS zanbase DESTINATION lib)
install (TARGETS zannet DESTINATION lib)


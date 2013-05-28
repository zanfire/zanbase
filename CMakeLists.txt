# Author: Matteo Valdina

#
# 
#
cmake_minimum_required(VERSION 2.8)
project(zanbase)

# CMake modules.
include(CheckIncludeFiles)
include(CheckLibraryExists)

# Testing requirements.
enable_testing()
include(Dart)

set(zanbase_VERSION_MAJOR 1)
set(zanbase_VERSION_MINOR 0)
set(zanbase_VERSION_PATCH 0)

#
# Required modules.
#
find_package(Threads REQUIRED)

check_include_files(pthread.h HAVE_PTHREAD_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(arpa/inet.h HAVE_ARPA_INET_H)
check_include_files(arpa/inet.h HAVE_UNISTD_H)
check_include_files(netinet/in.h HAVE_NETINET_IN_H)
check_include_files(sys/socket.h HAVE_SYS_SOCKET_H)



#
# Optional modules.
#
option(ENABLED_DMALLOC "Enable DMALLOC integration." OFF)
if(ENABLED_DMALLOC)
  check_include_files(dmalloc.h HAVE_DMALLOC_H)
  check_library_exists(dmallocthcxx malloc "" HAVE_LIBDMALLOCTHCXX)
endif(ENABLED_DMALLOC)

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")


set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-gdbb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Subproject
add_subdirectory(src)
add_subdirectory(tests)


# Install
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include/zanbase)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include/zanbase FILES_MATCHING PATTERN "*.h")


add_test (NAME TestOne COMMAND tests/tests_runner)

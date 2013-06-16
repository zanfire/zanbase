# Build file for zanbase project.
# Author: Matteo Valdina

cmake_minimum_required(VERSION 2.8)
project(zanbase)

#
# Check supported OS.
#
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(OS_LINUX true)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(OS_WIN32 true)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if(NOT OS_LINUX AND NOT OS_WIN32)
  message(FATAL_ERROR "Unsupported build platform.")
endif(NOT OS_LINUX AND NOT OS_WIN32)

# CMake modules.
include(CheckIncludeFiles)
include(CheckLibraryExists)

# Testing requirements.
enable_testing()
include(Dart)

# Version.
set(zanbase_VERSION_MAJOR 1)
set(zanbase_VERSION_MINOR 0)
set(zanbase_VERSION_PATCH 0)
# TODO: Fill with SVN/Git revision.
set(zanbase_VERSION_REVISION None)

# Tracing
set(CMAKE_VERBOSE_MAKEFILE OFF)

option(ENABLED_FUNC_TRACE "Enable function traceing." OFF)
if(ENABLED_FUNC_TRACE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finstrument-functions")
endif(ENABLED_FUNC_TRACE)

#
# Required modules.
#
find_package(Threads REQUIRED)

#
# Check includes.
#
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


option(ENABLED_FUNC_TRACE "Enable function traceing." OFF)
if(ENABLED_FUNC_TRACE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finstrument-functions")
endif(ENABLED_FUNC_TRACE)


configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src/base")
include_directories("${PROJECT_SOURCE_DIR}/src/net")

#
# Compiler flags
#
if(OS_LINUX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdbb3")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif(OS_LINUX)

#
# Subproject
#
add_subdirectory(src)
add_subdirectory(tests)


#
# Docs
#
option(GEN_DOC "Create and install the HTML based API documentation (requires Doxygen)" ON)
if(GEN_DOC)
  find_package(Doxygen)
  if(NOT DOXYGEN_FOUND)
    message(WARN_ERROR "Doxygen is needed to build the documentation.")
  else(NOT DOXYGEN_FOUND)
    set(doxyfile_in  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${PROJECT_BINARY_DIR}/Doxyfile)
    set(doxy_html_index_file ${CMAKE_CURRENT_BINARY_DIR}/docs/gen/html/index.html )
    set(doxy_output_root ${CMAKE_CURRENT_BINARY_DIR}/docs/gen)
    set(doxy_input ${PROJECT_SOURCE_DIR}/src)
    #set(doxy_extra_files ${CMAKE_CURRENT_SOURCE_DIR}/mainpage.dox) # Pasted into Doxyfile.in                                 

    configure_file( ${doxyfile_in} ${doxyfile} @ONLY )
    add_custom_command( OUTPUT ${doxy_html_index_file}  
	  COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile} 
      MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in} ${doxy_extra_files} COMMENT "Generating HTML documentation")
                                                 
    add_custom_target(doc ALL DEPENDS ${doxy_html_index_file} )

    install(DIRECTORY ${doxy_output_root}/html DESTINATION share/doc )
    install(DIRECTORY ${doxy_output_root}/man DESTINATION share )
  endif(NOT DOXYGEN_FOUND)
endif(GEN_DOC)
                                                                                              
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include/zanbase)
install (DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include/zanbase FILES_MATCHING PATTERN "*.h")


add_test (NAME TestOne COMMAND tests/tests_runner)

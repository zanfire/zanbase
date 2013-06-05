# Build zanbase library.
#

#if(ENABLED_FUNC_TRACE)
#  #  set(FUNC_TRACE_CXX_FLAGS "-finstrument-functions")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FUNC_TRACE_CXX_FLAGS}")
#
#endif(ENABLED_FUNC_TRACE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${zanbase_BINARY_DIR})

AUX_SOURCE_DIRECTORY(base zanbase_base_SOURCES)
add_library(zanbase STATIC ${zanbase_base_SOURCES})

AUX_SOURCE_DIRECTORY(net zanbase_net_SOURCES)
add_library(zannet STATIC ${zanbase_net_SOURCES})


install (TARGETS zanbase DESTINATION lib)
install (TARGETS zannet DESTINATION lib)


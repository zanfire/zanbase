# Test stuff.

#if(ENABLED_FUNC_TRACE)
#  #  set(FUNC_TRACE_CXX_FLAGS "-finstrument-functions")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FUNC_TRACE_CXX_FLAGS}")
#endif(ENABLED_FUNC_TRACE)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finstrument-functions")


link_directories(${zanbase_BINARY_DIR}/)
add_executable(tests_runner	
  main.cpp
  trace.c
  base/zStringTest.cpp
  base/zStrTokTest.cpp
  base/zArrayTest.cpp
  base/zThreadTest.cpp
  base/zFileTest.cpp
  base/zTestTest.cpp
  base/zGetOptTest.cpp
  base/zBufferTest.cpp
)

target_link_libraries(tests_runner zanbase)
target_link_libraries(tests_runner ${CMAKE_THREAD_LIBS_INIT} )

# Test


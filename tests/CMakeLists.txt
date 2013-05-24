# Test stuff.

link_directories(${zanbase_BINARY_DIR}/)
add_executable(tests_runner	
  main.cpp
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


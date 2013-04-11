#include_directories(${zanbase_SOURCE_DIR}/include)

link_directories(${zanbase_BINARY_DIR}/)
add_executable(tests_runner	
  main.cpp
	zStringTest.cpp
	zStrTokTest.cpp
	zArrayTest.cpp
	zThreadTest.cpp
	zFileTest.cpp
	zTestTest.cpp
	zGetOptTest.cpp
	zBufferTest.cpp
)

target_link_libraries(tests_runner zanbase)
target_link_libraries(tests_runner ${CMAKE_THREAD_LIBS_INIT} )

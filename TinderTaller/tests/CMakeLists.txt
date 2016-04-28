 #uso estandar c++11
 set (CMAKE_CXX_STANDARD 11)
ENABLE_TESTING()

SET(CMAKE_CXX_FLAGS "-g -fprofile-arcs -ftest-coverage -std=c++11")

SET(CMAKE_C_FLAGS="-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")

SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")



#includes
include_directories(/usr/local/include)
include_directories(../include)


#Library:

LINK_DIRECTORIES( ../lib/rocksdb-master/)
LINK_DIRECTORIES( ../lib/googletest/)
LINK_DIRECTORIES(../src)

#srcTests
file(GLOB_RECURSE _SOURCES_CPP_TESTS "*.cpp")

#exe
add_executable(Test ${_SOURCES_CPP_TESTS})


#Agrego el rocksdb
 TARGET_LINK_LIBRARIES(Test libtindertaller)
 TARGET_LINK_LIBRARIES(Test gtest)
 TARGET_LINK_LIBRARIES(Test gtest_main)
 TARGET_LINK_LIBRARIES(Test pthread)
 TARGET_LINK_LIBRARIES(Test rocksdb )
 TARGET_LINK_LIBRARIES(Test curl )

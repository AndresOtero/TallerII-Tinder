 #uso estandar c++11
 set (CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-g -fprofile-arcs -ftest-coverage -std=c++11")


#includes
include_directories(/usr/local/include)
include_directories(../include)


#Library:

LINK_DIRECTORIES( ../lib/rocksdb-master/)
LINK_DIRECTORIES( ../lib/googletest/)
LINK_DIRECTORIES(../src)


#exe
add_executable(Test Test.cpp)


#Agrego el rocksdb
 TARGET_LINK_LIBRARIES(Test libtindertaller)
 TARGET_LINK_LIBRARIES(Test gtest)
 TARGET_LINK_LIBRARIES(Test gtest_main)
 TARGET_LINK_LIBRARIES(Test pthread)
 TARGET_LINK_LIBRARIES(Test rocksdb )

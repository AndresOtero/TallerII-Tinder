 #uso estandar c++11
 set (CMAKE_CXX_STANDARD 11)
ENABLE_TESTING()

SET(CMAKE_CXX_FLAGS "-g -ggdb  -std=c++11")	





#includes
include_directories(/usr/local/include)
include_directories(../include)


#Library:

LINK_DIRECTORIES( ../lib/rocksdb-master/)
LINK_DIRECTORIES( ../lib/googletest/)
LINK_DIRECTORIES(../src)
LINK_DIRECTORIES(../src/Handlers)
LINK_DIRECTORIES(../src/Utils)

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
 TARGET_LINK_LIBRARIES(Test curl  )

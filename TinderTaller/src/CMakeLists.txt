 #uso estandar c++11
 set (CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-g -fprofile-arcs -ftest-coverage -std=c++11")


#includes
include_directories(/usr/local/include)
include_directories(../include)
include_directories(../lib/rocksdb-master/include)
include_directories(../lib/googletest/include/)
include_directories(../include/json/)


#Library:
LINK_DIRECTORIES( ../lib/rocksdb-master/)
LINK_DIRECTORIES( ../lib/googletest/)
LINK_DIRECTORIES( ../lib/jsoncpp-master/src/build/src/lib_json)

#Src
file(GLOB SOURCES "./*")
file(GLOB DirUtils "./Utils/*")
file(GLOB DirHandlers "./Handlers/*")

#exe
add_executable(tindertaller ${SOURCES} ${DirUtils} ${DirHandlers})
add_library(libtindertaller SHARED ${SOURCES} ${DirUtils} ${DirHandlers})

#Agrego el rocksdb
 TARGET_LINK_LIBRARIES(tindertaller -fprofile-arcs)
 TARGET_LINK_LIBRARIES(tindertaller -ftest-coverage)
TARGET_LINK_LIBRARIES(tindertaller rocksdb )
TARGET_LINK_LIBRARIES(tindertaller jsoncpp )


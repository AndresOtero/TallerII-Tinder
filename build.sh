#!/bin/sh
set -ex
#sudo apt-get install libgflags-dev
#sudo apt-get install libsnappy-dev
#sudo apt-get install zlib1g-dev
#sudo apt-get install libbz2-dev
#sudo apt-get install libpthread-stubs0-dev
cd TinderTaller
cd lib
cd rocksdb-master
make shared_lib	
cd ..
cd googletest
cmake -DBUILD_SHARED_LIBS=ON 
make
cd ..	
cd ..
mkdir -p build
cd build
cmake ../
make 
#cd tests
#./Test
#cd ..
#cd src
#./tindertaller

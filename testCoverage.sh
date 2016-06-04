lcov --directory . --zerocounters
./build.sh
./Test.sh
rm -rf testCoverage
mkdir testCoverage
cd testCoverage
lcov --directory ../TinderTaller/ --capture --output-file output.info --no-external
lcov -r output.info /TinderTaller/include/\* -o output.info
lcov -r output.info /TinderTaller/src/Utils/jsoncpp.cpp -o output.info
lcov -r output.info /TinderTaller/src/Utils/sha256.cpp -o output.info
genhtml output.info 

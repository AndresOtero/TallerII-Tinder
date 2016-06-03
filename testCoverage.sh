lcov --directory . --zerocounters
./build.sh
./Test.sh
rm -rf testCoverage
mkdir testCoverage
cd testCoverage
lcov --directory ../TinderTaller/ --capture --output-file output.info --no-external
lcov -r output.info /TinderTaller/include/\* -o output.info
genhtml output.info 

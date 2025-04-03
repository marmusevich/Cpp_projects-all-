#!/bin/bash

# set path in case script runs outside contained dir
cd "$(dirname "$0")/.."
PRJ_ROOT="$(pwd)"
BUILD_DIR="${PRJ_ROOT}/build_lin"
CONAN_CMAKE="${BUILD_DIR}/conan/cmake"
BUILD_TYPE=Debug


# for debug cmake file
#rm -r  $BUILD_DIR

mkdir $BUILD_DIR
conan install . --output-folder=$CONAN_CMAKE --build=missing --settings=build_type=$BUILD_TYPE
cmake -B $BUILD_DIR -D CMAKE_CXX_FLAGS="-g -O0 -Wall -fprofile-arcs -ftest-coverage" -D CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage" -DCMAKE_TOOLCHAIN_FILE=$CONAN_CMAKE/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build $BUILD_DIR 


#run tests
$BUILD_DIR/manager/test/ConnectionManager_tests 

#prepare report
COVERAGE_INFO=$BUILD_DIR/coverage.info
COVERAGE_REPORT=$BUILD_DIR/coverage-report/
rm -r $COVERAGE_INFO
rm -r $COVERAGE_REPORT

lcov --capture -d $BUILD_DIR -b $PRJ_ROOT --output-file $COVERAGE_INFO

#exclude/remove from report shared libs and test
lcov --remove $COVERAGE_INFO '/usr/*' "${BUILD_DIR}/vcpkg_installed/*" "${BUILD_DIR}/CMakeFiles/*" "${PRJ_ROOT}/external/*" "${PRJ_ROOT}/manager/test/*" --output-file $COVERAGE_INFO

#special case for us - remove headers from report
lcov --remove $COVERAGE_INFO '*.hpp' --output-file $COVERAGE_INFO


genhtml -t "Connection manager coverage report" $COVERAGE_INFO --output-directory $COVERAGE_REPORT

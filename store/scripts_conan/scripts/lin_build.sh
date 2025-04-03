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
cmake -B $BUILD_DIR -DCMAKE_TOOLCHAIN_FILE=$CONAN_CMAKE/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build $BUILD_DIR



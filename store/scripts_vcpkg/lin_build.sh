#!/bin/bash

# set path in case script runs outside contained dir
cd "$(dirname "$0")/.."
PRJ_ROOT="$(pwd)"
BUILD_DIR="${PRJ_ROOT}/Build"

vcpkg install

# for debug cmake file
#rm -r  $BUILD_DIR

mkdir $BUILD_DIR
cmake -B $BUILD_DIR 
cmake --build $BUILD_DIR
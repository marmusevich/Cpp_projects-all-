##############################################################################
# CMake Header and Project Settings
##############################################################################
cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(pattern_tests VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tests
  test.cpp
  decorator.cpp
  visitor.cpp
)





# target_link_libraries(tests
  # PRIVATE
    # Boost::boost
    # Boost::unit_test_framework
# )
# add_test(NAME tests  COMMAND tests  ${TEST_PARAMS})










##############################################################################
##############################################################################

# exemple

# set(TEST_NAME ndslive-utils-tests-experiments-curl)
# add_executable(${TEST_NAME})
# target_sources(${TEST_NAME}
   # PRIVATE
      # Curl.cpp
# )

# find_package(GTest CONFIG REQUIRED)
# find_package(CURL REQUIRED)
# find_package(ZLIB REQUIRED)

# enable_testing()

# target_link_libraries(${TEST_NAME}
   # PRIVATE
      # # test framework
      # GTest::gtest GTest::gmock_main GTest::gtest_main GTest::gmock
      # # tesed libraries
      # CURL::libcurl
      # ZLIB::ZLIB
      # ZserioCppRuntime
# )





##############################################################################
# Service Dependencies
##############################################################################
#find_package(zstd CONFIG REQUIRED)

#add_subdirectory(3rdparty/...)

##############################################################################

#add_library(utils STATIC
#  include/ndslive-utils/CNetworkStatistics.h
#  src/CNetworkStatistics.cpp
#)


# target_link_libraries(utils
  # PRIVATE
    # nlohmann_json::nlohmann_json
  # PUBLIC
    # Boost::filesystem
    # Boost::date_time
# )

#add_subdirectory(tests)



cmake_minimum_required(VERSION 3.0)
project(cpp-settings VERSION 0.1 LANGUAGES CXX)

message("${PROJECT_NAME} version ${PROJECT_VERSION}")
message("CMake build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic-errors")

# Google C++ unit test framework
find_package(GTest)
if(GTEST_FOUND)
    ENABLE_TESTING()
    add_subdirectory(test)
endif(GTEST_FOUND)

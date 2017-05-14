cmake_minimum_required(VERSION 3.0)
project(cpp-settings VERSION 0.1 LANGUAGES CXX)
message("${PROJECT_NAME} version ${PROJECT_VERSION}")

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory)
          and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

message("CMake build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic-errors")

# C++ ISO standard
set(CPP_ISO_STANDARD "c++11" CACHE STRING "C++ ISO standard")
message("Use ${CPP_ISO_STANDARD} ISO standard")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CPP_ISO_STANDARD}")

# Version string
configure_file (
    "${PROJECT_SOURCE_DIR}/include/BlasBooster/Utilities/Version.h.in"
    "${PROJECT_SOURCE_DIR}/include/BlasBooster/Utilities/Version.h"
)

# Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem serialization system REQUIRED)
if(Boost_FOUND)
    add_definitions(-DUSE_BOOST -DHAVE_SHARED_POINTER -DBOOST_DATE_TIME_POSIX_TIME_STD_CONFIG -DBOOST_SYSTEM_NO_DEPRECATED)
endif(Boost_FOUND)

# Unit tests
find_package(GTest)
if(GTEST_FOUND)
    ENABLE_TESTING()
    add_subdirectory(test)
endif(GTEST_FOUND)
cmake_minimum_required(VERSION 3.3)
project(GoMatrix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp GoMatrix.h GoMatrix.cpp)
add_executable(GoMatrix ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.3)
project(GoMatrix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp GoMatrix.h Contur.h helpingClasses.h Player.h GoGame.h GoMatrix.cpp Contur.cpp
        Player.cpp
        GoGame.cpp)
add_executable(GoMatrix ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.8)
project(linear-system-solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp command.hpp command.cpp)
add_executable(linear-system-solver ${SOURCE_FILES})
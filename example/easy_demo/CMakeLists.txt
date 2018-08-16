# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (easy_demo)

add_executable(easy_demo ../../src/include/signals.h main.cpp)

# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (easy_demo)

add_executable(easy_demo ../../src/include/signals.h main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
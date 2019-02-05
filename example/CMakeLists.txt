cmake_minimum_required (VERSION 3.8)

add_executable(demo easy_demo/main.cpp)

target_include_directories(demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src/)

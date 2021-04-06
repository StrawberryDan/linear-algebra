cmake_minimum_required(VERSION 3.17)
project(linear_algebra)

set(CMAKE_CXX_STANDARD 20)

add_executable(linear-algebra-test src/test.cpp)
target_include_directories(linear-algebra-test PRIVATE include)
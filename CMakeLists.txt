cmake_minimum_required(VERSION 3.20)
project(linear_algebra VERSION 1.00 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(linear-algebra)
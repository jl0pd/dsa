cmake_minimum_required(VERSION 3.12)

project(Fibonacci Heap)

set(SOURCE_EXE test.cpp)

set(SOURCE_LIB fibonacci.hpp)

add_library(fibonacci STATIC $(SOURCE_LIB))

add_executable(main $(SOURCE_EXE))

target_link_libraries(main fibonacci)

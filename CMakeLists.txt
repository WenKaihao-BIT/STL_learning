cmake_minimum_required(VERSION 3.23)
project(STL_learning)

set(CMAKE_CXX_STANDARD 14)

add_executable(STL_learning main.cpp   alloc/myalloc.h alloc/myconstruct.h alloc/__throw_bad_alloc.h)

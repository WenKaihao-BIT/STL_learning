cmake_minimum_required(VERSION 3.23)
project(STL_learning)

set(CMAKE_CXX_STANDARD 14)

include_directories(Containtor/list_containtor/include)
add_executable(STL_learning main.cpp )
add_executable(list_containtor_test Containtor/list_containtor/test.cpp)

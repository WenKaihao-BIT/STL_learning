cmake_minimum_required(VERSION 3.23)
project(STL_learning)

set(CMAKE_CXX_STANDARD 14)

add_executable(STL_learning main.cpp allocator_learn.h iter/3mylist.h iter/3mylist-iter.h iter/3mylist-iter-test.cpp iter/3find.h iter/Traits_learning.h containtor/myVector.h containtor/myVectorIterator.h)

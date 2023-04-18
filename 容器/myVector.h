//
// Created by Q on 2023/4/18.
//

#ifndef STL_LEARNING_MYVECTOR_H
#define STL_LEARNING_MYVECTOR_H
#include "iostream"
class alloc;
template<class T,class Alloc=alloc>
class myVector{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef value_type& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
};
#endif //STL_LEARNING_MYVECTOR_H

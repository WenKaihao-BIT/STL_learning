//
// Created by Q on 2023/4/12.
//

#ifndef STL_LEARNING_3FIND_H
#define STL_LEARNING_3FIND_H
#include "iostream"
#include "3mylist-iter.h"
template<class InputIterator ,class T>
InputIterator find(InputIterator first,InputIterator last,const T &value){
    while (first!=last&&*first!=value)
        ++first;
    return first;
}
#endif //STL_LEARNING_3FIND_H

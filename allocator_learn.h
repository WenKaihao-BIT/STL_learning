//
// Created by Q on 2023/4/11.
//

#ifndef STL_LEARNING_ALLOCATOR_LEARN_H
#define STL_LEARNING_ALLOCATOR_LEARN_H
#include "new.h"
/** region ## construct v1 ## */
template<class T1,class T2>
inline void construct(T1*p,const T2&value){
    new (p)T1(value);
}
/** endregion */

/** region ## destroy v1 ## */
template<class T>
inline void destroy(T* pointer){
    pointer->~T();
}
/** endregion */
#endif //STL_LEARNING_ALLOCATOR_LEARN_H

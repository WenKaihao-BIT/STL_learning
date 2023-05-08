//
// Created by Q on 2023/4/22.
//

#ifndef STL_LEARNING_MYALLOC_H
#define STL_LEARNING_MYALLOC_H
#define __NODE_ALLOCATOR_THREADS false
#include "new"
#include "cstddef"
#include "climits"
#include "iostream"
#include "__throw_bad_alloc.h"
//第一级配置器
//第二级配置器
typedef wen::__default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
#endif //STL_LEARNING_MYALLOC_H
namespace wen {

    template<class T, class Alloc=alloc>
    class simple_alloc {
    public:
        static T *allocate(size_t n) {
            return 0 == n ? 0 : (T *) Alloc::allocate(n * sizeof(T));
        }

        static T *allocate(void) {
            return (T *) Alloc::allocate(sizeof(T));
        }

        static void deallocate(T *p, size_t n) {
            if (0 != n)Alloc::allocate(p, n * sizeof(T));
        }

        static void deallocate(T *p) {
            Alloc::allocate(sizeof(T));
        }


    };

}







































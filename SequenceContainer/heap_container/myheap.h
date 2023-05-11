//
// Created by Q on 2023/5/11.
//

#include <cstddef>

#ifndef STL_LEARNING_MYHEAP_H
#define STL_LEARNING_MYHEAP_H

#endif //STL_LEARNING_MYHEAP_H
/**
 *  binary heap 是一种完全二叉树
 *  实现  heap    算法
 *  在vector尾部插入新值，将新值与父节点进行比较，其值大于父节点则交换位置
 *
 **/
/** region ## value_type 函数 ## */
namespace wen{
    template<class T>
    typename T::value_type value_type(const T& iter){
        return typename T::value_type();
    }
    template<class T>
    T value_type(T*){
        return T();
    }
    /** endregion */
    /** region ## distance_type ## */
    template<class T>
    typename T::difference_type distance_type(const T& iter){
        return typename T::difference_type();
    }
    template<class T>
    ptrdiff_t distance_type(T*){
    return ptrdiff_t();
    }
    /** endregion */

    //函数声明

    template<class RandomAccessIterator,class Distance,class T>
    inline void __push_heap_aux(RandomAccessIterator first,RandomAccessIterator last,Distance,T);

    template<class RandomAccessIterator,class Distance,class T>
    void __push_heap(RandomAccessIterator first,Distance holeIndex,Distance topIndex,T value);



    template<class RandomAccessIterator>
    inline void push_heap(RandomAccessIterator first,RandomAccessIterator last){
        __push_heap_aux(first,last, distance_type(first),value_type(first));
    }


    template<class RandomAccessIterator,class Distance,class T>
    inline void __push_heap_aux(RandomAccessIterator first,RandomAccessIterator last,Distance,T){
        __push_heap(first,Distance((last-first)-1),Distance(0),T(*(last-1)));
    }
    template<class RandomAccessIterator,class Distance,class T>
    void __push_heap(RandomAccessIterator first,Distance holeIndex,Distance topIndex,T value){
        Distance parent=(holeIndex-1)/2;
        //采用max-heap
        while (holeIndex>topIndex&&*(first+parent)<value){
//            *(first+holeIndex)
        }
    }

}
//
// Created by Q on 2023/5/11.
//



#ifndef STL_LEARNING_MYHEAP_H
#define STL_LEARNING_MYHEAP_H
#include <cstddef>
#include "iostream"
#include "../../iter/my_traits.h"
/**
 *  binary heap 是一种完全二叉树
 *  实现  heap    算法
 *  在vector尾部插入新值，将新值与父节点进行比较，其值大于父节点则交换位置
 *
 **/
    /** region ## value_type 函数 ## */
namespace wen{

    /** region ## heap-without-compare ## */
    /** region ## push_heap ## */
    //新节点已经插入到heap中
    //函数声明
    template<class RandomAccessIterator>
    inline void push_heap(RandomAccessIterator first,RandomAccessIterator last);

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
        Distance parent=(holeIndex-1)/2;//找父节点
        //采用max-heap
        while (holeIndex>topIndex&&*(first+parent)<value){
            *(first+holeIndex) = *(first+parent);
            holeIndex=parent;
            parent=(holeIndex-1)/2;
        }
        *(first+holeIndex)=value;
    }
    /** endregion */

    /** region ## pop_heap ## */
    //函数声明
    template<class RandomAccessIterator>
    inline void pop_heap(RandomAccessIterator first,RandomAccessIterator last);

    template<class RandomAccessIterator,class T>
    inline void __pop_heap_aux(RandomAccessIterator first,RandomAccessIterator last,T);

    template<class RandomAccessIterator,class Distance,class T>
    void __pop_heap(RandomAccessIterator first,RandomAccessIterator last,RandomAccessIterator result,T value,Distance);

    template<class RandomAccessIterator,class Distance,class T>
    void __adjust_heap(RandomAccessIterator first,Distance holeIndex,Distance len,T value);



    template<class RandomAccessIterator>
    inline void pop_heap(RandomAccessIterator first,RandomAccessIterator last){
        __pop_heap_aux(first,last, value_type(first));
    }
    template<class RandomAccessIterator,class T>
    inline void __pop_heap_aux(RandomAccessIterator first,RandomAccessIterator last,T){
        __pop_heap(first,last-1,last-1,T(*(last-1)), distance_type(first));
    }
    template<class RandomAccessIterator,class Distance,class T>
    void __pop_heap(RandomAccessIterator first,RandomAccessIterator last,RandomAccessIterator result,T value,Distance){
        *result=*first;
        __adjust_heap(first,Distance(0),Distance(last-first),value);
    }
    template<class RandomAccessIterator,class Distance,class T>
    void __adjust_heap(RandomAccessIterator first,Distance holeIndex,Distance len,T value){
        Distance topIndex=holeIndex;
        Distance secondChild =2*holeIndex+2;
        //如果根节点有右孩子
        while (secondChild<len){
            if(*(first+secondChild)<*(first+(secondChild-1)))
                secondChild--;
            //令子节点较大的值为新洞值
            *(first+holeIndex)=*(first+secondChild);
            holeIndex=secondChild;
            secondChild=2*holeIndex+2;
        }
        //如果根节点无右孩子
        if(secondChild==len){
            *(first+holeIndex) = *(first+(secondChild-1));
            holeIndex=secondChild-1;
        }
        __push_heap(first,holeIndex,topIndex,value);

    }

    /** endregion */

    /** region ## sort_heap ## */
    template<class RandomAccessIterator>
    void sort_heap(RandomAccessIterator first,RandomAccessIterator last){
        while (last-first>1)
            pop_heap(first,last--);


    }
    /** endregion */

    /** region ## make_heap ## */
    //函数声明
    template<class RandomAccessIterator,class T,class Distance>
    void __make_heap(RandomAccessIterator first,RandomAccessIterator last,T,Distance);




    template<class RandomAccessIterator>
    inline void make_heap(RandomAccessIterator first,RandomAccessIterator last){
        __make_heap(first,last, value_type(first), distance_type(first));
    }
    template<class RandomAccessIterator,class T,class Distance>
    void __make_heap(RandomAccessIterator first,RandomAccessIterator last,T,Distance){
        if(last-first<2) return;
        Distance len=last-first;
        Distance parent =(len-2)/2;
        while (true){
            __adjust_heap(first,parent,len,T(*(first+parent)));
            if(parent==0)return;
            parent--;
        }
    }

    /** endregion */
    /** endregion */

    /** region ## heap-with-compare ## */
    /** region ## push_heap ## */
    //新节点已经插入到heap中
    //函数声明
    template<class RandomAccessIterator,class Compare>
    inline void push_heap(RandomAccessIterator first,RandomAccessIterator last);

    template<class RandomAccessIterator,class Distance,class T,class Compare>
    inline void __push_heap_aux(RandomAccessIterator first,RandomAccessIterator last,
                                Distance,T,Compare comp);

    template<class RandomAccessIterator,class Distance,class T,class Compare >
    void __push_heap(RandomAccessIterator first,Distance holeIndex,Distance topIndex,T value,Compare comp);



    template<class RandomAccessIterator,class Compare>
    inline void push_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp){
        __push_heap_aux(first,last, distance_type(first),value_type(first),comp);
    }


    template<class RandomAccessIterator,class Distance,class T,class Compare>
    inline void __push_heap_aux(RandomAccessIterator first,RandomAccessIterator last,Distance,T,Compare comp){
        __push_heap(first,Distance((last-first)-1),Distance(0),T(*(last-1)),comp);
    }
    template<class RandomAccessIterator,class Distance,class T,class Compare>
    void __push_heap(RandomAccessIterator first,Distance holeIndex,Distance topIndex,T value,Compare comp){
        Distance parent=(holeIndex-1)/2;//找父节点
        //采用max-heap
        while (holeIndex>topIndex&&comp(*(first+parent),value)){
            *(first+holeIndex) = *(first+parent);
            holeIndex=parent;
            parent=(holeIndex-1)/2;
        }
        *(first+holeIndex)=value;
    }
    /** endregion */

    /** region ## pop_heap ## */
    //函数声明
    template<class RandomAccessIterator,class Compare>
    inline void pop_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp);

    template<class RandomAccessIterator,class T,class Compare>
    inline void __pop_heap_aux(RandomAccessIterator first,RandomAccessIterator last,T,Compare comp);

    template<class RandomAccessIterator,class Distance,class T,class Compare>
    void __pop_heap(RandomAccessIterator first,RandomAccessIterator last,RandomAccessIterator result,T value,Distance,Compare comp);

    template<class RandomAccessIterator,class Distance,class T,class Compare>
    void __adjust_heap(RandomAccessIterator first,Distance holeIndex,Distance len,T value,Compare comp);



    template<class RandomAccessIterator,class Compare>
    inline void pop_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp){
        __pop_heap_aux(first,last, value_type(first),comp);
    }
    template<class RandomAccessIterator,class T,class Compare>
    inline void __pop_heap_aux(RandomAccessIterator first,RandomAccessIterator last,T,Compare comp){
        __pop_heap(first,last-1,last-1,T(*(last-1)), distance_type(first),comp);
    }
    template<class RandomAccessIterator,class Distance,class T,class Compare>
    void __pop_heap(RandomAccessIterator first,RandomAccessIterator last,RandomAccessIterator result,T value,Distance,Compare comp){
        *result=*first;
        __adjust_heap(first,Distance(0),Distance(last-first),value,comp);
    }
    template<class RandomAccessIterator,class Distance,class T,class Compare>
    void __adjust_heap(RandomAccessIterator first,Distance holeIndex,Distance len,T value,Compare comp){
        Distance topIndex=holeIndex;
        Distance secondChild =2*holeIndex+2;
        //如果根节点有右孩子
        while (secondChild<len){
            if(comp(*(first+secondChild),*(first+(secondChild-1))))
                secondChild--;
            //令子节点较大的值为新洞值
            *(first+holeIndex)=*(first+secondChild);
            holeIndex=secondChild;
            secondChild=2*holeIndex+2;
        }
        //如果根节点无右孩子
        if(secondChild==len){
            *(first+holeIndex) = *(first+(secondChild-1));
            holeIndex=secondChild-1;
        }
        __push_heap(first,holeIndex,topIndex,value,comp);

    }

    /** endregion */

    /** region ## sort_heap ## */
    template<class RandomAccessIterator,class Compare>
    void sort_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp){
        while (last-first>1)
            pop_heap(first,last--,comp);


    }
    /** endregion */

    /** region ## make_heap ## */
    //函数声明
    template<class RandomAccessIterator,class T,class Distance,class Compare>
    void __make_heap(RandomAccessIterator first,RandomAccessIterator last,T,Distance,Compare comp);




    template<class RandomAccessIterator,class Compare>
    inline void make_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp){
        __make_heap(first,last, value_type(first), distance_type(first),comp);
    }
    template<class RandomAccessIterator,class T,class Distance,class Compare>
    void __make_heap(RandomAccessIterator first,RandomAccessIterator last,T,Distance,Compare comp){
        if(last-first<2) return;
        Distance len=last-first;
        Distance parent =(len-2)/2;
        while (true){
            __adjust_heap(first,parent,len,T(*(first+parent)),comp);
            if(parent==0)return;
            parent--;
        }
    }

    /** endregion */
    /** endregion */
}

#endif //STL_LEARNING_MYHEAP_H
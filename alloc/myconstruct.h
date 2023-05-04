//
// Created by Q on 2023/4/24.
//

#ifndef STL_LEARNING_MYCONSTRUCT_H
#define STL_LEARNING_MYCONSTRUCT_H
#include "new.h"
#include "iostream"
#include "type_traits"
namespace wen{
    template<class T1,class T2>
    inline void construct(T1*p,const T2&value){
        new(p)T1(value);
    }

    template<class T>
    inline void destroy(T* ptr){
        ptr->~T();
    }

    template<class ForwardIterator>
    inline void destroy(ForwardIterator first,ForwardIterator last){
        __destroy(first,last,value_type(first));
    }

    template<class ForwardIterator,class T>
    inline void __destroy(ForwardIterator first,ForwardIterator last,T*){
        typedef typename std::is_trivially_destructible<T>::value trivial_destructor;//type-traits 用来检测析构函数可有可无
        __destroy_aux(first,last,trivial_destructor());
    }

    template<class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first,ForwardIterator last,__false_type){
        for(;first<last;++first)
            destroy(&*first);
    }
    template<class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first,ForwardIterator last,__true_type){}
    inline void destroy(char*,char*){}
    inline void destroy(wchar_t *,wchar_t *){}



}
#endif //STL_LEARNING_MYCONSTRUCT_H

//
// Created by Q on 2023/4/12.
//

#ifndef STL_LEARNING_TRAITS_LEARNING_H
#define STL_LEARNING_TRAITS_LEARNING_H
#include "iostream"

template<class T>
struct MtIter{
    typedef T value_type;
    value_type * ptr;
    MtIter(value_type* p=0):ptr(p){}
    value_type& operator*() const{return *ptr;}
};
//在此处我们定义了MtIter的value_type 为T ，则在下面的func种通过I::value_type
//可以萃取T
template<class I>
typename I::value_type//此处必须加typename，因为此处为模板类
func(I ite){
    return ite.num;
}

template<class I>
struct iterator_traits{
    typedef typename I::value_type value_type;
    typedef typename I::difference_type difference_type;
    typedef typename I::pointer pointer;
    typedef typename I::reference reference;
};

template<class T>
struct iterator_traits<T*>{
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};
template<class T>
struct iterator_traits<const T*>{
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};
template<class I>
typename iterator_traits<I>::value_type
func(I ite){return *ite;}
template<class I,class T>
typename iterator_traits<I>::difference_type
count(I first ,I last,const T & value){
    typename iterator_traits<I>::difference_type n=0;
    for(;first!=last;++first)
        if(*first == value)
            ++n;
    return n;
}




















#endif //STL_LEARNING_TRAITS_LEARNING_H

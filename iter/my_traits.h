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


namespace wen{
    /** region ## Iterator-Tag ## */
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag:public input_iterator_tag{};
    struct bidirectional_iterator_tag:public forward_iterator_tag{};
    struct random_access_iterator_tag:public bidirectional_iterator_tag{};
/** endregion */

    /** region ## tiaits ## */
    template<class I>
    struct iterator_traits{
        typedef typename I::value_type value_type;
        typedef typename I::difference_type difference_type;
        typedef typename I::pointer pointer;
        typedef typename I::reference reference;
        typedef typename I::iterator_category iterator_category;

    };
//模板特例 针对传统指针的萃取包括 const T*
    template<class T>
    struct iterator_traits<T*>{
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef random_access_iterator_tag iterator_category;
    };
    template<class T>
    struct iterator_traits<const T*>{
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef random_access_iterator_tag iterator_category;

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

/** endregion */

    /** region ## advance learning ## */
    template<class InputIterator,class Distance>
    void advance_II(InputIterator &i,Distance n){
        while (n--)++i;
    }
    template<class BidirectionalIterator,class Distance>
    void advance_BI(BidirectionalIterator& i,Distance n){
        if(n>0)
            while (n--) ++i;
        else
            while (n++) --i;
    }
    template<class RandomAccessIterator,class Distance>
    void advance_RAI(RandomAccessIterator& i,Distance n){
        i+=n;
    }
//采用 advance 进行整合
    template<class Iterator>
    bool is_random_access_iterator(const Iterator& );
    template<class Iterator>
    bool is_bidirectional_iterator(const Iterator& );
    template<class InputIterator,class Distance>
    void advance_pre(InputIterator& i,Distance n){
        if(is_random_access_iterator(i))
            advance_RAI(i,n);
        else if (is_bidirectional_iterator(i))
            advance_BI(i,n);
        else
            advance_II(i,n);
    }

    template<class InputIterator,class Distance>
    inline void __advance(InputIterator& i,Distance n,input_iterator_tag){
        while(n--)++i;
    }
    template<class ForwardIterator,class Distance>
    inline void __advance(ForwardIterator& i,Distance n,forward_iterator_tag){
        while(n--)++i;
    }
    template<class BidirectionalIterator,class Distance>
    void __advance(BidirectionalIterator& i,Distance n,bidirectional_iterator_tag) {
        if (n > 0)
            while (n--) ++i;
        else
            while (n++) --i;
    }

    template<class RandomAccessIterator,class Distance>
    void __advance(RandomAccessIterator& i,Distance n,random_access_iterator_tag){
        i+=n;
    }
//利用traits机制进行标记
    template<class InputIterator,class Distance>
    inline void advance(InputIterator& i,Distance n)
    {
        __advance(i,n,iterator_traits<InputIterator>::iterator_category());
    }
/** endregion */

    /** region ## distance learning ## */
    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    __distance(InputIterator first,InputIterator last,input_iterator_tag){
        typename iterator_traits<InputIterator>::difference_type n=0;
        while (first!=last){
            ++first;++n;
        }
        return n;
    }
    template<class RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type
    __distance(RandomAccessIterator first,RandomAccessIterator last,random_access_iterator_tag){
        return last-first;
    }
    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first,InputIterator last){
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        return __distance(first,last,category());
    }


/** endregion */

    /** region ## find ## */
    template<class InputIterator,class T>
    inline InputIterator
    __find(InputIterator first,InputIterator last,const T& value,input_iterator_tag){
        InputIterator result=InputIterator();
        while (first!=last){
            if(*first==value){
                return first;
            }
            ++first;
        }
        return result;
    }
    template<class InputIterator,class T>
    inline InputIterator
    find(InputIterator first,InputIterator last,const T& value){
        typedef typename iterator_traits<InputIterator>::iterator_category category;
        return __find(first,last,value,category());
    }
/** endregion */

//    /** region ## value_type ## */
//    template<class T>
//    typename T::value_type value_type(const T& iter){
//        return typename T::value_type();
//    }
//    template<class T>
//    T value_type(T*){
//        return T();
//    }
///** endregion */

//    /** region ## distance_type ## */
//    template<class T>
//    typename T::difference_type distance_type(const T& iter){
//        return typename T::difference_type();
//    }
//    template<class T>
//    ptrdiff_t distance_type(T*){
//        return ptrdiff_t();
//    }
//    /** endregion */
}














#endif //STL_LEARNING_TRAITS_LEARNING_H

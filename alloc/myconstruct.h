//
// Created by Q on 2023/4/24.
//
/** region ## 存在问题 ## */
    //value_type()未定义
    //__false_type和 __true_type 未定义
/** endregion */
#ifndef STL_LEARNING_MYCONSTRUCT_H
#define STL_LEARNING_MYCONSTRUCT_H
#include "new.h"
#include "iostream"
#include "type_traits"
#define  __true_type std::true_type
#define  __false_type std::false_type
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
    /** region ## uninitialized_fill_n ## */
    template< class ForwardIterator,class Size,class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
                                                Size n,const T&x){
        return __uninitialized_fill_n(first,n,x,value_type(first));//value_type函数用来萃取，【未实现】
    }
    template< class ForwardIterator,class Size,class T,class T1>
    inline ForwardIterator __uninitialized_fill_n(ForwardIterator first,Size n,const T&x,T1*){
        typedef typename std::is_pod<T1> is_POD;
        return __uninitialized_fill_n_aux(first,n,is_POD());
    }
    template< class ForwardIterator,class Size,class T>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,
                                                      Size n,const T&x,__true_type){
        return std::fill_n(first,n,x);//没自己写！
    }
    template< class ForwardIterator,class Size,class T>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,
                                                      Size n,const T&x,__false_type){
        ForwardIterator cur = first;
        //省略异常处理
        for(;n>0;--n,++cur)
            construct(&*cur,x);
        return cur;
    }
    /** endregion */
    /** region ## uninitialized_copy ## */
    template<class InputIterator,class ForwardIterator>
    inline ForwardIterator
        uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result){
        return __uninitialized_copy(first,last,result,value_type(result));
        }
    template<class InputIterator,class ForwardIterator,class T>
    inline ForwardIterator
    __uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result){
        typedef typename std::is_pod<T> is_POD;
        return __uninitialized_copy_aux(first,last,result,is_POD());
    }
    template<class InputIterator,class ForwardIterator>
    inline ForwardIterator
    __uninitialized_copy_aux(InputIterator first,InputIterator last,
                             ForwardIterator result,__true_type){
        return std::copy(first,last,result);
    }
    template<class InputIterator,class ForwardIterator>
    inline ForwardIterator
    __uninitialized_copy_aux(InputIterator first,InputIterator last,
                             ForwardIterator result,__false_type){
        ForwardIterator cur = result;
        //省略异常处理机制
        for(;first!=last;++first,++cur)
            construct(&*cur,*first);
        return cur;
    }
    //特例化 char* wchar_t*
    inline char* uninitialized_copy(const char* first,const char*last,char* result){
        memmove(result,first,last-first);
        return result+(last-first);
    }
    inline wchar_t * uninitialized_copy(const wchar_t * first,const wchar_t *last,wchar_t * result){
        memmove(result,first,sizeof (wchar_t )*(last-first));
        return result+(last-first);
    }
    /** endregion */
    /** region ## uninitialized_fill ## */
    template<class ForwardIterator,class T>
    inline void uninitialized_fill(ForwardIterator first,ForwardIterator last,
                                     const T&x){
         __uninitialized_fill(first,last,x,value_type(first));
    }
    template<class ForwardIterator,class T,class T1>
    inline void __uninitialized_fill(ForwardIterator first,ForwardIterator last,
                                     const T&x,T1*){
        typedef typename std::is_pod<T> is_POD;
        __uninitialized_fill_aux(first,last,x,is_POD());
    }
    template<class ForwardIterator,class T>
    inline void __uninitialized_fill(ForwardIterator first,ForwardIterator last,
                                     const T&x,__true_type){
        std::fill(first,last,x);
    }
    template<class ForwardIterator,class T>
    inline void __uninitialized_fill(ForwardIterator first,ForwardIterator last,
                                     const T&x,__false_type){
        ForwardIterator cur=first;
        for(;cur!=last;++cur)
            construct(&*cur,x);
    }
    /** endregion */

}
#endif //STL_LEARNING_MYCONSTRUCT_H

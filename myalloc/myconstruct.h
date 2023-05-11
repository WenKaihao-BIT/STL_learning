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
#include "../iter/my_traits.h"

namespace wen{
    typedef  std::true_type __true_type;
    typedef  std::false_type __false_type;

    /** region ## value_type 函数 ## */
    template<class T>
    struct __value_type{
        typedef typename T::value_type value_type;
    };
    template<class T>
    struct __value_type<T*>{
        typedef  T value_type;
    };
    /** endregion */

    template<class T1,class T2>
    inline void construct(T1*p,const T2&value){
        new(p)T1(value);
    }

    template<class T>
    inline void destroy(T* ptr){
        ptr->~T();
    }
    //函数声明
    template<class ForwardIterator,class T>
    inline void __destroy(ForwardIterator first,ForwardIterator last,T);
    template<class ForwardIterator,class T>
    inline void __destroy_aux(ForwardIterator first,ForwardIterator last,__false_type);
    template<class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first,ForwardIterator last,__true_type);

    template<class ForwardIterator>
    inline void destroy(ForwardIterator first,ForwardIterator last){
        __destroy(first,last,__value_type<ForwardIterator>());
    }

    template<class ForwardIterator,class T>
    inline void __destroy(ForwardIterator first,ForwardIterator last,T){
        typedef typename T::value_type value_type;
        typedef typename std::is_trivially_destructible<value_type> trivial_destructor;//type-traits 用来检测析构函数可有可无
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

    //函数声明
    template< class ForwardIterator,class Size,class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
                                                Size n,const T&x);

    template< class ForwardIterator,class Size,class T,class T1>
    inline ForwardIterator __uninitialized_fill_n(ForwardIterator first,Size n,const T&x,T1);

    template< class ForwardIterator,class Size,class T>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,
                                                      Size n,const T&x,__true_type);
    template< class ForwardIterator,class Size,class T>
    inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,
                                                      Size n,const T&x,__false_type);


    template< class ForwardIterator,class Size,class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
                                                Size n,const T&x){
        return __uninitialized_fill_n(first,n,x,__value_type<ForwardIterator>());
    }

    template< class ForwardIterator,class Size,class T,class T1>
    inline ForwardIterator __uninitialized_fill_n(ForwardIterator first,Size n,const T&x,T1){
        typedef typename T1::value_type value_type;
        typedef typename std::is_pod<value_type> is_POD;
        return __uninitialized_fill_n_aux(first,n,x,is_POD());
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
        return __uninitialized_copy(first,last,result,__value_type<ForwardIterator>());
        }
    template<class InputIterator,class ForwardIterator,class T>
    inline ForwardIterator
    __uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result,T){
        typedef typename T::value_type value_type;
        typedef typename std::is_pod<value_type> is_POD;
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
    //函数声明
    template<class ForwardIterator,class T>
    inline void uninitialized_fill(ForwardIterator first,ForwardIterator last,
                                   const T&x);
    template<class ForwardIterator,class T,class T1>
    inline void __uninitialized_fill(ForwardIterator first,ForwardIterator last,
                                     const T&x,T1);
    template<class ForwardIterator,class T>
    inline void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,
                                     const T&x,__true_type);
    template<class ForwardIterator,class T>
    inline void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,
                                    const T&x,__false_type);





    template<class ForwardIterator,class T>
    inline void uninitialized_fill(ForwardIterator first,ForwardIterator last,
                                     const T&x){
         __uninitialized_fill(first,last,x,__value_type<ForwardIterator>());
    }
    template<class ForwardIterator,class T,class T1>
    inline void __uninitialized_fill(ForwardIterator first,ForwardIterator last,
                                     const T&x,T1){
        typedef typename T1::value_type value_type;
        typedef typename std::is_pod<value_type> is_POD;
        __uninitialized_fill_aux(first,last,x,is_POD());
    }
    template<class ForwardIterator,class T>
    inline void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,
                                     const T&x,__true_type){
        std::fill(first,last,x);
    }
    template<class ForwardIterator,class T>
    inline void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,
                                     const T&x,__false_type){
        ForwardIterator cur=first;
        for(;cur!=last;++cur)
            construct(&*cur,x);
    }
    /** endregion */

}
#endif //STL_LEARNING_MYCONSTRUCT_H

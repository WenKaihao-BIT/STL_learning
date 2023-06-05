//
// Created by Q on 2023/5/24.
//

#ifndef STL_LEARNING_ALGOBASE_H
#define STL_LEARNING_ALGOBASE_H
#include "iostream"
#include "../../iter/Iterator.h"
#include "../../AssociativeContainer/pair/mypair.h"
#include "../../iter/my_type_traits.h"

namespace wen{
    /** region ## 函数声明 ## */

    template<class InputIterator,class OutputIterator>
    inline OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result);
    inline char* copy(const char*first,const char* last,char*result);
    inline wchar_t* copy(const wchar_t*first,const wchar_t* last,wchar_t*result);
    template<class InputIterator,class OutputIterator>
    struct __copy_dispatch;
    template<class T>
    struct __copy_dispatch<T*,T*>;
    template<class T>
    struct __copy_dispatch<const T*,T*>;
    template<class InputIterator,class OutIterator>
    inline OutIterator __copy(InputIterator first,InputIterator last,
                              OutIterator result,input_iterator_tag);
    template<class RandomAccessIterator,class OutIterator>
    inline OutIterator __copy(RandomAccessIterator first,RandomAccessIterator last,
                              OutIterator result,random_access_iterator_tag);
    template<class RandomAccessIterator,class OutIterator,class Distance>
    inline OutIterator __copy_d(RandomAccessIterator first,RandomAccessIterator last,
                                OutIterator result,Distance*);
    template<class T>
    inline T* __copy_t(const T*first,const T*last,T* result,__true_type);
    template<class T>
    inline T* __copy_t(const T*first,const T*last,T* result,__false_type);
    /** endregion */
    /** region ## equal ## */
    template<class InputIterator1,class  InputIterator2>
    inline bool equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2){
        for(;first1!=last1;++first1,++first2){
//            std::cout<<*first1<<' '<<*first2<< std::endl;
            if(*first1!=*first2)
                return false;
        }

        return true;
    }
    template<class InputIterator1,class  InputIterator2,class BinaryPredicate>
    inline bool equal(InputIterator1 first1,InputIterator1 last1,
                      InputIterator2 first2,BinaryPredicate binary_pred){
        for(;first1!=last1;++first1,++first2)
            if (!binary_pred(*first1,*first2))
                return false;
        return true;
    }

    /** endregion */
    
    /** region ## fill_n ## */
    template<class OutIterator,class Size,class T>
    OutIterator fill_n(OutIterator first,Size n,const T& value){
        for(;n>0;--n,++first)
            *first=value;
        return first;
    }
    /** endregion */
    
    /** region ## iter_swap ## */
    template<class ForwardIterator1,class ForwardIterator2,class T>
    inline void __iter_swap(ForwardIterator1 a,ForwardIterator2 b,T*){
        T tmp=*a;
        *a=*b;
        *b=tmp;
    }
    /** endregion */
    
    /** region ## lexicographical_compare ## */
    template<class InputIterator1,class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1,InputIterator1 last1,
                                 InputIterator1 first2,InputIterator1 last2){
        for(;first1!=last1&&first2!=last2;++first1,++first2){
            if(*first1<*first2)
                return true;
            if(*first2<*first1)
                return false;
        }
        return first1==last1&&first2!=last2;
    }
    /** endregion */

    /** region ## max ## */
    template<class T>
    inline const T& max(const T&a,const T&b){
        return a<b?b:a;
    }

    template<class T,class Compare>
    inline const T& max(const T& a,const T& b,Compare comp){
        return comp(a,b)?b:a;
    }


    /** endregion */

    /** region ## min ## */
    template<class T>
    inline const T& min(const T&a,const T&b){
        return a>b?b:a;
    }

    template<class T,class Compare>
    inline const T& min(const T& a,const T& b,Compare comp){
        return comp(b,a)?b:a;
    }
    /** endregion */

    /** region ## mismatch ## */
    template<class InputIterator1,class InputIterator2>
    pair<InputIterator1,InputIterator2> mismatch(InputIterator1 first1,
                                                 InputIterator1 last1,
                                                 InputIterator2 first2){
        while (first1!=last1&&*first1==*first2){
            ++first1;
            ++first2;
        }
        return pair<InputIterator1,InputIterator2>(first1,first2);
    }
    template<class InputIterator1,class InputIterator2,class BinaryPredicate>
    pair<InputIterator1,InputIterator2> mismatch(InputIterator1 first1,
                                                 InputIterator1 last1,
                                                 InputIterator2 first2,
                                                 BinaryPredicate binary_pred){
        while (first1!=last1&&binary_pred(*first1,*first2)){
            ++first1;
            ++first2;
        }
        return pair<InputIterator1,InputIterator2>(first1,first2);
    }
    /** endregion */
    
    /** region ## copy ## */




    template<class InputIterator,class OutputIterator>
    inline OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result){
        std::cout<<"copy-function"<<std::endl;
        return __copy_dispatch<InputIterator,OutputIterator>()(first,last,result);
    }
    //特殊版本(1),重载形式
    inline char* copy(const char*first,const char* last,char*result){
        std::cout<<"const-char-copy-function"<<std::endl;
        memmove(result,first,last-first);
        return result+(last-first);
    }

    //特殊版本(2),重载形式
    inline wchar_t* copy(const wchar_t*first,const wchar_t* last,wchar_t*result){
        std::cout<<"wchar-copy-function"<<std::endl;
        memmove(result,first,sizeof (wchar_t )*(last-first));
        return result+(last-first);
    }

    //完全泛化版本
    template<class InputIterator,class OutputIterator>
    struct __copy_dispatch{
            OutputIterator operator()(InputIterator first, InputIterator last,OutputIterator result){
                std::cout<<"copy_dispatch-InputIterator-function"<<std::endl;
                return __copy(first,last,result, iterator_category(first));
            }
        };

    template<class T>
    struct __copy_dispatch<T*,T*>{
        T* operator()(T* first,const T* last,T*result){
            std::cout<<"copy_dispatch-T-T-function"<<std::endl;
            typedef typename __type_traits<T>::has_trivial_assignment_operator t;
            return __copy_t(first,last,result,t());
        }
    };

    template<class T>
    struct __copy_dispatch<const T*,T*>{
        T* operator()(const T* first,const T* last,T*result){
            std::cout<<"copy_dispatch-const T-T-InputIterator-function"<<std::endl;
            typedef typename __type_traits<T>::has_trivial_assignment_operator t;
            return __copy_t(first,last,result,t());
        }
    };
    //InputIterator
    template<class InputIterator,class OutIterator>
    inline OutIterator __copy(InputIterator first,InputIterator last,
                              OutIterator result,input_iterator_tag){
        std::cout<<"__copy-InputIterator-function"<<std::endl;
        for(;first!=last;++result,++first)
            *result=*first;
        return result;
    }

    //RandomAccessIterator
    template<class RandomAccessIterator,class OutIterator>
    inline OutIterator __copy(RandomAccessIterator first,RandomAccessIterator last,
                              OutIterator result,random_access_iterator_tag){
        std::cout<<"__copy-RandomAccessIterator-function"<<std::endl;
        return __copy_d(first,last,result, distance_type(first));
    }

    template<class RandomAccessIterator,class OutIterator,class Distance>
    inline OutIterator __copy_d(RandomAccessIterator first,RandomAccessIterator last,
             OutIterator result,Distance*){
        std::cout<<"__copy_d-function"<<std::endl;
        for(Distance n=last-first;n>0;--n,++result,++first)
            *result=*first;
        return result;
    }
    //针对 trivial_assignment_operator
    template<class T>
    inline T* __copy_t(const T*first,const T*last,T* result,__true_type){
        std::cout<<"__copy_t_memmove-function"<<std::endl;
        memmove(result,first, sizeof(T)*(last-first));
        return result+(last-first);
    }
    //针对 non-trivial_assignment_operator
    template<class T>
    inline T* __copy_t(const T*first,const T*last,T* result,__false_type){
        std::cout<<"__copy_t_to_copy_d-function"<<std::endl;
        return __copy_d(first,last,result, (ptrdiff_t*)0);
    }

    /** endregion */
    
    /** region ## copy_backward ## */



    /** endregion */
    
    /** region ## set-algorithms ## */
    /** region ## set_union ## */
    template<class InputIterator1,class InputIterator2,class OutputIterator>
    OutputIterator set_union(InputIterator1 first1,InputIterator1 last1,
                             InputIterator2 first2,InputIterator2 last2,
                             OutputIterator result){
        while (first1!=last1&&first2!=last2){
            if(*first1<*first2){
                *result=*first1;
                ++first1;
            }
            if(*first2<*first1){
                *result=*first2;
                ++first2;
            }
            else{
                *result=*first1;
                ++first1;
                ++first2;
            }
            ++result;
        }
        return (first1,last1, copy(first1,last1,result));
    }
    /** endregion */
    
    /** region ## set_intersection ## */
    //要求集合顺序排列
    template<class InputIterator1,class InputIterator2,class OutputIterator>
    OutputIterator set_intersection(InputIterator1 first1,InputIterator1 last1,
                             InputIterator2 first2,InputIterator2 last2,
                             OutputIterator result){
        while (first1!=last1&&first2!=last2){
            if(*first1<*first2)
                ++first1;
            if(first2<*first1)
                ++first2;
            else{
                *result=*first1;
                ++first1;
                ++first2;
                ++result;
            }
            return result;
        }
    }
    /** endregion */
    
    /** region ## set_difference ## */
    //有序排列
    
    template<class InputIterator1,class InputIterator2,class OutputIterator>
    OutputIterator set_difference(InputIterator1 first1,InputIterator1 last1,
                                    InputIterator2 first2,InputIterator2 last2,
                                    OutputIterator result){
        while (first1!=last1&&first2!=last2){
            if(*first1<*first2){
                *result=*first1;
                ++first1;
                ++result;
            }
            else if(*first2<*first1)
                ++first2;
            else{
                ++first1;
                ++first2;
            }
            return copy(first1,last1,result);
        }
    }
    /** endregion */
    
    /** region ## set_symmetric_difference ## */
    template<class InputIterator1,class InputIterator2,class OutputIterator>
    OutputIterator set_symmetric_difference(InputIterator1 first1,InputIterator1 last1,
                                  InputIterator2 first2,InputIterator2 last2,
                                  OutputIterator result){
        while(first1!=last1&&first2!=last2){
            if(*first1<*first2){
                *result=*first1;
                ++first1;
                ++result;
            } else if(*first2<*first1){
                *result=*first2;
                ++first2;
                ++result;
            }
            else{
                ++first1;
                ++first2;
            }
            return copy(first2,last2, copy(first1,last1,result));
        }
    }
    /** endregion */
    /** endregion */
}


#endif //STL_LEARNING_ALGOBASE_H

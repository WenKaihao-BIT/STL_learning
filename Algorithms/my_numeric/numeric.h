//
// Created by Q on 2023/5/23.
//

#ifndef STL_LEARNING_ACCUMULATE_H
#define STL_LEARNING_ACCUMULATE_H
#include "../../iter/my_traits.h"
namespace wen{
    /** region ## accumulate ## */
    template<class InputIterator,class T>
    T accumulate(InputIterator first,InputIterator last,T init){
        for(;first!=last;++first)
            init=init+*first;
        return init;
    }

    template<class InputIterator,class T,class BinaryOperation>
    T accumulate(InputIterator first,InputIterator last,T init,
                 BinaryOperation binary_op){
        for(;first!=last;++first)
            init = binary_op(init,*first);
        return init;
    }
    /** endregion */

    /** region ## adjacent_difference ## */
    ///相邻元素的差额
    //result 指向尾后
    template<class InputIterator,class OutputIterator,class T>
    OutputIterator __adjacent_difference(InputIterator first,InputIterator last,
                                         OutputIterator result,T){
        T value=*first;
        while (++first!=last){
            T tmp=*first;
            *++result=tmp-value;
            value=tmp;
        }
        return ++result;
    }
    template<class InputIterator,class OutputIterator,class T,class BinaryOperation>
    OutputIterator __adjacent_difference(InputIterator first,InputIterator last,
                                         OutputIterator result,T,BinaryOperation binary_op){
        T value=*first;
        while (++first!=last){
            T tmp=*first;
            *++result=binary_op(tmp,value);
            value=tmp;
        }
        return ++result;
    }

    template<class InputIterator,class OutputIterator>
    OutputIterator adjacent_difference(InputIterator first,InputIterator last,
                                       OutputIterator result){
        if(first==last) return result;
        *result = *first;
        return __adjacent_difference(first,last,result,value_type(first));
    }

    template<class InputIterator,class OutputIterator,class BinaryOperation>
    OutputIterator adjacent_difference(InputIterator first,InputIterator last,
                                       OutputIterator result,BinaryOperation binary_op){
        if(first==last) return result;
        *result = *first;
        return __adjacent_difference(first,last,result, value_type(first),binary_op);
    }
    /** endregion */

    /** region ## 内积 ## */
    template<class InputIterator1,class InputIterator2,class T>
    T inner_product(InputIterator1 first1,InputIterator1 last1,
                    InputIterator2 first2,T init ){
        for(;first1!=last1;++first1,++first2)
            init = init +(*first1* *first2);
        return init;
    }
    template<class InputIterator1,class InputIterator2,class T,class BinaryOperation>
    T inner_product(InputIterator1 first1,InputIterator1 last1,
                    InputIterator2 first2,T init,BinaryOperation binary_op){
        for(;first1!=last1;++first1,++first2)
            init = binary_op(init +binary_op(*first1, *first2));
        return init;
    }
    /** endregion */



}




















#endif //STL_LEARNING_ACCUMULATE_H



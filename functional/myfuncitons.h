//
// Created by Q on 2023/5/15.
//

#ifndef STL_LEARNING_MYFUNCITONS_H
#define STL_LEARNING_MYFUNCITONS_H

#endif //STL_LEARNING_MYFUNCITONS_H
namespace wen{
    template<class Arg,class Result>
    struct unary_function{
        typedef Arg argument_type;
        typedef Result result_type;
    };
    template<class T>
    struct identity:public unary_function<T,T>{
        const T& operator()(const T& x)const{return x;}
    };
    template<typename Arg1, typename Arg2, typename Result>
    struct binary_function
    {
        typedef Arg1 	first_argument_type;

        typedef Arg2 	second_argument_type;

        typedef Result 	result_type;
    };
}
//针对pair的仿函数
template<class _pair>
    struct select1st{
    typedef typename _pair::first_type first_type;
    typedef typename _pair::second_type second_type;
        first_type& operator()(const _pair&p){return p.first;}
};

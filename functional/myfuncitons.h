//
// Created by Q on 2023/5/15.
//

#ifndef STL_LEARNING_MYFUNCITONS_H
#define STL_LEARNING_MYFUNCITONS_H


namespace wen{
    template<class Arg,class Result>
    struct unary_function{
        typedef Arg argument_type;
        typedef Result result_type;
    };

    template<typename Arg1, typename Arg2, typename Result>
    struct binary_function
    {
        typedef Arg1 	first_argument_type;
        typedef Arg2 	second_argument_type;
        typedef Result 	result_type;
    };


    ///swap函数
    template<class T>
    void swap(T &l,T &r){
        T tmp= l;
        l=r;
        r=tmp;
    }

    template<class T>
    void swap(T* &l,T* &r){
        T* tmp=l;
        l=r;
        r=tmp;
    }

    /** region ## 运算类仿函数 ## */
    template<class T>
    struct plus:public binary_function<T,T,T>{
        T operator()(const T&x,const T&y)const{return x+y;}
    };
    //.....
    /** endregion */

    /** region ## 关系运算类仿函数 ## */
    template<class T>
    struct equal_to:public binary_function<T,T,bool>{
        bool operator()(const T&x,const T&y)const{return x==y;}
    };
    /** endregion */

    /** region ## 逻辑类仿函数 ## */
    template<class T>
    struct logical_and:public binary_function<T,T,bool>{
        bool operator()(const T&x,const T&y)const{return x&&y;}
    };
    /** endregion */

    /** region ## 证同 ## */
    template<class T>
    struct identity:public unary_function<T,T>{
        const T& operator()(const T& x)const{return x;}
    };
    /** endregion */
    /** region ## 选择 ## */
    template<class pair>
    struct select1st:public unary_function<pair,typename pair::first_type>{
        const typename pair::first_type&
        operator()(const pair&x)const{return x.first;}
    };
    template<class pair>
    struct select2nd:public unary_function<pair,typename pair::second_type>{
        const typename pair::second_type&
        operator()(const pair&x)const{return x.second;}
    };
    /** endregion */
    /** region ## 投射 ## */
    template<class Arg1,class Arg2>
    struct project1st:public binary_function<Arg1,Arg2,Arg1>{
        Arg1 operator()(const Arg1&x,const Arg2&)const{return x;}
    };
    template<class Arg1,class Arg2>
    struct project2nd:public binary_function<Arg1,Arg2,Arg2>{
        Arg1 operator()(const Arg1&a,const Arg2&x)const{return x;}
    };
    /** endregion */
}

#endif //STL_LEARNING_MYFUNCITONS_H
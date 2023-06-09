//
// Created by Q on 2023/5/30.
//

#ifndef STL_LEARNING_MYADAPTERS_H
#define STL_LEARNING_MYADAPTERS_H

#include <istream>
#include "../iter/my_traits.h"
#include "../functional/myfuncitons.h"


namespace wen{
    /** region ## insert iterators ## */
    /** region ## back_insert_iterator ## */
    //将迭代器的赋值操作改为插入（尾插）操作

    template<class Container>
    class back_insert_iterator{
    protected:
        Container* container;
    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
        explicit back_insert_iterator(Container&x):container(&x){}
        back_insert_iterator<Container>&
        operator=(const typename Container::value_type& value){
            container->push_back(value);
            return *this;
        }
        back_insert_iterator<Container>&
        operator*(){return *this;}
        back_insert_iterator<Container>&
        operator++(){return *this;}
        back_insert_iterator<Container>&
        operator++(int){return *this;}
    };

    template<class Container>
    inline back_insert_iterator<Container>back_inserter(Container&x){
        return back_insert_iterator<Container>(x);
    }
/** endregion */

    /** region ## front_insert_iterator ## */

    /** endregion */

    /** region ## insert_iterator ## */

    /** endregion */
    /** endregion */

    /** region ## reverse iterators ## */
    template<class Iterator>
    class reverse_iterator{
    protected:
        Iterator current;
    public:
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;

        typedef Iterator iterator_type;
        typedef reverse_iterator<Iterator>self;
    public:
        reverse_iterator(){}
        explicit reverse_iterator(iterator_type x):current(x){}
        reverse_iterator(const self& x):current(x.current){}

        iterator_type base()const{return current;}
        reference operator*()const{
            Iterator tmp = current;
            return *--tmp;
        }
        pointer operator->()const{return &(operator*());}

        self& operator++(){
            --current;
            return *this;
        }
        self operator++(int){
            self tmp=*this;
            --current;
            return tmp;
        }
        self& operator--(){
            ++current;
            return *this;
        }
        self operator--(int){
            self tmp=*this;
            ++current;
            return tmp;
        }
        self operator+(difference_type n)const{
            return self(current-n);
        }
        self operator+=(difference_type n)const{
            current -= n;
            return *this;
        }
        self operator-(difference_type n)const{
            return self(current+n);
        }
        self operator-=(difference_type n)const{
            current += n;
            return *this;
        }
        reference operator[](difference_type n)const{return *(*this+n);}



    };
    /** endregion */
    
    /** region ## stream iterators ## */
    
    /** region ## istream_iterator ## */
    template<class T,class Distance=ptrdiff_t>
    class istream_iterator{
        friend bool operator==(const istream_iterator<T,Distance&>x,
                               const istream_iterator<T,Distance&>y);
    protected:
        std::istream* stream;
        T value;
        bool end_marker;
        void read(){
            end_marker = (*stream) ? true: false;
            if(end_marker) *stream>>value;
            end_marker = (*stream) ? true: false;
        }
    public:
        typedef input_iterator_tag iterator_category;
        typedef T                  value_type;
        typedef Distance           difference_type;
        typedef const T*           pointer;
        typedef const T&           reference;
        istream_iterator():stream(&std::cin),end_marker(false){}
        istream_iterator(std::istream &s):stream(&s){read();}
        reference operator*()const{return value;}
        pointer operator->()const{return &(operator*());}

        istream_iterator<T,Distance>& operator++(){
            read();
            return *this;
        }
        istream_iterator<T,Distance>operator++(int){
            istream_iterator<T,Distance>tmp=*this;
            read();
            return tmp;
        }
    };
    /** endregion */
    
    /** region ## ostream_iterator ## */
    template<class T>
    class ostream_iterator{
    protected:
        std::ostream* stream;
        const char* string;//输出后的间隔符

    public:
        typedef output_iterator_tag   iterator_category;
        typedef void                  value_type;
        typedef void                  difference_type;
        typedef void                  pointer;
        typedef void                  reference;
        ostream_iterator(std::ostream &s):stream(&s),string(0){}
        ostream_iterator(std::ostream &s,const char *c):stream(&s),string(c){}
        ostream_iterator<T>&operator=(const T& value){
            *stream<<value;
            if(string) *stream<<string;
            return *this;
        }
        ostream_iterator<T>& operator*(){return *this;}
        ostream_iterator<T>& operator++(){return *this;}
        ostream_iterator<T>& operator++(int){return *this;}

    };

    /** endregion */
    /** endregion */

    /** region ## not1 not2 ## */
    template<class Predicate>
    class unary_negate
            :public unary_function<typename Predicate::argument_type,bool>{
    protected:
        Predicate pred;
    public:
        explicit unary_negate(const Predicate&x):pred(x){}
        bool operator()(const typename Predicate::argument_type&x )const{
            return !pred(x);
        }
    };
    template<class Predicate>
    inline unary_negate<Predicate>not1(const Predicate& pred){
        return unary_negate<Predicate>(pred);
    }

    template<class Predicate>
    class binary_negate
            :public binary_function<typename Predicate::first_argument_type,
                                    typename Predicate::second_argument_type,
                                                    bool>{
    protected:
        Predicate pred;
    public:
        explicit binary_negate(const Predicate&x):pred(x){}
        bool operator()(const typename Predicate::argument_type&x,
                        const typename Predicate::argument_type&y)const{
            return !pred(x,y);
        }
    };
    template<class Predicate>
    inline unary_negate<Predicate>not2(const Predicate& pred){
        return binary_negate<Predicate>(pred);
    }
    /** endregion */
    
    /** region ## binder1st,bind2nd ## */
    template<class Operation>
    class binder1st
            :public unary_function<typename Operation::second_argument_type,
                                    typename Operation::result_type>{
    protected:
        Operation op;
        typename Operation::first_argument_type value;

    public:
        binder1st(const Operation&x,const typename Operation::irst_argument_type& y)
        :op(x),value(y){}
        typename Operation::result_type
        operator()(const typename Operation::second_argument_type&x)const{
            return op(value,x);
        }
    };
    template<class Operation,class T>
    inline binder1st<Operation> bind1st(const Operation& op,const T&x){
        typedef typename Operation::first_argument_type arg1_type;
        return binder1st<Operation>(op,arg1_type(x));
    }

    template<class Operation>
    class binder2nd
            :public unary_function<typename Operation::first_argument_type,
                    typename Operation::result_type>{
    protected:
        Operation op;
        typename Operation::second_argument_type value;

    public:
        binder2nd(const Operation&x,const typename Operation::irst_argument_type& y)
                :op(x),value(y){}
        typename Operation::result_type
        operator()(const typename Operation::first_argument_type&x)const{
            return op(x,value);
        }
    };
    template<class Operation,class T>
    inline binder1st<Operation> bind2nd(const Operation& op,const T&x){
        typedef typename Operation::second_argument_type arg2_type;
        return binder1st<Operation>(op,arg2_type(x));
    }
    /** endregion */

    /** region ## compose1 compose2 ## */
    //f(),g() 用于产生h(x)=f(g(x))
    template<class Operation1,class Operation2>
    class unary_compose
            :public unary_function<typename Operation2::argument_type,
                    typename Operation1::result_type>{
    protected:
        Operation1 op1;
        Operation2 op2;
    public:
        unary_compose(const Operation1&x,const Operation2& y)
            :op1(x),op2(y){}
        typename Operation1::result_type
        operator()(const typename Operation2::argument_type& x)const{
            return op1(op2(x));
        }
    };

    template<class Operation1,class Operation2>
    inline unary_compose<Operation1,Operation2>
    compose1(const Operation1& op1,const Operation1& op2){
        return unary_compose<Operation1,Operation2>(op1,op2);
    }
    
    //用来产生h(x)=f(g1(x),g2(x)) f(x) g1(x) g2(x)
    template<class Operation1,class Operation2,class Operation3>
    class binary_compose
            :public unary_function<typename Operation2::argument_type,typename Operation1::result_type>{
    protected:
            Operation1 op1;
            Operation2 op2;
            Operation3 op3;
    public:
            binary_compose(const Operation1&x,const Operation2&y,Operation3&z):op1(x),op2(y),op3(z){}
            typename Operation1::result_type
            operator()(const typename Operation2::argument_type& x)const{
                return op1(op2(x),op3(x));
            }
        };
    template<class Operation1,class Operation2,class Operation3>
    inline binary_compose<Operation1,Operation2,Operation3>
            compose2(const Operation1& op1,const Operation1& op2,const Operation1& op3){
        return binary_compose<Operation1,Operation2,Operation3>(op1,op2,op3);
            }

    /** endregion */

    /** region ## ptr_fun ## */
    template<class Arg,class Result>
    class pointer_to_unary_function:public unary_function<Arg,Result>
    {
    protected:
        Result (*ptr)(Arg);//内部成员，函数指针
    public:
        pointer_to_unary_function(){}
        explicit pointer_to_unary_function(Result (*x)(Arg)):ptr(x){}

        Result operator()(Arg x)const{return ptr(x);}
    };

    template<class Arg,class Result>
    inline pointer_to_unary_function<Arg,Result>
            ptr_fun(Result (*x)(Arg)){
        return pointer_to_unary_function<Arg,Result>(x);
            }

    template<class Arg1,class Arg2,class Result>
    class pointer_to_binary_function:public binary_function<Arg1,Arg2,Result>
    {
    protected:
        Result (*ptr)(Arg1,Arg2);//内部成员，函数指针
    public:
        pointer_to_binary_function(){}
        explicit pointer_to_binary_function(Result (*x)(Arg1,Arg2)):ptr(x){}

        Result operator()(Arg1 x,Arg2 y)const{return ptr(x,y);}
    };

    template<class Arg1,class Arg2,class Result>
    inline pointer_to_binary_function<Arg1,Arg2,Result>
    ptr_fun(Result (*x)(Arg1,Arg2)){
        return pointer_to_binary_function<Arg1,Arg2,Result>(x);
    }
    /** endregion */

    template<class S,class T>
    class mem_fun_t:public unary_function<T*,S>{
    public:
        explicit mem_fun_t(S(T::*pf)()const):f(pf){}
        S operator()(T* p)const{return (p->*f)();}
    private:
        S(T::*f)()const;
    };

    template<class S,class T>
    class const_mem_fun_t:public unary_function<T*,S>{
    public:
        explicit const_mem_fun_t(S(T::*pf)()const):f(pf){}
        S operator()(T* p)const{return (p->*f)();}
    private:
        S(T::*f)()const;
    };

    template<class S,class T>
    class mem_fun_ref_t:public unary_function<T,S>{
    public:
        explicit mem_fun_ref_t(S(T::*pf)()):f(pf){}
        S operator()(T& r)const{return (r.*f)();}
    private:
        S(T::*f)()const;
    };
    template<class S,class T>
    class const_mem_fun_ref_t:public unary_function<T,S>{
    public:
        explicit const_mem_fun_ref_t(S(T::*pf)()const):f(pf){}
        S operator()(T& r)const{return (r.*f)();}
    private:
        S(T::*f)()const;
    };


}


#endif //STL_LEARNING_MYADAPTERS_H

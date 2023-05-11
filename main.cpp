
#include<iostream>
#include "SequenceContainer/vector_container/vector.h"
#include "vector"
using namespace wen;

template<class T>
class test{
public:
    typedef T value_type;
    typedef value_type& reference ;
    typedef const value_type& const_reference ;
    test(int n,const_reference value){std::cout<<n<<'-'<<value<<std::endl;}
};
template<class Iterator>
struct value_type_traits{
    typedef typename Iterator::value_type value_type;
};

template<class T>
class auto_ptr{
public:
    typedef T value_type;
    value_type * ptr;
    auto_ptr(value_type* p=0):ptr(p){}
    value_type& operator*() const{return *ptr;}
};
template<class T>
struct __value_type2{
    typedef typename T::value_type value_type;
};
template<class T>
struct __value_type2<T*>{
    typedef  T value_type;
};



void fun1(std::true_type){
    std::cout<<"true"<<std::endl;
}
void fun1(std::false_type){
    std::cout<<"false"<<std::endl;
}
template<class T>
void test2(T*){
    typedef  T value_type;
    auto is_int=std::is_integral<value_type>();
//    std::cout<< typeid(is_int).name()<<std::endl;
    fun1(is_int);
}
template<class T>
void test2(T){
    typedef typename T::value_type value_type;
    auto is_int =std::is_integral<value_type>();
//    std::cout<< typeid(is_int).name()<<std::endl;
//    std::cout<<is_int<<std::endl;
    fun1(is_int);
}
struct true_type:std::true_type {

};
int main() {
//    vector<int>iv(2,9);
//    test<int>iv(2,9);
//    int a=5;
//    int *ptr=&a;
//    double *ptr2;
//    auto_ptr<int>aptr(ptr);
//    test2(aptr);
//    test2(auto_ptr<double>());
//    std::vector<int>nums;
////    wen::uninitialized_fill_n(nums.begin(),5,-1);
//    test<int>abc();
//    fun1(true_type());
    int *ptr;
    ptr=simple_alloc<int,alloc>::allocate();
    construct(ptr,5);
    std::cout<<*ptr<<std::endl;
    destroy(ptr);
    simple_alloc<int,alloc>::deallocate(ptr);


    return 0;
}

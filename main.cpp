
#include<iostream>
#include "SequenceContainer/vector_container/vector.h"
#include "vector"
using namespace wen;

template<class InputIterator>
struct iterator_1{
    iterator_1(){std::cout<<"构造函数"<<std::endl;}
    iterator_1(const iterator_1&){std::cout<<"拷贝构造函数"<<std::endl;};
};

template<class InputIterator>
InputIterator fun(InputIterator f,InputIterator l){
    std::cout<<"fun"<<std::endl;
    return f;
}
int main() {
    iterator_1<int>a;
    iterator_1<int>b;
    fun(a,b);


    return 0;
}

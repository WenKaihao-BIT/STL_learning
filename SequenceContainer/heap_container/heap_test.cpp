//
// Created by Q on 2023/5/11.
//
#include "myheap.h"
#include "iostream"
#include "../vector_container/vector.h"
int main(){
    int a=5;
    int *ptr=&a;
//    std::cout<< typeid(wen::distance_type(ptr)).name()<<std::endl;
    wen::vector<int>::iterator iter;
//    std::cout<< typeid(wen::distance_type(iter)).name()<<std::endl;
//    std::cout<< typeid(long long).name()<<std::endl;
    wen::push_heap(iter,iter);
    auto p=wen::distance_type(iter);
    return 0;
}
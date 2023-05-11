//
// Created by Q on 2023/5/9.
//
#include "mydeque.h"
#include "vector"
#include "iostream"
int foo(int a){return a;}
int main(){
    wen::deque<int,alloc,8>ideq3;
    wen::deque<int,alloc,8>ideq(20,9);
    std::cout<<"size = "<<ideq.size()<<std::endl;
    wen::deque<int,alloc,8>::iterator iter;
    std::cout<<"buffer = "<<iter.buffer_size()<<std::endl;
    std::cout<<"begin = "<<*ideq.begin()<<std::endl;
//    std::cout<<"begin = "<<*ideq.end()<<std::endl;
    for(int i=0;i<ideq.size();++i)
        ideq[i]=i;
    for(int i=0;i<ideq.size();++i)
        std::cout<<ideq[i]<<' ';
    std::cout<<std::endl;


    for (int i = 0; i < 3; ++i) {
        ideq.push_back(i);
    }
    for(int i=0;i<ideq.size();++i)
        std::cout<<ideq[i]<<' ';
    std::cout<<std::endl;

    ideq.push_back(3);
    for(int i=0;i<ideq.size();++i)
        std::cout<<ideq[i]<<' ';
    std::cout<<std::endl;
    std::cout<<"size = "<<ideq.size()<<std::endl;

    ideq.push_front(99);
    for(int i=0;i<ideq.size();++i)
        std::cout<<ideq[i]<<' ';
    std::cout<<std::endl;

    ideq.push_front(98);
    ideq.push_front(97);
    for(int i=0;i<ideq.size();++i)
        std::cout<<ideq[i]<<' ';
    std::cout<<std::endl;
    std::cout<<"size = "<<ideq.size()<<std::endl;

    wen::deque<int,alloc,8>::iterator itr;
    itr=wen::find(ideq.begin(),ideq.end(),99);
    std::cout<<*itr<<std::endl;
    std::cout<<*(itr.cur)<<std::endl;

//    ideq.clear();
//    std::cout<<"size = "<<ideq.size()<<std::endl;

//    ideq.erase(ideq.begin()+4);//存在问题
//    std::cout<<(ideq.size()>>1)<<std::endl;
//    for(int i=0;i<ideq.size();++i)
//        std::cout<<ideq[i]<<' ';
//    std::cout<<std::endl;






    return 0;
}
//
// Created by Q on 2023/5/12.
//
#include "my_priority_queue.h"


int main(){
    int ia[9]={0,1,2,3,4,8,9,3,5};
    wen::priority_queue<int>ipq(ia,ia+9);
    wen::vector<int>a(ia,ia+9);
//    std::cout<<a.size();
//    for(auto itr=a.begin();itr!=a.end();itr++)std::cout<<*itr<<' ';std::cout<<std::endl;
    std::cout<<"size= "<<ipq.size()<<std::endl;
    for(int i=0;i<ipq.size();++i)
        std::cout<<ipq.top()<<' ';std::cout<<std::endl;

    while (!ipq.empty()){
        std::cout<<ipq.top()<<' ';
        ipq.pop();
    }
    std::cout<<std::endl;
    return 0;
}
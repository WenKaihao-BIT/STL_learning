//
// Created by Q on 2023/5/8.
//
#include "iostream"
#include "myList.h"
int main(){
    wen::myList<int>ilist;
    std::cout<<"size= "<<ilist.size()<<std::endl;//size=0
    ilist.push_back(-1);
    ilist.push_back(-2);
    ilist.push_back(-3);
    ilist.push_back(-4);
    ilist.push_back(-5);
    std::cout<<"size= "<<ilist.size()<<std::endl;//size=5
    wen::myList<int>::iterator ite;
    for(ite=ilist.begin();ite!=ilist.end();++ite)
        std::cout<<*ite<<' ';
    std::cout<<std::endl;//-1 -2 -3 -4 -5
    ite= wen::find(ilist.begin(),ilist.end(),-3);
    if(ite!=0)
        ilist.insert(ite,999);
    for(ite=ilist.begin();ite!=ilist.end();++ite)
        std::cout<<*ite<<' ';
    std::cout<<std::endl;//-1 -2 -3 -4 -5
}
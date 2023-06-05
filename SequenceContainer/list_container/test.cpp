//
// Created by Q on 2023/5/8.
//
#include <algorithm>
#include "iostream"
#include "list.h"
#include "../vector_container/vector.h"
int main(){
    wen::list<int>ilist;
    std::cout<<"size= "<<ilist.size()<<std::endl;//size=0
    ilist.push_back(-1);
    ilist.push_back(-2);
    ilist.push_back(-3);
    ilist.push_back(-4);
    ilist.push_back(-5);
    std::cout<<"size= "<<ilist.size()<<std::endl;//size=5
    wen::list<int>::iterator ite;
    for(ite=ilist.begin();ite!=ilist.end();++ite)
        std::cout<<*ite<<' ';
    std::cout<<std::endl;//-1 -2 -3 -4 -5
    ite= wen::find(ilist.begin(),ilist.end(),-3);
    if(ite!=0)
        ilist.insert(ite,999);
    for(ite=ilist.begin();ite!=ilist.end();++ite)
        std::cout<<*ite<<' ';
    std::cout<<std::endl;//-1 -2 999 -3 -4 -5
    ite = ilist.begin();
    ilist.erase(ite);
    for(ite=ilist.begin();ite!=ilist.end();++ite)
        std::cout<<*ite<<' ';
    std::cout<<std::endl;// -2 999 -3 -4 -5
    wen::list<int>ilist2;
    ilist2.push_back(-9999);
    ilist.swap(ilist2);
    for(ite=ilist.begin();ite!=ilist.end();++ite)
        std::cout<<*ite<<' ';
    std::cout<<std::endl;
    wen::list<int>ilist3;
    wen::vector<int>iv;
    iv.push_back(1);
//    iv.push_back(2);
//    iv.push_back(3);
//    ilist3.insert(ilist3.begin(),iv.begin(),iv.end());
//    for(ite=ilist3.begin();ite!=ilist3.end();++ite)
//        std::cout<<*ite<<' ';
//    std::cout<<std::endl;

}
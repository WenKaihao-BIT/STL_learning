//
// Created by Q on 2023/5/16.
//
#include "mySet.h"
#include "iostream"
using namespace std;
int main(){
    int i;
    int ia[5]={0,1,2,3,4};
    wen::set<int>iset(ia,ia+5);
    cout<<"size= "<<iset.size()<<endl;
    cout<<"3 count= "<<iset.count(3)<<endl;
    iset.insert(3);
    cout<<"size= "<<iset.size()<<endl;
    cout<<"3 count= "<<iset.count(3)<<endl;
    iset.insert(5);
    cout<<"size= "<<iset.size()<<endl;
    cout<<"3 count= "<<iset.count(3)<<endl;
//    iset.erase(1); RB树移除旋转未实现
    auto ite1=iset.find(1);
    if(ite1==iset.end()) cout<<"not find"<<endl;
    else cout<<"find= "<<*ite1<<endl;
    return 0;
}
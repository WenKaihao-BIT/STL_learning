//
// Created by Q on 2023/5/23.
//
#include "vector.h"
#include "iostream"
using namespace std;
int main(){
    wen::vector<int>a(5,5);
    wen::vector<int>b(6,6);
    for(auto item:a)cout<<item<<" ";cout<<endl;
    for(auto item:b)cout<<item<<" ";cout<<endl;
    a.swap(b);
    for(auto item:a)cout<<item<<" ";cout<<endl;
    for(auto item:b)cout<<item<<" ";cout<<endl;
    int c=5,d=6;
    int*p=&c,*q=&d;
    wen::swap(p,q);
    cout<<*p<<' '<<*q<<endl;




    return 0;
}
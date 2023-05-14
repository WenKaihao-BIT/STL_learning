//
// Created by Q on 2023/5/12.
//
#include "my_slist.h"

using namespace std;
int main(){
    int i;
    wen::slist<int>islist;
    cout<<"size = "<<islist.size()<<endl;
    islist.push_front(9);
    islist.push_front(1);
    islist.push_front(2);
    islist.push_front(3);
    islist.push_front(4);
    cout<<"size = "<<islist.size()<<endl;
    wen::slist<int>::iterator ite = islist.begin();
    wen::slist<int>::iterator ite2 = islist.end();
//    islist.begin()++;
//    islist.erase(ite);
    for(;ite!=ite2;++ite)
        cout<<*ite<<' ';
    cout<<endl;
//    cout<<"size = "<<islist.size()<<endl;
    ite = find(islist.begin(),islist.end(),3);
    if(ite!=0)
        islist.insert(ite,99);
    for(ite=islist.begin();ite!=ite2;++ite)
        cout<<*ite<<' ';
    cout<<endl;
    cout<<"size = "<<islist.size()<<endl;
    return 0;
}
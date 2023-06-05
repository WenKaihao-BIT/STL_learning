//
// Created by Q on 2023/5/24.
//
#include "algobase.h"
#include "iostream"
#include "../../SequenceContainer/vector_container/vector.h"
#include "../../SequenceContainer/list_container/list.h"
#include "algorithm"
using namespace std;

class C{
public:
    C():_data(3){}
private:
    int _data;
};
int main(){
    const char ccs[5]={'a','b','c','d','e'};
    char ccd[5];
//    wen::copy(ccs,ccs+5,ccd);

    const wchar_t cwcs[5]={'a','b','c','d','e'};
    wchar_t cwcd[5];
//    wen::copy(cwcs,cwcs+5,cwcd);
//    for(auto p=cwcd;p!=cwcd+5;p++)
//        cout<<*p<<' ';

    int ia[5]={0,1,2,3,4};
    wen::copy(ia,ia+5,ia);

    wen::list<int>ilists(ia,ia+5);



    return 0;
}
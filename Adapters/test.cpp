//
// Created by Q on 2023/5/30.
//
#include "myAdapters.h"
#include "iostream"
#include "../SequenceContainer/deque_container/mydeque.h"
using namespace std;
int main(){
    wen::deque<int>id1;
    id1.push_back(1);
    id1.push_back(0);
    id1.push_back(1);
    id1.push_back(2);
    id1.push_back(3);
    id1.push_back(4);
    id1.push_back(0);
    id1.push_back(1);
    id1.push_back(2);
    id1.push_back(5);
    id1.push_back(3);

    wen::reverse_iterator<wen::deque<int>::iterator>rite2(id1.end());
    cout<<*(rite2)<<endl;
    cout<<*(++++++rite2)<<endl;
    cout<<*(--rite2)<<endl;
    cout<<*(rite2.base())<<endl;
    wen::istream_iterator<int>a(cin);
    wen::ostream_iterator<int>b(cout);
    b=*(a);
    return 0;
}
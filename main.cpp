
#include<iostream>
#include "Containtor/sequence_containtor/myVector.h"
using namespace wen;

template<class T>
class test{
public:
    typedef T value_type;
    typedef value_type& reference ;
    typedef const value_type& const_reference ;
    test(int n,const_reference value){std::cout<<n<<'-'<<value<<std::endl;}
};
int main() {
//    myVector<int>iv(2,9);
//    test<int>iv(2,9);
    int a=4;
    std::cout<<&a;
    return 0;
}

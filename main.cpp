#include "allocator_learn.h"
#include<iostream>
#include<string>
#include<vector>
#include "new.h"
#include "containtor//myVector.h"
using namespace std;
class test{
public:
    test(const string &na,const int num):name(na),number(num){cout<<"调用构造函数"<<endl;}
    ~test(){cout<<"调用析构函数"<<endl;};
private:
    string name;
    int number;
};
int main() {
    test t("Li",123);
    auto p=&t;
    construct(p,t);
    destroy(p);
    return 0;
}

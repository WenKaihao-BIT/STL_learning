//
// Created by Q on 2023/5/23.
//
#include "numeric.h"
#include "iostream"
#include "vector"
using namespace std;
int main(){
    vector<int> nums={1,3,5,7,8};
    vector<int>result(10,0);
    auto first=result.begin();
    auto q=wen::adjacent_difference(nums.begin(),nums.end(),first);
    for(auto item:nums)cout<<item<<' ';cout<<endl;
    for(auto item:result)cout<<item<<' ';cout<<endl;
    cout<<*q<<endl;

    return 0;
}
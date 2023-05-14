//
// Created by Q on 2023/5/11.
//
#include "myheap.h"
#include "iostream"
#include "../vector_container/vector.h"
#include "vector"
int main(){
    int a=5;
    int *ptr=&a;
    wen::vector<int>::iterator iter;
    std::vector<int>nums={5,3,2,1,4};
    auto comp=std::less<std::vector<int>::value_type>();
    wen::push_heap(nums.begin(),nums.end(),comp);
    for(auto item:nums) std::cout<<item<<" ";std::cout<<std::endl;
//    wen::pop_heap(nums.begin(),nums.end(),comp);
//    for(auto item:nums) std::cout<<item<<" ";std::cout<<std::endl;
//    wen::sort_heap(nums.begin(),nums.end(),comp);
//    for(auto item:nums) std::cout<<item<<" ";std::cout<<std::endl;
    std::vector<int>nums2={1,2,3,4,5,6,7};
    wen::make_heap(nums2.begin(),nums2.end(),comp);
    for(auto item:nums2) std::cout<<item<<" ";

    return 0;
}
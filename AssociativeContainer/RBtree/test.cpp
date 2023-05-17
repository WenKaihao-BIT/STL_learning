//
// Created by Q on 2023/5/13.
//
#include "myRBtree.h"
#include "iostream"
#include "../../functional/myfuncitons.h"
#include "vector"
using namespace std;

int main(){
    wen::rb_tree<int,int,wen::identity<int>,less<int>>itree;
//    cout<<itree.empty()<<endl;
//    cout<<itree.size()<<endl;
    vector<int>nums={10,7,8,15,5,6,11,13,12};
    itree.insert_equal(nums.begin(),nums.end());
//    itree.insert_equal(nums.begin(),nums.end());
//    itree.insert_unique(3);
//    itree.insert_unique(8);
//    itree.insert_unique(5);
//    itree.insert_unique(9);
//    itree.insert_unique(13);
//    itree.insert_unique(5);
    cout<<"size= "<<itree.size()<<endl;
    wen::rb_tree<int,int,wen::identity<int>,less<int>>itree2;
    auto it=itree.begin();
    for(;it!=itree.end();++it)
        cout<<*it<<' ';
    cout<<endl;
    auto it1=itree.lower_bound(22);
    auto it2=itree.upper_bound(22);
    cout<<wen::distance(it1,it2)<<endl;
    auto it4=itree.find(6);
    if(it4!=itree.end())cout<<"Find : "<<*it4<<endl;
    else cout<<"not find"<<endl;
//    int ia[5]={0,1,2,3,4};
//    wen::rb_tree<int,int,wen::identity<int>,less<int>>itree3;
//    itree3.insert_unique(ia,ia+5);
    wen::rb_tree<int,int,wen::identity<int>,less<int>>::const_iterator it5;
    it5==it1;
    return 0;
}

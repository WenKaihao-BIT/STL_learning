//
// Created by Q on 2023/5/17.
//
using namespace std;
#include "iostream"
#include "mymap.h"
//#include "../../functional/myfuncitons.h"
int main(){
    wen::map<string,int>simap;
    simap[string("jjhou")]=1;
    simap[string("jerry")]=2;
    simap[string("jason")]=3;
    simap[string("jimmy")]=4;
//    auto q=select1st<pair<string,int>>::first_type;
//    cout<< typeid(select1st<pair<string,int>>::second_type).name()<<endl;
    wen::pair<const string,int>value(string("david"),5);
//    cout<<value.second<<endl;
    wen::map<string,int>::value_type a(string("david"),5);
    simap.insert(value);
    wen::map<string,int>::iterator simap_iter = simap.begin();
    for(;simap_iter!=simap.end();++simap_iter)
        cout<<simap_iter->first<<' '<<simap_iter->second<<endl;
    int number = simap[string("jjhou")];
    cout<<number<<endl;
    auto ite1 = simap.find(string("mchen"));
    if(ite1 == simap.end())
        cout<<"mchen not found"<<endl;
    auto ite2 = simap.find(string("jerry"));
    if(ite2 != simap.end())
        cout<<"jerry found"<<endl;
    ite1->second=9;
    int number2=simap[string("jerry")];
    cout<<number2<<endl;




    return 0;
}
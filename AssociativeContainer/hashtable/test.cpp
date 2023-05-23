//
// Created by Q on 2023/5/18.
//
#include "hashtable.h"
#include "iostream"
#include "../../functional/myfuncitons.h"
#include "my_hash_fun.h"
using namespace std;
int main(){
    wen::hashtable<int,int,std::hash<int>,
            wen::identity<int>,std::equal_to<int>,wen::alloc
                        >iht(50,std::hash<int>(),std::equal_to<int>());
    cout<<iht.size()<<endl;
    cout<<iht.bucket_count()<<endl;
    cout<<iht.max_bucket_count()<<endl;
    iht.insert_unique(59);
    iht.insert_unique(63);
    iht.insert_unique(108);
    iht.insert_unique(2);
    iht.insert_unique(53);
    iht.insert_unique(55);
    cout<<iht.size()<<endl;
    cout<<"------------"<<endl;
    auto ite=iht.begin();
    for(int i=0;i<iht.size();++i,++ite)
        cout<<*ite<<' ';
    cout<<endl;
    for(int i=0;i<iht.bucket_count();++i){
        int n=iht.elems_in_bucket(i);
        if(n!=0)
            cout<<"bucket ["<<i<<"] has "<<n<<" elems."<<endl;
    }
    cout<<"------------"<<endl;
    for (int i = 0; i <=47 ; ++i) {
        iht.insert_equal(i);
    }
    cout<<iht.size()<<endl;
    cout<<iht.bucket_count()<<endl;
    cout<<"------------"<<endl;
    for(int i=0;i<iht.bucket_count();++i){
        int n=iht.elems_in_bucket(i);
        if(n!=0)
            cout<<"bucket ["<<i<<"] has "<<n<<" elems."<<endl;
    }
    auto ite2=iht.begin();
    for(int i=0;i<iht.size();++i,++ite2)
        cout<<*ite2<<' ';
    cout<<endl;
    cout<<"------------"<<endl;
    cout<<*(iht.find(2))<<endl;
    cout<<iht.count(2)<<endl;
    wen::hashtable<int,int,std::hash<int>,
            wen::identity<int>,std::equal_to<int>,wen::alloc
    >iht3(50,std::hash<int>(),std::equal_to<int>());
    iht3.insert_unique(999);
    cout<<"iht3 size= "<<iht3.size()<<endl;
    iht.swap(iht3);
    cout<<"iht size= "<<iht.size()<<endl;
    ite2=iht.begin();
    for(int i=0;i<iht.size();++i,++ite2)
        cout<<*ite2<<' ';
    cout<<endl;
    ite2=iht3.begin();
    for(int i=0;i<iht3.size();++i,++ite2)
        cout<<*ite2<<' ';
    cout<<endl;
    return 0;
}
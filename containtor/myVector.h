//
// Created by Q on 2023/4/18.
//

#ifndef STL_LEARNING_MYVECTOR_H
#define STL_LEARNING_MYVECTOR_H
#include "iostream"
class alloc;


template<class T,class Alloc=alloc>
class myVector{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator; //Random Access Iterators
    typedef value_type& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
protected:
    typedef simple_alloc<value_type,Alloc> data_allocator;
    iterator start;
    iterator finish;
    iterator end_of_storage;
    void insert_aux(iterator position,const T&x);
    void dellocate(){
        if(start)
            data_allocator ::deallocate(start,end_of_storage-start);
    }
    void fill_initialize(size_type n,const T& value){
        start = allocate_and_fill(n,value);
        finish=start+n;
        end_of_storage = finish;
    }
public:
    iterator begin(){return start;}
    iterator end(){return finish;}
    size_type size()const{return size_type (end()-begin());}
    size_type capacity()const {
        return size_type (end_of_storage-begin());
    }
    bool empty()const{return begin()==end();}
    reference operator[](size_type n){return *(begin()+n);}
    myVector():start(0),finish(0),end_of_storage(0){}
    myVector(size_type n,const reference value){ fill_initialize(n,value);}
    myVector(long n,const reference value){ fill_initialize(n,value);}
    myVector(int n,const reference value){ fill_initialize(n,value);}
    explicit myVector(size_type n){ fill_initialize(n,T());}
    ~myVector(){
        destroy(start,finish);
    }
    reference front(){return *begin();}
    reference back(){return *(end()-1);}
    void push_back(const T& x){
        if(finish!=end_of_storage){
            construct(finish,x);
            ++finish;
        } else
            insert_aux(end(),x);
    }
    void pop_back(){
        --finish;
        destory(finish);
    }
    iterator erase(iterator position){
        if(position+1!=end())
            copy(position+1,finish,position);
        --finish;
        destory(finish);
        return position;
    }
    void resize(size_type new_size,const T& x){
        if(new_size<size())
            erase(begin()+new_size,end());
        else
            insert(end(),new_size-size(),x);
    }
    void resize(size_type new_size){ resize(new_size,T());}
protected:
    iterator allocate_and_fill(size_type n,const T& x){
        uninitialized_fill_n(result,n,x);
        return result;
    }















};
#endif //STL_LEARNING_MYVECTOR_H

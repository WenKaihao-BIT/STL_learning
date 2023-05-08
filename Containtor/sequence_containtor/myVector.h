//
// Created by Q on 2023/4/18.
//

#ifndef STL_LEARNING_MYVECTOR_H
#define STL_LEARNING_MYVECTOR_H
#include "iostream"
#include "../../myalloc/mymemory.h"
#endif //STL_LEARNING_MYVECTOR_H

namespace wen{
    template<class T,class Alloc=alloc>
    class myVector{
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef value_type* iterator; //Random Access Iterators
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
    protected:
        typedef simple_alloc<value_type,Alloc> data_allocator;
        iterator start;
        iterator finish;
        iterator end_of_storage;
        void insert_aux(iterator position,const T&x);
        void deallocate(){
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
        /** region ## 构造函数 ## */
        myVector():start(0),finish(0),end_of_storage(0){}
        myVector(size_type n,const_reference value){ fill_initialize(n,value);}
        myVector(long n,const_reference value){ fill_initialize(n,value);}
        myVector(int n,const_reference value){ fill_initialize(n,value);}
        explicit myVector(size_type n){ fill_initialize(n,T());}
        /** endregion */
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
            destroy(finish);
        }
        iterator erase(iterator position){
            /*用来消除迭代器位置处的元素
             * 将该位置后所有元素前移并用destroy回收最后一个元素*/
            if(position+1!=end())
                uninitialized_copy(position+1,finish,position);
            --finish;
            destroy(finish);
            return position;
        }
        iterator erase(iterator first,iterator last){
            iterator i= uninitialized_copy(last,finish,finish);
            destroy(i,finish);
            finish=finish-(last-first);
            return first;
        }
        void clear(){ erase(begin(),end());}
        void resize(size_type new_size,const T& x){
            if(new_size<size())
                erase(begin()+new_size,end());
            else
                insert(end(),new_size-size(),x);
        }
        void resize(size_type new_size){ resize(new_size,T());}
        void insert(iterator position,size_type n,const T&x);
    protected:
        iterator allocate_and_fill(size_type n,const T& x){
            iterator result=data_allocator ::allocate(n);
            uninitialized_fill_n(result,n,x);
            return result;
        }


    };

    template<class T, class Alloc>
    void myVector<T, Alloc>::insert_aux(myVector::iterator position, const T &x) {
    if(finish!=end_of_storage){
        construct(finish,*(finish-1));
        ++finish;
        value_type x_copy=x;
        std::copy_backward(position,finish-2,finish-1);
        *position=x_copy;
    } else{
        const size_type old_size=size();
        const size_type len=old_size!=0?2*old_size:1;
        iterator new_start=data_allocator ::allocate(len);
        iterator new_finish=new_start;
        try{
            new_finish= uninitialized_copy(start,position,new_start);
            construct(new_finish,x);
            ++finish;
            new_finish= uninitialized_copy(position,finish,new_finish);
        }

        catch (...) {
            destroy(new_start,new_finish);
            data_allocator ::deallocate(new_start,len);
            throw;
        }
        destroy(begin(),end());
        deallocate();
        start=new_start;
        finish=new_finish;
        end_of_storage=new_start+len;
    }
    }

    template<class T, class Alloc>
    void myVector<T, Alloc>::insert(myVector::iterator position, myVector::size_type n, const T &x) {
    if(n!=0){
        if(size_type(end_of_storage-finish)>=n){
            //剩余空间大于新增元素的个数
            value_type x_copy=x;
            const size_type elems_after=finish-position;
            iterator old_finish=finish;
            if(elems_after>n){
                uninitialized_copy(finish-n,finish,finish);
                finish+=n;
                std::copy_backward(position,old_finish-n,old_finish);
                std::fill(position,position+n,x_copy);
            } else{
                uninitialized_fill_n(finish,n-elems_after,x_copy);
                finish+=n-elems_after;
                uninitialized_copy(position,old_finish,finish);
                finish+=elems_after;
                std::fill(position,old_finish,x_copy);
            }
        } else{
                /*没看懂内容*/
        }
    }
    }
}


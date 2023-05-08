//
// Created by Q on 2023/5/5.
//

#ifndef STL_LEARNING_3AUTOPTR_H
#define STL_LEARNING_3AUTOPTR_H

#endif //STL_LEARNING_3AUTOPTR_H
template<class T>
class auto_ptr{
public:
    explicit auto_ptr(T*p=0):pointee(p){}
    template<class U>
    auto_ptr(auto_ptr<U>&rhs):pointee(rhs.release()){}
    ~auto_ptr(){delete pointee;}

    template<class U>
    auto_ptr<T>& operator=(auto_ptr<U>&rhs){
        if(this!=&rhs)reset(rhs.release());
        return *this;
    }
    T& operator*()const{return *pointee;}
    T* operator->()const{return pointee;}
    T* get()const{return pointee;}

private:
    T *pointee;
};
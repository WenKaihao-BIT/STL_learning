//
// Created by Q on 2023/4/12.
//

#ifndef STL_LEARNING_3MYLIST_ITER_H
#define STL_LEARNING_3MYLIST_ITER_H
#include "3mylist.h"

template<class Item>
struct ListIter{
    Item *ptr;
    explicit ListIter(Item *p= nullptr):ptr(p){}
    Item& operator*()const{return *ptr;}
    Item* operator->() const{return ptr;}
    ListIter&operator++(){
        ptr=ptr->next();
        return *this;
    }
    ListIter operator++(int){
        ListIter tmp = *this;
        ++*this;
        return tmp;
    }
    bool operator==(const ListIter& i) const{
        return ptr==i.ptr;
    }
    bool operator!=(const ListIter& i) const{
        return ptr!=i.ptr;
    }

};

template<typename T>
bool operator!=(const ListItem<T>&item,T n){
    return item.value()!=n;
}

template<class Item>
struct Listiter2:public std::iterator_traits<std::forward_iterator_tag>{
    
    };
#endif //STL_LEARNING_3MYLIST_ITER_H

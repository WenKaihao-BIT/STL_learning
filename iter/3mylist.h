//
// Created by Q on 2023/4/12.
//

#ifndef STL_LEARNING_3MYLIST_H
#define STL_LEARNING_3MYLIST_H
#include "iostream"

template<typename T>class ListItem;

/** region ## List ## */
template<typename T>
class List{

public:
    void insert_front(T value);
    void insert_end(T value);
    void display(std::ostream&os=std::cout) const;
    ListItem<T>*front()const{return _front;}
    ListItem<T>*end()const{return _end;}
    long size()const{return _size;}
private:
    ListItem<T>*_end= nullptr;
    ListItem<T>*_front= nullptr;
    long _size=0;

};

template<typename T>
void List<T>::insert_front(T value) {
    ListItem<T>*tmp=new ListItem<T>(value);
    if(tmp) {
        tmp->_next = _front;
        _front = tmp;
        if(_size==0)
            _end=_front;
        _size++;
    }
}

template<typename T>
void List<T>::insert_end(T value) {
    ListItem<T>*tmp=new ListItem<T>(value);
    if(tmp) {
        if(_size==0)
            this->insert_front(value);
        else{
            _end->_next=tmp;
            _end=tmp;
            _size++;
        }
    }
}

template<typename T>
void List<T>::display(std::ostream &os) const {
    auto ptr=_front;
    while (ptr!= nullptr){
        os<<ptr->_value<<' ';
        ptr=ptr->_next;
    }

    os<<std::endl;
}
/** endregion */
/** region ## ListItem ## */
template<typename T>
class ListItem{
    friend  class List<T>;
public:
    explicit ListItem(const T& val):_value(val),_next(nullptr){}
    T value() const {return _value;}
    ListItem* next() const {return _next;}
private:
    T _value;
    ListItem* _next;
};
/** endregion */

#endif //STL_LEARNING_3MYLIST_H

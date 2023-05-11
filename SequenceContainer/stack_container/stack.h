//
// Created by Q on 2023/5/11.
//

#ifndef STL_LEARNING_MYSTACK_H
#define STL_LEARNING_MYSTACK_H
#include "../../my_config.h"
#include "../deque_container/mydeque.h"
#endif //STL_LEARNING_MYSTACK_H

namespace wen{

    template<class T,class Sequence = deque<T>>
    class stack{
        friend bool operator==(const stack&, const stack&);
        friend bool operator<(const stack&, const stack&);
    public:
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::size_type size_type;
        typedef typename Sequence::reference reference;
        typedef typename Sequence::const_reference const_reference;
    protected:
        Sequence c;
    public:
        stack()=default;
        bool empty()const{return c.empty;}
        size_type size()const{return c.size();}
        reference top(){return c.back();}
        const_reference top()const{return c.back();}
        void push(const value_type& x){ return c.push_back(x);}
        void pop(){c.pop_back();}
    };

    template<class T,class Sequence>
    bool operator==(const stack<T,Sequence>& x, const stack<T,Sequence>& y){
        return x.c==y.c;
    }
    template<class T,class Sequence>
    bool operator<(const stack<T,Sequence>& x, const stack<T,Sequence>& y) {
        return x.c<y.c;
    }
}

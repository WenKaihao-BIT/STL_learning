//
// Created by Q on 2023/5/12.
//

#include <cstddef>
#include "../../myalloc/mymemory.h"
#include "../../my_config.h"
#ifndef STL_LEARNING_MY_SLIST_H
#define STL_LEARNING_MY_SLIST_H

#endif //STL_LEARNING_MY_SLIST_H
namespace wen{
    struct __slit_node_base{
        __slit_node_base* next;
    };
    template<class T>
    struct __slist_node:public __slit_node_base{
        T data;
    };
    //全局函数，在其后插入新节点
    inline __slit_node_base* __slist_make_link
        (__slit_node_base* prev_node,__slit_node_base* new_node){
            new_node->next=prev_node->next;
            prev_node->next=new_node;
        return new_node;
    }
    inline size_t __slist_size(__slit_node_base* node){
        size_t result= 0;
        for(;node!=0;node=node->next)
            ++result;
        return result;
    }
    struct __slist_iterattor_base{
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef forward_iterator_tag iterator_category;

        __slit_node_base * node;
        __slist_iterattor_base(__slit_node_base* x):node(x){}
        void incr(){node=node->next;}
        bool operator==(const __slist_iterattor_base& x)const{
            return node==x.node;
        }
        bool operator!=(const __slist_iterattor_base& x){
            return node!=x.node;
        }
    };
    template<class T,class Ref,class Ptr>
    struct __slist_iterator: public __slist_iterattor_base{
        typedef __slist_iterator<T,T&,T*>  iterator;
        typedef __slist_iterator<T,const T&,const T*>  const_iterator;
        typedef __slist_iterator<T,Ref,Ptr>    self;

        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef __slist_node<T> list_node;

        __slist_iterator(list_node* x): __slist_iterattor_base(x){}
        __slist_iterator(): __slist_iterattor_base(0){}
        __slist_iterator(const iterator& x): __slist_iterattor_base(x.node){}

        reference operator*()const{return ((list_node*)node)->data;}
        pointer operator->()const{return &(operator*());}

        self & operator++(){
            incr();
            return *this;
        }
        self &operator++(int){
            self tmp=*this;
            incr();
            return tmp;
        }


    };

    template<class T,class Alloc=alloc>
    class slist{
    public:
        typedef T value_type;//1
        typedef  __slist_iterator<T,T&,T*> iterator;
        typedef  const __slist_iterator<T,T&,T*> const_iterator;
        typedef value_type& reference;  //2
        typedef size_t size_type;   //3
        typedef value_type *pointer;    //4
        typedef const value_type& const_reference;
        typedef bidirectional_iterator_tag iterator_category;//5
        typedef ptrdiff_t difference_type;

    private:
        typedef __slist_node<T>list_node;
        typedef __slit_node_base list_node_base;
        typedef __slist_iterattor_base iterator_base;
        typedef simple_alloc<list_node> list_node_allocator;

        static list_node* create_node(const value_type & x){
            list_node* node =list_node_allocator::allocate();
            __STL_TRY{
                construct(&node->data,x);
                node->next=0;
            }
            __STL_UNWIND(list_node_allocator::deallocate(node));
            return node;
        }
        static void destroy_node(list_node* node){
            destroy(&node->data);
        }

    private:
        list_node_base head;
    public:
        slist(){head.next=0;}
        ~slist(){clear();}

    public:
        iterator begin(){return iterator((list_node*)head.next);}
        iterator end(){return iterator(0);}
        size_type size() const{return __slist_size(head.next);}
        bool empty()const{return head.next==0;}
        void swap(slist&L){
            list_node_base*tmp=head.next;
            head.next=L.head.next;
            L.head.next=tmp;
        }
        iterator erase(iterator position){
//            if(position<*this->begin()||position>*this->end())
//                return iterator(0);
            iterator tmp=position;
            ++position;
            *tmp=*position;
            tmp.node->next=position.node->next;
            destroy_node((list_node*)position.node);
            return position;
        }
        void insert(iterator position,const value_type& x){
            value_type x_copy=x;
            list_node *tmp= create_node(x_copy);
            tmp->next=position.node->next;
            position.node->next=tmp;
        }
    public:
        reference front(){return ((list_node*)head.next)->data;}
        void push_front(const value_type&x){
            __slist_make_link(&head, create_node(x));
        }
        void pop_front(){
            list_node *node = (list_node*)head.next;
            head.next = node->next;
            destroy_node(node);
        }
        void clear(){
            iterator tmp=begin();
            while (tmp!=end()){
                destroy_node((list_node*)tmp.node);
                tmp++;
            }
        }
    };





}

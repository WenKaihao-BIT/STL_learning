//
// Created by Q on 2023/5/7.
//

#ifndef STL_LEARNING_MYLIST_H
#define STL_LEARNING_MYLIST_H
#include "../../iter/my_traits.h"
#include "../../myalloc/mymemory.h"
#endif //STL_LEARNING_MYLIST_H
namespace wen{
    /** region ## __list_node-4.9 ## */
        template<class T>
        struct __list_node{
            typedef void* void_pointer;
            void_pointer prev;
            void_pointer next;
            T data;
        };
    /** endregion */

    /** region ## __list_node-4.9 ## */
//    struct _List_node_base{
//        _List_node_base *_M_next;
//        _List_node_base *_M_prev;
//    };
//
//    template<typename T>
//    struct __list_node:public _List_node_base{
//        T _M_data;
//    };
    /** endregion */

    /** region ## list-iterator ## */
    template<class T,class Ref,class Ptr>
    struct __list_iterator{
        typedef __list_iterator<T,T&,T*>    iterator;
        typedef __list_iterator<T,Ref,Ptr>  self;

        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef __list_node<T>* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        link_type node;

        //constructor
        __list_iterator(link_type x):node(x){}
        __list_iterator(){}
        __list_iterator(const iterator& x):node(x.node){}

        bool operator==(const self& x)const {return node==x.node;}
        bool operator!=(const self& x)const {return node!=x.node;}

        reference operator*()const{return (*node).data;}

        pointer operator->()const{return &(operator*());}

        self& operator++(){
            node=(link_type)((*node).next);
            return *this;
        }
        self& operator++(int){
            self tmp=*this;
            ++*this;
            return tmp;
        }

        self& operator--(){
            node=(link_type)((*node).prev);
            return *this;
        }
        self& operator--(int){
            self tmp=*this;
            --*this;
            return tmp;
        }

    };
/** endregion */
    /** region ## list ## */
    template<class T,class Alloc=alloc>
    class myList{
    protected:
        typedef __list_node<T> list_node;
        //空间配置器
        typedef simple_alloc<list_node,Alloc>list_node_allocator;

    public:
        typedef list_node * link_type;
        typedef T value_type;
        typedef  __list_iterator<T,T&,T*> iterator;
        typedef  const __list_iterator<T,T&,T*> const_iterator;
        typedef value_type& reference;
        typedef size_t size_type;
        typedef bidirectional_iterator_tag iterator_category;//双向的
        typedef ptrdiff_t difference_type;

    protected:
        link_type node;
    public:
        iterator begin(){return (link_type)((*node).next);}
        const_iterator begin()const{return (link_type)((*node).next);}
        iterator end()const{return node;}
        iterator end(){return node;}
        bool empty()const{return node->next==node;}
        difference_type size()const{
            difference_type result=0;
            //此处为什么要用const版本？？
            result=distance(begin(),end());
            return result;
        }
        reference front(){return *begin();}
        reference back(){return *(--end());}
    protected:
        //配置一个节点并传回
        link_type get_node(){return list_node_allocator ::allocate();}
        //释放一个节点
        void put_node(link_type p){list_node_allocator ::deallocate(p);}
        //产生一个节点，配置其元素
        link_type create_node(const T& x){
            link_type p=get_node();
            construct(&p->data,x);
            return p;
        }
        //销毁一个节点
        void destroy_node(link_type p){
            destroy(&p->data);
            put_node(p);
        }
    public:
        myList(){empty_initialize();}


        void push_back(const T&x){ insert(end(),x);}
        void push_front(const T&x){ insert(begin(),x);}
        //在position插入一个节点
        iterator insert(iterator position,const T&x);
        //移除position处的节点
        iterator erase(iterator position);
        void pop_front(){ erase(begin());}
        void pop_back(){iterator tmp=end();
            erase(--tmp);}
        void clear();
        void remove(const T& value);
    protected:
        void empty_initialize(){
            node = get_node();
            node->next=node;
            node->prev=node;
        }
    };

    template<class T, class Alloc>
    typename myList<T,Alloc>::iterator
    myList<T, Alloc>::insert(myList::iterator position, const T &x){
        link_type tmp= create_node(x);
        tmp->next=position.node;
        tmp->prev=position.node->prev;
        (link_type(position.node->prev)->next)=tmp;
        position.node->prev=tmp;
        return tmp;
    }

    template<class T, class Alloc>
    typename myList<T,Alloc>::iterator
    myList<T, Alloc>::erase(iterator position) {
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next=next_node;
        next_node->prev=prev_node;
        return iterator (next_node);
    }

    template<class T, class Alloc>
    void myList<T, Alloc>::clear() {
        link_type cur=(link_type) node->next;
        while (cur!=node){
            link_type tmp=cur;
            cur=(link_type)cur->next;
            destroy_node(tmp);
        }
        node->next=node;
        node->prev=node;

    }

    template<class T, class Alloc>
    void myList<T, Alloc>::remove(const T &value) {
        iterator first=begin();
        iterator last=end();
        while (first!=last){
            iterator next=first;
            ++next;
            if(*first==value)erase(first);
            first=next;
        }
    }




/** endregion */
}
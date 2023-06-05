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

        //循环链表
        iterator operator+(int n){
            iterator result=*this;
            while (n!=0){
                ++result;
                --n;
            }
            return result;
        }
        iterator operator-(int n){
            iterator result=*this;
            while (n!=0){
                --result;
                --n;
            }
            return result;
        }


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
    class list{
    protected:
        typedef __list_node<T> list_node;
        //空间配置器
        typedef simple_alloc<list_node,Alloc>list_node_allocator;

    public:
        typedef list_node * link_type;
        typedef T value_type;   //1
        typedef  __list_iterator<T,T&,T*> iterator;
        typedef  const __list_iterator<T,T&,T*> const_iterator;
        typedef value_type& reference;  //2
        typedef size_t size_type;   //3
        typedef value_type *pointer;    //4
        typedef const value_type& const_reference;
        typedef bidirectional_iterator_tag iterator_category;   //5双向的
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
        list(){empty_initialize();}


        void push_back(const T&x){ insert(end(),x);}
        void push_front(const T&x){ insert(begin(),x);}
        //在position插入一个节点
        iterator insert(iterator position,const T&x);
        template<class InputIterator>
        void insert(iterator position,InputIterator first,InputIterator last){
            for(;first!=last;first++)
                insert(position,*first);
        }
        //移除position处的节点
        iterator erase(iterator position);
        void pop_front(){ erase(begin());}
        void pop_back(){iterator tmp=end();
            erase(--tmp);}
        void clear();
        void remove(const T& value);
        //移除数值相同的连续元素
        void unique();
        //将第二个链表接到position之后
        void splice(iterator position, list<T>&x){
            if(!x.empty())
                transfer(position,x.begin(),x.end());
        }
        void splice(iterator position, list<T>&, iterator i){
            iterator j=i;
            ++j;
            if(position==i||position==j) return;
            transfer(position,i,j);
        }
        void splice(iterator position, list<T>&, iterator first, iterator last){
            if(first!=last)
                transfer(position,first,last);
        }
        //将两个通过递增排序的链表合并
        void merge(list<T>&x){
            iterator first1=begin();
            iterator last1=end();
            iterator first2=x.begin();
            iterator last2=x.end();

            while (first1!=last1&&first2!=last2){
                if(*first2<*first1){
                    iterator next=first2;
                    transfer(first1,first2,++next);
                    first2=next;
                } else
                    ++first1;
            }
            if(first2!=last2)transfer(last1,first2,last2);
        }
        void swap(list<T>&x){
            list<T>tmp=*this;
            *this=x;
            x=tmp;
        }
        //将链表倒置
        void reverse();
        void sort();

    protected:
        void empty_initialize(){
            node = get_node();
            node->next=node;
            node->prev=node;
        }
        //将[first,last)移动到position之前
        void transfer(iterator position,iterator first,iterator last);
    };

    template<class T, class Alloc>
    typename list<T,Alloc>::iterator
    list<T, Alloc>::insert(list::iterator position, const T &x){
        link_type tmp= create_node(x);
        tmp->next=position.node;
        tmp->prev=position.node->prev;
        (link_type(position.node->prev)->next)=tmp;
        position.node->prev=tmp;
        return tmp;
    }

    template<class T, class Alloc>
    typename list<T,Alloc>::iterator
    list<T, Alloc>::erase(iterator position) {
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next=next_node;
        next_node->prev=prev_node;
        destroy_node(position.node);
        return iterator (next_node);
    }

    template<class T, class Alloc>
    void list<T, Alloc>::clear() {
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
    void list<T, Alloc>::remove(const T &value) {
        iterator first=begin();
        iterator last=end();
        while (first!=last){
            iterator next=first;
            ++next;
            if(*first==value)erase(first);
            first=next;
        }
    }

    template<class T, class Alloc>
    void list<T, Alloc>::unique() {
        iterator first = begin();
        iterator last = end();
        if(first==last) return;
        iterator next=first;
        while (++next!=last){
            if(*first==*next)
                erase(next);
            else
                first=next;
            next=first;
        }
    }

    template<class T, class Alloc>
    void list<T, Alloc>::transfer(iterator position, iterator first, iterator last) {
        if(position!=last){
            (*(link_type((*last.node).prev))).next=position.node;
            (*(link_type((*first.node).prev))).next=last.node;
            (*(link_type ((*position.node).prev))).next=first.node;
            link_type tmp=link_type ((*position.node).prev);
            (*position.node).prev=(*last.node).prev;
            (*last.node).prev=(*first.node).prev;
            (*first.node).prev=tmp;

        }
    }

    template<class T, class Alloc>
    void list<T, Alloc>::reverse() {
        if(node->next==node||link_type(node->next)->next==node)
            return;
        iterator first = begin();
        ++first;
        while (first!=end()){
            iterator old=first;
            ++first;
            transfer(begin(),old,first);
        }
    }

    template<class T, class Alloc>
    void list<T, Alloc>::sort() {
        if(node->next==node||link_type(node->next)->next==node)
            return;
        list<T>carry;
        list<T>counter[64];
        int fill = 0;
        while (!empty()){
            carry.splice(carry.begin(),*this,begin());
            int i=0;
            while (i<fill&&!counter[i].empty()){
                counter[i].merge(carry);
                carry.swap(counter[i++]);
            }
            carry.swap(counter[i]);
            if(i==fill) ++fill;
        }
        for(int i=1;i<fill;++i)
            counter[i].merge(counter[i-1]);
        swap(counter[fill-1]);

    }




/** endregion */
}
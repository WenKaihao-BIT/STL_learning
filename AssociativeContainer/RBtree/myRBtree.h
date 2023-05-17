//
// Created by Q on 2023/5/13.
//
#include "../../myalloc/mymemory.h"
#include "../../my_config.h"
#include "../pair/mypair.h"

#ifndef STL_LEARNING_MYRBTREE_H
#define STL_LEARNING_MYRBTREE_H

#endif //STL_LEARNING_MYRBTREE_H
typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;
namespace wen{
    /** region ## 声明 ## */
    struct __rb_tree_node_base;

    template<class value>
    struct __rb_tree_node;

    struct __rb_tree_base_iterator;

    template<class value,class Ref,class Ptr>
    struct __rb_tree_iterator;

    template<class Key,class Value,class KeyOfValue,
            class Compare,class Alloc>
    class rb_tree;

    void __rb_tree_rotate_left(__rb_tree_node_base*x,__rb_tree_node_base*& root);

    void __rb_tree_rotate_right(__rb_tree_node_base*x,__rb_tree_node_base*& root);

    void __rb_tree_rebalance(__rb_tree_node_base* x,__rb_tree_node_base*& root);
    /** endregion */

    struct __rb_tree_node_base{
        typedef __rb_tree_color_type color_type;
        typedef __rb_tree_node_base* base_ptr;

        color_type color;   //节点颜色，非红即黑
        base_ptr parent;    //RB树父亲节点
        base_ptr left;      //指向左节点
        base_ptr right;     //指向右节点
        static base_ptr minimum(base_ptr x){
            while (x->left!=0)  x=x->left;
            return x;
        }
        static base_ptr maximum(base_ptr x){
            while (x->right!=0) x=x->right;
            return x;
        }
    };

    template<class value>
    struct __rb_tree_node:public __rb_tree_node_base{
        typedef __rb_tree_node<value>* link_type;
        value value_field;
    };
    struct __rb_tree_base_iterator{
        typedef __rb_tree_node_base::base_ptr base_ptr;
        typedef bidirectional_iterator_tag  iterator_category;//5
        typedef ptrdiff_t difference_type;//4
        base_ptr node;
        void increment(){
            if(node->right!=0){
                node=node->right;
                while (node->left!=0)
                    node= node->left;
            }
            else{
                base_ptr y=node->parent;
                while (node==y->right){
                    node=y;
                    y=y->parent;
                }
                if(node->right!=y)
                    node=y;
            }

        }
        void decrement(){
            //node指向end()
            if(node->color==__rb_tree_red&&node->parent->parent==node)
                node=node->right;
            else if(node->left!=0){
                base_ptr y=node->left;
                while (y->right!=0)
                    y=y->right;
                node=y;
            }
            else{
                base_ptr y= node->parent;
                while (node==y->left){
                    node=y;
                    y=y->parent;
                }
                node=y;
            }
        }
    };

    template<class value,class Ref,class Ptr>
    struct __rb_tree_iterator:public __rb_tree_base_iterator{
        typedef value value_type;//1
        typedef Ref reference;//2
        typedef Ptr pointer;//3
        typedef __rb_tree_iterator<value,value&,value*> iterator;
        typedef __rb_tree_iterator<value,const value&,const value*> const_iterator;
        typedef __rb_tree_iterator<value,Ref,Ptr> self;
        typedef __rb_tree_node<value>* link_type;

        __rb_tree_iterator(){}
        __rb_tree_iterator(link_type x){node=x;}
        __rb_tree_iterator(const iterator& it){node=it.node;}

        reference operator*()const{return link_type(node)->value_field;}
        pointer operator->()const{return &(operator*());}

        self& operator++(){increment();return *this;}
        self operator++(int){
            self tmp=*this;
            increment();
            return tmp;
        }

        self& operator--(){decrement();return *this;}
        self operator--(int){
            self tmp=*this;
            decrement();
            return tmp;
        }

        bool operator==(const iterator& x)const{
            return x.node== this->node;
        }
        bool operator!=(const iterator& x)const{
            return !(*this==x);
        }
    };

    template<class Key,class Value,class KeyOfValue,
            class Compare,class Alloc=alloc>
    class rb_tree{
    protected:
        typedef void* void_pointer;
        typedef __rb_tree_node_base* base_ptr;
        typedef __rb_tree_node<Value> rb_tree_node;
        typedef simple_alloc<rb_tree_node,Alloc> rb_tree_node_allocator;
        typedef __rb_tree_color_type color_type;
    public:
        typedef Key key_type;
        typedef Value value_type;
        typedef value_type* pointer;
        typedef const value_type * const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef rb_tree_node* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
    protected:
        link_type get_node(){return rb_tree_node_allocator::allocate(); }
        void put_node(link_type p){rb_tree_node_allocator::deallocate(p);}
        link_type create_node(const value_type& x){
            link_type tmp=get_node();
            __STL_TRY{
                construct(&tmp->value_field,x);
            }
            __STL_UNWIND(put_node(tmp));
            return tmp;
        }
        link_type clone_node(link_type x){
            link_type tmp= create_node(x->value_field);
            tmp->color=x->color;
            tmp->left=0;
            tmp->right=0;
            return tmp;
        }
        void destroy_node(link_type p){
            destroy(&p->value_field);
            put_node(p);
        }
    protected:
        size_type node_count;
        link_type header;
        Compare key_compare;

        link_type& root()const{return (link_type&)header->parent;}
        link_type& leftmost()const{return (link_type&)header->left;}
        link_type& rightmost()const{return (link_type&)header->right;}

        static link_type& left(link_type x){
            return (link_type&)(x->left);
        }
        static link_type& right(link_type x){
            return (link_type&)(x->right);
        }
        static link_type& parent(link_type x){
            return (link_type&)(x->parent);
        }
        static reference value(link_type x){
            return x->value_field;
        }
        static const Key& key(link_type x){
            return KeyOfValue()(value(x));
        }
        static color_type& color(link_type x){
            return (color_type&)(x->color);
        }

        static link_type& left(base_ptr x){
            return (link_type&)(x->left);
        }
        static link_type& right(base_ptr x){
            return (link_type&)(x->right);
        }
        static link_type& parent(base_ptr x){
            return (link_type&)(x->parent);
        }
        static reference value(base_ptr x){
            return ((link_type)x)->value_field;
        }
        static const Key& key(base_ptr x){
            return KeyOfValue()(value(link_type (x)));
        }
        static color_type& color(base_ptr x){
            return (color_type&)(link_type (x)->color);
        }

        //求最大最小值
        static link_type maximum(link_type x){
            return (link_type)__rb_tree_node_base::maximum(x);
        }
        static link_type minimum(link_type x){
            return (link_type)__rb_tree_node_base::minimum(x);
        }
    public:
        typedef __rb_tree_iterator<value_type,reference,pointer> iterator;
        typedef const __rb_tree_iterator<value_type,reference,pointer> const_iterator;
    private:
        iterator __insert(base_ptr x_,base_ptr y_,const value_type& v);
        link_type __copy(link_type x,link_type p);
        void __erase(link_type x);
        void init(){
            header=get_node();
            color(header)=__rb_tree_red; //令header为红色
            root()=0;
            leftmost()=header;  //令header的左子节点为自己
            rightmost()=header; //令header的右子节点为自己
        }
    public:
        rb_tree(const Compare& comp=Compare())
            :node_count(0),key_compare(comp){init();}
        ~rb_tree(){
//            clear();
            put_node(header);
        }
        rb_tree<Key,Value,KeyOfValue,Compare,Alloc>&
            operator=(const rb_tree<Key,Value,KeyOfValue,Compare,Alloc>& x){
                this->header=x.header;
                this->node_count=x.node_count;
                this->key_compare=x.key_compare;
        }
    public:
        Compare key_comp()const{return key_compare;}
        iterator begin(){return leftmost();}
        iterator end(){return header;}
        iterator begin()const{return leftmost();}
        iterator end()const{return header;}

        bool empty()const{return node_count==0;}
        size_type max_size(){return size_type(-1);}
        size_t size()const{return node_count;}
        void swap(const rb_tree<Key,Value,KeyOfValue,Compare,Alloc>&x);
        void clear(){
            iterator tmp= this->begin();
            while (tmp!=this->end()){
                put_node(((link_type)tmp.node));
                ++tmp;
            }
            node_count=0;
        }
        iterator lower_bound(const key_type& k){
            link_type y=header;
            link_type x=root();
            while (x!=0){
                if(!key_compare(key(x),k)){
                    y=x;
                    x= left(x);
                }
                else
                    x= right(x);
            }
            return iterator(y);
        }
        iterator lower_bound(const key_type& k)const{
            link_type y=header;
            link_type x=root();
            while (x!=0){
                if(!key_compare(key(x),k)){
                    y=x;
                    x= left(x);
                }
                else
                    x= right(x);
            }
            return iterator(y);
        }
        iterator upper_bound(const key_type& k){
            link_type y=header;
            link_type x=root();
            while (x!=0){
                if((key_compare(k,key(x)))){
                    y=x;
                    x=left(x);
                }
                else
                    x=right(x);
            }
            return iterator(y);

        }
        iterator upper_bound(const key_type& k)const{
            link_type y=header;
            link_type x=root();
            while (x!=0){
                if((key_compare(k,key(x)))){
                    y=x;
                    x=left(x);
                }
                else
                    x=right(x);
            }
            return iterator(y);

        }
        pair<iterator,iterator> equal_range(const key_type& x){
            return std::pair<iterator,iterator>(lower_bound(x), upper_bound(x));
        }
        pair<iterator,iterator> equal_range(const key_type& x)const{
            return pair<iterator,iterator>(lower_bound(x), upper_bound(x));
        }
        difference_type count(const key_type& x)const{
            pair<iterator,iterator>tmp= equal_range(x);
            return distance(tmp.first,tmp.second);
        }
        void erase();
        iterator find(const key_type& k){
            link_type y=header;
            link_type x=root();
            while (x!=0){
                if(!(key_compare(key(x),k))){
                    y=x;
                    x= left(x);
                } else
                    x= right(x);
            }
            iterator j=iterator(y);
            return (j==end()||key_compare(k,key(j.node)))?end():j;
        }

    public:
        //节点值允许重复
        iterator insert_equal(const value_type& v);
        //迭代器版本
        template<class InputIterator>
            iterator insert_equal(InputIterator first,InputIterator last);
        //不允许节点重复
        pair<iterator,bool> insert_unique(const value_type& v);
        //迭代器版本
        template<class InputIterator>
        pair<iterator,bool>insert_unique(InputIterator first,InputIterator last);



    };

    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const value_type &v) {
        link_type y = header;
        link_type x=root();
        while (x!=0){
            y=x;
            x=key_compare(KeyOfValue()(v),key(x))? left(x): right(x);
        }
        return __insert(x,y,v);
    }

    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    template<class InputIterator>
    typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(InputIterator first, InputIterator last) {
        iterator result;
        while (first!=last){
            result= insert_equal(*first);
            first++;
        }
        return result;
    }

    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    pair<typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator,bool>
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const value_type &v) {
        link_type y = header;
        link_type x=root();
        bool comp= true;
        while (x!=0){
            y=x;
            comp=key_compare(KeyOfValue()(v),key(x));
            x=comp? left(x): right(x);
        }
        iterator j=iterator(y);
        if(comp)
            if(j==begin())
                return pair<iterator,bool>(__insert(x,y,v), true);
            else
                --j;
        if(key_compare(key(j.node),KeyOfValue()(v)))
            return pair<iterator,bool>(__insert(x,y,v), true);
        return pair<iterator,bool>(j, false);
    }

    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    template<class InputIterator>
    pair<typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator, bool>
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(InputIterator first, InputIterator last) {
        pair<iterator,bool>result;
        while (first!=last){
            result= insert_unique(*first);
            first++;
        }
        return result;
    }


    template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__insert(rb_tree::base_ptr x_, rb_tree::base_ptr y_,
                                                              const value_type &v) {
        link_type x=(link_type)x_;
        link_type y=(link_type)y_;
        link_type z;
        if(y==header||x!=0||key_compare(KeyOfValue()(v),key(y))){
            z= create_node(v);//产生一个新节点
            left(y)=z;//满足key值小于父节点，成为父节点的左孩子
            if(y==header){//空树
                root()=z;
                rightmost()=z;
            }
            // y为最左边的节点
            else if(y == leftmost())
                leftmost()=z;
        }
        else{
            z= create_node(v);
            right(y)=z;
            if(y==rightmost())
                rightmost()=z;
        }
        parent(z)=y;
        left(z)=0;
        right(z)=0;

        __rb_tree_rebalance(z,header->parent);
        ++node_count;
        return iterator(z);
    }




    inline void
    __rb_tree_rebalance(__rb_tree_node_base* x,__rb_tree_node_base*& root) {
        x->color = __rb_tree_red;
        while (x != root && x->parent->color == __rb_tree_red) {//父节点为红
            if (x->parent == x->parent->parent->left) {//父节点为祖父节点的左子结点
                __rb_tree_node_base *y = x->parent->parent->right;
                if (y && y->color == __rb_tree_red) {//伯父节点存在且为红
                    // 父节点和伯父节点都为红色，则把这两个节点改成黑色，祖父节点改为红色
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    x = x->parent->parent;
                }
                else {//无伯父节点或者伯父节点为黑
                    if (x == x->parent->right) {//情况2
                        x = x->parent;
                        __rb_tree_rotate_left(x, root);
                    }
                    //情况1
                    x->parent->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    __rb_tree_rotate_right(x->parent->parent, root);
                }
            }
            else {//父节点为祖父节点的右子结点
                __rb_tree_node_base *y = x->parent->parent->left;
                if (y && y->color == __rb_tree_red) {//伯父节点存在且为红
                    // 父节点和伯父节点都为红色，则把这两个节点改成黑色，祖父节点改为红色
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    x->parent->parent->color = __rb_tree_red;
                    x=x->parent->parent;
                }
                else{
                    if(x==x->parent->left){
                        x=x->parent;
                        __rb_tree_rotate_right(x,root);
                    }
                    x->parent->color=__rb_tree_black;
                    x->parent->parent->color=__rb_tree_red;
                    __rb_tree_rotate_left(x->parent->parent,root);
                }

            }
        }
        root->color=__rb_tree_black;
    }

    inline void
    __rb_tree_rotate_left(__rb_tree_node_base*x,__rb_tree_node_base*& root){
        __rb_tree_node_base* y=x->right;
        x->right=y->left;
        if(y->left!=0)
            y->left->parent=x;
        y->parent=x->parent;
        if(x==root)
            root = y;
        else if(x==x->parent->left)
            x->parent->left=y;
        else
            x->parent->right=y;
        y->left=x;
        x->parent=y;
    }
    inline void
    __rb_tree_rotate_right(__rb_tree_node_base*x,__rb_tree_node_base*& root){
        __rb_tree_node_base*y=x->left;
        x->left=y->right;
        if(y->right!=0)
            y->right->parent=x;
        y->parent=x->parent;
        if(x==root)
            root=y;
        else if(x==x->parent->left)
            x->parent->left=y;
        else
            x->parent->right=y;
        y->right=x;
        x->parent=y;
    }

}

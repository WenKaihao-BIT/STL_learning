//
// Created by Q on 2023/5/17.
//
#include "../../myalloc/mymemory.h"
#include "../RBtree/myRBtree.h"
#include "../../functional/myfuncitons.h"
#ifndef STL_LEARNING_MYMAP_H
#define STL_LEARNING_MYMAP_H

#endif //STL_LEARNING_MYMAP_H
namespace wen{
    template<class Key, class T,
            class Compare = std::less<Key>, class Alloc=alloc>
    class map{
    public:
        typedef Key key_type;
        typedef T data_type;
        typedef T mapped_type;
        typedef pair<const Key,T> value_type;
        typedef Compare key_compare;

        class value_compare
                :public binary_function<value_type,value_type,bool>{
            friend class map<Key,T,Compare,Alloc>;
        protected:
            Compare comp;
            value_compare(Compare c):comp(c){}
        public:
            bool operator()(const value_type&x,const value_type&y)const{
                return comp(x.first,y.first);
            }
        };
    private:
        typedef rb_tree<key_type,value_type,
            select1st<value_type>,key_compare,Alloc> rep_type;
        rep_type t;
    public:
        /** region ## typedef ## */
        typedef typename rep_type ::pointer pointer;
        typedef typename rep_type ::const_pointer const_pointer;
        typedef typename rep_type ::reference reference;
        typedef typename rep_type ::const_reference  const_reference;
        //允许通过迭代器修改元素的实值
        typedef typename rep_type ::iterator iterator;
        typedef typename rep_type ::const_iterator const_iterator;
//        typedef typename rep_type ::reverse_iterator reverse_iterator;
//        typedef typename rep_type ::const_reverse_iterator const_reverse_iterator;
        typedef typename rep_type ::size_type size_type;
        typedef typename rep_type ::difference_type difference_type;
        /** endregion */

        /** region ## 内存分配器、回收器 ## */

        /** endregion */

        /** region ## 拷贝构造函数 ## */
        map():t(Compare()){}
        explicit map(const Compare& comp):t(comp){}

        template<class InputIterator>
        map(InputIterator first,InputIterator last):t(Compare())
                {t.insert_unique(first,last);}
        template<class InputIterator>
        map(InputIterator first,InputIterator last,const Compare& comp):t(comp)
        {t.insert_unique(first,last);}

        map(const map<Key,T,Compare,Alloc>&x):t(x.t){}
        /** endregion */

        /** region ## 操作符重载 ## */
        map<Key,T,Compare,Alloc>& operator=(const map<Key,T,Compare,Alloc>&x){
            t=x.t;
            return *this;
        }
        T& operator[](const key_type& k){
            return (*((insert(value_type(k,T()))).first)).second;
        }

        friend bool operator==(const map&,const map&);
        friend bool operator<(const map&,const map&);


        /** endregion */

        /** region ## 操作行为 ## */
        key_compare key_comp() const {return t.key_comp();}
        value_compare value_comp() const {return value_compare(t.key_comp());}
        iterator begin(){return t.begin();}
        const_iterator begin()const{return t.begin();}
        iterator end() {return t.end();}
        const_iterator end() const {return t.end();}
        //rbegin rend
        bool empty()const{return t.empty();}
        size_type size()const{return t.size();}
        size_type max_size()const{return t.max_size();}
        void swap(map<Key,T,Compare,Alloc>&x){
            return t.swap(x.t);
        }
        //insert
        pair<iterator,bool>insert(const value_type& x){
            return t.insert_unique(x);
        }
        iterator insert(iterator position,const value_type& x){
            typedef typename rep_type::iterator rep_iterator;
            return t.insert_unique((rep_iterator&)position,x);
        }
        template<class InputIterator>
        void insert(InputIterator first,InputIterator last){
            t.insert_unique(first,last);
        }
        //erase
        void erase(iterator position){
            typedef typename rep_type::iterator rep_iterator;
            t.erase((rep_iterator&)position);
        }
        size_type erase(const key_type&x){
            return t.erase(x);
        }
        void erase(iterator first,iterator last){
            typedef typename rep_type::iterator rep_iterator;
            t.erase((rep_iterator&)first,(rep_iterator&)last);
        }
        
        void clear(){t.clear();}
        /** endregion */
        
        /** region ## map操作 ## */
        iterator find(const key_type& x){return t.find(x);}
        const_iterator find(const key_type& x)const{return t.find(x);}
        size_type count(const key_type& x)const{return t.count(x);}
        iterator lower_bound(const key_type& x){return t.lower_bound(x);}
        const_iterator lower_bound(const key_type& x)const{return t.lower_bound(x);}
        iterator upper_bound(const key_type& x){return t.upper_bound(x);}
        const_iterator upper_bound(const key_type& x)const{return t.upper_bound(x);}
        pair<iterator,iterator>equal_range(const key_type&x){
            return t.equal_range(x);
        }
        pair<const_iterator,const_iterator>equal_range(const key_type&x)const{
            return t.equal_range(x);
        }
        /** endregion */





    };

    template<class Key, class T,class Compare, class Alloc>
    inline bool operator==(const map<Key,T,Compare,Alloc>&x,
            const map<Key,T,Compare,Alloc>&y){
        return x.t=y.t;
    }
    template<class Key, class T,class Compare, class Alloc>
    inline bool operator<(const map<Key,T,Compare,Alloc>&x,
                           const map<Key,T,Compare,Alloc>&y){
        return x.t<y.t;
    }
}
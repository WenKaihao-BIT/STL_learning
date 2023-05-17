//
// Created by Q on 2023/5/17.
//
#include "iostream"
#include "../../myalloc/mymemory.h"
#include "../RBtree/myRBtree.h"
#include "../../functional/myfuncitons.h"
#ifndef STL_LEARNING_MULTISET_H
#define STL_LEARNING_MULTISET_H

#endif //STL_LEARNING_MULTISET_H
namespace wen{
    template<class Key,class Compare=std::less<Key>,class Alloc = alloc>
    class multiset{
    public:
        typedef Key key_type;
        typedef Key value_type;

        //key value采用同一个比较函数
        typedef Compare key_compare;
        typedef Compare value_compare;
    private:
        typedef rb_tree<key_type,value_type,
        identity<value_type>,key_compare,Alloc> rep_type;
        rep_type t;
    protected:
        typedef  multiset<Key,Compare,Alloc> self;
    public:
        typedef typename rep_type::const_reference reference;
        typedef typename rep_type ::const_reference const_reference;
        typedef typename rep_type ::const_pointer pointer;
        typedef typename rep_type ::const_pointer const_pointer;
        typedef typename rep_type ::const_iterator iterator;

        typedef typename rep_type::const_iterator const_iterator;
        //待完善
//        typedef typename rep_type ::const_reverse_iterator reverse_iterator;
//        typedef typename rep_type::const_iterator const_reverse_iterator;

        typedef typename rep_type ::size_type size_type;
        typedef typename rep_type ::difference_type difference_type;
    public:
        multiset():t(Compare()){}
        explicit  multiset(const Compare& comp):t(comp){}

        template<class InputIterator>
        multiset(InputIterator first,InputIterator last)
                :t(Compare()){t.insert_equal(first,last);}

        template<class InputIterator>
        multiset(InputIterator first,InputIterator last,const Compare&comp)
                :t(comp){t.insert_equal(first,last);}

        multiset(const  multiset<Key,Compare,Alloc>& x):t(x.t){}
        self & operator=( multiset<Key,Compare,Alloc>& x){t=x.t;return *this;}
    public:
        key_compare key_comp()const{return t.key_comp();}
        value_compare value_comp()const{return t.key_comp();}

        iterator begin()const{return t.begin();}
        iterator end()const{return t.end();}

//        reverse_iterator rbegin();
//        reverse_iterator rend();
        bool empty()const{return t.empty();}
        size_type size()const{return t.size();}
        size_type max_size()const{return t.max_size();}


        void swap( multiset<Key,Compare,Alloc>&x){t.swap(x.t);}
        pair<iterator,bool>insert(const value_type& x){
            pair<typename rep_type::iterator,bool>p=t.insert_equal(x);
            return pair<iterator,bool>(p.first,p.second);
        }
        iterator insert(iterator position,const value_type& x){
            typedef typename rep_type::iterator rep_iterator;
            return t.insert_equal((rep_iterator&)position,x);
        }

        template<class InputIterator>
        void insert(InputIterator first,InputIterator last){
            t.insert_equal(first,last);
        }

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

        // multiset operation:
        iterator find(const key_type& x){return t.find(x);}
        const_iterator find(const key_type& x)const{return t.find(x);}
        size_type count(const key_type& x)const{return t.count(x);}
        iterator lower_bound(const key_type& x)const{return t.lower_bound(x);}
        iterator upper_bound(const key_type& x)const{return t.upper_bound(x);}
        pair<iterator,iterator>equal_range(const key_type&x)const{
            return t.equal_range(x);
        }
    };

    template<class Key,class Compare,class Alloc>
    inline bool operator==(const  multiset<Key,Compare,Alloc>&x,
                           const   multiset<Key,Compare,Alloc>&y){
        return x.t==y.t;
    }

    template<class Key,class Compare,class Alloc>
    inline bool operator<(const  multiset<Key,Compare,Alloc>&x,
                          const   multiset<Key,Compare,Alloc>&y){
        return x.t<y.t;
    }


}
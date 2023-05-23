//
// Created by Q on 2023/5/22.
//
#include "iostream"
#include "../../myalloc/myalloc.h"
#include "../hashtable/hashtable.h"
#ifndef STL_LEARNING_MYHASHSET_H
#define STL_LEARNING_MYHASHSET_H

#endif //STL_LEARNING_MYHASHSET_H

namespace wen{
    template<class Value,
             class HashFcn=std::hash<Value>,
             class EqualKey=std::equal_to<Value>,
             class Alloc = alloc>
    class hash_set{
    private:
        typedef hashtable<Value,Value,HashFcn,EqualKey,Alloc> ht;
        ht rep;
    public:
    public:
        typedef typename ht::key_type key_type;
        typedef typename ht ::value_type value_type;
        typedef typename ht::asher hasher;
        typedef typename ht ::key_equal key_equal;
        typedef typename ht::size_type size_type;
        typedef typename ht::difference_type difference_type;
        typedef typename ht::const_pointer pointer;
        typedef typename ht::const_pointer const_pointer;
        typedef typename ht::const_reference reference;
        typedef typename ht::const_reference const_reference;
        typedef typename ht::const_iterator iterator;
        typedef typename ht::const_iterator const_iterator;

        hasher hash_funct()const { return rep.hash_funct();}
        key_equal key_eq() const { return rep.key_eq();}
    public:
        hash_set():rep(100,hasher(),key_equal()){}
        explicit hash_set(size_type n):rep(n,hasher(),key_equal()){}
        hash_set(size_type n,const hasher&hf):rep(n,hf,key_equal()){}
        hash_set(size_type n,const hasher&hf,const key_equal&eql):rep(n,hf,eql){}

        template<class InputIterator>
        hash_set(InputIterator f,InputIterator l)
                :rep(100,hasher(),key_equal()){rep.insert_unique(f,l);}

        template<typename InputIterator>
        hash_set(InputIterator f,InputIterator l,size_type n,const hasher& hf)
                :rep(n,hf,key_equal()){rep.insert_unique(f,l);}
    public:
        size_type size()const{return rep.size();}
        size_type max_size()const{return rep.max_size();}
        bool empty()const{return rep.empty();}
        void swap(hash_set& hs){rep.swap(hs.rep);}
        friend bool operator==(const hash_set&,const hash_set&);
        //set不支持修改
        iterator begin()const{return rep.begin();}
        iterator end()const{return rep.end();}
    public:
        pair<iterator,bool>insert(const value_type& obj){
            pair<typename ht::iterator,bool>p=rep.insert_unique(obj);
            return pair<iterator,bool>(p.first,p.second);
        }

        template<typename InputIterator>
        void insert(InputIterator f,InputIterator l){rep.insert_unique(f,l);}
        iterator find(const key_type& key){return rep.find(key);}
        iterator count(const key_type& key){return rep.count(key);}
        size_type erase(const key_type& key){return rep.erase(key);}
        void erase(iterator it){rep.erase(it);}
        void erase(iterator f,iterator l){rep.erase(f,l);}
        void clear(){rep.clear();}


    };

    template<class Value,class HashFcn,class EqualKey,class Alloc >
    bool operator==(const hash_set<Value,HashFcn,EqualKey,Alloc>&hs1,
            const hash_set<Value,HashFcn,EqualKey,Alloc>&hs2) {
        return hs1.rep==hs2.rep;
    }


}
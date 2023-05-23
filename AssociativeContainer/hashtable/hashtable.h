//
// Created by Q on 2023/5/18.
//



#ifndef STL_LEARNING_HASHTABLE_H
#define STL_LEARNING_HASHTABLE_H
#include "../../myalloc/mymemory.h"
#include "../../SequenceContainer/vector_container/vector.h"
#include "../../my_config.h"
#include "prime.h"
#include "../pair/mypair.h"
#include "../../functional/myfuncitons.h"



namespace wen{
    /** region ## hashtable_node ## */
    template<class Value>
    struct __hashtable_node{
        __hashtable_node* next;
        Value val;
    };
    /** endregion */
    
    /** region ## hashtable_iterator ## */
    template<class Value, class Key, class HashFcn,
            class ExtractKey,class EqualKey,class Alloc=alloc>
    class hashtable;

    template<class Value, class Key, class HashFcn,
            class ExtractKey,class EqualKey,class Alloc>
    struct __hashtable_iterator;





    template<class Value, class Key, class HashFcn,
            class ExtractKey,class EqualKey,class Alloc>
    struct __hashtable_iterator{
        typedef hashtable<Value,Key,HashFcn,ExtractKey,EqualKey,Alloc> hashtable;
        typedef __hashtable_iterator<Value,Key,HashFcn,ExtractKey,EqualKey,Alloc> iterator;
//        typedef __hashtable_const_iterator<Value,Key,HashFcn,ExtractKey,EqualKey,Alloc> const_iterator;
        typedef __hashtable_node<Value> node;

        typedef forward_iterator_tag iterator_category;
        typedef Value value_type;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef Value& reference;
        typedef Value* pointer;

        node* cur;
        hashtable* ht;

        /** region ## 构造拷贝函数 ## */
        __hashtable_iterator(node* n,hashtable* tab):cur(n),ht(tab){}
        __hashtable_iterator()= default;
        /** endregion */

        /** region ## 操作符重载 ## */
        reference operator*()const{return cur->val;}
        pointer operator->()const{return &(operator*());}
        iterator& operator++(){
            const node* old=cur;
            cur=cur->next;
            if(!cur){
                size_type bucket=ht->bkt_num(old->val);
                while (!cur&&++bucket<ht->buckets.size())
                    cur=ht->buckets[bucket];
            }
            return *this;
        }
        iterator operator++(int){
            iterator tmp=*this;
            ++*this;
            return tmp;
        }
        bool operator==(const iterator& it)const{return cur==it.cur;}
        bool operator!=(const iterator& it)const{return cur!=it.cur;}
        /** endregion */






    };
    /** endregion */
    /** region ## hashtable ## */
    template<class Value, class Key, class HashFcn,
            class ExtractKey,class EqualKey,class Alloc>
    class hashtable{
    public:
        typedef HashFcn hasher;
        typedef EqualKey key_equal;
        typedef size_t size_type;
        typedef Value value_type;//1
        typedef Key key_type;
        typedef __hashtable_iterator<Value,Key,HashFcn
                    ,ExtractKey,EqualKey,Alloc> iterator;
        typedef const __hashtable_iterator<Value,Key,HashFcn
                ,ExtractKey,EqualKey,Alloc> const_iterator;
        friend struct
                __hashtable_iterator<Value,Key,HashFcn
                        ,ExtractKey,EqualKey,Alloc>;


    private:
        hasher hash;
        key_equal equals;
        ExtractKey get_key;

        typedef __hashtable_node<Value> node;
        typedef simple_alloc<node,Alloc> node_allocator;

        vector<node*,Alloc>buckets;
        size_type num_elements;
    public:

    public:
        size_type bucket_count()const{return buckets.size();}
        size_type max_bucket_count()const{return __stl_prime_list[__stl_num_primes-1];}


    protected:

        /** region ## 节点配置和释放 ## */
        node* new_node(const value_type& obj){
            node* n=node_allocator ::allocate();
            n->next=0;
            __STL_TRY{
                construct(&n->val,obj);
                return n;
            }
            __STL_UNWIND(node_allocator::deallocate(n))

        }
        void delete_node(node* n){
            destroy(&n->val);
            node_allocator ::deallocate(n);
        }
        void initialize_buckets(size_type n){
            const size_type n_buckets=next_size(n);
            buckets.reserve(n_buckets);
            buckets.insert(buckets.end(),n_buckets,(node*)0);
            num_elements=0;
        }
        size_type next_size(size_type n)const{return __stl_next_prime(n);}//返回接近n并大于n的质数
        /** endregion */

        void resize(size_type num_elements_hint);
        size_type bkt_num(const value_type&obj,size_type n)const
        {return bkt_num_key(get_key(obj),n);}
        size_type bkt_num(const value_type&obj){
            return bkt_num_key(get_key(obj));
        }
        size_type bkt_num_key(const key_type& key)const{
            return bkt_num_key(key,buckets.size());
        }
        size_type bkt_num_key(const key_type& key,size_t n)const{
            return hash(key)%n;
        }


        pair<iterator,bool>insert_unique_noresize(const value_type& obj);
        iterator insert_equal_noresize(const value_type&obj);
    public:
        /** region ## 构造拷贝析构函数 ## */
        hashtable(size_type n,const HashFcn& hf,const EqualKey& eql):
        hash(hf),equals(eql),get_key(ExtractKey()),num_elements(0){initialize_buckets(n);}
        void clear(){
            for(size_type i=0;i<buckets.size();++i){
                node* cur=buckets[i];
                while (cur!=0){
                    node* next=cur->next;
                    delete_node(cur);
                    cur=next;
                }
                buckets[i]=0;
            }
            num_elements = 0;
        }
        size_type size()const{return num_elements;}

        /** endregion */

        /** region ## 操作 ## */
        ///键值不允许重复
        pair<iterator,bool>insert_unique(const value_type& obj){
            resize(num_elements+1);
            return insert_unique_noresize(obj);
        }
        ///键值允许重复
        iterator insert_equal(const value_type& obj){
            resize(num_elements+1);
            return insert_equal_noresize(obj);
        }
        ///拷贝
        void copy_from(const hashtable& ht);
        ///迭代器
        iterator begin(){
            for(size_type n=0;n<buckets.size();++n)
                if(buckets[n])
                    return iterator(buckets[n],this);
            return end();
        }
        const_iterator begin()const{
            for(size_type n=0;n<buckets.size();++n)
                if(buckets[n])
                    return iterator(buckets[n],this);
            return end();
        }
        iterator end(){return iterator(0, this);}
        const_iterator end()const{return iterator(0, this);}
        size_type elems_in_bucket(size_type bucket){
            size_type result=0;
            for(node*cur=buckets[bucket];cur;cur=cur->next)
                result+=1;
            return result;
        }
        iterator find(const key_type&key){
            size_type n= bkt_num_key(key);
            node *first;
            for(first=buckets[n];first&&!equals(get_key(first->val),key);
                                            first=first->next){}
            return iterator(first,this);
        }
        size_type count(const key_type& key)const{
            const size_type n= bkt_num_key(key);
            size_type result=0;
            for(node*cur=buckets[n];cur;cur=cur->next)
                if(equals(get_key(cur->val),key))
                    ++result;
            return result;
        }
        size_type nax_size()const{return (size_type)-1;}
        bool empty()const{return size()==0;}
        void swap(hashtable& ht){
            wen::swap(hash,ht.hash);
            wen::swap(equals,ht.equals);
            wen::swap(get_key,ht.get_key);
            buckets.swap(ht.buckets);
            wen::swap(num_elements,ht.num_elements);
        }
        /** endregion */


    };

    template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    void hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::resize(hashtable::size_type num_elements_hint) {
        const size_type old_n = buckets.size();
        //拿元素的个数和 bucket vector的大小比较
        if(num_elements_hint>old_n){
            const size_type n= next_size(num_elements_hint);
            if(n>old_n){
                vector<node*,Alloc>tmp(n,(node*)0);
                  for(size_type bucket = 0;bucket<old_n;++bucket){
                      node* first=buckets[bucket];
                      while (first){
                          //计算元素在新的buckets的编号
                          size_type new_bucket = bkt_num(first->val,n);
                          //指向下一个元素
                          buckets[bucket]=first->next;
                          //头部插入
                          first->next = tmp[new_bucket];
                          tmp[new_bucket]=first;
                          //取得下一个node
                          first=buckets[bucket];
                      }
                  }

                buckets.swap(tmp);
            }
        }
    }

    template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    pair<typename hashtable<Value, Key, HashFcn, ExtractKey,EqualKey,Alloc>::iterator, bool>
    hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::insert_unique_noresize(const value_type &obj) {
        const size_type n = bkt_num(obj);
        node *first=buckets[n];
        for(node*cur=first;cur;cur=cur->next){
            if(equals(get_key(cur->val),get_key(obj)))
                return pair<iterator,bool>(iterator(cur,this), false);

        }
        node* tmp= new_node(obj);
        tmp->next=first;
        buckets[n]=tmp;
        ++num_elements;
        return pair<iterator,bool>(iterator(tmp,this),true);

    }

    template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    typename hashtable<Value, Key, HashFcn, ExtractKey,EqualKey,Alloc>::iterator
    hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::insert_equal_noresize(const value_type &obj) {

        const size_type n = bkt_num(obj);
        node *first=buckets[n];
        for(node*cur=first;cur;cur=cur->next){
            if(equals(get_key(cur->val),get_key(obj))){
                node*tmp= new_node(obj);
                tmp->next=cur->next;
                cur->next=tmp;
                ++num_elements;
                return iterator(tmp,this);
            }

        }
        node* tmp= new_node(obj);
        tmp->next=first;
        buckets[n]=tmp;
        ++num_elements;
        return iterator(tmp,this);

    }

    template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
    void hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::copy_from(const hashtable &ht) {
        buckets.clear();
        buckets.reserve(ht.buckets.size());
        buckets.insert(buckets.end(),ht.buckets.size(),(node*)0);
        __STL_TRY{
            for(size_type i=0;i<ht.buckets.size();++i){
                if(const node* cur=ht.buckets[i]){
                    node*copy= new_node(cur->val);
                    buckets[i]=copy;

                    for(node*next=cur->next;next;next=cur->next){
                        copy->next= new_node(next->val);
                        copy=copy->next;
                    }
                }
            }
            num_elements=ht.num_elements;
        }
        __STL_UNWIND(clear())
    }

    /** endregion */




}

#endif //STL_LEARNING_HASHTABLE_H
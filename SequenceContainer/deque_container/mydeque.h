//
// Created by Q on 2023/5/9.
//

#ifndef STL_LEARNING_MYDEQUE_H
#define STL_LEARNING_MYDEQUE_H

#include "../../myalloc/mymemory.h"
#include "../../iter/my_traits.h"
#include "../../my_config.h"
#endif //STL_LEARNING_MYDEQUE_H
namespace wen{

    /** region ## deque-iterator ## */
    size_t __deque_buf_size(size_t n,size_t sz);
    template<class T,class Ref,class Ptr,size_t BufSize>
    struct __deque_iterator{
        typedef __deque_iterator<T,T&,T*,BufSize> iterator;
        typedef __deque_iterator<T,const T&,const T*,BufSize> const_iterator;
        static size_t buffer_size(){return __deque_buf_size(BufSize, sizeof(T));}

//        typedef random_access_iterator_tag iterator_category;   //1
        typedef input_iterator_tag iterator_category;
        typedef T value_type;   //2
        typedef Ptr pointer;    //3
        typedef Ref reference;  //4
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;  //5
        typedef T** map_pointer;

        typedef __deque_iterator self;

        T* cur;
        T* first;
        T* last;
        map_pointer node;

        void set_node(map_pointer new_node){
            node=new_node;
            first=*new_node;
            last=first+difference_type(buffer_size());
        }
        reference operator*()const{return *cur;}
        pointer operator->()const{return &(operator*());}
        difference_type operator-(const self &x)const{
            return difference_type (buffer_size())*(node-x.node-1)+
                    (cur-first)+(x.last-x.cur);
        }
        self &operator++(){
            ++cur;
            if(cur==last){
                set_node(node+1);
                cur=first;
            }
            return *this;
        }
        self &operator++(int){
            self tmp=*this;
            ++*this;
            return tmp;
        }
        self &operator--(){
            if(cur==last){
                set_node(node-1);
                cur=first;
            }
            --cur;
            return *this;
        }
        self &operator--(int){
            self tmp=*this;
            --*this;
            return tmp;
        }
        self &operator+=(difference_type n){
            difference_type offset = n+(cur-first);
            //目标位置不在同一缓冲区
            if(offset>=0&&offset<difference_type(buffer_size()))
                cur+=n;
            //目标位置在同一缓冲区
            else{
                difference_type node_offset=
                        offset>0?offset/difference_type(buffer_size())
                        :-difference_type ((-offset-1)/buffer_size())-1;
                set_node(node+node_offset);
                cur=first+(offset-node_offset*difference_type(buffer_size()));
            }
            return *this;
        }
        self &operator-=(difference_type n){return *this+=-n;}
        self operator+(difference_type n)const{
            self tmp=*this;
            return tmp+=n;
        }
        self operator-(difference_type n)const{
            return (*this)-=n;
        }
        reference operator[](difference_type n)const{return *(*this+n);}
        bool operator==(const self& x)const{return cur==x.cur;}
        bool operator!=(const self& x)const{return !(*this==x);}
        bool operator<(const self& x)const{
            return (node==x.node)?(cur<x.cur):(node<x.node);
        }
    };
    inline size_t __deque_buf_size(size_t n,size_t sz){
        return n!=0?n:((sz<512?size_t(512/sz):size_t(1)));
    }
    /** endregion */

    /** region ## deque ## */
    template<class T,class Alloc=alloc,size_t BufSiz=0>
    class deque{
    public:
        typedef T value_type;
        typedef  __deque_iterator<T,T&,T*,BufSiz> iterator;
        typedef  const __deque_iterator<T,T&,T*,BufSiz> const_iterator;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;
        typedef size_t size_type;
        typedef bidirectional_iterator_tag iterator_category;//双向的
        typedef ptrdiff_t difference_type;
    protected:
        typedef pointer* map_pointer;

    protected://Data members
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size;
    public:
        iterator begin(){return start;}
        iterator end(){return finish;}
        reference operator[](size_t n){
            return start[difference_type(n)];
        }
        reference front(){return *start;}
        reference back(){
            iterator tmp = finish;
            --tmp;
            return *tmp;
        }
        size_t size()const{return finish-start;}
        //max_size??? 返回-1？
        size_t max_size() const {return size_type (-1);}
        bool empty()const{return finish==start;}
        void push_back(const value_type& t){
            if(finish.cur!=finish.last-1){
                construct(finish.cur,t);
                ++finish.cur;
            } else
                push_back_aux(t);
        }
        void pop_back(){
            if(finish.cur!=finish.first){
                --finish.cur;
                destroy(finish.cur);
            }
            else
                pop_back_aux();
        }
        void push_front(const value_type& t){
            if(start.cur!=start.first){
                construct(start.cur-1,t);
                --start.cur;
            } else
                push_front_aux(t);
        }
        void pop_front(){
            if(start.cur!=start.last-1){
                destroy(start.cur);
                ++start.cur;
            }
            else
                pop_front_aux();
        }
        void clear();
        iterator erase(iterator pos);
        iterator erase(iterator first,iterator last);
        iterator insert(iterator position ,const value_type &x);
    protected:
        //空间分配
        typedef simple_alloc<value_type,Alloc>data_allocator;
        typedef simple_alloc<pointer,Alloc>map_allocator;
        //配置缓存区
        typedef simple_alloc<value_type>node_allocator;
        enum {__initial_map_size=8};
        void fill_initialize(size_type n,const value_type& value);
        void create_map_nodes(size_type num_elements);
        pointer allocate_node(){
            return (pointer)node_allocator::allocate(iterator::buffer_size()/ sizeof(value_type));
        }
        void deallocate_node( T* ptr){
            node_allocator ::deallocate(ptr,iterator::buffer_size()/sizeof(value_type));
        }
        size_t initial_map_size(){return __initial_map_size;}
        void push_back_aux(const value_type& t);
        void pop_back_aux();
        void push_front_aux(const value_type& t);
        void pop_front_aux();
        void reserve_map_at_back(size_type nodes_to_add=1);
        void reserve_map_at_front(size_type nodes_to_add=1);
        void reallocate_map(size_type nodes_to_add,bool add_at_front);
        iterator insert_aux(iterator position ,const value_type &x);
    public:
        //construct
        deque(int n,const value_type& value):start(),finish(),map(0),map_size(0){
            fill_initialize(n,value);
        }
        deque():start(),finish(),map(0),map_size(0){
            fill_initialize(0,value_type());
        };
    };

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::fill_initialize
            (deque::size_type n, const value_type &value) {
        create_map_nodes(n);
        map_pointer cur;
        __STL_TRY{
            for(cur = start.node;cur<finish.node;++cur)
                uninitialized_fill(*cur,*cur+iterator::buffer_size(),value);
            uninitialized_fill(finish.first,finish.cur,value);
        } catch (...) {

        }
    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::create_map_nodes(deque::size_type num_elements) {
        //一个map要管理几个节点，最少8个，最多所需节点数+1
        size_type num_nodes = num_elements/iterator::buffer_size()+1;
        map_size= std::max(initial_map_size(),num_nodes+2);
        map=map_allocator ::allocate(map_size);
        //使得nstart和nfinish指向全部节点的最中央区段
        map_pointer nstart = map+(map_size-num_nodes)/2;
        map_pointer nfinish = nstart+num_nodes-1;
        map_pointer cur;
        __STL_TRY{
            for(cur=nstart;cur<=nfinish;++cur)
                *cur = allocate_node();
        }
        catch (...) {

        }
        start.set_node(nstart);
        finish.set_node(nfinish);
        start.cur=start.first;
        finish.cur=finish.first+num_elements%iterator::buffer_size();


    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::push_back_aux(const value_type &t) {
//        std::cout<<"in push_back_aux"<<std::endl;
        value_type t_copy = t;
        reserve_map_at_back();
        *(finish.node+1)=allocate_node();
        __STL_TRY{
            construct(finish.cur,t_copy);
            finish.set_node(finish.node+1);
            finish.cur=finish.first;
        }
        __STL_UNWIND(deallocate_node(*(finish.node+1)));

    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::push_front_aux(const value_type &t) {
        value_type t_copy = t;
        reserve_map_at_front();
        *(start.node-1)=allocate_node();
        __STL_TRY{
            start.set_node(start.node-1);
            start.cur=start.last-1;
            construct(start.cur,t_copy);
        }
        catch (...) {
            start.set_node(start.node+1);
            start.cur=start.first;
            deallocate_node(*(start.node-1));
        }
    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::reserve_map_at_back(deque::size_type nodes_to_add) {
        if(nodes_to_add+1>map_size-(finish.node-map))
            reallocate_map(nodes_to_add, false);
    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::reserve_map_at_front(deque::size_type nodes_to_add) {
        if(nodes_to_add>start.node-map)
            reallocate_map(nodes_to_add, true);
    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::reallocate_map(deque::size_type nodes_to_add, bool add_at_front) {
        size_type old_num_nodes = finish.node-start.node+1;
        size_type new_num_nodes = old_num_nodes+nodes_to_add;
        map_pointer new_nstart;
        if(map_size>2*new_num_nodes){
            new_nstart = map+(map_size-new_num_nodes)/2+(add_at_front?nodes_to_add:0);
            if(new_nstart<start.node)
                std::copy(start.node,finish.node+1,new_nstart);
            else
                std::copy_backward(start.node,finish.node+1,new_nstart+old_num_nodes);
        }
        else{
            size_type new_map_size=map_size+std::max(map_size,nodes_to_add)+2;
            map_pointer new_map =map_allocator ::allocate(new_map_size);
            new_nstart=new_map+(new_map_size-new_num_nodes)/2
                       +(add_at_front?nodes_to_add:0);
            std::copy(start.node,finish.node+1,new_nstart);
            map_allocator ::deallocate(map,map_size);
            map = new_map;
            map_size = new_map_size;
        }

        start.set_node(new_nstart);
        finish.set_node(new_nstart+old_num_nodes-1);
    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::clear() {
        //策略 保留1个缓存区
        for(map_pointer node = start.node+1;node<finish.node;++node){
            destroy(*node,*node+iterator::buffer_size());
            data_allocator ::deallocate(*node,iterator::buffer_size());
        }
        if(start.node!=finish.node){
            destroy(start.cur,start.last);
            destroy(finish.cur,finish.last);
            data_allocator ::deallocate(finish.first,iterator::buffer_size());
        }
        else
            destroy(start.cur,start.last);
        finish=start;
    }

    template<class T, class Alloc, size_t BufSiz>
    typename deque<T,Alloc,BufSiz>::iterator deque<T, Alloc, BufSiz>::erase(deque::iterator pos) {
        iterator next=pos;
        ++next;
        difference_type index=pos-start;
        if(index<(size()>>1)){
            std::copy_backward(start,pos,next);//存在问题
            pop_front();
        }
        else{
            std::copy(next,finish,pos);
            pop_back();
        }
        return start+index;
    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::pop_back_aux() {
        //只有当finish.cur==finish.first时才会被调用，此时该节点对于内存为空
        deallocate_node(finish.first);
        finish.set_node(finish.node-1);
        finish.cur=finish.last-1;
        destroy(finish.cur);
    }

    template<class T, class Alloc, size_t BufSiz>
    void deque<T, Alloc, BufSiz>::pop_front_aux() {
        destroy(start.cur);
        deallocate_node(start.first);
        start.set_node(start.node+1);
        start.cur=start.first;
    }

    template<class T, class Alloc, size_t BufSiz>
    typename deque<T,Alloc,BufSiz>::iterator
    deque<T, Alloc, BufSiz>::erase(deque::iterator first, deque::iterator last) {

        if(first==start&& last==finish){
            clear();
            return finish;
        }
        else{
            difference_type n = last-first;
            difference_type elems_before = first-start;
            if(elems_before<(size()-n)/2){
                std::copy_backward(start,first,last);
                iterator new_start = start+n;
                destroy(start,new_start);
                for(map_pointer cur=start.node;cur<new_start.node;++cur)
                    data_allocator ::deallocate(*cur,iterator::buffer_size());
                start=new_start;
            }
            else{
                std::copy(last,finish,first);
                iterator new_finish = finish - n;
                destroy(new_finish,finish);
                for(map_pointer cur=new_finish+1;cur<=finish.node;++cur)
                    data_allocator ::deallocate(*cur,iterator::buffer_size());
                finish = new_finish;
            }
            return start+elems_before;

        }
    }

    template<class T, class Alloc, size_t BufSiz>
    typename deque<T,Alloc,BufSiz>::iterator
    deque<T, Alloc, BufSiz>::insert(deque::iterator position, const value_type &x) {
        if(position.cur==start.cur){
            push_front(x);
            return start;
        }
        else if(position.cur == finish.cur){
            push_back(x);
            iterator tmp = finish;
            --tmp;
            return tmp;
        } else{
            return insert_aux(position,x);
        }
    }

    template<class T, class Alloc, size_t BufSiz>
    typename deque<T,Alloc,BufSiz>::iterator
    deque<T, Alloc, BufSiz>::insert_aux(deque::iterator position, const value_type &x) {
        difference_type index = position - start;
        value_type x_copy =x;
        if(index<size()/2){
            push_front(front());
            iterator front1=start;
            ++front1;
            iterator front2=front1;
            ++front2;
            position = start+index;
            iterator pos1=position;
            ++pos1;
            std::copy(front2,pos1,front1);
        } else{
            push_back(back());
            iterator back1 = finish;
            --back1;
            iterator back2 = back1;
            --back2;
            position=start+index;
            std::copy_backward(position,back2,back1);
        }
        *position = x_copy;
        return position;
    }


    /** endregion */




}
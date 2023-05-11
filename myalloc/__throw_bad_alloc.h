//
// Created by Q on 2023/4/26.
//

#ifndef STL_LEARNING___THROW_BAD_ALLOC_H
#define STL_LEARNING___THROW_BAD_ALLOC_H

#include <cstddef>
#include <cstdlib>
#include "new"
#define __THROW_BAD_ALLOC throw std::bad_alloc()

namespace wen{
    //第一级分配器
    template<int inst>
    class __malloc_alloc_template {
    private:
        //oom:out of memory
        static void *oom_malloc(size_t);

        static void *oom_realloc(void *, size_t);

        static void (*__malloc_alloc_oom_handler)();

    public:
        static void *allocate(size_t n) {
            void *result = malloc(n);
            //内存无法满足要求
            if (0 == result) result = oom_malloc(n);
            return result;
        }

        static void deallocate(void *p,size_t/*n*/){
            free(p);
        }

        static void *reallocate(void *p, size_t/*old_sz*/, size_t new_sz) {
            void *result = realloc(p, new_sz);
            if (0 == result) result = oom_realloc(p, new_sz);
            return result;
        }

        static void (*set_malloc_handler(void (*f)()))() {
            void (*old)() =__malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = f;
            return (old);
        }

    };
//malloc_alloc out-of-memory handling
    template<int inst>
    void(*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)()=0;

    template<int inst>
    void *__malloc_alloc_template<inst>::oom_malloc(size_t n) {
        void (*my_malloc_handler)();
        void *result;
        for(;;){
            my_malloc_handler=__malloc_alloc_oom_handler;
            if(0==my_malloc_handler){__THROW_BAD_ALLOC;}
            (*my_malloc_handler)();
            result = malloc(n);
            if(result) return result;
        }
    }

    template<int inst>
    void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n) {
        void (* my_malloc_handler)();
        void *result;
        for(;;){
            my_malloc_handler = __malloc_alloc_oom_handler;
            if(0==my_malloc_handler){__THROW_BAD_ALLOC;}
            (*my_malloc_handler)();
            result = realloc(p,n);
            if(result) return result;
        }
    }
    //二级配置器
    enum {__ALIGN = 8};
   enum {__MAX_BYTES=128};
   enum {__NFREELISTS = __MAX_BYTES/__ALIGN};
    template<bool threads,int inst>
    class __default_alloc_template{
    private:
        //将bytes 上调到8的倍数
        static size_t ROUND_UP(size_t bytes){
            return (((bytes)+__ALIGN)&~(__ALIGN-1));
        }
    private: //free-lists的节点构造
        union obj{
            union obj* free_list_link;
            char client_data[1];
        };
    private:
        static obj *volatile free_list[__NFREELISTS];
        static size_t FREELIST_INDEX(size_t bytes){
            return (((bytes)+__ALIGN-1)/__ALIGN-1);
        }
        static void *refill(size_t n);
        static char *chunk_alloc(size_t size,int &nobjs);

        static char *start_free;
        static char *end_free;
        static size_t heap_size;
    public:
        static void *allocate(size_t n);
        static void deallocate(void *p,size_t n);
        static void *reallocate(void *p,size_t old_sz,size_t new_sz);

    };
    template<bool threads,int inst>
    char* wen::__default_alloc_template<threads,inst>::start_free=0;
    template<bool threads,int inst>
    char* wen::__default_alloc_template<threads,inst>::end_free=0;
    template<bool threads,int inst>
    size_t wen::__default_alloc_template<threads,inst>::heap_size=0;
    template<bool threads,int inst>
    typename wen::__default_alloc_template<threads,inst>::obj*volatile
            wen::__default_alloc_template<threads,inst>::free_list[__NFREELISTS]=
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    template<bool threads, int inst>
    void *__default_alloc_template<threads, inst>::allocate(size_t n) {
        obj * volatile*my_free_list;
        obj *result;
        if(n>(size_t)__MAX_BYTES)
            return __malloc_alloc_template<inst>::allocate(n);
        my_free_list = free_list+ FREELIST_INDEX(n);
        result=*my_free_list;
        if(result==0){
            void *r= refill((ROUND_UP(n)));
            return r;
        }
        *my_free_list=result->free_list_link;
        return result;
    }

    template<bool threads, int inst>
    void __default_alloc_template<threads, inst>::deallocate(void *p, size_t n) {
        obj *q=(obj*)p;
        obj *volatile *my_free_list;
        if(n>(size_t)__MAX_BYTES){
            __malloc_alloc_template<inst>::deallocate(p,n);
            return;
        }
        my_free_list=free_list+ FREELIST_INDEX(n);
        q->free_list_link=*my_free_list;
        *my_free_list=q;
    }

    template<bool threads, int inst>
    void *__default_alloc_template<threads, inst>::refill(size_t n) {
        int nobjs=20;
        char *chunk= chunk_alloc(n,nobjs);//通过引用传参，可能会改变nobjs
        obj*volatile*my_free_list;
        obj *result;
        obj *current_obj,*next_obj;
        int i;
        if(1==nobjs) return (chunk);
        my_free_list=free_list+ FREELIST_INDEX(n);
        result=(obj*)chunk;
        *my_free_list = next_obj=(obj*)(chunk+n);
        for(i=1;;i++){
            current_obj=next_obj;
            next_obj=(obj*)((char*)next_obj+n);
            if(nobjs-1==i){
                current_obj->free_list_link=0;
                break;
            } else{
                current_obj->free_list_link=next_obj;
            }
        }
        return (result);
    }

    template<bool threads, int inst>
    char *__default_alloc_template<threads, inst>::chunk_alloc(size_t size, int &nobjs) {
        char *result;
        size_t total_bytes=size*nobjs;
        size_t bytes_left = end_free-start_free;
        if(bytes_left>=total_bytes){
            result=start_free;
            start_free += total_bytes;
            return (result);
        } else if(bytes_left>=size){
            nobjs=bytes_left/size;
            total_bytes = size *nobjs;
            result=start_free;
            start_free += total_bytes;
            return (result);
        } else{
            size_t bytes_to_get = 2*total_bytes+ ROUND_UP(heap_size>>4);
            if(bytes_left>0){
                obj*volatile*my_free_list=free_list+ FREELIST_INDEX(bytes_left);
                //调整free list_container ,将内存池中残余的内存编入
                ((obj*)start_free)->free_list_link=*my_free_list;
                *my_free_list=(obj*)start_free;
            }
            //配置heap空间，补充内存池
            start_free=(char*) malloc(bytes_to_get);
            if(0==start_free){
                //heap空间不足，malloc()失败
                int i;
                obj*volatile*my_free_list,*p;
                for(i=size;i<__MAX_BYTES;i+=__ALIGN){
                    my_free_list=free_list+ FREELIST_INDEX(i);
                    p=*my_free_list;
                    if(0!=p){
                        *my_free_list=p->free_list_link;
                        start_free=(char*)p;
                        end_free=start_free+i;
                        return (chunk_alloc(size,nobjs));
                    }
                }
                end_free=0;
                //山穷水尽，调用低级分配器
                start_free=(char*)__default_alloc_template<threads,inst>::allocate(bytes_to_get);
            }
            heap_size+=bytes_to_get;
            end_free=start_free+bytes_to_get;
            return (chunk_alloc(size,nobjs));
        }

    }
}
























#endif //STL_LEARNING___THROW_BAD_ALLOC_H

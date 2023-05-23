//
// Created by Q on 2023/5/22.
//
#include "../../my_config.h"
#ifndef STL_LEARNING_MY_HASH_FUN_H
#define STL_LEARNING_MY_HASH_FUN_H

#endif //STL_LEARNING_MY_HASH_FUN_H
namespace wen{
    template<class Key>struct hash{};
    inline size_t __stl_hash_string(const char * s){
        unsigned long h=0;
        for(;*s;++s)
            h=5*h+*s;
        return size_t(h);
    }
    __STL_TEMPLATE_NULL struct hash<char*>{
        size_t operator()(const char*s)const{return __stl_hash_string(s);}
    };
    __STL_TEMPLATE_NULL struct hash<const char*>{
        size_t operator()(const char*s)const{return __stl_hash_string(s);}
    };
    __STL_TEMPLATE_NULL struct hash<char>{
        size_t operator()(char x)const{return x;}
    };
    __STL_TEMPLATE_NULL struct hash<unsigned char>{
        size_t operator()(unsigned char x)const{return x;}
    };
    //.....省略
}

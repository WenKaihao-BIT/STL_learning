//
// Created by Q on 2023/5/18.
//

#ifndef STL_LEARNING_PRIME_H
#define STL_LEARNING_PRIME_H
#include "iostream"


namespace wen{
    static const int __stl_num_primes =28;
    static const unsigned long __stl_prime_list[__stl_num_primes] =
            {
                    53ul,         97ul,         193ul,       389ul,       769ul,
                    1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
                    49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
                    1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
                    50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
                    1610612741ul, 3221225473ul, 4294967291ul
            };
    inline unsigned long __stl_next_prime(unsigned long n){
        const unsigned long *first=__stl_prime_list;
        const unsigned long *last = __stl_prime_list+__stl_num_primes;
        const unsigned long *pos=std::lower_bound(first,last,n);
        return pos==last?*(last-1):*pos;
    }
}


#endif //STL_LEARNING_PRIME_H
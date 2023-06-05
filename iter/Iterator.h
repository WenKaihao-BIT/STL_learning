//
// Created by Q on 2023/5/24.
//

#ifndef STL_LEARNING_ITERATOR_H
#define STL_LEARNING_ITERATOR_H
#include "my_traits.h"

namespace wen{
    /** region ## value_type ## */
    template<class Iterator>
    inline typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator&){
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }
    /** endregion */

    /** region ## distance_type ## */
    template<class Iterator>
    inline typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator&){
       return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
    }
    /** endregion */

    /** region ## iterator_category ## */
    template<class I>
    inline typename iterator_traits<I>::iterator_category
    iterator_category(const I&){
        typedef typename iterator_traits<I>::iterator_category category;
        return category();
    }
/** endregion */



}


#endif //STL_LEARNING_ITERATOR_H
//
// Created by Q on 2023/5/13.
//

#ifndef STL_LEARNING_MYRBTREE_H
#define STL_LEARNING_MYRBTREE_H

#endif //STL_LEARNING_MYRBTREE_H
typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base{
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base* base_ptr;

    color_type color;
    base_ptr parent;
    base_ptr left;
    base_ptr right;
};
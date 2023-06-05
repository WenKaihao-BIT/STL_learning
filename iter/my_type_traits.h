//
// Created by Q on 2023/5/5.
//

#ifndef STL_LEARNING_MY_TYPE_TRAITS_H
#define STL_LEARNING_MY_TYPE_TRAITS_H
#define __STL_TEMPLATE_NULL template<>

#endif //STL_LEARNING_MY_TYPE_TRAITS_H

struct __true_type{};
struct __false_type{};
template<class type>
struct __type_traits{
    typedef __true_type this_dummy_member_must_be_first;
    typedef __false_type has_trivial_default_constructor;
    typedef __false_type has_trivial_copy_constructor;
    typedef __false_type has_trivial_assignment_operator;
    typedef __false_type has_trivial_destructor;
    typedef __false_type is_POD_type;
};

__STL_TEMPLATE_NULL struct __type_traits<char> {
    typedef __true_type has_trivial_default_constructor;
    typedef __true_type has_trivial_copy_constructor;
    typedef __true_type has_trivial_assignment_operator;
    typedef __true_type has_trivial_destructor;
    typedef __true_type is_POD_type;
};
__STL_TEMPLATE_NULL struct __type_traits<int> {
    typedef __true_type has_trivial_default_constructor;
    typedef __true_type has_trivial_copy_constructor;
    typedef __true_type has_trivial_assignment_operator;
    typedef __true_type has_trivial_destructor;
    typedef __true_type is_POD_type;
};
//对其他进行省略...

//原生指针特例化
template<class T>
struct __type_traits<T*>{
    typedef __true_type has_trivial_default_constructor;
    typedef __true_type has_trivial_copy_constructor;
    typedef __true_type has_trivial_assignment_operator;
    typedef __true_type has_trivial_destructor;
    typedef __true_type is_POD_type;
};
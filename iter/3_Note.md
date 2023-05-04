# Traits
## 5种迭代器的相应型（associated types）
### iterator_category
    5类迭代器

    Input iterator

    Output iterator

    Forward iterator

    Bidirectional iterator

    Random Access iterator
    ·原生指针是一种Random Access iterator

### value_type
    指的是迭代器所指对象的类型
### pointer
    指迭代器的指针类型 item*
### reference
    指迭代器采用引用的类型 item&
### difference_type
    指的是两个迭代器之间的距离
## Traits 萃取特性
    通过定义5种迭代器的相应型规范来萃取相应的类型
    例如：在class I 中定义value_type后可以在后续使用I::value_type萃取value_type
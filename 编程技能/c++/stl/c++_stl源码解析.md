<!-- ---
title: "STL源码解析"
date: 2017-10-30T09:43:48+08:00
lastmod: 2017-10-31T15:43:48+08:00
draft: false
tags: [reading]
categories: [c++]
author: "Archillieus"
autoCollapseToc: true

#menu:
#  main:
#    parent: "docs"
#    weight: 1
#    #name: "hi"
#    #url: "https://gohugo.io"
--- -->

Reference:

+ 侯捷《STL源码解析》

核心组件：container，algorithm, iterator, allocator, functor, adapter

## 1.源码：资源配置器Allocator

（1）设计：<font color=red>向system heap申请空间，考虑多线程，考虑内存不足的措施，考虑过多小型区块造成内存破碎问题。</font>  
（2）std规格的allocators定义在defallocator.h，只是对::operator new和::operator delete的简单包装，并未考虑分配效率，分配失败等情况。在sgi_stl中使用stl_alloc.h,实现二级分配策略。  
（3）当申请大于128B时，执行一级分配，直接使用c的malloc和free。有历史原因，而且c++没有remalloc操作。  
（4）当申请小于128时，利用内存池进行分配回收，实行8字节对齐,维护16个linklist。<font color=red>利用union实现链表节点结构，可以避免额外的管理空间。</font>当内存不足时，执行一级策略向系统申请，由于一级使用c语言，所以用c语言模拟c++的new handle机制。stl标准的配置器定义在memory中。  

## 2.源码：迭代器Iterator

(1)iterator is a smart pointer, the most common actions of pointer are defeference and memeber access. so the most important design of iterator is overloading of operator * and operator ->.
In reference to auto_ptr, a wrapper of native pointer to deal with the memory leak problem.

```c++
template <class T>
class auto_ptr {
public:
    explicit auto_ptr(T *p = 0) : pointee(p) {};
    template<class U>
    auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release());
    ~ autp_ptr() {};

    template<class U>
    auto_ptr<T>& operator=(auto_ptr<U>& rhs) {
        if (this != &rhs) reset(rhs.release());
        return *this;
    }
    T& operator*() {return *pointee};
    T* operator->() {return pointee};
    T* get() {return pointee};
    //...

private:
    T *pointee;
}
```

```c++
template <class item>
struct Iterator {
    item* ptr;
    Iterator(item* p = 0) : ptr(p) {};

    item& operator*() const {return *ptr};
    item* operator->() const {return ptr};

//以下两个operator++遵循标准作法
    Iterator<item>& operator++() {  //pre-increment,item要不要写？
        ptr = pte->next(); return *this;
    }
    Iterator<item> operator++(int) {  //post-increment
        Iterator tmp = *this; ++*this; return tmp;
    }

    bool operator==(const Iterator& i) const {return ptr==i.ptr;}
    bool operator!=(const Iterator& i) const (return ptr!=i.ptr;)
}
```

（2）traits编程技法：类型萃取  

+ 利用function template 的自变量推导机制。
+ 加上原生类型和const的偏特化。
+ 注意typeid的使用。
+ 迭代器最常用的五种型别(嵌套的)：value_type , difference_type , pointer , reference , iterator_categor
+ 五种迭代器(继承，重载)：input Interator, output Iterator, Forward Interator, Bidirectionnal, RandomAccess

```c++
template <class T>
struct iterator_traits {
    typedef typename T::value_type value_type;
}

template <class T>
struct iterator_traits<T*> {
    typedef T value_type;
}

template <class T>
struct iterator_traits<const T*> {
    typedef T value_type;
}
```

```c++
//stl提供了iterator class作为迭代器的父类
template <class Category,
          class T,
          class Distance = ptrdiff_t,
          class Pointer = T *,
          class Reference = T&,>
struct iterator {
    typedef Category iterator_catogary;
    typedef T value_type;
    typedef Distance defference_type;
    typedef Pointer pointer;
    typedef Reference reference;
}
```

> traits编程技法，大量运用于STL中。它运用nest type的编码技巧和编译器的template自变量推导功能，补强c++未能提供的关于类型的认证功能，补强c++不为strong type的遗憾。

## 3.源码：序列容器Sequence Containers

![stl容器](../rsc/program/stlContainer.png)

### (1)vector

### (2)list

### (3)deque

### (4)stack

### (5)queue

### (6)priority_queue

### 思考

1)vector和list分别在什么情况下使用？  
2)为什么set和map的实现使用RB-tree？RB-tree对于AVL-tree的优势在哪？
<https://blog.csdn.net/mmshixing/article/details/51692892>

## 4.源码：关联式容器Associative Containers

> unordered_map的底层是hashtable, 所有与顺序无关；map的底层是红黑树，所以map的效率取决于红黑树的效率。

### (1)RB_tree

### (2)set

### (3)map

### (4)multiset

### (5)multimap

## 5.源码：算法Algorithm

## 6.源码：函数对象Function Class

> 仿函数的作用主要在哪？STL所提供的各种算法，往往有两个版本，其中一个版本是最常用的某种运算，第二个版本表现为泛化的过程，允许用户“以template参数来指定所要采用的策略“。如果要将”操作“作为算法的参数，唯一的方法是将该”操作“设计为一个函数，再将函数的指针当作算法的一个参数;或者就该”操作“设计为一个所谓的函数对象，并将该对象作为算法的一个参数。  
>
> 那么为什么不使用函数指针呢？原因在于函数指针不能满足STL对于抽象性的要求，也不能满足软件的要求（函数指针无法和STL其他组件搭配，产生更灵活的变化）。
>
> 函数对象必须自定义function call运算符(operator()),拥有这样的运算符后，我们就可以在仿函数的对象后面加上一对小括号，以此调用函数对象定义的operator()。若以操作数的个数分，可分为一元和二元，若以功能分，可分为Arithmetic, Rational, Logical。头文件\<functional\>。
>
> 一般而言，不会有人单独运用这些功能机器简单的函数对象，主要用途是搭配STL算法。

### unary_function

```c++
template <class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
}
```

### binary_function

### 6个算术函数对象

+ plus\<T>
+ minus\<T>
+ multiplies\<T>
+ divides\<T>
+ modulus\<T>
+ negation\<T>

### 6个运算函数对象

+ equal_to\<T>
+ not_equal_to\<T>
+ greater\<T>
+ greater_equal\<T>
+ less\<T>
+ less_equal\<T>

### 3个逻辑运算函数对象

+ logical_and\<T>
+ logical_or\<T>
+ logical_not\<T>

## 7.源码：配接器Adapter

### container adapters

+ queue
+ stack
+ priority_queue

### iterator adapters

+ insert iterators(底层为容器)
+ reverse iterators(底层为iterator)
+ iostream iterators(底层为iostream)

注：所谓迭代器配接器很少以迭代器为直接对象，所谓对迭代器的修饰只是一种观念上的改变。

### function adapters(超灵活，数量最庞大)

> function adapters的价值在于，通过他们之间的绑定，组合，修饰能力，几乎可以无限制地创造出各种表达式，搭配STL算法一起使用。
>
> function adapters提供了一系列辅助函数。STL提供了众多的配接器，使”一般函数“和”成员函数“得以无缝地与其他配接器和算法结合起来。
>
> 所有期望获得配接能力的组件，本身必须是可配接的。换句话说，一元仿函数必须继承自unary_function, 二元仿函数必须继承自binary_function, 成员函数必须经过mem_fun处理过，一般函数必须经过ptr_fun处理过。

+ `bind1st(const Op& op, const T& x), bind2nd();`
+ `not1(const Pred& pred), not2();`
+ `ptr_fun(Result(*fp)(Arg))`, `ptr_fun(Result(*fp)(Arg1, Arg2));`
+ mem_fun(S (T::*f)()), mem_fun(S (T::*f)() const), mem_fun_ref(S (T::*f)()), mem_fun_ref(S (T::*f)() const) 二元的重载了。
---
title: "C++常见问题"
date: 2017-10-07T09:43:48+08:00
lastmod: 2019-03-01T15:43:48+08:00
draft: false
tags: []
categories: [c++]
author: "Archillieus"
autoCollapseToc: true

#menu:
#  main:
#    parent: "docs"
#    weight: 1
#    #name: "hi"
#    #url: "https://gohugo.io"
---

## Basic

+ [进程的地址空间？](https://harttle.land/2015/07/22/memory-segment.html)

> 进程持有堆空间，线程持有栈空间。栈空间规模一般为几M，如1M，4M。堆的规模，理论上内存有多大，堆就可以建多大。堆大小在编译是就固定， 堆大小在运行是动态变化。

+ [哪些变量会默认初始化，哪些会随机初始化？](https://harttle.land/2015/10/05/cpp-variable-init.html)
+ [构造函数和析构函数没有返回值，以及抛出异常的问题？](https://www.cnblogs.com/luxiaoxun/archive/2012/09/06/2673249.html)
+ [什么情况下stl的迭代器和引用会非法化？](https://blog.csdn.net/y1196645376/article/details/52938474)
+ [类的对象会调用默认构造函数，对象的指针不会调用默认构造函数？](https://harttle.land/2015/06/22/cpp-object-lifecycle.html)
+ int * a = new int(10); a在栈， 10在堆。
+ [全局对象，静态对象，局部对象，const， static， static const](https://blog.csdn.net/jinpeng_cumt/article/details/52723131)
+ [静态函数只能访问静态变量。static变量在类外初始化，避免重复定义。常量对象只能访问构造函数，析构函数和常量函数，所有属性赋值都会编译报错。](https://harttle.land/2015/06/24/cpp-static-and-const-member.html)

> const修饰的量确切说叫只读量，不是常量。
> 可能在栈区，可能在全局区，看作用域以及有没有static修饰了，如果没有对其取地址的话，也可能被编译器优化为字
> 面常量。

+ [static_cast, dynamic_cast, const_cast](https://www.cnblogs.com/chenyangchun/p/6795923.html)
+ 类中的方法只声明，不定义，如果没被调用会报错吗？虚函数除外。
+ [引用占用内存？](https://stackoverflow.com/questions/1179937/how-does-a-c-reference-look-memory-wise)
+ [Item 3 : 尽量使用常量](https://harttle.land/2015/07/21/effective-cpp-3.html)
+ 确保变量初始化？
+ [对象中有引用成员时，默认的赋值运算符会被delete掉?](https://harttle.land/2015/07/23/effective-cpp-5.html)
+ [Item 7 : 将多态基类的析构函数定义为虚函数？](https://harttle.land/2015/07/24/effective-cpp-7.html)
+ [指针占几个字节？](https://zhidao.baidu.com/question/505146033.html)
+ [标准库的sizeof(string)占几个字节？64bit和32bit还不一样？](https://zhidao.baidu.com/question/165120550.html)
+ [类的存储字节如何对齐？](https://harttle.land/2015/07/24/effective-cpp-7.html)

> 对齐方式：最大基本数据类型，函数在代码段，所以与sizeof()无关。使用``#pragma pack()``自定义对齐

+ [Item 8 : 为什么不要再析构函数中抛出异常？](https://harttle.land/2015/07/26/effective-cpp-8.html)
+ [c++的异常处理好像有争议哦？](https://www.zhihu.com/question/22889420)
+ [Item 9 : 在构造/析构时不要调用虚函数](https://harttle.land/tags.html#Effective-C++)
+ [Item 10 : 赋值运算符重载要返回自己引用](https://harttle.land/2015/07/28/effective-cpp-10.html)
+ [Item 11 : 赋值运算符的自赋值问题](https://harttle.land/2015/07/30/effective-cpp-11.html)
+ ??过多判断语句会影响程序的运行效率吗？
+ ??c++哪些机制是异常安全的？如何保证异常安全？
+ 可以忽略函数返回值的处理？
+ [Item 12 : 完整地拷贝对象](https://harttle.land/2015/08/01/effective-cpp-12.html)
+ [Item 14 : ??资源管理类要特别注意拷贝行为](https://harttle.land/2015/08/04/effective-cpp-14.html)
+ [数组名类似指针？(了解一下，不纠结) 指针数组，数组指针](https://www.cnblogs.com/ddx-deng/archive/2012/12/16/3755862.html)
+ <https://www.cnblogs.com/kwdeblog/p/6097362.html>
+ [Item 16 : 使用同样的形式来new和delete](https://harttle.land/2015/08/07/effective-cpp-16.html)
+ [Item 17 : 在单独的语句将new的对象放入智能指针中](https://harttle.land/2015/08/08/effective-cpp-17.html)
+ [Item 18 : 让接口容易被正确使用，不易被误用](https://harttle.land/2015/08/08/effective-cpp-17.html)
+ [Item 19 : 把类的设计当作类型的设计](https://harttle.land/2015/08/12/effective-cpp-19.html)
+ [Item 20 : 传递常量引用比传值更好？](https://harttle.land/2015/08/13/effective-cpp-20.html)
+ [Item 21 : 不要返回对象的引用](https://harttle.land/2015/08/18/effective-cpp-21.html)

> int *x = new int(100); 在函数退出时，x会被撤销，但是栈空间并没有释放，对该地址的解引用仍然有效，所以函数返回x（地址拷贝），这是合法合理的。

+ [Item 22 : 数据成员应该声明为私有](https://harttle.land/2015/08/19/effective-cpp-22.html)
+ [Item 23 : 非成员非友元函数优于成员函数](https://harttle.land/2015/08/20/effective-cpp-23.html)
+ [Item 24 : 用非成员函数来支持所有元的类型转换](https:/harttle.land/2015/08/22/effective-cpp-24.html)
+ [Item 26 : 尽量推迟变量的定义](https://harttle.land/2015/08/24/effective-cpp-26.html)
+ [Item 27 : 最小化类型转换](https://harttle.land/2015/08/25/effective-cpp-27.html)
+ ??bitwise constness and logical constness
+ [Item 28 : 不要返回对象内部的句柄](https://harttle.land/2015/08/26/effective-cpp-28.html)
+ [Item 29 : 追求异常安全的代码](https://harttle.land/2015/08/27/effective-cpp-29.html)
+ [c++的异常处理](https://blog.csdn.net/daheiantian/article/details/6530318)
+ [Item 30 : 如何理解inline函数？](https://harttle.land/2015/08/28/effective-cpp-30.html)
+ [Item 31 : 最小化文件之间的编译依赖](https://harttle.land/2015/08/29/effective-cpp-31.html)
+ [Item 32 : 确保public继承is-a](https://harttle.land/2015/08/30/effective-cpp-32.html)
+ [Item 38, 39 : 组合和private继承](https://harttle.land/2015/09/05/effective-cpp-38.html)
+ <https://harttle.land/2015/09/06/effective-cpp-39.html>
+ [Item 33 : 避免隐藏继承来的名称](https://harttle.land/2015/08/31/effective-cpp-33.html)
+ [Item 34 : 区分接口继承和实现继承](https://harttle.land/2015/09/01/effective-cpp-34.html)
+ [Item 36 : 不要重写继承来的非虚函数](https://harttle.land/2015/09/01/effective-cpp-34.html)
+ [Item 37 : 不要重写父类函数的默认参数](https://harttle.land/2015/09/01/effective-cpp-34.html)
+ ??多继承会遇到哪些问题？
+ [Item 41 : 隐式接口和编译时多态](https://harttle.land/tags.html#Effective-C++)
+ [Item 42 : typename的两种用法](https://harttle.land/2015/09/09/effective-cpp-42.html)
+ [Item 43 : 访问模板基类中的名称](https://harttle.land/2015/09/10/effective-cpp-43.html)
+ [Item 44 : 将参数无关的代码重构到模板外去](https://harttle.land/2015/09/12/effective-cpp-44.html)
+ [Item 45 : 使用成员模板函数来接收所有兼容的类型](https://harttle.land/2015/09/13/effective-cpp-45.html)
+ [STL的traits机制](https://blog.csdn.net/lihao21/article/details/55043881)
+ [预处理指令及宏定义](https://www.cnblogs.com/zi-xing/p/4550246.html)
+ <http://blog.chinaunix.net/uid-29067889-id-3819834.html>
+ 如何重载自增，自减，解引用？前置还是后置？
+ 什么是::operator new?和new有什么差别？  <http://blog.jobbole.com/106923/>
+ [关键词union怎么用？](http://zh.cppreference.com/w/cpp/language/union)
+ [enum枚举变量所占内存大小？](https://blog.csdn.net/bulebin/article/details/54388735)
+ 由constexpr引起的常量表达式问题：
  + [神秘的constexpr](https://www.cnblogs.com/wangxiaobao/p/5966394.html)
  + [编译器常量和运行期常量](https://bbs.csdn.net/topics/100054572)
  + [VLA变长数组](https://www.cnblogs.com/qingergege/p/7520565.html)
+ [内存分配方式](https://blog.csdn.net/gukesdo/article/details/6548256)
+ 自己实现scoped_ptr和shared_ptr
+ 虚表和虚表指针：  
  + <http://blog.51cto.com/boyishachang/1284520>
  + <https://songlee24.github.io/2014/09/02/cpp-virtual-table/>
+ [断言与静态断言](http://deltamaster.is-programmer.com/posts/29649.html)
  + <https://blog.csdn.net/makenothing/article/details/23555073>
+ [c++11新特性](http://blog.guoyb.com/tags/C-11/)
+ queue pop()操作：对象销毁？内存释放？
+ c++和c语言的差别？  
  + 多范式，exception，重载（自定义行为），各种机制，模板，命名空间
+ [c++自由存储区是否等同于堆？](http://www.qingpingshan.com/rjbc/cyy/35186.html)
+ stl中的sort()是使用快排(qsort())吗？稳定排序使用什么（stable_sort）？(TimSort in python)
+ 实现一个list的快排？
+ stl中string的底层实现原理？
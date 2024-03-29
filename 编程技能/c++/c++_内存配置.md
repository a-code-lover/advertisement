### c语言内存操作

+ malloc：申请指定字节数的内存。申请到的内存中的初始值不确定，一般使用memset初始化。
+ realloc：更改以前分配的内存长度（增加或减少）。当增加长度时，可能需将以前分配区的内容移到另一个足够大的区域，而新增区域内的初始值则不确定。
+ calloc：为指定长度的对象，分配能容纳其指定个数的内存。申请到的内存的每一位（bit）都初始化为 0。
+ memcpy：函数memcpy从src的位置开始向后复制num个字节的数据到dest的内存位置，在遇到’\0’不会停下来，如果src与dest任何的重叠，复制结果都是未定义的。
+ memmove：和memcpy区别在于dest与src内存块可以重叠。
+ memset：以str的起始位置开始的n个字节的内存区域用整数value进行填充。

`void* malloc ( size_t size );`  
`void free ( void *pointer );`  
`void* realloc (void *ptr, size_t new_size );`  
`void* calloc ( size_t num_elements, size_t element_size );`  
`void* memcpy(void* dest,const void* src,size_t num);`
`void* memmove(void* dest,const void* src,size_t num);`
`void* memset(void* str,int value,size_t num);`

### malloc, free

```c++
char *str = (char*) malloc(100);
assert(str != nullptr);

free(p);
p = nullptr;
```

### new, delete

+ `new/new[]`：完成两件事，先底层调用`malloc`(`operator new`)分了配内存，然后调用构造函数（创建对象）,最后返回指针。
+ `delete/delete[]`：也完成两件事，先调用析构函数（清理资源），然后底层调用`free`(`operator delete`)释放空间。

保持(new, delete)和(new [], delete[])使用的一致性：

new 在申请内存时会自动计算所需字节数，而 malloc 则需我们自己输入申请内存空间的字节数。

### ::operator new, ::operator delete

### placement new

#### (1)new, operator new, placement new区别

+ `new`：不能被重载，其行为总是一致的。它先调用operator new分配内存，然后调用构造函数初始化那段内存。
+ `operator new`：要实现不同的内存分配行为，应该重载operator new，而不是new。
+ `placement new`：只是operator new重载的一个版本，它并不分配内存，允许你在一个已经分配好的内存中（栈或者堆中）构造一个新的对象。

#### (2)为什么需要使用`placement new`

1.用 `placement new` 解决buffer的问题

> 问题描述：用new分配的数组缓冲时，由于调用了默认构造函数，因此执行效率上不佳。若没有默认构造函数则会发生编译时错误。如果你想在预分配的内存上创建对象，用缺省的new操作符是行不通的。要解决这个问题，你可以用placement new构造。它允许你构造一个新对象到预分配的内存上。

2.增大时空效率的问题

> 使用new操作符分配内存需要在堆中查找足够大的剩余空间，显然这个操作速度是很慢的，而且有可能出现无法分配内存的异常（空间不够）。placement new就可以解决这个问题。我们构造对象都是在一个预先准备好了的内存缓冲区中进行，不需要查找内存，内存分配的时间是常数；而且不会出现在程序运行中途出现内存不足的异常。所以，placement new非常适合那些对时间要求比较高，长时间运行不希望被打断的应用程序。

#### (3)语法

```c++
new (palce_address) type
new (palce_address) type (initializers)
new (palce_address) type [size]
new (palce_address) type [size] { braced initializer list }
```

### delete this合法吗？

+ 必须保证 this 对象是通过 new（不是 new[]、不是 placement new、不是栈上、不是全局、不是其他对象成员）分配的
+ 必须保证调用 delete this 的成员函数是最后一个调用 this 的成员函数
+ 必须保证成员函数的 delete this 后面没有调用 this 了
+ 必须保证 delete this 后没有人使用了

### [如何定义一个只能在堆上（栈上）的对象的类？](https://www.nowcoder.com/questionTerminal/0a584aa13f804f3ea72b442a065a7618)

只能在堆上：将析构函数设置为私有

> 原因：C++是静态绑定语言，编译器管理栈上对象的生命周期，编译器在为类对象分配栈空间时，会先检查类的析构函数的访问性。若析构函数不可访问，则不能在栈上创建对象。

只能在堆上：将new和delete重载为私有

> 原因：在堆上生成对象，使用 new 关键词操作，其过程分为两阶段：第一阶段，使用 new 在堆上寻找可用内存，分配给对象；第二阶段，调用构造函数生成对象。将 new 操作设置为私有，那么第一阶段就无法完成，就不能够在堆上生成对象。

### 分配内存的技巧

+ 避免分配大量的小内存块。分配堆上的内存有一些系统开销，所以分配许多小的内存块比分配几个大内存块的系统开销大。
+ 仅在需要时分配内存。只要使用完堆上的内存块，就释放它。

### std::new_handler

这是一个回调函数，主要用于operator new申请内存不成功的时候调用，感觉可以类比于信号处理函数，operator new申请不成功（接受到某个信号），调用该handler（触发信号处理函数）。最主要的用途就是通过set_new_handler()来更换不同的处理函数。

### SGI stl二级内存分配策略

> stl中考虑小区块可能造成的碎片问题，设计二级配置器，第一级配置器直接使用malloc()和free();第二级配置器则视情况采用不同的策略：当配置区块超过128字节时，则视之为足够大，便调用第一级配置器；当配置区块小于128字节时，则视之为过小，为了降低额外负担，便采用复杂的内存池的方式来整理，而不再求助于第一级配置器。
> 内存池实行8字节对齐,维护16个linklist,每个list上集合着大小分别为8，16，24，...128大小的内存块。利用union实现链表节点结构，可以避免额外的管理空间。当内存不足时，执行一级策略向系统申请，由于一级使用c语言，所以用c语言模拟c++的new handle机制。

### 操作系统内存管理

#### 内存连续分配

> 固定分区：简单开销小，但造成内部碎片，分区数目固定不利于并发。
> 动态分区：没有内部碎片，但会造成外部碎片，分配策略相对复杂，分区回收时需要合并，开销大。常用四种分配策略。
> 首次适应不仅简单，通常也是最好和最快的，unix的最初版本使用了该策略；最佳适应法性能是最差的，会留下大量碎片；最坏适应法对大区块切割，很快导致没有可用大区块，性能也差。

+ 首次适应法：按分区地址的先后顺序从头查找，找到符合要求的第一个分区进行分配，但随着分配增多（低端被切割小块），每次查找的时间开销会增大。
+ 循环首次适应法：按分区地址先后次序，每次从上一次分配的分区开始查找。分配和释放性能好，但大区块不易保留。
+ 最佳适应法：空闲分区按容量递增形成链表，找到第一个满足的空闲分区。
+ 最坏适应法：空闲分区按容量递减形成链表，找到第一个满足的空闲分区，即最大分区。

#### 伙伴系统

> 固定分区和动态分区方式都有不足之处。固定分区方式限制了活动进程的数目，当进程大小与空闲分区大小不匹配时，内存空间利用率很低。动态分区方式算法复杂，回收空闲分区时需要进行分区合并等，系统开销较大。伙伴系统方式是对以上两种内存方式的一种折衷方案。

伙伴系统规定，无论是已分配分区或未分配分区，其大小均为2的k次幂，不同大小的空闲分区形成各自的空闲分区链表。当需要为进程分配一个长度为n的存储空间时:

1. 首先计算一个i 值，使 2^(i－1) < n ≤ 2^i；
2. 然后在空闲分区大小为2^i的空闲分区,若找到，即把该空闲分区分配给进程；
3. 否则，表明长度为2^i的空闲分区已经耗尽，则在分区大小为2^(i＋1)的空闲分区链表查找；
4. 若存在 2^(i＋1)的一个空闲分区，则把该空闲分区分为相等的两个分区，**这两个分区称为一对伙伴**，其中的一个分区用于配，而把另一个加入分区大小为2^i的空闲分区链表中。

#### 内存不连续分配

在当前的操作系统中，普遍采用的是基于分页和分段机制的虚拟内存机制，该机制较伙伴算法更为合理和高效，但在多处理机系统中，伙伴系统仍不失为一种有效的内存分配和释放的方法，得到了大量的应用。

> 分页
> 分段

### Linux内存模型(待补充)

参考：
[linux内存模型](<http://www.10tiao.com/html/606/201806/2664605452/1.html>)
<https://github.com/huihut/interview>

### 二维数组的申请和销毁

```c++
void fun(int x,int y)
{
    //定义指向指针的指针
    int **n;
    //先动态申请一个动态一维数组
    n=new int * [x];
    //循环给每个元素上申请一个动态一维数组
    for(int i=0;i<x;i++)
        n[i]=new int[y];

    //释放内存空间，先释放每一行的空间，再释放整体的空间
    for(int i=0;i<x;i++)
        delete[] n[i];
    delete []n;
}
```
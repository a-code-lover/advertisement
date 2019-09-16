
### 什么是仿函数（functor）？

所谓的仿函数(functor，函数对象)，是通过重载()运算符模拟函数形为的类。这里需要明确两点：仿函数不是函数，它是个类；仿函数重载了`()`，使得可以像调用函数一样使用。另外，**lambda表达式也是一种函数对象**。

> 生成器(generator)是不用参数就可以调用的函数符(仿函数)。  
> 一元函数(unary function) 是用一个参数就可以调用的函数符。  
> 二元函数(binary function)是用两个参数就可以调用的函数符。  
> 例如：供给给for_each()的函数符应该是一个一元函数，因为它每次用于一个容器元素。  
>
> 当然，这些概念都有相应的改进版：  
> 返回bool值的一元函数是谓词(predicate)；  
> 返回bool值的二元函数是二元谓词(binary predicate)。  
> 例如：供给给sort函数的第三个参数就应该是一个二元谓词，表示一个优先级关系。  

### 为什么需要仿函数？

迭代和处理逻辑分离，在STL中大量使用，性能好。

> **函数对象带有状态**：函数对象相对于普通函数是“智能函数”，这就如同智能指针相较于传统指针。因为函数对象除了提供函数调用符方法，还可以拥有其他方法和数据成员。所以函数对象有状态。即使同一个类实例化的不同的函数对象其状态也不相同，这是普通函数所无法做到的。而且函数对象是可以在运行时创建。
>
> **每个函数对象有自己的类型**：对于普通函数来说，只要签名一致，其类型就是相同的。但是这并不适用于函数对象，因为函数对象的类型是其类的类型。这样，函数对象有自己的类型，这意味着函数对象可以用于模板参数，这对泛型编程有很大提升。更加具有通用性。
>
> **函数对象一般快于普通函数**：因为函数对象一般用于模板参数，模板一般会在编译时会做一些优化。
> 函数对象的适配器，更加灵活，复用。

### 仿函数怎么用？

> 在stl中广泛用到，如`<algorithm>`的每个算法函数一般提供两个版本，一个是默认版本，一个是用户自定义规则的版本，这时候规则就是通过仿函数来定制传入的。
>
> 仿函数的使用和函数指针一样，所以即可传入函数指针，也可传仿函数，推荐后者。

```c++
template<typename _RandomAccessIterator>
inline void
sort(_RandomAccessIterator __first, _RandomAccessIterator __last);

template<typename _RandomAccessIterator, typename _Compare>  
inline void
sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp);

sort(vec.begin(), vec.end(), greater<int>()); //降序排列
```

### 一元、二元仿函数？

### 仿函数和函数指针的区别？

c语言通过函数指针实现函数的传递；

### STL內建仿函数

+ 算术型：`plus<T>, minus<T>, multiplies<T>, divides<T>, modulus<T>`
+ 关系型：`equal_to<T>, greater<T>, less<T>`
+ 逻辑运算：`logical_and<T>, logical_or<T>, logical_no<T>`

### 函数适配器

在库中提供的函数适配器分为两类：
（1）绑定器（binder），是一种函数适配器，它通过将一个操作数绑定到给定值而将二元函数对象转换为一元函数对象。
（2）求反器（negator），是一种函数适配器，它将谓词函数对象的真值求反。

参考：
<https://www.hustyx.com/cpp/6/>
[函数对象与函数指针](https://blog.csdn.net/haolexiao/article/details/53493837)
[lambda表达式与函数对象](https://www.jianshu.com/p/d686ad9de817)
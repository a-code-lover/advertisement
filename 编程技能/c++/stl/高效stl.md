# Scott Meyers 《Effective STL》

## 前言

    她从未忘记提醒我生活比C++和软件重要。

该书写的时间比较早，部分技术已经过时或者有更好的实现方式，但任然值得一读。

四种标准序列容器：vector,string,deque,1ist；
四种标准关联容器：set,map,multiset,multimap；
五种迭代器：输入，输出，前向，双向，随机；
重载函数调用操作符（`operator()`）的任何类叫做仿函数类，从这样的类建立的对象成为函数对象或仿函数；
函数`bind1st`和`bind2nd`称为绑定器；

`typename C::const_interator`：依赖类型；

不使用`vector<bool>`：该容器并未实际保存bool类型，而是为了节省空间使用bit。因此在操作该类型的时候用到了指针引用，不当操作可能会引起一般容器不存在的问题，同时该类型也不支持一般容器的很多操作。

**循环会总成效率的损失。**

**没有析构函数的类的公有继承是一大c++禁忌。**

推荐使用foreach；

避免循环的一课：`copy(ssp.begin(), ssp.end(), ostream_iterator<string>(cout, "\n"));`

```c++
typedef deque<int>::const_iterator ConstIter;
typedef deque<int>::iterator Iter;
ConstIter ci;
...
Iter i = dq.begin();
std::advance(i, std::distance<ConstIter>(i, ci)); // 获得const_iteraor对应的iterator
```

```c++
vector<int> results; // 把transmogrify应用于
transform(values.begin(), values.end(), // values中的每个对象，
          back_inserter(results), // 在results的结尾, 此处使用results.end()错误，
          transmogrify); // 插入返回的values
```

inserter允许你强制将算法的结果插入容器中的任意位置。

resize()和reserve()扩展的一个区别，reserve只是扩展的内存，内存是空白的，不能直接把元素拷贝进去，要用inserter。resize()扩充的时候有默认初始化，可以直接把新元素拷贝进去。

`vec.erase(std::remove(vec.begin(), vec.end(), 10), vec.end());`

四个标准函数适配器：`not1`, `not2`, `bind1st`, `bind2nd`;
仿函数类必须继承自unary_function或binary_function，这样才可适配。以上四种适配器只能与可适配的函数对象合作。
可适配类必须只有一个`operator()`函数。有时候需要定义多个调用形式，这时候就放弃了可适配性。

无分支循环编程：想起了tx循环复杂度要求。。。。

对于set的查找，成员函数是对数复杂度，find算法是线性复杂度？？？
list的成员函数几乎都是特化过的。

## 50条

容器：
1.仔细选择你的容器;

2.小心对“容器无关代码”的幻想；

3.使容器里对象的拷贝轻量而正确；

4.用empty代替size检查是否为0；

5.尽量使用区间成员函数代替它们的单元素兄弟；

6.警惕c++最令人恼怒的解析问题；

7.在使用new指针的容器时，记得容器销毁前释放空间；

9.在删除选项中仔细选择；

10.注意分配器的协定和约束； ？？？

11.理解自定义分配器的正确用法； ？？？

12.对STL容器线性安全性的期待现实一些；

vector和string

13.尽量使用vector和string代替动态分配的数组；

14.使用reserve来避免不必要的重新分配；

15.小心string实现的多样性；c++11不运行使用引用计数实现string

16.如何将vector和string的数据传给遗留代码；

18.避免使用`vector<bool>`

关联容器：

19.了解相等和等价的差别；

20.为指针的关联容器指定比较类型；

21.永远让比较函数对相等的值返回false；

24.当关乎效率时应该在operator[]和insert之间仔细选择；

迭代器：

27.使用advance和distance将const_iterator转换为iterator;

28.了解reverse_iterator的base得到的iterator;

算法：

30.保证目标区间足够大；

31.了解你的排序选择；

32.如何真的想删除东西使用类似remove和erase组合；

33.提防对指针容器使用remove;

34.注意哪个算法需要有序区间；

35.使用mismatch和lexicographical来比较不区分大小写的字符串；

37.使用accumulate和for_each来统计区间

仿函数类：

38.仿函数设计成值传递；

39.使用纯函数做判别式；

40.使仿函数类可适配；

42.确定`less<T>`表示operator< ???

使用STL编程：

43.尽量使用算法调用代替循环；

44.尽量使用成员函数代替同名算法；

45.注意count, find, binary_search, lower_bound, upper_bound和equal_range区别；

46.考虑使用函数对象代替函数作为算法中的参数；

47.避免产生只写代码；

48.总是include合适的头文件；

49.学习stl有关的诊断信息；

50.熟悉stl相关网站。











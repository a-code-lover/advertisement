
### 为什么使用智能指针？

为了解决c++内存泄露的问题，c++11引入智能指针。

```c++
void remodel(std::string & str)
{
    std::string * ps = new std::string(str);
    ...
    if (weird_thing()) //发生异常时，delete不执行导致内存泄漏。
        throw exception();
    str = *ps;
    delete ps;
    return;
}
```

### 智能指针是什么？

智能指针的原理：接受一个申请好的内存地址，将基本类型指针封装到类，构造一个保存在栈上的智能指针对象，当程序退出栈的作用域范围后，由于栈上的对象自动被销毁，智能指针内部保存的内存也被自动释放掉。在析构函数里面编写delete，利用对象的自动析构达到自动释放内存。

### 怎么用？

在< memory >头文件内提供三种智能指针：`shared_ptr` `unique_ptr` `weak_ptr`

`shared_ptr`

```java
std::shared_ptr<Person> p1(new Person(1));// Person(1)的引用计数为1
std::shared_ptr<Person> p2 = std::make_shared<Person>(2);
p1.reset(new Person(3));// 首先生成新对象，然后引用计数减1，引用计数为0，故析构Person(1)
                        // 最后将新对象的指针交给智能指针
std::shared_ptr<Person> p3 = p1;//现在p1和p3同时指向Person(3)，Person(3)的引用计数为2

p1.reset();//Person(3)的引用计数为1
p3.reset();//Person(3)的引用计数为0，析构Person(3)
```

注意事项：

+ 不要用同一个原始指针初始化多个`shared_ptr`, 会造成二次销毁;
+ 不要在函数实参创建`shared_ptr`， 不同编译器参数的计算顺序不同;
+ 避免循环引用，智能指针的最大陷阱之一，循环引用会导致内存泄漏。

将unique_ptr转为shared_ptr？

### 为什么弃用auto_ptr？

`auto_ptr`和`unique_ptr`一样使用所有权模型，但是`unique_ptr`更严格，不允许赋值，赋值操作会导致编译错误，从而避免了内存错误的可能性。总之，弃用auto_ptr：避免潜在的内存奔溃可能。

```c++
template <class T>
class auto_ptr {
private:
    T *pointee;

public:
    explicit auto_ptr(T *p = 0) : pointee(p) {}
    template<class U>
    auto_ptr(auto_ptr<U>& rhs) : pointee(rhs.release()){}
    ~ auto_ptr() {if(pointee) delete(pointee);}

    template<class U>
    auto_ptr<T>& operator=(auto_ptr<U>& rhs) {
        if (this != &rhs) reset(rhs.release()); //剥夺所有权可以避免多次销毁，但是访问rhs会出错。
        return *this;
    }
    T& operator*() {return *pointee;}
    T* operator->() {return pointee;}
    T* get() {return pointee;}
    //...
};
```

```java
void f() {
    auto_ptr< string> ps (new string ("good boy"));
    auto_ptr<string> vocation;
    vocaticn = ps;
    cout << *ps << endl; //程序崩溃，ps为空指针
}
```

### unique_ptr比auto_ptr更智能

```c++
unique_ptr<string> demo(const char * s)
{
    unique_ptr<string> temp (new string (s))；
    return temp；
}
unique_ptr<string> ps;
ps = demo('Uniquely special")； //unique_ptr是临时右值，则编译器允许赋值

unique_ptr<string> pu1(new string ("hello world"));
unique_ptr<string> pu2;
pu2 = pu1;                                      // #1 not allowed
unique_ptr<string> pu3;
pu3 = unique_ptr<string>(new string ("You"));   // #2 allowed
```

### 选择哪一种智能指针？

STL容器包含指针时，可使用`shared_ptr`，因为stl算法一般都支持拷贝和赋值操作。
如果函数使用new分配内存，并返回指针，则将返回类型声明为`unique_ptr`是不错的选择。
boost库提供shared_ptr(类似), scoped_ptr(类似unique_ptr)

### 智能指针是多线程安全的吗？

[多线程读写shared_ptr加锁](https://www.cnblogs.com/Solstice/archive/2013/01/28/2879366.html)
[shared_ptr是否线程安全](https://beamnote.com/2014/is-shared-ptr-thread-safe/)

### 智能指针是异常安全的吗？

### 有没有引用计数更好的方法？

### 高级使用

`shared_ptr`支持定制型删除器（custom deleter），可防范 Cross-DLL 问题（对象在动态链接库（DLL）中被 new 创建，却在另一个 DLL 内被 delete 销毁）、自动解除互斥锁

参考：

<http://www.cnblogs.com/lanxuezaipiao/p/4132096.html>
[常见使用错误](http://blog.jobbole.com/104666/)
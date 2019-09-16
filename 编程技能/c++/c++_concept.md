# concept of c++

参考教程：

+ <http://www.cplusplus.com/doc/tutorial/>
+ [effective c++中文翻译版](https://wizardforcel.gitbooks.io/effective-cpp/content/)
+ [代码规范](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/)
+ [注释规范统一](https://blog.csdn.net/guyue35/article/details/46775211)

## 1.etc

1. NULL:macro definition of a null pointer, in c++11 standard, we use nullptr. ``#define NULL 0`` or ``#define NULL (void*)0`` , in fact the 0 has different meanings depending on the context in which its used.

2. 正则表达式和类的{}要加分号。

## 2.class initialization

``= default`` **显式默认**  ``= delete`` **显式禁用某个函数**

as soon as a class has some constructor taking any number of parameters explicitly declared, the compiler no longer provides an implicit default constructor, and no longer allows the declaration of new objects of that class without arguments.
对于内置类型而言，new仅仅是分配内存，除非后面显示加(),相当于调用它的构造函数，对于自定义类型而言，只要一调用new，那么编译器不仅仅给它分配内存，还调用它的默认构造函数初始化，即使后面没有加()。

<http://www.cplusplus.com/doc/tutorial/classes2/>

## 3.struct and union for class

>Classes can be defined not only with keyword class, >but also with keywords struct and union.
>
>The keyword struct, generally used to declare plain data structures, can also be used to declare classes that have member functions, with the same syntax as with keyword class. The only difference between both is that members of classes declared with the keyword struct have public access by default, while members of classes declared with the keyword class have private access by default. For all other purposes both keywords are equivalent in this context.
>
>Conversely, the concept of unions is different from that of classes declared with struct and class, since unions only store one data member at a time, but nevertheless they are also classes and can thus also hold member functions. The default access in union classes is public.

## 4.compilation error and runtime error

## 5.operator overload

Operators are overloaded by means of operator functions, which are regular functions with special names.

```c++
class CVector {
  public:
    int x,y;
    CVector () {};
    CVector (int a,int b) : x(a), y(b) {}
    CVector operator + (const CVector&);
};

CVector CVector::operator+ (const CVector& param) {
  CVector temp;
  temp.x = x + param.x;
  temp.y = y + param.y;
  return temp;
}
//But some operators can also be overloaded as non-member functions.
CVector operator+ (const CVector& lhs, const CVector& rhs) {
  CVector temp;
  temp.x = lhs.x + rhs.x;
  temp.y = lhs.y + rhs.y;
  return temp;
}

c = a + b;
c = a.operator+ (b);
```

## 6.static

In fact, static members have the same properties as non-member variables but they enjoy class scope. For that reason, and to avoid them to be declared several times, they cannot be initialized directly in the class, but need to be initialized somewhere outside it.
Because member functions are like non-member functions, they cannot access non-static members of the class (neither member variables nor member functions). They neither can use the keyword this.

## 7.const object

>const objects are limited to access only member functions marked as const, but non-const objects are not restricted and thus can access both const and non-const member functions alike.
>
>When an object of a class is qualified as a const object:const MyClass myobject;
The access to its data members from outside the class is restricted to read-only, as if all its data members were const for those accessing them from outside the class. Note though, that the constructor is still called and is allowed to initialize and modify these data members:

```c++
int get() const {return x;}        // const member function
const int& get() {return x;}       // member function returning a const&
const int& get() const {return x;} // const member function returning a const& 
```

member overloaded as constness

```c++
// overloading members on constness
#include <iostream>
using namespace std;

class MyClass {
    int x;
  public:
    MyClass(int val) : x(val) {}
    const int& get() const {return x;}
    int& get() {return x;}
};

int main() {
  MyClass foo (10);
  const MyClass bar (20);
  foo.get() = 15;         // ok: get() returns int&
// bar.get() = 25;        // not valid: get() returns const int&
  cout << foo.get() << '\n';
  cout << bar.get() << '\n';

  return 0;
}
```

## 8.explicit : converting constructor

+ <https://www.cnblogs.com/ymy124/p/3632634.html>
+ <https://www.cnblogs.com/this-543273659/archive/2011/08/02/2124596.html>

C++中的explicit关键字只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的, 跟它相对应的另一个关键字是implicit, 意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式).

## 9.class template

```c++
template <class T> class mycontainer { ... }; //generic template
template <> class mycontainer <char> { ... }; //template specialization

template <class T>
T mypair<T>::getmax ()
// the third T (the one between angle brackets) is also a requirement: It specifies that this function's template parameter is also the class template parameter.
```

## 10.copy constructor

[shallow copy vs deep copy](https://stackoverflow.com/questions/2657810/deep-copy-vs-shallow-copy)
<http://www.cplusplus.com/doc/tutorial/classes2/>

```c++
MyClass foo;
MyClass bar (foo);       // object initialization: copy constructor called
MyClass baz = foo;       // object initialization: copy constructor called
foo = bar;               // object already initialized: copy assignment called
```

Note that baz is initialized on construction using an equal sign, but this is not an assignment operation! (although it may look like one)

```c++
MyClass fn();            // function returning a MyClass object
MyClass foo;             // default constructor
MyClass bar = foo;       // copy constructor
MyClass baz = fn();      // move constructor
foo = bar;               // copy assignment
baz = MyClass();         // move assignment
```

## 11.leaky abstraction

## 12.inline functions

>Calling a function generally causes a certain overhead (stacking arguments, jumps, etc...), and thus for very short functions, it may be more efficient to simply insert the code of the function where it is called, instead of performing the process of formally calling a function.

## 13.inheritance

<https://harttle.land/2015/06/29/cpp-encapsulation-and-inheritance.html>

>Unless otherwise specified, the constructors of a derived class calls the default constructor of its base classes (i.e., the constructor taking no arguments). Calling a different constructor of a base class is possible, using the same syntax used to initialize member variables in the initialization list.

|             | public    | protected | private |
| ----------- | :-------: | :-------: | ------- |
| public inh  | public    | protected | no |
| protect inh | protected | protected | no |
| private inh | private   | private   | no |

## [14.polymorphism]

<http://www.cplusplus.com/doc/tutorial/polymorphism/>  
<https://harttle.land/2015/06/28/cpp-polymorphism.html>
>One of the key features of class inheritance is that a pointer to a derived class is type-compatible with a pointer to its base class. Polymorphism is the art of taking advantage of this simple but powerful and versatile feature.
>
>A virtual member is a member function that can be redefined in a derived class, while preserving its calling properties through references.
>
>A class that declares or inherits a virtual function is called a polymorphic class. Classes that contain at least one pure virtual function are known as abstract base classes. Virtual members and abstract classes grant C++ polymorphic characteristics, most useful for object-oriented projects.
>
>An abstract base class is not totally useless. It can be used to create pointers to it, and take advantage of all its polymorphic abilities. And can actually be dereferenced when pointing to objects of derived (non-abstract) classes.

## [15.type casting]

<http://www.cplusplus.com/doc/tutorial/typecasting/)>  
no_safe

```c++
double x = 10.3;
int y;
y = int (x);    // functional notation
y = (int) x;    // c-like cast notation
```

## 16.Exceptions

## 17.lambda

1. Capture 子句（在 C++ 规范中也称为 lambda 引导。）<https://blog.csdn.net/zh379835552/article/details/19542181>
2. 参数列表（可选）。 （也称为 lambda 声明符)
3. 可变规范（可选）。
4. 异常规范（可选）。
5. 尾随返回类型（可选）。
6. “lambda 体”

![lambda](../rsc/lambda.jpg)

```c++
result = [](const string& str){return"Hello World" + str;}("3!");
//equal to below
auto lambda = [](const string& str){return"Hello World" + str;};
string result = lambda("3!");
```

## [18.可变模板参数](http://www.cnblogs.com/qicosmos/p/4325949.html)

### (1)可变模板参数函数

```c++
template <class... T>
void f(T... args)
{
    cout << sizeof...(args) << endl; //打印变参的个数
}

f();        //0
f(1, 2);    //2
f(1, 2.5, "");    //3
```

### (2)递归展开：

```c++
template<typename T>
T sum(T t)
{
    return t;
}
template<typename T, typename ... Types>
T sum (T first, Types ... rest)
{
    return first + sum<T>(rest...);
}

sum(1,2,3,4); //10
```

### (3)逗号展开

```c++
template <class T>
void printarg(T t)
{
   cout << t << endl;
}

template <class ...Args>
void expand(Args... args)
{
   int arr[] = {(printarg(args), 0)...};
}

expand(1,2,3,4);
```

### (4)可变模板参数类

```c++
//前向声明,可以忽略
template<typename... Args>
struct Sum;

//基本定义
template<typename First, typename... Rest>
struct Sum<First, Rest...>
{
    enum { value = Sum<First>::value + Sum<Rest...>::value };
};

//递归终止
template<typename Last>
struct Sum<Last>
{
    enum { value = sizeof (Last) };
};
```

## 19.完美转发 std::forward

>When used according to the following recipe in a function template, forwards the argument to another function with the value category it had when passed to the calling function.

传参时保持参数的左值或右值属性

```c++
template<class T>
void wrapper(T&& arg)
{
    foo(std::forward<T>(arg)); // Forward a single argument.
}
```

参考：<https://blog.csdn.net/liujiayu2/article/details/49279419>

## 20.RAII机制

Resource acquisition is auquisition.
**本质内容是用对象代表资源，把管理资源的任务转化为管理对象的任务，将资源的获取和释放与对象的构造和析构
对应起来，从而确保对象生命周期内资源一定有效，对象在销毁时资源一定释放。在智能指针，lock_guard等中使用。**

## 21.指针

### (1)智能指针

**shared_ptr**  
<https://blog.csdn.net/Xiejingfa/article/details/50750037>  
<https://heleifz.github.io/14696398760857.html>  
<https://blog.csdn.net/sixdaycoder/article/details/45787713>

**weak_ptr**
用于解决shared_ptr相互引用时的死锁问题。  

**unique_ptr**  一次

### (2)野指针

>野指针指向一个已删除的对象或未申请访问受限内存区域的指针。与空指针不同，野指针无法通过简单地判断是否为 NULL避免，而只能通过养成良好的编程习惯来尽力减少。对野指针进行操作很容易造成程序错误。

成因：  

+ 指针未初始化：任何指针变量刚被创建时不会自动成为NULL指针，它的缺省值是随机的，它会乱指一气。所以，指针变量在创建的同时应当被初始化，要么将指针设置为NULL，要么让它指向合法的内存。
+ 指针对象释放后未置空：别看free和delete的名字（尤其是delete），它们只是把指针所指的内存给释放掉，但并没有把指针本身干掉。此时指针指向的就是“垃圾”内存。释放后的指针应立即将指针置为NULL，防止产生“野指针”。
+ 指针操作超过作用域

### (3)悬空指针

>在C/C++等语言中，悬空指针（Dangling Pointer）指的是：一个指针的指向对象已被删除，那么就成了悬空指针。野指针是那些未初始化的指针。有时也把野指针和悬空指>针通称悬空指针。

### (4)裸指针

c/c++的原始指针，与智能指针对应。
指针和变量一样，也是有地址的，只不过变量的值被解释成一个值，而指针的值被解释成一个地址。实现树的题目可以训练指针的使用。

## 22.volatile

+ <https://blog.csdn.net/friendbkf/article/details/45542337>  
+ <https://blog.csdn.net/whatday/article/details/52511071>

## 23.define宏定义的缺陷：

+ <https://blog.csdn.net/ipmux/article/details/17336809>  
+ <https://blog.csdn.net/wangweixaut061/article/details/6042633>  
+ <https://blog.csdn.net/u013910522/article/details/22672057>

## 24.functor仿函数：

仿函数重载(),生成的是对象，而不是函数调用。  

+ <https://my.oschina.net/llehs/blog/180594>
+ <http://www.bogotobogo.com/cplusplus/functors.php>  
+ <https://blog.csdn.net/tianshuai1111/article/details/7687983>

## 25.RTTI机制

<https://blog.csdn.net/magoyang/article/details/52480001>

## 26.全特化和偏特化

>定义：正对任何template参数更进一步的条件限制，所设计出来的一个特化版本。

```c++
template<typename T>
class c {...}; //这个泛化版本允许T为任何类型
template<typename T>
class c(T*) {...}; //这个特化版本仅适用T为原生指标
```

## 27.TMP模板元编程

+ <https://www.cnblogs.com/liangliangh/p/4219879.html>

## 28.正则表达式

+ <http://blog.sina.com.cn/s/blog_4a0824490102x4hv.html>
+ <http://blog.guoyb.com/2016/09/10/cpp11-9/>

## 29.Exception异常机制是c++区别于c的一个重要方面

<https://blog.csdn.net/zhangyifei216/article/details/50410314>  
[堆栈解退](https://blog.csdn.net/daye704/article/details/50699215)  
<https://senitco.github.io/2017/10/15/cplusplus-exception/>

## 30.function template的类型推导机制

## 31.placement new()

<https://blog.csdn.net/zhangxinrun/article/details/5940019>

## 32.decltype()


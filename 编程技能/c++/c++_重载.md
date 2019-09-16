# 重载

C语言不支持重载。

## 运算符重载

重载的运算符是具有特殊名字的函数，对于二元运算符，左侧运算对象传递给第一个参数，而右侧运算对象传递给第二个参数。

+ 不能重载内置类型的运算，对于一个运算符函数，它或是类的成员，或者至少含有一个类类型的参数；
+ 当一个重载的运算符是成员函数时，this隐式绑定到左侧的运算对象，所以成员运算符函数的参数数量比运算对象的数量少一个；
+ 处理重载函数调用运算符`operator()`之外，其他重载运算符不能含有默认参数；
+ 只能重载已有的运算符，不能重载的运算符`::`, `.`, `.*`, `?:`，逻辑运算符、逗号、取地址符等不建议重载;
+ 通过函数调用或者使用普通表达式调用，二者等价；
+ 使用与内置类型一致的含义，如何重载输出运算符不打印换行；
+ 赋值、下标、函数调用和箭头运算符必须是类的成员。

```c++
//重载输出运算符

//重载赋值运算符

//重载下标运算符
```

### 赋值运算符重载

```c++
//重载赋值运算符，默认的指针是浅拷贝，重载为深拷贝
class MyStr
{
private:
  string *_strptr;
public:
  MyStr(){};
  MyStr(string str) {
    _strptr = new string(str);
  }
  MyStr(const MyStr& mystr) {
    _strptr = new string(*mystr._strptr);
  }
  MyStr& operator=(const MyStr& mystr) { // 赋值１：覆盖默认赋值运算
    if (this != &mystr) {
      if (_strptr)
        delete _strptr;
      //默认的行为：_strptr = mystr._strptr;
      //mystr只能访问const函数
      _strptr = new string();
      *_strptr = *(mystr._strptr); //为什么能访问private？
    }
    return *this;
  }

  MyStr& operator=(string str) { //赋值２：不会覆盖默认赋值运算
    *_strptr = str;
    return *this;
  }

  ~MyStr() {delete _strptr;}

  string* get() const{
    return _strptr;
  }
  
  friend ostream& operator<<(ostream& out, const MyStr &ms); //重载输出运算符，声明为友员可以输出private
};

ostream& operator<<(ostream& out, MyStr&ms) {
  cout << *ms._strptr;
  return out;
}
```

+ 调用时机，区分拷贝构造函数和赋值函数，如果匹配的构造函数和赋值运算符重载函数同时存在，则调用赋值运算符重载函数。

```c++
  Mystr a("mike");
  string str = "john";
  //如果没有第二个赋值函数，则先执行构造函数，再执行第一个构造函数
  //如果第二个赋值函数，则直接执行第二个赋值函数；
  a = str;
```

+ 提供默认版本的时机，程序没有显式地提供一个以本类或本类的引用为参数的赋值运算符重载函数时，编译器会自动生成这样一个赋值运算符重载函数。注意我们的限定条件，不是说只要程序中有了显式的赋值运算符重载函数，编译器就一定不再提供默认的版本，而是说只有程序显式提供了以本类或本类的引用为参数的赋值运算符重载函数时，编译器才不会提供默认的版本。即编译器默认提供`MyStr& operator=(const MyStr& mystr)`的实现。
+ 赋值运算符重载只能是类的非静态成员函数，不能是静态成员函数，因为静态成员函数只能访问静态变量；不能是友员函数，，因为友员函数不属于这个类，此时编译器会生成默认版本的赋值含，产生二义性。
+ 赋值运算符不能被继承，因为派生类有自己的成员。

参考：<https://www.cnblogs.com/zpcdbky/p/5027481.html>

### 输入输出运算符重载

```c++
class MyStr {
  ...
  // 重载为成员函数
  // ostream& operator<<(ostream& out) {
  //   out << *(this->_strptr);
  //   return out;
  // }
  friend ostream& operator<<(ostream& out, const MyStr &ms); //此处使用const
  friend istream& operator<<(istream& out, MyStr &ms); //此处无const
};

ostream& operator<<(ostream& out, const MyStr&ms) {
  cout << *ms._strptr;
  return out;
}

istream& operator>>(istream& in, MyStr& ms) {
  string s;
  in >> s;
  *(ms.get()) = s;
  return in;
}

int main() {
  MyStr a("mike");
  cout << a << endl;
  cin >> a;
  cout << a << endl;
  return 0;
}
```

如果直接重载为类的成员函数，则因为this指针默认为第一个参数，此时调用方式是`ClassObj << cout;`，实现方式为注释部分。因此为了与IO标准库一致，使用友员函数（注意重载赋值运算符不能使用友员）。

### 重载下标运算符

```c++
char Flag = '*';
class MyStr {
  ...
  char& operator[](int i) {
    if (i >= 0 && i < length)
      return (*_strptr)[i];
    else
      cout << "索引越界" << endl;
    return flag;
  }
};
```

### 重载算术和关系运算符

```c++
class MyStr {
private:
  string m_name;
public:
  MyStr(){}
  MyStr(string name) : m_name(name){}
  bool operator==(const MyStr &rhs) {
    return m_name == rhs.m_name;
  }
  MyStr operator+(const MyStr &rhs) {
    MyStr sum;
    sum.m_name = this->m_name + rhs.m_name;
    return sum;
  }
};
```

### 重载递增递减

```c++
class MyStr {
private:
  int m_age;
public:
  MyStr(){}
  MyStr(int age) : m_age(age){}
  MyStr& operator++() { // 前置类型返回引用
    ++this->m_age;
    return *this;
  }
  MyStr operator++(int) { // 后置类型返回临时变量
    MyStr ret = *this;
    ++*this;
    return ret;
  }
  friend ostream& operator<<(ostream& out, const MyStr& ms);
};
```

### 重载转换运算符

```c++
//operator TypeNmae()
struct B
{
  explicit B(int) {}
  explicit operator bool() const { return true; }
};

if (B) ...
```

## 函数重载

### 什么是函数重载？

函数重载是指在同一作用域内，可以有一组具有相同函数名，不同参数列表的函数，这组函数被称为重载函数。重载函数通常用来命名一组功能相似的函数，这样做减少了函数名的数量，避免了名字空间的污染，对于程序的可读性有很大的好处。

### 为什么需要使用函数重载？

+ 试想如果没有函数重载机制，如在C中，你必须要这样去做：为这个print函数取不同的名字，如print_int、print_string。这里还只是两个的情况，如果是很多个的话，就需要为实现同一个功能的函数取很多个名字，如加入打印long型、char*、各种类型的数组等等。这样做很不友好！
+ 类的构造函数跟类名相同，也就是说：构造函数都同名。如果没有函数重载机制，要想实例化不同的对象，那是相当的麻烦！
+ 操作符重载，本质上就是函数重载，它大大丰富了已有操作符的含义，方便使用，如+可用于连接字符串等

### 使用

```c++
  const string& shorterString（const string &s1, const string &s2) {
    return s1.size() < s2.size() ? s1 : s2;
  }
  string& shorterString(string &s1, string $s2) {
    auto &r = shorterString(const_cast<const string&>(s1), const_cast<const string&>(s2));
    // auto会忽略引用
    return const_cast<string&>(r);
  }
```

1.一个拥有**顶层const**的形参无法和另一个没有顶层const的形参区别开来，不能重载；如果形参是某种类型的指针或引用，**底层const**可以实现重载。  
2.const_cast在重载函数的情景最有用

### 函数模板和函数重载

当您想对可能不同的类型执行相同的操作时,模板可以提供优势。
当您要根据类型应用不同的操作时,可以使用重载。

### 函数模板的特化和重载

```c++
//non-template function
inline const int& max( const int& a, const int& b ) {
  std::cout << "non-template max() is called" << std::endl;
  return a < b ? b : a;
}

//template function
template < typename T >
inline const T& max( const T& a, const T& b ) {
  std::cout << "template max() is called" << std::endl;
  return a < b ? b : a;
}

int main() {
::max( 7.0, 42.0 ); //template max() is called
::max( 'a', 'b' ); //template max() is called
::max( 7, 42 ); //non-template max() is called
::max<>( 7, 42 ); //template max() is called
::max< double >( 7, 42 ); //template max() is called
::max( 'a', 42.7 ); //non-template max() is called
::max<int>('a', 42); //template max() is called
::max<>('a', 42); //编译错误
return 0;
}
```

参考：
<https://blog.csdn.net/colddie/article/details/8664428>  
<https://imzlp.me/posts/10380/>
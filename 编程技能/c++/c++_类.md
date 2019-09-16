### 访问控制与继承

类使用protected关键字声明它希望与派生类分享而不想被其他公共访问的成员。

+ 和私有成员一样，protected成员对于类的用户是不可访问的；
+ 和公有成员一样，protected成员对于派生类的成员和友员是可以访问的；
+ 派生类不能访问普通的基类对象的protected成员；

```c++
class Base {
public:
  void pub_mem();
protected:
  int prot_mem;
private:
  char priv_mem;
};

struct Pub_Derv : public Base {
  // 正确：能访问protected成员
  int f() {return prot_mem;}
  // 错误：不能访问基类private成员
  char g() {return priv_mem;}
};

struct Priv_Derv : private Base {
  // 正确：private不影响派生类的访问权限
  int f1() {return prot_mem;}
};

struct Derived_from_Public : public Pub_Derv {
  // 正确
  int use_base() {return prot_mem;}
};

struct Derived_from_Private : public Priv_Derv {
  //错误
  int use_Base() {return prot_mem;}
};
```

| ----------- | public    | protected | private |
| ----------- | :-------: | :-------: | ------- |
| public inh  | public    | protected | no |
| protect inh | protected | protected | no |
| private inh | private   | private   | no |

### 注意事项

+ const对象不能访问非const成员函数；
+ static成员函数只能访问static成员变量；
+ 类可以嵌套，即类里面定义新的类，命名空间也可以嵌套；
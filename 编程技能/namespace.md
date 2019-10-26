## 如何声明不在同一个命名空间的两个类

假设B类中有个A的成员变量，然后我们又不想在B类头文件中引用A类的头文件（为了加快编译速度）。

### 如果类A,B没有命名空间

```c++
class A;  
  
class B {  
  A* val;  
}  
```

### 如果类A,B在同一个命名空间

```c++
namespace NB {
  class A;

  class B {
    A* val;
  }
}
```

### 如果类A,B在不同的命名空间

```c++
namespace NA {  
  class A;  
}  
  
namespace NB {  
  class B  
  {  
    A* val;  
  }  
}  
```

## 命名总结

### 一般通用命名

lhs, rhs：左边，右边

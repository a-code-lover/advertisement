
### [强制类型转换](http://c.biancheng.net/cpp/biancheng/view/3297.html)

#### static_cast

+ 用于非多态类型的转换
+ 不执行运行时类型检查（转换安全性不如 dynamic_cast）
+ 原有的自动类型转换，例如 short 转 int、int 转 double、**向上转型**等；
+ void指针和具体类型指针之间的转换，例如void *转int *、char *转void *等；
+ 有转换构造函数或者类型转换函数的类与其它类型之间的转换，例如 double 转 Complex（调用转换构造函数）、Complex 转 double（调用类型转换函数）。
+ static_cast也不能用来去掉表达式的 const 修饰和 volatile 修饰。

#### dynamic_cast

+ 用于多态类型的转换
+ 执行行运行时类型检查
+ 只适用于指针或引用
+ 对不明确的指针的转换将失败（返回 nullptr），但不引发异常
+ 可以在整个类层次结构中移动指针，包括向上转换、**向下转换**

#### const cast

> const与非const, volatile与非volatile转换

#### reinterpret_cast

+ 用于位的简单重新解释，`reinterpret_cast`可以认为是`static_cast`的一种补充，一些`static_cast`不能完成的转换
+ 允许将任何指针转换为任何其他指针类型（如`char*`到`int*`或`One_class*`到`Unrelated_class*`之类的转换，但其本身并不安全）
+ 也允许将任何整数类型转换为任何指针类型以及反向转换。
+ `reinterpret_cast`运算符不能丢掉`const`、`volatile`或`__unaligned`特性。
+ 滥用`reinterpret_cast`运算符可能很容易带来风险。除非所需转换本身是低级别的，否则应使用其他强制转换运算符之一。

### 运行时类型信息(RTTI)

+ dynamic_cast
  + 用于多态类型转换
+ typeid
  + typeid 运算符允许在运行时确定对象的类型
  + type_id 返回一个 type_info 对象的引用
  + 如果想通过基类的指针获得派生类的数据类型，基类必须带有虚函数
  + 只能获取对象的实际类型
+ type_info
  + ype_info 类描述编译器在程序中生成的类型信息。 此类的对象可以有效存储指向类型的名称的指针。 type_info 类还可存储适合比较两个类型是否相等或比较其排列顺序的编码值。 类型的编码规则和排列顺序是未指定的，并且可能因程序而异。
  + 头文件`typeinfo`
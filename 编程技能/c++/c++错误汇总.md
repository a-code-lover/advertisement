## segmentation fault

段错误应该就是访问了不可访问的内存，这个内存要么是不存在的，要么是受系统保护的。常见情况包括：

1. 对指向常量的指针进行写操作

2. 访问了不存在的内存，最常见是访问空指针，主要指针初始化的问题

3. 访问不允许访问的内存，常见为数组越界，将整型当指针访问

4. 在读一个格式错误文件是产生segmentation fault

## undefined reference to

1.链接时缺失相关目标文件(.o)，一般是编译是依赖条件写少了；
2.链接时缺少相关的库文件(.a|.so);
3.注意链接的先后顺序和完备；

## redefinition of 'xxx'

include循环引用的问题，添加条件编译。
[头文件互相包含的方法，但不推荐使用，应避免循环引用](https://www.zhihu.com/question/28353585)

## forward declaration of class

可以声明一个类而不定义它
`class Screen;//declaration of the Screen class`
这个声明,有时候被称为前向声明(forward declaration),在程序中引入了类类型的Screen.在声明之后,定义之前,类Screen是一个不完全类型(incompete type),即已知Screen是一个类型,但不知道包含哪些成员.
不完全类型只能以有限方式使用,不能定义该类型的对象,不完全类型只能用于定义指向该类型的指针及引用,或者用于声明(而不是定义)使用该类型作为形参类型或返回类型的函数.
也就是说我们使用前置声明是因为不想引入该类的头文件，但是前置声明是有限制的。这里我继承了该类，而继承是需要了解类的内部结构的，所以造成了这个错。

## "Cannot declare member function ...to have static linkage"

在头文件声明了static函数，则在源文件实现时不需要加static关键字。
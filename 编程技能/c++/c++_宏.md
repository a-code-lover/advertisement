# 宏的基本使用

摘自：<https://www.cnblogs.com/zhizhiyu/p/10155614.html>

## 不带参数的宏定义

`#define PI 3.1415926`
把程序中出现的PI全部换成3.1415926
说明：
（1）宏名一般用大写
（2）使用宏可提高程序的通用性和易读性，减少不一致性，减少输入错误和便于例如：数组大小常用宏定义
（3）预处理是在编译之前的处理，而编译工作的任务之一就是语法检查，预处理法检查。
（4）宏定义末尾不加分号；
（5）宏定义写在函数的花括号外边，作用域为其后的程序，通常在文件的最开头。
（6）可以用#undef命令终止宏定义的作用域
（7）宏定义可以嵌套
（8）`字符串" "中永远不包含宏`，字符串的内容不进行宏替换
（9）宏定义不分配内存，变量定义分配内存。

## 带参数的宏定义

（1）实参如果是表达式容易出问题
`#define S(r) r*r`
`area=S(a+b)`;第一步换为`area=r*r`;,第二步被换为`area=a+b*a+b`
正确的宏定义是`#define S(r) ((r)*(r))`
（2）`宏名和参数的括号间不能有空`
（3）宏替换只作替换，不做计算，不做表达式求
（4）函数调用在编译后程序运行时进行，并且分配内存。宏替换在编译前进行，不内
（5）宏的哑实结合不存在类型，也没有类型转换
（6）函数只有一个返回值，利用宏则可以设法得到多个
（7）宏展开使源程序变长，函数调用不
（8）宏展开不占运行时间，只占编译时间，函数调用占运行时间（分配内存、保留现场、值传递、返回值）

### \#的用法

`#define STR(str) #str`

`#`用于把宏定义中的参数两端加上字符串的`"`
比如，这里STR(my#name)会被替换成"my#name"
一般由任意字符都可以做形参，但以下情况会出错
STR())这样，编译器不会把“)”当成STR()的参数
STR(,)同上，编译器不会把“,”当成STR的参数
STR(A,B)如果实参过多，则编译器会把多余的参数舍去。（VC++2008为例)
STR((A,B))会被解读为实参为：(A,B)，而不是被解读为两个实参，第一个是(A第二个是B)。

### \##的用法

`#define WIDE(str) L##str`

则会将形参str的前面加上L
比如：`WIDE("abc")`就会被替换成`L"abc"`
如果有`#define FUN(a,b)` `vo##a##b()`
那么`FUN(id ma,in)`会被替换成`void main()`

`需要注意的是凡宏定义里有用'#'或'##'的地方宏参数是不会再展开.`
例子参考：<https://www.cnblogs.com/zhizhiyu/p/10155614.html>

## 使用场景

1.填充结构，例如构建json结构。

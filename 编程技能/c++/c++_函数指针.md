### 普通函数指针

c语言函数指针的定义形式：`返回类型 (*函数指针名称)(参数类型,参数类型,参数类型，…);`  
c++函数指针的定义形式：`返回类型 （类名称::*函数成员名称）（参数类型，参数类型，参数类型，….);`

```c++
void (*funP)(int);   //声明也可写成void(*funP)(int x)，但习惯上一般不这样。
void (*funA)(int);
void myFun(int x){}
int main()
{
    //一般的函数调用
    myFun(100);

    funP=&myFun;  //将myFun函数的地址赋给funP变量
    (*funP)(200);  //通过函数指针变量来调用函数

    funA=myFun;
    funA(300);

    // myFun的函数名与funP、funA函数指针都是一样的，即都是函数指针。
    // myFun函数名是一个函数指针常量，而funP、funA是函数数指针变量，这是它们的关系。
    // 转：函数名调用如果都得如(*myFun)(10)这样，那书写与读起来都是不方便和不习惯的。所以C语言的设计者们才会
    // 设计成又可允许myFun(10)这种形式地调用（这样方便多了，并与数学中的函数形式一样）。
    funP(400);
    (*funA)(600);
    (*myFun)(1000);

    typedef int (*fp)(int a); //typedef简化函数指针定义
    fp f = myFun;
    fp b[] = {funP, funA, myFun}; //构造函数指针数组
    return 0;
}
```

### 成员函数指针

1. 函数指针赋值要使用`&`，`返回类型 (classname::*fptrname)(参数列表) = &classname::funcname;`
2. 使用`object.*fptrname(参数)`(实例对象)或者`objectptr->*(参数)`（实例对象指针）调用类成员函数指针所指向的函数

```c++
class A {
    void setA(int a);
    virtual void print();
}
class B:public A {
    void setB(int b);
    virtual void print();
}

int main() {
    A a;
    B b;
    void (A::*ptr)(int) = &A::setA;
    void (A::*vptr)() = &A::print;
    A* pa = &a;

    //对于非虚函数，返回其在内存的真实地址
    printf("A::set(): %p\n", &A::setA);
    //对于虚函数， 返回其在虚函数表的偏移位置
    printf("B::print(): %p\n", &A::print);

    a.print();
    (a.*ptr)(100);
    (pa->*ptr)(100);
    return 0;
}
```

### 静态成员函数指针

```c++
class A {
public:
    void funcA();
    static void funcB();

    void (A::*p1)();
    void (*p2)();

    A(){
        p1 = &A::funA;
        p2 = &A::funB;

        //p1 =&A::funb;//error
        //p2 =&A::funa;//error
        //p1=&funa;//error,编译器错误 C2276
        //p2=&funb;//error,编译器错误 C2276
    }
};

int main() {
    A a;
    (a.*a.p1)(); //打印A，这个语法太过分了！！！！

    void (A::*p)() = a.p1;
    (a.*p)();

    /*尽管a.p2本身是个非static变量,但是a.p2是指向static函数的函数指针，
        **所以下面这就话是错的!
        */
    //p = a.p2;//error
    void (*pp)(void);
    pp = &A::funb;
    pp(); //打印 B

    return 0;
}
```

参考：<http://www.runoob.com/w3cnote/cpp-func-pointer.html>
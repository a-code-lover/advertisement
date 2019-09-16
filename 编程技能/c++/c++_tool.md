# tools extension of c++ development

## 1.Basic

## 2.G++

[reference : Linux下gcc和gdb](http://blog.51cto.com/goodhx/1734760)
[Linux下静态库和动态库的链接](https://blog.csdn.net/benpaobagzb/article/details/51364005)
<https://blog.csdn.net/surgewong/article/details/39236707>

+ g++ -E *.cpp (预处理，生成.i/.ii文件，预处理起cpp)
+ g++ -S *.cpp (生成.s汇编文件，编辑器egcs,用编辑器打开看到汇编指令)
+ g++ -c *.cpp (生成.o目标文件，汇编器as)
+ g++ *.o *.exe -L $PATH (生成执行程序，链接器ld)
+ g++ -o test.exe test.cpp (包括编译链接，直接生成执行程序)
+ -o (表示输出)
+ -g (表示可调试)
+ -v (输出编译过程和编译器版本信息)
+ "-std=c++11"
+ "-Wall" (输出gcc提供的所有警告)
+ "-static-libgcc" (链接静态库)

## 3.extension library

### (1)日志库：[boost::log and glog](https://blog.csdn.net/lltaoyy/article/details/56674538)

### (2)http库：facebook/proxygen

### (3)souce-to-source compiler: facebook/hip hop for PHP(translate php into c++)

## 4.编译器

python解释器：cpython, ipython, pypy.

### (1)GCC(G++)

### (2)LLVM(Clang)

<http://www.aosabook.org/en/llvm.html>  
<http://llvm.org/docs/tutorial/LangImpl05.html>
> a typical Three-Phase Compiler:  
> source -->[front end] [optimizer] [backend] -->machine code

1)DraggonEgg是一个GCC插件，使得GCC能够使用LLVM优化器和代码生成器来取代GCC自己的优化器和代码生成器。

### (3)MSVC(vc++)

## 5.GDB

(1)[gdb调试打印容器](https://blog.csdn.net/xiedejun1984/article/details/5752945)　　
[gdb调试基础](https://cloud.tencent.com/developer/article/1036960)

+ vscode是直接调用gdb。
+ (gdb) print *(myVector._M_impl._M_start)@myVector.size() 打印整个vector。
+ print *(myVector._M_impl._M_start)@N 打印第N个成员。
+ 在vscode的debug console中执行-exec p myVector查看容器模板

(2)enable-pretty-printing

## 6.项目打包工具，编译工具，调试工具，代码格式化工具，

### cmake工具

## 7.skia开源二位图形库

Chrome,Firefox,Android等众多产品的图形渲染引擎。

## 8.Cryto++加密库

<http://www.cppblog.com/ArthasLee/archive/2010/12/01/135186.html>
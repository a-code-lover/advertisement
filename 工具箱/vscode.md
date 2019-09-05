# notes for vscode

## 1.reference

+ [official](https：//code.visualstudio.com/docs/languages/cpp)
+ [vscode入门](https：//www.jianshu.com/p/3dda4756eca5)
+ [vim入门](https：//feifeiyum.github.io/2017/01/23/vimusage/)
+ [中文文档](https：//legacy.gitbook.com/book/jeasonstudio/vscode-cn-doc/details)
+ [基本使用教程](https：//www.w3cschool.cn/visualstudiocode/)
+ [配置c++](https：//www.zhihu.com/question/30315894)
+ [配置c++](https：//blog.csdn.net/qq_32126633/article/details/78838554)
+ [snippets](https://www.jianshu.com/p/1f1132df1def)

## 2.shortcut(C-k, C-s)

### (1)editor

+ C-k, v ： markdown live preview (C-S-v)
+ C-S-p / f1： show command palettte
+ C-space ： intellisense suggestions
+ C-1/2 ： 编辑器切换
+ A-num ： 标签切换 C-pageup/pagedown
+ C-p ： 快速打开最近打开的文件
+ C-k,C-s ： 查看所有快捷键
+ C-p, right arrow ： open muliple files
+ C-k, z ： zen mode
+ C-` ： terminal / C-S-y ： console;
+ C-l ： clear terminal C-k
+ C-S-e ： switch between explorer and editor
+ c-s-\：跳转到括号匹配处
+ C-a: choose all
+ C-up/down：滚动
+ A-arrowleft/right：last editor
+ S-A-arrowright: expand selection
+ S-点击split：垂直分割 C-k, C-\
+ C-g: go to line
+ F7: next symbol highlight
+ C-S-b: select build task to run

### (2)code

+ C-[/] ： indent line/outdent line
+ C-i ： select current line
+ C-S-p + 输入fold ： 可以查看所有折叠快捷键
+ A-arrow up/down ： move one line up or down
+ A-arrow left/right: last location
+ S-A-mouse drag： choose column
+ S-A-a: toggle block comment
+ C-k, v：markdown同时编辑预览
+ C-backspace/delete: delete a word
+ C-S-[/] : fold
+ C-k, C-0: fold all C-k, C-j: unfold all
+ A-z: toggle world wrap

### (3) etc

+ C-k, C-t: change color theme
+ terminal focus C-k: clear
+ C-S-y: debug terminal
+ C-S-u: toggle output
+ C-S-m: toggle problem
+ C-j: open/close panel面板
+ C-1: focus editor
+ C-k, C-arrowup/d/l/r: focus editor group
+ C-0: focus sidebar
+ C-f: focus find widget  esc/S-esc
+ C-S-pageup/down：切换panel顺序
+ S-A-f: format all C-k,C-f: format selection
+ C-k, C-f: format select
+ A-f5: move to next change
+ C-S-o: go to symbol in file
+ C-9, A-0: last editor
+ C-r: open recently
+ C-S-t: reopen closed editor
+ C-m: tab move focus通过tab获取焦点
+ C-win-w: toggle tab visibility
+ A-pageup/down: scroll

### (4)plugin  

#### settting sync

<https：//www.cnblogs.com/ashidamana/p/6761085.html>

+ S-A-u/d ： 同步

### (5)cpp

+ A-n: navigate
+ A-o: switch header/source
+ f12: declaration
+ A-f12: peak definition

## 3.编译环境

Mind： the folder .vscode must be put together with src files.

### c++

1. 数组越界竟然不输出错误，而是直接退出。。。。。。
2. c_cpp_properties.json文件中的includePath用于静态编译检查，实际在编译是要**将链接的文件添加到gcc的参数**中。
3. [gdb调试打印容器](https://blog.csdn.net/xiedejun1984/article/details/5752945)
    + vscode是直接调用gdb。
    + (gdb) print *(myVector._M_impl._M_start)@myVector.size() 打印整个vector。
    + print *(myVector._M_impl._M_start)@N 打印第N个成员。
    + 在vscode的debug console中执行-exec p myVector查看容器模板。
4. C-S-b: build, 可以通过terminal运行编译好的程序。

## 选择

ctrl+L:选择一行

### 离线安装插件依赖

To use the "offline" .vsix (that doesn't download OS-based dependencies on extension activation), download the .vsix that matches your OS and run the "Install from VSIX" command in VS Code.
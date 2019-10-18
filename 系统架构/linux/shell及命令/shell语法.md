# shell script

shell script用在系统管理上是一项很好的工具，但用在处理大量数值运算上不够好，因为速度较慢，且使用的cpu资源较多，造成主机的资源分配不良。

指令从上而下，从左而右分析执行；多个空格和空行会被忽略掉，tab当做空格；**如果读到一个enter符号，则尝试开始执行该命令**；如果一行内容太多，可以使用`\enter`衍生到下一行；使用`#`注释。

将网络上的好用的脚本拿来，改成合适自己主机的样子，学习效果最快。

## 基本

`#!/bin/bash`
`exit 0`
加上注释，author/program/time说明；
计算整数：var=$((10 % 2))
计算小数：`echo "123.12*55.5" | bc`
通过bash执行脚步其实是在子程序bash执行；通过source或小数点执行脚本则是在父程序中执行。
perm是权限的简写。
中括号的判断用法几乎和test是一样的，由于中括号使用在很多地方，所以用中括号判断时需要在中括号的两端加上空格分隔。
一个等号和两个等号都可以用作判断，推荐使用两个。
中括号内的变量需要双引号括起来，常量使用双引号或者单引号。

`name="vbird tsai"; [ ${name} == "vbird" ]`：报错too many arguments, 等同于`[ vbird tsai == "vbird"]`

`$@`：所有参数内容，`$#`：参数个数，`$0`：脚本文件路径名称，`shift n`：拿掉前面n个参数；

```shell
if [] || []; then
  ...
elif []; then
  ...
fi

case ${} in
  "")
    something
    ;;
  "")
    something
    ;;
  *)
    something
    ;;
esac

function fname(){
  something
}

while [ condition ] # until
do
  something
done

for var in condition
do
  something
done

for sit in $(seq 1 100) # 1到100, {1..100}也可以，{a..g}从a到g。

for (( i=1; i<=100; i=i+1))
do
  s=$((${s}+${i}))
done
```

`sh -n test.sh`：不执行脚本，仅检查语法
`sh -x test.sh`：将使用到的script内容显示在屏幕上

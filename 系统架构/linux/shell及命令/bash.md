# bash

`last`：数据源`/var/log/wtmp`,默认记录每个用户的登录次数和持续时间等信息；

### 变量

+ echo $PATH 或者 echo ${PATH},推荐使用后者;
+ myname=mike, 变量使用等号设置，等号两边不能有空格，变量名必须符合要求;
+ 双引号内的特殊字符如$等,可以保有原本的特性；而单引号内的特殊字符仅表示纯文本，如var="lang is $LANG"和var='lang is $LANG'区别。
+ 可使用转义字符将特殊字符转为一般字符；
+ 在一串指令的执行过程中，如需由其他指令提供信息，可以使用反单引号或者$指令；如：`version=$(uname -r), echo $version`
+ 扩充变量时，使用`“$变量名”`(**加双引号**)或者`${变量名}`（推荐），如：PATH="$PATH":/home/bin或者PATH=${PATH}:/home/bin
+ 若变量需要在其他子程序中使用，需要**使用export将变量变为环境变量**，如export PATH；
+ 通常大写为系统默认变量，自定义变量使用小写，方便区分；
+ 使用unset取消变量；
+ 注意引号配对规则，如name=`"vbird's name"`或`name=vbird\'s\ name`;

1.环境变量

通过env和export(不带参数)指令查阅所有环境变量，通过set常看所有环境变量与定义变量。

常用的环境变量，HOME,SHELL,HISTSIZE,PATH,LANG,RANDOM
常用的bash变量，PS1(bash提示字符),$(shell PID),?(上一指令成功与否回传值),OSTYPE/HOSTTYPE/MACHINETYPE

2.语言变量

`locale -a`：查看支持的语系，`locale`：查看当前语系设置；
语系文件放在`/usr/lib/locale`目录下，配置文件在`/etc/locale.conf`。
qq  qqjj

如何语系变量未设定，则会被LANG(主语言的环境)或LC_ALL(整体语系的环境)取代。

3.使用

`read -p 提示信息 -t 等待时间 variable`:从键盘输入读取变量值;
`declare -i rand=${RANDOM}*10/(65536/2)`：产生0-9随机数;
`declare -a(数组) -i(整数) -x(环境变量) -r(只读)`：默认为字符串，可声明类型，使用+取消动作；

4.变量删除，替换

`echo ${MAIL##/*/}`：保留文件名，`##`从左往右最长匹配，`#`
`echo ${MAIL%/*}`：保留文件路径，`%`从右往左最短匹配，`%%`

`${variable/old/new}`：替换第一个
`${variable//old/new}`：替换所有

`var=${str-expr}`,`-,+,=`三种判断替换
`var=${str:-expr}`

### alias/history

`alias lm='ls -al | more'`，注意使用单括号
`alias`：查看所有别名设置
`unalias lm`：取消设置
`!ssh`:执行最近的以ssh开头的命令
`history -c;history -w`：清空bash命令记录，主动写histfile，安全考虑；

### bash环境

1.指令执行顺序

1. 以绝对路径或者相对路径执行，如`/bin/ls或./ls`;
2. 有alias找到命令执行；
3. 有bash的内建（builtin）指令执行；
4. 通过$PATH变量顺序搜寻到第一个指令执行；

`type -a echo`：查看echo这个指令的顺序。
`cat /etc/issue`：查看修改登录欢迎信息, issue.net用于显示远程telnet登陆；`/etc/motd`登录后提示的额外信息；

2.bash配置

login shell:需要登录流程的bash,如tty1-tty6;
non-login shell:不需登录流程，如X window。

+ `/etc/profile`：系统整体设定，还会调用其他配置文件，包括`/etc/profile.d/*.sh 和 /etc/locale.conf`等；
+ `～/.bash_profile 或 ～/.bash_login 或 ～/.profile`：三个文件只会按顺序读取其中一个（兼容多种shell的使用习惯），为用户个人设定；.bash_profile文件会再调用`~/.bashrc`文件。
+ `source或者小数点.`：读入环境配置文件的指令

以上均为login shell读取的配置文件，对于non-login shell，只会读取`.bashrc`文件。

`/etc/man_db.conf`：指定执行man时，man page的查找路径，使用tarball安装软件时，需要手动将路径`/usr/local/software/man`添加上去。
`~/.bash_logout`：指定注销bash后，系统吧帮我们完成什么动作再退出。

+ C-s：暂停屏幕输出，
+ c-q：恢复屏幕输出，
+ C-z：暂停指令执行，
+ C-c：终止指令，
+ C-u：删除整行指令，
+ C-d：输入结束，

### 重定向

`1>`：正确信息输出，中间没有空格；
`2>`：错误信息输出，中间没有空格；
`2>&1`：正确信息与错误信息一并输出；
`2> /dev/null`：垃圾桶黑洞装置，忽略错误输出；

`cat > catfile`：获取屏幕输入，保存到catfile，C-d终止输入；
`cat > catfile < .bashrc`：获取.bashrc文件作为输入，输出到catfile，类似cp;
`cat > catfile << "eof"`：获取屏幕输入，输入eof为终止；

连续指令下达：`; 或 && 或 ||`，分号两个指令没有相关性。与或则是根据前一条指令执行成功与否再执行后面的指令。

### 管道

1.摘取

`echo ${PATH} | cut -d ':' -f 3,5`:以冒号为分隔符，第三个到第五个；
`export | cut -c 12-`:取每行输出的12个字符以后的数据；
`grep -i(忽略大小写) -n（输出行号） -c（统计次数） -v(反向选择)`

2.排序

`cat /etc/passwd | sort -t(分割符) ':' -k 3（第三栏排序） -n（以数字） -r(反向)`
`last | cut -d ' ' -f1 | sort | uniq（重复只显示一次） -c(统计) -i(忽略大小写)`
`wc -l(统计行数) -w(统计字数) -m(统计字符数)`
`last | tee -a last.list | cut -d " " -f1`：tee双向导流，同时输出到文件和屏幕，`-a`表示叠加方式。

3.转换

`tr -d(删除) s(去除重复)`
`last | tr '[a-z]' '[A-Z]'`：将所有小写变为大写;
`last | tr -d ':'`：删除所有冒号;

`col -x`：将tab用空格替代，`cat -A`:显示所有特殊字符；
`join paste expand`

4.分区

`split -b（以文件大小分割） -l（以行数分割）`
`cd /tmp; split -b 300k /etc/services services`：将services文件切割为servicesaa,servicesab等小文件；
`cat services* >> servicesback`：将小文件恢复为原文件；

5.参数转换

`id root`：查看用户id信息，该命令只接受一个参数，且不是管道命令
`cut -d ':' -f1 /etc/passwd | head -n 3 | xargs -p(交互) -n（每次接受几个参数） 1 id`
`xargs`：非常好用，为指令提供标准输入，参考鸟哥的教程10.6.7节。

6.减号

`tar -cvf - /home | tar -xvf - -C /tmp/homeback`：利用减号代替标准输入输出。

## 正则表达式（多练）

`^`在字符集合括号之内表示反向选择，在之外表示行首；
小数点表示任意一个字符，星号表示重复任意次。注意在通配符中星号代表0到无限个字符，而在正则中表示前一个字符重复0到无限次。

`grep -n 'go\{2,5\}g' regular.txt`：2到5个o，因为大括号在shell中是特殊字符，所以需要转义。

扩展RE支持字符：`+` `?` `|` `()` `()+`

1.`sed [-nefri] [adicps]`

`nl -b /etc/passwd | sed '2a drink tea'`
`sed 's/old/new/g'`

2.`printf`：格式化打印

3.awk

awk是一个非常好用的数据处理工具。相对与sed常常用于一整行的处理，awk则比较倾向于一行当中数个字段的处理。默认的字段分割符是tab或空格。

`last -n 5 | awk '{printf $1 '\t' $3}'`：最常用的动作，用来取数据；

awk每次处理一行，以字段为最小的处理单位。`NF`:当前行的字段数，`NR`：当前行数，`FS`：当前分隔符。

`cat /etc/passwd | awk 'BEGIN {FS=":"} $3 < 10 {print $1 "\t" $3}'`：基本语法是`awk '条件 {动作} 条件 {动作}'`

4.diff,patch

比较文件，产生补丁，升级还原






















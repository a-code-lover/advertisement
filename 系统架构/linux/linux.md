# linux notes

## 1.reference

+ [tools quick tutorial](http://linuxtools-rst.readthedocs.io/zh_CN/latest/base/01_use_man.html)
+ [common linux command](https://www.cnblogs.com/peida/archive/2012/12/05/2803591.html)
+ [all linux command](http://www.runoob.com/linux/linux-command-manual.html)
+ [terminal shortcut](https://www.cnblogs.com/cobbliu/p/3629772.html)
+ [bash 快捷键](https://github.com/hokein/Wiki/wiki/Bash-Shell%E5%B8%B8%E7%94%A8%E5%BF%AB%E6%8D%B7%E9%94%AE)

## 2.basic

+ [命令参数一个-和两个-](https://www.zhihu.com/question/41366215)
+ 命令前加一个减号表示忽略命令的部分错误继续执行。
+ /usr/share/application: contain all the graphic shortcuts of applications.
+ [查看系统版本](https://blog.csdn.net/u011669700/article/details/79443134)
+ python版本升级  
  + wget, tar -zxvf, cd, ./configure, make, sudo make install
+ python替换版本  
  <https://www.jianshu.com/p/9d3033d1b26f>
  <https://blog.csdn.net/fang_chuan/article/details/60958329>
  <http://www.5ycode.com/article/59.html>
+ 以d结尾命名服务，是守护进程。以.d结尾的文件夹，保持对原有配置的兼容，同时存在.config和.config.d或者同时存在rc和rc.d。
+ init.d: 包含许多系统各种服务的启动和终止的脚本。
+ ssh经常超时断开：/etc/ssh/sshd_config配置。
+ cat /etc/services 查看所有服务的网络端口号。
+ telnet 127.0.0.1 port 查看端口是否被占用。
+ [切换root用户](https://www.cnblogs.com/weiweiqiao99/archive/2010/11/10/1873761.html)
+ bc : 计算器
+ ctrl + d : terminal退出  ctrl + c

## 3.command

+ [ls -a -l -F -s -t -S / tree -L n](https://blog.csdn.net/xuehuafeiwu123/article/details/53817161)
+ nmcli / nmcli device show : 网络管理 (route -n, traceroute, netstat -r, )
+ uname
+ sudo apt install mesa-utils, glxinfo | grep rendering
+ useradd命令添加用户不能登录图形界面，使用adduser或者图形界面添加。
+ sudo /etc/init.d/gdm restart 重启图形界面

## 4.shortcut

+ C-A-t：终端
+ S-win-left/right/down/up：move window one monitor to left
+ C-A-T：switch system control
+ win-T：switch application
+ ctrl + alt + arrow up/down : swithch workspace
+ alt + ` : 在同一程序不同窗口切换
+ win-h：hide windows
+ shift + pageup/pagedown : terminal 翻页
+ win + launcher + num切换， + shift 新建
+ **文件夹下** alt + home : 到主文件夹， ctrl + h : 显示隐藏开关， f9 ： file侧边栏， alt + arrow ： 前进后退， ctrl + t : 新建标签， ctrl + shift + n : 新建文件夹，

## 5.tool

### (1)ssh

<http://www.ruanyifeng.com/blog/2011/12/ssh_remote_login.html>

### (2)./configure, make, make test, make install

<http://freetstar.com/trouble-shooting-configure-make-make-install>

这个要看你的Makefile的,约定俗成的而已。一般"潜规则"：

make就是make all,编译用的,具体编译了那些文件要看你的Makefile。

make install就是把编译出来的二进制文件,库,配置文件等等放到相应目录下，因为/usr/bin只有管理员才能向里面添加文件，所以通常要加sudo。

make clean清除编译结果。

具体的东西都在Makefile里面,只不过大部分应用程序的Makefile都是由configure脚本自动生成的,所以Makefile内容都差不多。

### (3)termtosvg

A Linux termimal recorder written in python that records your command lines sessions in standalone SVG animations.

## 5.shell script

### (1)Notice

1) no spaces before or after equal sign when set an variable.

### 快捷使用

+ C-a:行首
+ tab:補全

## 6.mysql

<http://www.cnblogs.com/xiaoluo501395377/archive/2013/04/07/3003278.html>
<https://blog.csdn.net/qq_35246620/article/details/70823903>  
[new installation, log in as root user](https://stackoverflow.com/questions/39281594/error-1698-28000-access-denied-for-user-rootlocalhost)
[remote connection](https://devdocs.magento.com/guides/v2.0/install-gde/prereq/mysql_remote.html)
[remote connection](https://www.cnblogs.com/XL-Liang/archive/2012/05/03/2481310.html)
[忘记密码](https://my.oschina.net/u/2297737/blog/688214)

### (1)完全卸载

[完全卸载参考，先卸载server](https://blog.csdn.net/w3045872817/article/details/77334886)
[8.0安装参考](https://blog.csdn.net/zyqblog/article/details/80159990)

### (2)操作

(1)mysql命令必须以分号结尾，否则不显示。  
(2)mysql可以输入多个语句执行。
(3)入门书籍：《mysql必知必会》。
(4)多数DBMS使用+或||实现拼接，mysql使用concat()函数实现。
(5)使用like或regexp匹配。
(6)Trim(), LTrim(), RTrim()去掉空格。
(7)sql函数：字符串，数值，日期时间，系统信息。
(8)Soundex()竟然支持类似发音匹配。
(9)aggregate函。
(10)数据分组：group by和having。
(11)字句顺序：select, from, where, group by, having, order by, limit.
(12)子查询。逐渐增加。
(13)联结：关系。

### (3)原理

## 7.gdb

<https://blog.csdn.net/analogous_love/article/details/53333894>
<http://wiki.ubuntu.org.cn/%E7%94%A8GDB%E8%B0%83%E8%AF%95%E7%A8%8B%E5%BA%8F>
[cdgb 0.7.0](https://cgdb.github.io/)
<https://zhuanlan.zhihu.com/p/32843449>

## 8.gnome

> 当图像界面崩掉时，可以通过tty重装gnome，直接在tty下装gnome就行，此时安装的是gnome和gnome classic。
[How To Re-Install Xorg Xserver Completely In Ubuntu](https://www.computersnyou.com/4945/re-install-xorg-xserver-completely-ubuntu/)
> 重装Ubuntu-desktop稍微复杂一些，以上教程当grub崩掉时，双系统在Windows添加新的启动项。
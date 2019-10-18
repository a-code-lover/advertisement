## 用户

`useradd username`：添加用户；
`useradd -D`:查看useradd的一些默认参数；
`passwd username`:设置密码；
`userdel -r username`：删除用户，连同home目录一起删除；
`usermod`：调整参数；

`finger username` `chfn`：查看和修改用户相关信息；

### 账号群组

`/etc/passwd`:`root:x:0:0:root:/root:/bin/bash`，用户/密码/uid/gid/说明/目录/shell;
`/etc/shadow`：`root:*:16559:5:60:7:5:16679:`，/用户/密码/更改日期/不可更改周期/需要更改周期/提前警告/宽限时间/失效时间/保留；
`/etc/group`：`root:x:0:`,/群名/密码/gid/支持账号名称；
`groups`:查看当前用户属于那些群组，第一个输出的为有效群组；
`newgrp`:切换有效群组，切换的名称必须在groups内；exit退出切换的有效群组；
`/etc/gshadow`
`/etc/default/useradd`：useradd指令的默认值调用了该文档；
`/etc/skel/`：用户home目录的各项数据都是从该目录复制过来的；

#### 群组操作

`groupadd 组名`：新建群组，-r：新建系统群组；
`gpasswd`：群组密码；
`groupmod -g gid -n newname oldname`;
`groupdel 组名`；
`gpasswd -A groupadm 组名`：添加群组管理员；-a：添加用户到群组，-d：从群组删除用户；

### 主用户组

`useradd -G classa mike`：创建新用户mike并添加到classa，同时创建主用户组mike；
`useradd -g classa mike`：创建新用户mike并添加到classa，主用户组为classa;
`usermod -a -G classa mike`：将已有用户mike添加到用户组classa;
`usermod -g classa mike`：直接将mike的主用户组该为classa；
`gpasswd -d mike classa`：将mike从用户组classa中删除，这要保证classa不是主用户组；

为什么每个用户都有一个与之同名的用户组？这与linux的权限机制有关，具体自己搜。

### 单独设置权限ACL（access control list）

`setfacl -m u:vbird:rx acl_test`
`getfacl acl_test`

### 用户切换

`su`或`su -`：切换到root用户；-m：表示使用目前的环境设定，不加载新使用者的配置文件；

`su`：nonlogin shell切换，这种方式很多原本的变量不会被改变，如USER/MAIL/PATH等；
`su -`和`su - username`：同时切换成新的环境；不能切换到系统账号，如sshd等。

`sudo`：su需要知道新切换的用户的密码。sudo则需要自己的密码。一般用户能够具有sudo使用权限，是由管理员事先审核通过的。与su相比则多用户不需要知道root密码。
`visudo`：修改/etc/sudoers文件指令，包含语法检查。
两次sudo指令间隔超过五分钟则需要重新输入密码；

系统账号使用的是`/sbin/nologin`的shell，这个shell是无法登入的，所以su无法切换到系统账号。

### 用户登录查询

`w` `who`：查看目前登入系统的用户；
`last`：查看使用者登录情况，包括可以是所有用户；
`lastlog`：查看每个账号最近登录时间；

查看系统启动时间：`who -b` `last reboot` `top` `w`






























































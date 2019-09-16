## reference

+ [linux守护进程的启动方法](http://www.ruanyifeng.com/blog/2016/02/linux-daemon.html)
+ [linux工具快速教程](https://linuxtools-rst.readthedocs.io/zh_CN/latest/index.html)
+ [systemd入门](http://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-commands.html)
+ [进程管理](http://gityuan.com/tags/#linux)
+ [进程的内存空间](https://github.com/1184893257/simplelinux/blob/master/mem.md)

## 问题

+ 进程和线程有什么区别？
+ 如何查看有哪些进程和线程？
+ 如何创建进程？如何创建线程？
+ [realid和effectiveid的区别？](https://stackoverflow.com/questions/32455684/difference-between-real-user-id-effective-user-id-and-saved-user-id)

## 基本概念

1.程序，进程，服务：
> 程序(program)：通常为binary program,放置在存储媒体中，为实体文件的形态存在；
> 进程(process)：程序触发后，将执行者权限与属性、程序的代码和所需数据等加载到内存中，操作系统给予这个内存单元一个标识符PID，可以说进程就是一个正在运行的程序。
> 服务(service)：常驻内存的进程通常负责一些系统提供的功能以及服务用户的各项任务，因此这些常驻程序称为服务。

2.进程调用流程（fork and exec）
> linux进程调用通常称为fork-and-exec流程，进程由父进程以复制（fork）的方式产生一个一模一样的子进程，然后被复制的子进程再以exec的方式执行实际要执行的程序，最终称为一个子进程的存在。

3.crontab定时任务（例行性工作排程）

> at指令执行单一排程任务，需要atd服务支持；
> crontab指令执行循环例行性排程，需要crond服务支持。

4.孤儿进程和僵尸进程
>孤儿进程：一个父进程退出，而它的一个或多个子进程还在运行，那么那些子进程将成为孤儿进程。孤儿进程将被init进程(进程号为1)所收养，并由init进程对它们完成状态收集工作。（没什么危害？？）
>僵尸进程：一个进程使用fork创建子进程，如果子进程退出，而父进程并没有调用wait或waitpid获取子进程的状态信息，那么子进程的进程描述符仍然保存在系统中，这种进程称之为僵尸进程。

5.service和daemon
>服务的提供总是需要程序的运行，达成服务的程序称为daemon,所以service和daemon没什么区别。一般服务在linux上使用时通常在名称后加d。

## 工作管理（job control）

1.对于一个终端接口，可以出现提示字符让你操作的环境称为前景（foreground），至于其他工作可以放在背景（background）运行。参考reference中“守护进程的启动方法”。

+ 工作管理的进程必须是shell的子进程（只管理自己的shell）;
+ 前景：可以控制与下达指令的环境；
+ 背景：可以自行运作，不能使用Ctrl-c终止，可使用bg/fg呼叫该工作；
+ 背景中的进程不能等待terminal/shell的输入。

2.工作管理

`&`：直接将指令放在背景执行；
`Ctrl-z`:将目前工作放到背景中暂停；
`jobs -l`:观察目前背景工作的状态，[+]代表最近放到背景的工作号码，可通过`fg`取出，[-]代表最近最后第二个放置到背景的工作号码，超过第三个后不显示；
`fg %jobnumber`：将背景工作拿到前景处理；
`bg %jobnumber`：让工作在背景状态下变为运作；
`kill -signalnum %jobnum`:管理背景工作，如重新执行，强制删除，正常结束等；
`kill -l`：显示目前kill能使用的signal有哪些；

3.以上管理的前景和背景都是针对bash,都会随着bash的关闭而终止，可以将工作放到系统背景中，实现脱机管理。

`disown`：将背景工作脱离bash；
`nohub [指令与参数] &`：不支持bash內建指令，必须是外部指令。

## 进程管理

1.基本问题：

+ 操作系统的各项工作都是有PID达成的，因此能不能进程某项工作，与该进程的权限有关；
+ 当整个系统的资源快用光时，如果找出最耗费资源的那个进程，然后删除该进程，让系统恢复正常；
+ 当某个程序写的不好，导致产生一个有问题的进程在内存当中，如何找出他并移除；
+ 当同时有五六项工作在系统中运行，如何让其中最重要的一项优先执行。

2.管理指令

`ps`参数：`-A`列出所有进程，`-o`自定义输出字段，`-u`有效使用者相关，
`ps aux`：*观察系统所有的进程数据
`ps -ef`:查看运行进程
`ps -l`：*仅观察自己bash的相关进程
`ps -lA`：也可以观察所有的进程数据
`ps axjf`：打印进程数
`top -d timegap -p pidnum`：动态观察进程变化，操作b,x,shift+[< >]
`pstree -up`：显示进程树，-u显示用户，-p显示进程号
`kill -signal PID`:向PID发信号
`killall -signal 指令名`：killall -i -9 bash
[top指令详解](http://www.cnblogs.com/peida/archive/2012/12/24/2831353.html)
[`free`](https://www.cnblogs.com/peida/archive/2012/12/25/2831814.html)：观察内存使用情况
`uname`：查看系统与核心信息
`uptime`：查看系统启动时间和负载
`netstat`：追踪网络和插槽文件
[vmstat工具](.)
[lsof工具](.)

造成僵尸进程的原因是进程执行完毕或者因故终止，但父进程却无法完整将该进程结束掉，导致该进程一致在内存中，占据PID号和资源。通过进程状态[STAT]为[Z]，且CMD后面加上[defunct]，代表该进程为僵尸进程。
如何处理僵尸进程？

主要的signal包括：（`kill -l` `man 7 signal`）
| 代号 | 名称 | 内容 |
| --- | --- | --- |
| 1   | SIGHUP | 启动被终止的进程，类似于重新启动 |
| 2   | SIGINT | 相当于ctrl-c中断进程 |
| 9   | SIGKILL | 强制中断 |
| 15  | SIGTERM | 执行完后序动作，正常终止 |
| 19  | SIGTOP | 相当于ctrl-z暂停 |

### 进程执行顺序

根据[PRI]优先级，[pri]值越小，优先级越高，越优先执行（并不以为着执行完，意味着占用更多执行时间）。
[PRI]由系统动态决定，不能干涉，用户可以调整Nice值。`PRI(new) = PRI+nice`

+ nice值的调整范围是-20～19；
+ root可以任意调整自己或者他人进程nice值，范围是-20～19；
+ 一般使用者仅可调整自己的进程nicde值，范围是0~19（避免一般用户抢占系统资源）；
+ 一般用户只能将nice值调高，例如本来nice是5，则未来仅能调整到大于5。

nice：给新执行的指令给予新的nice值； `nice -n -5 vim &` 将启动vim默认的NI值减少5
renice：已存在的进程nice重新调整； `renice -5 14836`将PID为14836的进程NI值设置为-5

### 创建进程

[子进程和父进程的区别](http://www.cnblogs.com/hnrainll/archive/2011/05/11/2043472.html)
[最简单的fork例程](https://www.cnblogs.com/hnrainll/archive/2011/05/11/2043501.html)

### 线程

`ps -T -p [pid]` 查看某个进程的所有线程，[-T]参数开启线程查看
`top -H -p [pid]` 查看特定进程的线程状况，**H键**切换进程（Tasks）和线程（Treads）查看模式。

## 系统服务管理

`systemctl list-units --type=target --all`
`systemctl list-unit-files` 查看服务
`systemctl list-dependencies` 查看服务依赖
`systemctl get-default` 默认模式
`systemctl list-sockets` 查看socket服务
`systemctl daemon-reload` 添加新的服务或更新配置使用

1.基本引导

+ daemon是什么？放在什么地方？功能是什么？
+ 如何启动daemon?如何有效管理？
+ 如果查看daemon打开了多少端口？如何关闭这些端口？这些端口各代表什么服务？

2.systemd启动服务管理

[systemd入门](http://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-commands.html)
[systemd管理实战](http://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-part-two.html)
[systemd发展](https://coolshell.cn/articles/17998.html)

3.状态
`systemctl list-units --type=service --all | grep cpu`

+ active(running)
+ active(excited)：仅执行一次就正常结束的服务；
+ active(waiting)：等待其他事件才能继续执行；
+ inactive：目前没有运行

预设状态：

+ enabled：开机执行；
+ disabled：开机不会执行；
+ static：不可以自启，可以被enabled服务唤醒；
+ mask：无论如何不能启动，因为已经被强制注销，同通过unmask修改。

4.开机启动项

+ systemctl list-unit-files 查看开机启动项
+ systemctl is-enabled redis.service  是否开机启动
+ systemctl enable redis.service  设置开机启动
+ systemctl disable redis.service  禁止开机启动

5.端口

`cat /etc/services`

6.操作模式（target）,切换

+ `systemctl poweroff`系统关机
+ `systemctl reboot`重新启动
+ `systemctl suspend`进入暂停模式
+ `systemctl hibernate`进入休眠模式
+ `systemctl rescue`进入救援模式
+ `systemctl emergency`进入紧急模式

7.创建hugo本地自启服务

`sudo vim /etc/systemd/system/hugo.service`
`systemctl enable hugo.service`

```service
[Unit]
Description=hugo local server service
After=network.target

[Service]
Type=simple
User=root
ExecStart=/home/mrk/blog/hugo_autostart.sh

[Install]
Wanted=multi-user.target
```
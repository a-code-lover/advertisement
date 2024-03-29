`rm -r ./*`

zip name.zip filename
zip -r name.zip folder
zip -r folder filename
tar -czvf name.tar.gz ./file ./folder
tar -xzvf ./folder name.tar.gz
tar -zxvf filename.tar.gz

jobs & ctrl+z fg bg kill %num

mkdir -p date/pipeline/test 循环创建目录
rm -r !(filename1 | filename2)：删除个别文件外的其他所有文件
ls -s 按大小排序 -t 按时间排序 -r 反向 -d 仅显示目录 -R 递归列出子目录

wc -l：统计行数 -m：统计字符数

ldd --version

grep name *
grep file\ name * 查找空格需要反斜杠转义

date +%s 查看时间戳

rm mv -i -r

`alt+.` 粘贴最后参数

### du

du：显示所有层级大小
du out.log: 显示文件大小
du dir：显示文件夹大小
du -s：显示总大小
-h
--max-depth=1：显示层级

### nohup

nohup /root/start.sh & ：不挂断地运行命令。

在shell中回车后提示：
[~]$ appending output to nohup.out
原程序的的标准输出被自动改向到当前目录下的nohup.out文件，起到了log的作用。

https://www.cnblogs.com/allenblogs/archive/2011/05/19/2051136.html

### 2>&1

command > file 2>&1 : 终端输出重定向到file, 将标准出错重定向到标准输出

### SSH本地上传和下载文件

下载：`scp <用户名>@<ssh服务器地址>:<文件路径> <本地文件名> `
上传：`scp <本地文件名> <用户名>@<ssh服务器地址>:<上传保存路径即文件名>`
文件夹加上参数：`-r`

## terminal 快速切换路径

一、目录栈指令

目录栈是用户最近访问过的系统目录列表，并以堆栈的形式管理。栈中的内容与Shell环境变量DIRSTACK的值对应

1、dirs

1）功能
显示当前目录栈中的所有记录（不带参数的dirs命令显示当前目录栈中的记录）

2）语法
（1）格式：dirs  [-clpv]  [+n]  [-n]
（2）选项
-c    删除目录栈中的所有记录
-l     以完整格式显示
-p    一个目录一行的方式显示
-v  **最常用**，每行一个目录来显示目录栈的内容，每个目录前加上的编号
+N  显示从左到右的第n个目录，数字从0开始
-N   显示从右到左的第n个日录，数字从0开始
注意：dirs始终显示当然目录, 再是堆栈中的内容；即使目录堆栈为空, dirs命令仍然只显示当然目录

2、pushd

1）功能
pushd命令常用于将目录加入到栈中，加入记录到目录栈顶部，并切换到该目录；若pushd命令不加任何参数，则会将位于记录栈最上面的2个目录对换位置

2）语法
（1）格式：pushd  [目录 | -N | +N]   [-n]
（2）选项
目录   将该目录加入到栈顶，并执行"cd 目录"，切换到该目录
+N   将第N个目录移至栈顶（从左边数起，数字从0开始）
-N    将第N个目录移至栈顶（从右边数起，数字从0开始）
-n    参数，将目录入栈时，不切换目录

3、popd

1）功能
popd用于删除目录栈中的记录；如果popd命令不加任何参数，则会先删除目录栈最上面的记录，然后切换到删除过后的目录栈中的最上面的目录

2）语法
（1）格式：pushd  [-N | +N]   [-n]
（2）选项
+N   将第N个目录删除（从左边数起，数字从0开始）
-N    将第N个目录删除（从右边数起，数字从0开始）
-n    参数，将目录出栈时，不切换目录

二.切换

`cd`
`cd -`:切到上一次目录

### terminal跳转

ctrl + w —往回删除一个单词，光标放在最末尾 
ctrl + k —往前删除到末尾，光标放在最前面（可以使用ctrl+a） 
ctrl + a 移动光标至的字符头 
ctrl + e 移动光标至的字符尾 
Ctrl + u 删除当前光标前面的文字
ctrl + l 清屏

屏幕滚动：shift+pageup/pagedown

### 前后台切换

1. command& 让进程在后台运行
2. jobs 查看后台运行的进程
3. fg %n 让后台运行的进程n到前台来
4. bg %n 让进程n到后台去，PS:"n"为jobs查看到的进程编号
5. ctrl + z 可以将一个正在前台执行的命令放到后台，并且暂停

### 进程操作状态

kill -stop pid：暂停后台进程
kill -cont pid：启动后台进程
kill -15 -0 pid：终止进程，先用15，不行用9

X     死掉的进程
<     高优先级
N     低优先级
L     有些页被锁进内存
s     包含子进程
`+`     位于后台的进程组；

### top/vmstat

### ssh

ssh -p 27611 root@176.122.153.179
ssh-keygen
ssh-copy-id -i id_rsa.pub root@176.122.153.179 公钥会添加到authorized_keys最后

ssh-keygen -b 4096 -t rsa -C root@192.168.237.201
命令执行完成之后，在当前目录会生成id_rsa和id_rsa.pub两个key文件。参数b指定key的长度，本例中指定的长度为4096。参数t指定加密算法，本例中使用的RSA加密算法。参数C可是邮件地址或域名等，会被添加到key的尾部，以示区分。

## Ubuntu bash

+ C-S-t 新建标签
+ C-S-w 关闭标签

## tmux多终端

[tmux详细教程](http://louiszhai.github.io/2017/09/30/tmux/)
<http://blog.kompaz.win/2017/03/08/Tmux%20%E9%85%8D%E7%BD%AE%E4%BD%BF%E7%94%A8/>
<https://blog.csdn.net/williamyuyuyu/article/details/79283374>
<https://blog.csdn.net/gatieme/article/details/49301037>
[customize status bar](https://hackernoon.com/customizing-tmux-b3d2a5050207)

滚屏： C-b [ 然后就可以使用鼠标或者箭头
兼容很多vim操作

### session

`tmux new -s demo`
`tmux detach`
`tmux a -t demo`
`tmux ls`
`tmux kill-session -t demo`
`tmux kill-server`

### 常用

更新配置文件，命令行模式执行：source-file .tmux.conf
滚屏： C-b [ 然后就可以使用鼠标或者箭头

帮助文档：`prefix-?`，可使用`/`查找
断开session：`prefix-d`
命令行模式：`prefix-:`
复制模式：`prefix-[`

窗口命令：c,&，p,n,w（列表）,f（查找）
面板命令：“,%，x,z(最大化),！(新窗口打开)

窗口变为面板：`join-pane -s demo:1.0`(session:window.pane)

列出信息缓存区：`prefix-~`
列出粘贴缓存区：`list-buffers`

### 复制模式

1. 输入 `+[ 进入复制模式
2. 按下 空格键 开始复制，移动光标选择复制区域
3. 按下 回车键 复制选中文本并退出复制模式
4. 按下 `+] 粘贴文本

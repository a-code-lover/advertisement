#### 查看端口占用

`netstat -a`：查看已连接服务端口，established
`netstat -ap`：查看所有服务端口，（listen，established）
`netstat -at`：查看所有tcp端口
`netstat -l`：查看所有服务状态
`netstat -ap | grep 1080`

#### lsof

lsof（list open files）是一个列出当前系统打开文件的工具。在linux环境下，任何事物都以文件的形式存在，通过文件不仅仅可以访问常规数据，还可以访问网络连接和硬件。所以如传输控制协议 (TCP) 和用户数据报协议 (UDP) 套接字等； 在查询网络端口时，经常会用到这个工具。

`lsof -i:8080`：查看使用该端口的进程PID
`ps -ef | grep pid`

#### 网络路由

`route -n`：查看路由状态（Dest，gateway, mask, iface, flags）
`ping ip`：发送ping包(ICMP协议)(包大小，ip,time,ttl)
`traceroute IP`:探测IP路由选择
`host domain`:查看域名对于ip
`host ip`:反向DNS查询
`ifconfig`：inet,mask,broadcast,inet6,mtu

#### ssh ID@host

参考：  
<https://linuxtools-rst.readthedocs.io/zh_CN/latest/index.html>
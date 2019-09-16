# 应用

## 内存空间

1.为类添加赋值运算符

![剑指offer:赋值运算符函数](../rsc/classAssignment.jpg)

2.c++和java通过socket传递结构体
> 注意c++的结构体会采用4字节对齐，所以发送时也要手动确保4字节对齐，否则解析会出错。
[int, float字节转换](https://blog.csdn.net/yao_shaobin/article/details/61914370)
[c++和c++使用相同的字节流格式](https://my.oschina.net/u/211101/blog/36720)
[c++和java使用相同的字节流格式](https://wenku.baidu.com/view/cff42c0edd88d0d233d46abc.html)

3.结构体转换为字节流涉及到大小端问题
> 常用的x86为小端模式，arm支持大小端模式，一般操作系统是小端模式，通信协议是大端模式。
[详解大端模式和小端模式](https://blog.csdn.net/ce123_zhouwei/article/details/6971544)
[为什么有大小端模式](http://www.ruanyifeng.com/blog/2016/11/byte-order.html)

## socket通信

[c++ socket编程实例](https://blog.csdn.net/u012391923/article/details/52881938)
[winsocket实例](https://www.cnblogs.com/churi/archive/2013/02/27/2935427.html)
[winsocket详细教程](https://lellansin.wordpress.com/tag/windows-%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B/)
[Windows官方接口](https://docs.microsoft.com/en-us/windows/desktop/api/winsock2/nf-winsock2-socket)
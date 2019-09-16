<!-- ---
title: "C++进程"
date: 2017-10-10T09:43:48+08:00
lastmod: 2019-03-01T15:43:48+08:00
draft: false
tags: [进程]
categories: [c++]
author: "Archillieus"
autoCollapseToc: true

# menu:
#  main:
#    parent: "docs"
#    weight: 1
#    #name: "hi"
#    #url: "https://gohugo.io"
--- -->

Reference:

+ [c++并发编程：好书]<https://www.kancloud.cn/jxm_zn/cpp_concurrency_in_action/264949>
+ [博客：c++并发指南系列]<https://www.cnblogs.com/haippy/p/3284540.html>
+ [thread基本例子](http://blog.gclxry.com/c-plus-plus-multi-thread/)

## 1.并发

c++标准库并未对进程间通信提供原生支持，所以实现多进程并发必须依赖与平台相关的API。
进程间通信的缺点：设置复制，速度慢，开销大，因为操作系统要提供进程间保护和进程管理，还有启动问题。
优点：安全，可以实现远程连接。

## 2.线程管理

### (1)启动

```c++
//普通函数
void do_some_work();
std::thread my_thread(do_some_work);
```

```c++
//函数对象
class background_task {
public:
  void operator() () {
    do_something;
    do_something_else;
  }
};

background_task f;
std::thread my_thread(f);
```

也可以使用lambda函数。

```c++
//分离还是等待线程结束
std::thread my_thread(do_something_inbackground);
my_thread.detach();
assert(!my_thread.joinable());
```

### (2)向线程函数传参

```c++
void f(int a, std::string const & s);
std::thread t(f, 10, "hallo");
```

```c++
class X {
public:
    void do_something(int & a) {

    };
}
X x;
int num(10);
//pass the reference of the object
std::thread t(&X::do_something, &x, num);
```

### (3)转移线程所有权

### (4)运行时决定线程数量

`std::thread::hardware_concurrence()`：返回可用硬件支持的并发线程数。这个数只是一个提示，可能不准确，若不支持该特性或不可计算，则返回0。

### (5)识别线程

`std::thread::id`  
`std::this_thread::get_id()`

```c++
std::thread::id master_thread;
void some_core_part_of_algorithm()
{
  if(std::this_thread::get_id()==master_thread)
  {
    do_master_thread_work();
  }
  do_common_work();
}
```

## 3.线程间共享数据

### (1)使用互斥量保护共享数据

>C++中通过实例化std::mutex创建互斥量，通过调用成员函数lock()进行上锁，unlock()进行解锁。不过，不推荐实践中直接去调用成员函数，因为调用成员函数就意味着，必须记住在每个函数出口都要去调用unlock()，也包括异常的情况。C++标准库为互斥量提供了一个**RAII**语法的模板类std::lock_guard，其会在构造的时候提供已锁的互斥量，并在析构的时候进行解锁，从而保证了一个已锁的互斥量总是会被正确的解锁。

```c++
std::list<int> some_list;
std::mutex some_mutex;
void add_to_list(int some_value) {
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(some_value);
}
```

问题：具有访问能力的指针和引用可以访问甚至修改被保护的数据，而且不受互斥锁的限制。因此，互斥量保护的数据需要对接口进行谨慎的设计，要确保互斥锁能够锁住任何保护的数据，而且不留后门。

### (2)谨慎设计代码保护共享数据

>只要没有成员函数通过返回值或者输出参数的形式向其调用者返回指向受保护数据的指针或引用，数据就是安全的。如果你还想往祖坟上刨，就没这么简单了。在确保成员函数不会传出指针或引用的同时，检查成员函数是否通过指针或引用的方式来调用也是很重要的(尤其是这个操作不在你的控制下时)。函数可能没在互斥量保护的区域内，存储着指针或者引用，这样就很危险。更危险的是：将保护数据作为一个运行时参数。

### (3)接口内在的条件竞争

细粒度锁，粗粒度锁

### (4)死锁

死锁，它的最大问题就是由两个或两个以上的互斥量来锁定一个操作。避免死锁的一般建议，就是让两个互斥量总以相同的顺序上锁：总在互斥量B之前锁住互斥量A，就永远不会死锁。某些情况下是可以这样用，因为不同的互斥量用于不同的地方，但可能有多个互斥量保护同一个类的独立实例。C++标准库有办法解决这个问题，std::lock——可以一次性锁住多个(两个以上)的互斥量，并且没有副作用(死锁风险)。

```c++
friend void swap(X& lhs, X& rhs)
  {
    if(&lhs==&rhs)
      return;
    std::lock(lhs.m,rhs.m); // 1
    std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock); // 2
    std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock); // 3
    swap(lhs.some_detail,rhs.some_detail);
  }
```

## 4.winsock

### (1)socket error

Error#10054: 个连接被对方重设。一个建立的连接被远程主机强行关闭，若远程主机上的进程异常终止运行（由于内存冲突或硬件故障），或者针对套接字执行了一次强行关闭，便会产生10054错误。针对强行关闭的情况，可用SO_LINGER套接字选项和setsockopt来配置一个套接字。

## 5.实践

### lock_guard, unique_lock, shared_lock, scoped_lock

```c++
int g_i = 0;
std::mutex g_i_mutex;  // 保护 g_i

void safe_increment()
{
  std::lock_guard<std::mutex> lock(g_i_mutex);
  ++g_i;
  std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
  // g_i_mutex 在锁离开作用域时自动释放
}
 
int main()
{
  std::cout << "main: " << g_i << '\n';
  std::thread t1(safe_increment);
  std::thread t2(safe_increment);
  t1.join();
  t2.join();
  std::cout << "main: " << g_i << '\n';
}
```

### thread join()

主线成生成并启动子线程，为了避免父线程在子线程结束之前退出（造成孤儿线程），对子线程执行`join()`方法，让父线程等待子线程结束后在终止。即让父线程等待子线程的终止。

### 循环打印id

```c++
std::mutex mymutex;
static int flag = 0;
std::condition_variable cv;
const static int threadNum = 3;
const static int num = 5;

void print(int idx) {
  for (int i = 0; i < num; i++) {
    std::unique_lock<mutex> ulm(mymutex);
    cv.wait(ulm, [&](){return (flag == idx);});
    cout << std::this_thread::get_id() << endl;
    flag = (flag+1)%threadNum;
    // 通知前，手动解锁以防正在等待的线程被唤醒后又立即被阻塞。
    ulm.unlock();
    cv.notify_all();
  }
}

int main()
{
  std::vector<thread> threads;
  for (int i = 0; i < threadNum; i++) {
      threads.push_back(std::thread(print, i));
  }
  std::for_each(threads.begin(), threads.end(), std::mem_fn(
      &std::thread::join));
  // 通知前，手动解锁以防正在等待的线程被唤醒后又立即被阻塞。
  return 0;
}
```
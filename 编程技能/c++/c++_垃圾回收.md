# 垃圾回收

## jvm垃圾回收

### 对象判活

1. 引用计数（弃用）
2. 可达性分析：商用
3. 两次标记与finalize()
4. 回收方法区

### 回收算法

1. 标记清除（mark-sweeping）
2. 复制算法(copy)
3. 标记清理（mark-compacting）
4. 分代清理（generational collection）:商用

## c++为什么不加入垃圾回收机制

“统一的自动垃圾回收系统无法适用于各种不同的应用环境，而又不至于导致实现上的负担。不同的应用环境，也许需要不同的垃圾回收器。即使可以成功，也会导致效率成本的增加。” 摘自<https://blog.csdn.net/yeahhook/article/details/6796242>

参考：
[深入Java虚拟机之GC](https://crowhawk.github.io/2017/08/10/jvm_2/)
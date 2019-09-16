# 关于ziplist

## 概论

ziplist是一个特殊编码的表，占一块连续的地址空间，采用变长编码，设计的目标是为了提高存储效率。ziplist用于存储字符串和整数，其中整数是按真正的二进制表示，而不是编码为字符串序列。它能以o(1)时间复杂度在表的两端提供push和pop操作。

`<zlbytes><zltail><zllen><entry>...<entry><zlend>`，采用小端存储。
`entry`的数据想：`<prevrawlen><len><data>`，设置`prevrawlen`是为了从后往前遍历。

## 缺点

为当ziplist变得很大的时候，它有如下几个缺点：

+ 每次插入或修改引发的realloc操作会有更大的概率造成内存拷贝，从而降低性能。
+ 一旦发生内存拷贝，内存拷贝的成本也相应增加，因为要拷贝更大的一块数据。
+ 当ziplist数据项过多的时候，在它上面查找指定的数据项就会性能变得很低，因为ziplist上的查找需要进行遍历。

ziplist并不擅长修改操作。

## hash与ziplist

hash随着数据的增大，其底层数据结构的实现是会发生变化的，当然存储效率也就不同。在field比较少，各个value值也比较小的时候，hash采用ziplist来实现；而随着field增多和value值增大，hash可能会变成dict来实现。当hash底层变成dict来实现的时候，它的存储效率就没法跟那些序列化方式相比了。

参考：  
<http://zhangtielei.com/posts/blog-redis-ziplist.html>
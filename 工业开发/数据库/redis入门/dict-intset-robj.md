# 基本结构

## dict

### 概述

dict本质上是为了解决算法的查找问题，基于哈希表的查找性能接近O(1)。  
在Redis中，dict是一个基于哈希表的算法，和传统哈希算法类似，采用拉链法解决冲突，在装载因子超过预定值时自动扩充内存，引起重哈希。  

### 重哈希

Redis的dict采用增量重哈希的方法，在需要扩充内存时，避免一次将所有的key进行重哈希，而是将重哈希操作分散到dict的各个增删查找中，这样可以避免重哈希期间单个请求的响应时间剧烈增加，与`快速响应时间`的设计原则一致。

为了实现增量式冲哈希，dict中包含**两个**哈希表`ht[0]`和`ht[1]`，当`rehashidx`等于-1时，表示当前没有重哈希，否则正在冲哈希；该字段记录冲哈希的步数。在重哈希时，先重`ht[0]`开始查找，若没找到再在`ht[1]`查找。每次增删查找操作都会将重哈希向前推进n步。插入时，进行重哈希则插入`ht[1]`，否则插入`ht[0]`。

重哈希结束后，交换`ht[0]`和`ht[1]`，并将`ht[1]`置空。

## sds

`<len><alloc><flags><char buf[]>`，sds定义五种头部结构，为了能是不同长度的字符串使用不同大小的header。

## robj

Redis数据库都是key-val映射，key应该是一个string，value可以是任意支持的类型如list,hash,string等。为了存储不同类型的value，设计了通用数据结构`robj`。

> robj所表示的就是Redis对外暴露的第一层面的数据结构：string, list, hash, set, sorted set，而每一种数据结构的底层实现所对应的是哪个（或哪些）第二层面的数据结构（dict, sds, ziplist, quicklist, skiplist, 等），则通过不同的encoding来区分。可以说，robj是联结两个层面的数据结构的桥梁。

### sds与string

+ 确切地说，string在Redis中是用一个robj来表示的。
+ 用来表示string的robj可能编码成3种内部表示：OBJ_ENCODING_RAW, OBJ_ENCODING_EMBSTR, OBJ_ENCODING_INT。其中前两种编码使用的是sds来存储，最后一种OBJ_ENCODING_INT编码直接把string存成了long型。
+ 在对string进行incr, decr等操作的时候，如果它内部是OBJ_ENCODING_INT编码，那么可以直接进行加减操作；如果它内部是OBJ_ENCODING_RAW或OBJ_ENCODING_EMBSTR编码，那么Redis会先试图把sds存储的字符串转成long型，如果能转成功，再进行加减操作。

## intset

### intset概述

intset顾名思义，是由整数组成的集合。实际上，intset是一个由整数组成的有序集合，从而便于在上面进行二分查找，用于快速地判断一个元素是否属于这个集合。它在内存分配上与ziplist有些类似，是连续的一整块内存空间，而且对于大整数和小整数（按绝对值）采取了不同的编码，尽量对内存的使用进行了优化。

`<encoding><length><contents[]>`

### intset与ziplist相比：

+ ziplist可以存储任意二进制串，而intset只能存储整数。
+ ziplist是无序的，而intset是从小到大有序的。因此，在ziplist上查找只能遍历，而在intset上可以进行二分查找，性能更高。
+ ziplist可以对每个数据项进行不同的变长编码（每个数据项前面都有数据长度字段len），而intset只能整体使用一个统一的编码（encoding）。

### 并，交，差算法
## TCP重传机制

+ 如何估算往返时间？只有在正确估算往返时间的前提下，才能知道一个TCP包多久没收到响应算超时？
+ 在已知往返时间的情况下，怎么确定重传时间和重传算法？

### 重传时间间隔

1. 报文段的样本RTT（sampleRTT）就是从某报文段被发出（即交给IP）到对该报文段的确认（ACK）被收到之间的时间。由于路由器的拥塞和系统负载的变化，估计的往返时间不会直接采用RTT值，而是采用：  
`EstimateRTT（新） = (1 - α) * EstimateRTT(旧) + α * SampleRTT，参考α=0.125`

2. 估算RTT的偏差，即sampleRTT偏离EstimateRTT的程度
`DevRTT = (1 - β) * DevRTT + β * | SampleRTT - EstimateRTT（旧？新？）| 参考β=0.25`

3. 重传时间间隔
`TimeoutInterval = EstimateRTT + 4 * DevRTT`

### 重传定时器

```c++
NextSeqNum = InitialSeqNumber
SendBase = InitialSeqNumber
循环：
  如果是收到了上层应用程序发出的数据：
    使用NextSeqNum创建新的TCP报文
    如果当前TCP重传定时器没有在运行：
      启动TCP重传定时器
    将TCP报文交给IP层
    NextSeqNum = NextSeqNum + length(data)
  如果TCP重传定时器超时：
    重传所有还没有被确认(ACK)的报文中seq最小的那个TCP报文
    启动TCP重传定时器
  如果收到了ACK报文，其中ACK值=y：
    如果 y > SendBase：
      SendBase = y
      如果当前还有没有被ACK的TCP报文：
        启动TCP重传定时器
```

### 超时时间加倍

> 每当TCP超时定时器被触发，意味着有TCP报文在指定时间内没有收到ACK，此时TCP会重传最小序号的没有ACK的报文。每次TCP重传时都会将下一次超时时间设置为先前值的两倍，而不是使用当前计算得到的EstimateRTT值。

### 快速重传?

> 超时触发重传存在的问题之一是超时周期可能相对较长。当一个报文段丢失时，这种长超时周期迫使发送方延迟重传丢失的分组，因而增加了端到端的时延。发送方通常可在超时事件发生之前通过注意所谓冗余ACK来检测丢包情况。  
>
> 如果TCP发送方收到相同数据的3个冗余ACK，将以这个做为一个提示，说明跟在这个已被确认过3次的报文段之后的报文已经丢失。一旦收到3个冗余ACK，TCP就执行快速重传（fast retransmit），即在该报文段的定时器过期之前重传丢失的报文段。

转自：
<https://www.codedump.info/post/20190227-tcp/>
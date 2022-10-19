redis的数据结构以及持久化操作

mysql mvcc undolog redo log

stl及其数据结构

发生了长尾请求，长尾延迟：

在进线程的基础上引入协程

假设这里thread1里面的coroutine都被消费完了，那么它可以去窃取thread2里面的coroutine进行执行，避免单个coroutine一直霸占着当前的thread，而造成长尾延迟

采用eventloop以及tcpserver，acceptor等类对象，对底层系统调用进行封装，屏蔽底层通信的复杂性

rpc和http的区别

为什么在分布式的集群里面用rpc而不是http（http是json，而rpc可以用更加简小的二进制协议）

并且rpc会附加更多的功能：超时重试，负载均衡

实际上：性能上的差异，rpc其实是一种思想，它的实现多样，既可以是socket（thift），也可以是http

dynamic_cast，基类转派生类
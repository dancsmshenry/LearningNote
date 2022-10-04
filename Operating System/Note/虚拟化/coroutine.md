# 协程和线程的切换比较

- https://www.zhihu.com/question/308641794/answer/572499202
- https://studygolang.com/articles/11014?fr=sidebar
- https://zhuanlan.zhihu.com/p/474353906
- 说白了就两点
  - 协程的切换是在内核态进行的，而线程的切换，要先切换特权级，然后到内核态进行切换
  - 协程切换所需的数据要少于线程
- 我的一个问题是为什么进入内核态的消耗会很大
  - 感觉int 0x80的陷入系统调用确实很慢，增大了消耗，但是现在用的sysenter陷入系统调用速度高很多了，感觉主要消耗不在态的切换了
  - 用户态到内核态，要刷新tlb，更换pagetable



对epoll和coroutine的理解

- epoll需要在kernel thread上阻塞2s，但是有可能阻塞到一半的时候（1s），就有很多fd可以读读写了，但是，epoll必须阻塞2s以后才能干活
- 而且，epoll会有很多的回调调用（fd有事件触发就是通过回调实现的）
- 而coroutine有自己的schedule，当前coroutine没事就切到下一个有事的coroutine干活，能够让当前线程几乎一直处于干活的状态



对于hook的理解

- 
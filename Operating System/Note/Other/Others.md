# 屏幕输出hello的执行流程



# posix



# volatile



# ELF文件



# 写屏障



# CPU嗅探机制

- https://zhuanlan.zhihu.com/p/115114220



# 思维上的转变

- 在算法竞赛中，要解决的难点其实是wrost case
- 而在os中，要解决的是average（frequent） case，让快的更快，慢的不那么慢



# vdso

- 不进入内核实现系统调用



# NUMA



# simd



# __thread

- ```cpp
  #include <iostream>
  #include <pthread.h>
  #include <unistd.h>
  #include <cstdio>
  
  __thread int i = 0;
  
  void* f1(void *arg)
  {
      i++;
      printf("f1 i address %p val %d\n", &i, i);
      return nullptr;
  }
  
  void* f2(void *arg)
  {
      i += 2;
      printf("f2 i address %p val %d\n", &i, i);
      return nullptr;
  }
  
  int main()
  {
      pthread_t pid1, pid2;
      i += 3;
      pthread_create(&pid1, NULL, f1, NULL);
      pthread_create(&pid2, NULL, f2, NULL);
      pthread_join(pid1, NULL);
      pthread_join(pid2, NULL);
      printf("main i address %p val %d\n", &i, i);
  
      return 0;
  }
  ```

- 编译问题：https://www.baidu.com/s?ie=UTF-8&wd=in%20function%20%60__static_initialization_and_destruction_0(int,%20int)%27%3A

- 编译指令：g++ test.cpp -o test -lpthread

- __ thread是GCC内置的线程局部存储设施。__ thread变量每一个线程有一份独立实体，各个线程的值互不干扰。可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量



注意事项：

- __thread是GCC内置的线程局部存储设施
- 只能修饰POD类型(类似整型指针的标量，不带自定义的构造、拷贝、赋值、析构的类型，二进制内容可以任意复制memset,memcpy,且内容可以复原).
- 不能修饰class类型，因为无法自动调用构造函数和析构函数.
- 可以用于修饰全局变量，函数内的静态变量，不能修饰函数的局部变量或者class的普通成员变量，且__thread变量值只能初始化为编译器常量
- cpp11引入了thread_local，线程存储期







# 对gc的理解

- 由于在 netpoll 中，SubReactor 本身也是一个 goroutine，受调度影响，不能保证 EpollWait 回调之后马上执行，所以这一块会有延迟；
  - 即epoll_wait返回后，可能因为gc或者说调度，不能够立马执行，导致了延迟
  - 这里说明了gc其实是有不好的地方的，要做优化，只能修改go runtime的源码，在其中注册一个回调函数，每次调度epollwait的受，把获取到的fd传递给回调执行



- 在网络库中，如果reactor的都是goroutine的话，实际上很难保证在多核情况之下，这些 Reactor 能并行执行；甚至在最极端情况之下，可能这些 Reactor 会挂在同一个 P 下，最终变成了串行执行，无法充分利用多核优势
  - 因为协程都是用户在调度，不能走多核



- epollwait回调后，是串行执行文件，可能出现长尾问题
- https://www.cloudwego.io/zh/blog/2021/10/09/%E5%AD%97%E8%8A%82%E8%B7%B3%E5%8A%A8%E5%9C%A8-go-%E7%BD%91%E7%BB%9C%E5%BA%93%E4%B8%8A%E7%9A%84%E5%AE%9E%E8%B7%B5/#server---%E4%B8%BB%E4%BB%8E-reactor-%E5%AE%9E%E7%8E%B0







# 进程cpu与内存占用都很低,但是压测qps一直上不去,怎么排查

- 代码问题：随机读的情况太多，磁盘负载太高
- 压测工具的问题：工具不行
- 网络掉包严重：rpc调用下游服务，掉包严重导致重传，导致qps上不去







# linux的一些小知识

## 实时系统

- 硬实时：给定的操作一定要在确定的时间内完成，重点并不在于操作一定要处理得多快，而是时间要可控（在最坏情况下也不能突破给定的时间）
- 而linux其实是软实时，只能说尽可能的满足进程的实时需求
  - 中断处理、虚拟内存、等机制的存在给处理时间带来了很大的不确定性。硬件的cache、磁盘寻道、总线争用、也会带来不确定性



## 几种linux的发行版本

- ubuntu，deepin，debian，centos，freebsd



## 抢占

- **linux 2.4**的设计就非常简单，**内核不支持抢占**。进程运行在内核态时（比如正在执行系统调用、正处于异常处理函数中）
  - 是不允许抢占的必须等到返回用户态时才会触发调度（确切的说，是在返回用户态之前，内核会专门检查一下是否需要调度）
  - 从效率上思考的：如果可抢占，那么当前拿到spin_lock的进程被没有spin_lock的进程抢占，导致可能很长一段时间都拿不到锁
  - 所以，一些实时性要求高的OS，不能容忍spin_lock，宁可改用更费劲的“睡眠-唤醒”过程，也不能因为禁用抢占而让更高优先级的进程等待
- linux 2.6则实现了内核抢占，但是在很多地方还是为了保护临界区资源而需要临时性的禁用内核抢占
# 屏幕输出hello的执行流程



# fpga



# dpdk



# posix



# Volatile



# ELF文件



# 写屏障



# CPU嗅探机制

- https://zhuanlan.zhihu.com/p/115114220



# 进程间通信的方式

- 管道，socket，共享内存，消息队列，信号





# 思维上的转变

- 在算法竞赛中，要解决的难点其实是wrost case
- 而在os中，要解决的是average（frequent） case，让快的更快，慢的不那么慢



主流计算机为小端



# vdso

- 不进入内核实现系统调用



# include 预编译



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

- 编译问题：

  - ```cpp
    https://www.baidu.com/s?ie=UTF-8&wd=in%20function%20%60__static_initialization_and_destruction_0(int,%20int)%27%3A
    ```

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
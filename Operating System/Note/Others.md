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



# 进程间同步的方式

- 锁，信号量，条件变量，管程



# 互斥



# 思维上的转变

- 在算法竞赛中，要解决的难点其实是wrost case
- 而在os中，要解决的是average（frequent） case，让快的更快，慢的不那么慢



主流计算机为小端



# vdso

- 不进入内核实现系统调用



# include 预编译



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
# 并发编程的两种模型

- message passing
- shared memory



# 线程同步的四项原则

- 首要原则是尽量最低限度地共享对象，减少需要同步的场合
  - 一个对象能不暴露给别的线程就不要暴露
  - 优先考虑immutable对象
  - 实在不行才暴露可修改的对象，并用同步措施来充分保护它
- 使用高级的并发编程构件：TaskQueue，Producer-Consumer Queue，CountDownLatch等
- 最后不得已必须使用底层同步原语时，只用非递归的互斥器和条件变量，慎用读写锁，不要用信号量
- 除了使用atomic整数之外，不自己编写lock-free代码，也不要用内核级同步原语，不凭空猜测"哪种做法性能会更好"
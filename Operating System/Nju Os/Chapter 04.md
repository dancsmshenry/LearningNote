- 为什么我们认为写的代码不能实现互斥

- ```cpp
  int locked = UNLOCK;
  
  void test() {
  retry:
      if (locked != UNLOCK) {
          goto retry;
      }
      locked = LOCK;
       // critial section
      locked = UNLOCK;
  }
  ```

- 因为对于locked的判断，首先是从内存中或者寄存器中取出locked，而如果两个线程同时取出locked的时候都是UNLOCK，那么就会出现失误

- 究其原因，还是因为判断和修改locked的过程是有多个状态，而线程的切换是由cpu决定的，切换有可能出现在每一个状态当中，就导致了互斥失败

- 准确来说，就是因为不能同时读写，即读和写一定要分步骤，基于这种事实才导致互斥是一件那么难得事情

- 所以，就需要原子指令硬件等来保证互斥吗

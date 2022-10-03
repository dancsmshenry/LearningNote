# 内核收包路径

- 包从硬件网卡（NIC) 上进来之后，会触发一个**中断**，告诉 cpu 网卡上有包过来了，需要处理，同时通过 DMA（direct memory access) 的方式把包存放到内存的某个地方，这块内存通常称为 ring buffer，是网卡驱动程序初始化时候分配的



- 当 cpu 收到这个中断后，会调用中断处理程序，这里的中断处理程序就是网卡驱动程序，因为网络硬件设备网卡需要驱动才能工作。网卡驱动会先关闭网卡上的中断请求，表示已经知晓网卡上有包进来的事情，同时也避免在处理过程中网卡再次触发中断，干扰或者降低处理性能。驱动程序启动软中断，继续处理数据包



- 然后 CPU 激活 NAPI 子系统，由 NAPI 子系统来处理由网卡放到内存的数据包。经过一些列内核代码，最终数据包来到内核协议栈。内核协议栈也就是 IP 层以及传输层。经过 IP 层之后，数据包到达传输层，内核根据数据包里面的 `{src_ip:src_port, dst_ip:dst_port}` 找到相应的 socket



- 然后把数据包放到这个 socket 的接收队列（接收缓冲区）中，准备通知应用程序，socket 就绪





# 从socket到应用程序

- 那么当 socket 就绪后，也就是数据包被放到 socket 的接收缓冲区后，如何通知应用程序呢？这里用到的是**等待队列**，也就是 **wait queue**

- ```cpp
  /**
   *  struct socket - general BSD socket
   *  @state: socket state (%SS_CONNECTED, etc)
   *  @type: socket type (%SOCK_STREAM, etc)
   *  @flags: socket flags (%SOCK_NOSPACE, etc)
   *  @ops: protocol specific socket operations
   *  @file: File back pointer for gc
   *  @sk: internal networking protocol agnostic socket representation
   *  @wq: wait queue for several uses
   */
  struct socket
  {
      socket_state state;
  
      short type;
  
      unsigned long flags;
  
      struct file *file; // 一个指向文件的指针
      struct sock *sk;
      const struct proto_ops *ops;
  
      struct socket_wq wq;
  };
  
  struct socket_wq
  {
      /* Note: wait MUST be first field of socket_wq */
      wait_queue_head_t wait;  // 等待队列
      struct fasync_struct *fasync_list; // 异步等待队列
      unsigned long flags; /* %SOCKWQ_ASYNC_NOSPACE, etc */
      struct rcu_head rcu;
  } ____cacheline_aligned_in_smp;
  ```

- **等待队列和异步等待队列中存放的是关注这个 socket 上的事件的进程**。区别是等待队列中的进程会处于阻塞状态，处于异步等待队列中的进程不会阻塞

- 当 socket 就绪后（接收缓冲区有数据），那么就会 wake up 等待队列中的进程，通知进程 socket 上有事件，可以开始处理了





# 总结一下收包以及触发的过程

- 包从网卡进来 
- 一路经过各个子系统到达内核协议栈（传输层） 
- 内核根据包的 {src_ip:src_port, dst_ip:dst_port} 找到 socket 对象（内核维护了一份四元组和 socket 对象的一一映射表） 
- 数据包被放到 socket 对象的接收缓冲区 
- 内核唤醒 socket 对象上的等待队列中的进程，通知 socket 事件 
- 进程唤醒，处理 socket 事件（read/write)





# IO多路复用的思考

- IO多路复用的本质还是阻塞，因为当有事件触发的时候线程会被阻塞在上下文，真正的非阻塞io只有异步io


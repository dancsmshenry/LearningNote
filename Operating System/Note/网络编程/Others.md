# linux下是如何接收数据的

版本一：数据包从网卡到内核协议栈，再到socket的接收缓冲区的步骤

- 当一个包从网卡进来之后，会触发一个中断，告诉CPU网卡上有包过来了，需要处理，同时通过DMA的方式把包存放到内存的某个地方，这个内存通常叫做ring buffer，是网卡驱动程序初始化的时候分配的
  - 中断：处理器接收到来自硬件或者软件的信号，提示产生了某件事情，需要处理
  
- 当CPU收到这个中断之后，会调用中断处理程序，这里的中断处理程序就是网卡驱动程序。

- 网卡驱动会关闭网卡上的中断请求，表示已经知晓网卡上有包进来的事情，同时也避免在处理过程中网卡再次触发中断，干扰或者降低处理性能

- 驱动程序启动软中断，继续处理数据包

- 然后CPU激活NAPI子系统，由NAPI子系统来处理由网卡放到内存的数据包

- 经过一系列内核代码，最终数据包来到内核协议栈

- 内核协议栈也就是IP层以及传输层，经过IP层之后，数据包到达传输层，内核根据数据包找到对应的socket

- 然后把数据包放到这个socket的接收队列中（接收缓冲区）中，准备通知应用程序，socket就绪

- 当socket就绪后，也就是数据包放到socket的接收缓冲区后的操作

  - ```c
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
    struct socket {
    	socket_state		state;
    
    	short			type;
    
    	unsigned long		flags;
    
    	struct file		*file;
    	struct sock		*sk;
    	const struct proto_ops	*ops;
    
    	struct socket_wq	wq;
    };
    
    
    struct socket_wq {
    	/* Note: wait MUST be first field of socket_wq */
    	wait_queue_head_t	wait;
    	struct fasync_struct	*fasync_list;
    	unsigned long		flags; /* %SOCKWQ_ASYNC_NOSPACE, etc */
    	struct rcu_head		rcu;
    } ____cacheline_aligned_in_smp;
    ```

  - 上述是socket的组成部分

  - 补充：一个socket实例中由一个file的指针，以及一个socket_wq变量，其中socket_wq中的wait表示等待队列，fasync_list表示异步等待队列

  - 等待队列和异步等待队列存放的都是socket上的事件进程

- 当socket就绪后（接收缓冲区有数据），那么就会wake up等待队列中的进程，通知进程socket上有事件可以处理

- 网卡有数据到来的时候，网卡会产生一个硬中断，把数据copy给内核，同时执行软中断调用刚才的回调函数，该函数会把epoll_litem加入到链表中，所以每次返回的时候，就知道哪些是就绪事件



- 版本二：
  - 1、计算机收到了对端传送的数据
  - 2、数据经由网卡传送到内存
  - 3、然后网卡通过中断信号通知cpu有数据到达，cpu执行中断程序
  - 4、此处的中断程序主要有两项功能，先将网络数据写入到对应socket的接收缓冲区里面，再唤醒进程A（因为没事的时候进程是阻塞的，要把它唤醒，阻塞：不会往下执行代码，也不会占用cpu资源）（那cpu是如何找到这个socket的呢，是通过端口）
  - 5、重新将进程A放入工作队列中
  - 网卡收到网线传过来的数据，经过硬件电路的传输，最终把数据写入到内存中的某个地址上
  - 当网卡把数据写入到内存后，网卡向cpu发出一个cpu中断信号，操作系统便知道有数据到来了
- 缺点：
  - 如果有10k个socket事件，那我难道要创建10k个线程去阻塞监听是否有事件吗？那我的内存全部都用去存线程的pcb算了；为此改变设计模式，让一个线程监听所有的socket，有事情就返回发生变动的socket，然后再分配线程给他，而这个起监听作用的函数就是io多路复用；即改变设计思路，原来是每个事件都搭配一个线程，现在是你有事件来我才分配线程给你work，否则的话平时就是监听
  - 人为的去判断，就是在用户代码中自旋实现所有阻塞socket的监听，但是每次判断socket是否产生数据，都涉及到用户态到内核态的切换，如果有很多个socket的话，就会非常的浪费系统资源







# 对于数据收发的理解

- 其实，在传输层中数据的传输并不代表服务端真的把全部的数据都传送了过来（可能有一部分还在服务端的发送缓冲区中没有传过来）
- 所以要判断信息有没有真的全部传送过来，通常有两种做法，一是指定数据长度，比如 HTTP Header 中的 Content-Length 字段。二是分隔符，比如："\r\n"，在 HTTP 中也有应用
- 所以，数据有没有收完，其实是应用层决定的，tcp只是管理数据的传输（分层的魅力）
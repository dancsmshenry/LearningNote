# PS

- IO多路复用本质上还是阻塞的，进程或线程还是会阻塞在调用select/poll/epoll函数上，真正的非阻塞还得是异步io（也就是proctor），或者是把epoll等函数包装成reactor
- select，poll需要每次把感兴趣的事件全量传入select或者poll方法中，内核每次都需要复制解析一边，浪费系统资源，而epoll维护了一个全局的rbt，不需要每次全量解析



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





# Select

### 其他

- 每次调用select都需要将进程加入到所有监视socket的等待队列，每次唤醒都需要从每个队列中移除
- 针对监听socket数据的问题：select是将所有需要监听的socket集合复制到内核态，系统帮我们监听是否有事件
- 针对线程使用自旋来时刻判断是否有数据：select是当线程没有事件的时候就阻塞，有事件的话就线程
- 事件集合：用户通过3个参数分别传入感兴趣的可读、可写及异常等事件，内核通过对这些参数的在线修改来反馈其中的就绪事件



### select的使用过程

- 使用copy_from_user从用户空间拷贝fd_set到内核空间
- 注册回调函数__pollwait
- 3、遍历所有fd，调用其对应的poll方法
  - 对于socket，这个poll方法是sock_poll，sock_poll根据情况会调用到tcp_poll,udp_poll或者datagram_poll
- 4、以tcp_poll为例，其核心实现就是__pollwait，也就是上面注册的回调函数
- 5、__pollwait的主要工作就是把current（当前进程）挂到设备的等待队列中，不同的设备有不同的等待队列。对于tcp_poll来说，其等待队列是sk->sk_sleep（注意把进程挂到等待队列中并不代表进程已经睡眠了）。在设备收到一条消息（网络设备）或填写完文件数据（磁盘设备）后，会唤醒设备等待队列上睡眠的进程，这时current便被唤醒了
- 6、poll方法返回时会返回一个描述读写操作是否就绪的mask掩码，根据这个mask掩码给fd_set赋值
- 7、如果遍历完所有的fd，还没有返回一个可读写的mask掩码，则会调用schedule_timeout是调用select的进程（也就是current）进入睡眠。当设备驱动发生自身资源可读写后，会唤醒其等待队列上睡眠的进程。如果超过一定的超时时间（schedule_timeout指定），还是没人唤醒，则调用select的进程会重新被唤醒获得CPU，进而重新遍历fd，判断有没有就绪的fd
- 8、把fd_set从内核空间拷贝到用户空间





### 缺点

- 单个进程可监视的fd数量被限制，即能监听端口的大小有限
- 对socket进行扫描是线性扫描，效率低下
  - 每次调用select，都需要把fd集合从用户态拷贝到内核态；同时每次调用select都需要在内核遍历传递进来的所有fd，开销很大
- 需要维护一个用来存放大量fd的数据结构
- 而且到用户态之后，还要再遍历一遍数组，找到有数据的fd来处理，时间复杂度on
- 为什么最大fd数量是1024：linux默认进程最多可以打开1024个文件







# Poll

- 和select一样，不过最大文件描述符数量比select大







# 为什么IO多路复用必须使用非阻塞IO

原因一：

- https://www.zhihu.com/question/37271342/answer/81808421
- 数据就算不被别人读走，也可能被内核丢弃
- 在Linux上，select（）可能会将套接字文件描述符报告为“ready for reading”，而随后的读取会阻塞。例如，当数据已到达但检查时校验和错误并被丢弃时，可能会发生这种情况。在其他情况下，文件描述符可能会被错误地报告为就绪。因此，在不应该阻塞的套接字上使用非阻塞可能更安全。



原因二：

- IO多路复用只会告诉你socket可读，但是不会告诉你有多少数据可读
- 所以server端只能一直读socket，一旦后续没有数据的话，就会阻塞在read上面（而非阻塞的read的话，没有数据就会返回错误，而不是阻塞）
- 所以，如果是io多路复用+阻塞io，coding的时候，每次读只能由loop告诉你有没有数据（而不是有多少数据），然后只能接着读一次（不一定能读完所有的数据），在是实现会非常的麻烦
- 接上，因此阻塞socket使用就必须read/write一次后就转到epoll_wait上，这对于网络流量较大的应用效率是相当低的



原因三：

- io多路复用只能告诉你能读，但不会说能读多少（和原因二很像）



原因四：

- 惊群效应：
  - 就是一个典型场景，多个进程或者线程通过 select 或者 epoll 监听一个 listen socket，当有一个新连接完成三次握手之后，所有进程都会通过 select 或者 epoll 被唤醒，但是最终只有一个进程或者线程 accept 到这个新连接，若是采用了阻塞 I/O，没有accept 到连接的进程或者线程就 block 住了



参考：

- epoll的ET模式必须使用非阻塞io
- ET模式指的是当数据从无到有时，才通知该fd。数据读不完，也不会再次通知，所以read时一定要采用循环的方式一直读到read函数返回-1为止。此时采用阻塞的read，那么就阻塞了整个线程。



summary

- 调用io多路复用只能是可能知道有数据可读，但是不知道有多少数据可读（即可能会循环多次的调用read，所以不能用阻塞io），也不知道当read真正去读的时候是否真的有数据（参考原因一，可能数据校验和不对，直接被loss了）
- 如果是非阻塞socket，read()不到的话会返回一个EAGAIN是嘛，然后就退出read循环了？然后就等下一次epoll



对于数据收发的理解

- 其实，在传输层中数据的传输并不代表服务端真的把全部的数据都传送了过来（可能有一部分还在服务端的发送缓冲区中没有传过来）
- 所以要判断信息有没有真的全部传送过来，通常有两种做法，一是指定数据长度，比如 HTTP Header 中的 Content-Length 字段。二是分隔符，比如："\r\n"，在 HTTP 中也有应用
- 所以，数据有没有收完，其实是应用层决定的，tcp只是管理数据的传输（分层的魅力）



# 参考

- https://rebootcat.com/2020/09/26/epoll_cookbook/
- https://www.cnblogs.com/charlesblc/p/6242479.html
- https://blog.csdn.net/wteruiycbqqvwt/article/details/90299610
- https://zhuanlan.zhihu.com/p/392988660
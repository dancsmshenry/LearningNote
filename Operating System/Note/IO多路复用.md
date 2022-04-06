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







# Epoll

### epoll的数据结构

#### 红黑树

- 程序在内核空间开辟一块缓存，用来管理 epoll 红黑树，高效添加和删除
- 红黑树位于内核空间，用来直接管理 socket，减少和用户态的交互

- 为什么支持百万句柄

  - 不用重复传递，调用epoll_wait时相当于以往调用
- 为什么用红黑树

  - 早期使用hashmap效率高，但是内存空间占用大，就改为了红黑树
  - 同时kernel中有现有的rbtree，而没有通用的hashtable
  - 方便事件的查询和删除，还有插入（背景：有些事件一开始是要监听的，就要插入，如果有重复的话，插入的时候就要注意；但是后续又不用了，就要实现删除）
  - 正是因为高效的查找和删除，导致能够突破文件描述符数量的限制，支持百万句柄





#### 双向链表

- 使用双向链表缓存就绪的socket，数量较少
- 只需要拷贝这个双向链表到用户空间，在遍历即可，注意这里也需要拷贝，没有共享内存









### epoll的使用流程

- ```cpp
  #include <sys/epoll.h>
  
  //# open an epoll file descriptor
  //# epoll_create1 可以理解为 epoll_create 的增强版（主要支持了 close-on-exec）
  int epoll_create(int size);
  int epoll_create1(int flags);
  
  //# 往 epoll instance 上添加、删除、更改一个节点（socket)
  int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
  
  //# wait for events on epoll instance
  int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
  
  //# close and clear epoll instance
  int close(int fd);
  ```



#### epoll_create

- 实际上是创建了一个eventpoll实例，其中包含了一个红黑树和一个双向链表

- ```cpp
  struct eventpoll {
      struct rb_root rbr;//红黑树的根节点，这棵树中存储所有添加到epoll中的需要监控的事件
      struct list_head rdlist;//双向链表中存放着将要通过epoll_wait返回给用户的满足条件的事件
  };
  ```

- eventpoll是直接位于内核空间的

- 红黑树的叶子节点都是epitem结构体

- ```cpp
  struct epitem {
     ...
     
  	union {
  		/* RB tree node links this structure to the eventpoll RB tree */
  		struct rb_node rbn;
  		/* Used to free the struct epitem */
  		struct rcu_head rcu;
  	};
  
  	/* List header used to link this structure to the eventpoll ready list */
  	struct list_head rdllink;
  
  	/* The file descriptor information this item refers to */
  	struct epoll_filefd ffd;
  
  	/* The "container" of this item */
  	struct eventpoll *ep;
  
  	/* List header used to link this item to the "struct file" items list */
  	struct list_head fllink;//指向了上述的就绪链表
  
  	/* wakeup_source used when EPOLLWAKEUP is set */
  	struct wakeup_source __rcu *ws;
  
  	/* The structure that describe the interested events and the source fd */
  	struct epoll_event event;//表示socket fd关心的事件
  	
  	...
  };
  ```





#### epoll_ctl

- 添加或者删除事件

- ```cpp
  int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
  ```

- 当我们向eventpoll添加节点时，实际上还会在这个socket对象的wait queue上注册一个callback function，当这个











# 参考

- https://rebootcat.com/2020/09/26/epoll_cookbook/
- https://www.cnblogs.com/charlesblc/p/6242479.html
- https://blog.csdn.net/wteruiycbqqvwt/article/details/90299610
- https://zhuanlan.zhihu.com/p/392988660
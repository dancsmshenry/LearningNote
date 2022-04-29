epoll_wait函数

- 格式：`int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);`
- 功能：阻塞一小段时间并等待事件发生，返回事件集合，也就是获取内核的事件通知
- 说白了，就是遍历这个双向链表，把这个双向链表里边的节点数据拷贝出去，拷贝完毕后就从双向链表里移除
- 因为双向链表里记录的是所有有数据/有事件的socket（tcp连接）
- 参数：epfd，是epoll_create（）返回的epoll对象描述符
- 参数events：是内存，也是数组，长度是maxevents，表示此次epoll_wait调用可以收集到的maxevents个已经继续（已经准备好的）读写事件
- 说白了，就是返回实际发生事件的tcp连接数目
- 参数timeout：阻塞等待的时长
- epitem结构设计的高明之处，既能够作为红黑树的节点，又能够作为双向链表中的节点



内核向双向链表增加节点一般有四种情况

- 客户端完成三路握手，服务器要accept
- 当客户端关闭连接，服务器也要调用close关闭
- 客户端发送数据来，服务器要用read，recv来接收数据
- 当**可以**发送数据时，服务器可以调用send，write
- 也还有其他的情况







# Epoll

## epoll的数据结构

### 红黑树

- 用途：用于存放需要监听的fd

- 实现：程序在内核空间开辟一块缓存，用来管理 epoll 的红黑树，实现对socket的管理，减少和用户态的交互

- ```cpp
  struct rb_root rbr;
  ```



### 双向链表

- 用途：

  - 缓存就绪的socket和可读可写的fd
  - 只需要拷贝这个双向链表到用户空间，在遍历即可（注意这里也需要拷贝，没有共享内存）

- ```cpp
  struct list_head rdllist;
  ```



### 等待队列

- wait_queue_head_t wq
- epoll_wait使用的等待队列（使用这个系统调用的进程的fd，如果没有事件发生的话，就一直阻塞，否则就把他唤醒）放着正在等待的进程
- 每个epoll对象都会有一个等待队列，该队列会记录有哪些进程阻塞在epoll_wait函数上，所以当有就绪事件时，知道唤醒那些进程







## epoll的使用流程

### epoll_create

- ```cpp
  //# open an epoll file descriptor
  //# epoll_create1 可以理解为 epoll_create 的增强版（主要支持了 close-on-exec）
  int epoll_create(int size);
  int epoll_create1(int flags);
  ```

- 实际上是在内核空间创建了一个eventpoll实例，其中包含了一个红黑树和一个双向链表

- ```cpp
  struct eventpoll {
      struct rb_root rbr;//红黑树的根节点，这棵树中存储所有添加到epoll中的需要监控的事件
      struct list_head rdlist;//双向链表中存放着将要通过epoll_wait返回给用户的满足条件的事件
  };
  
  struct epitem {//红黑树的叶子节点
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



### epoll_ctl

- ```cpp
  //# 往 epoll instance 上添加、删除、更改一个fd（socket)
  int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
  ```

- 当我们向eventpoll添加节点时，实际上还会在这个socket对象的wait queue上注册一个callback function，告诉内核，如果这个fd的中断到了，就把它放到准备就绪的链表中



### epoll_wait

- ```cpp
  //# wait for events on epoll instance
  int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
  ```

- 等待其管理的连接上的IO事件

- 内核通过一个事件表直接管理用户感兴趣的所有事件，因此每次调用epoll_wait时，无需反复传入用户感兴趣的事件，epoll_wait系统调用的参数events仅用来反馈就绪的事件







# Q&A

- epoll是在linux内核版本2.544才被引入的

- 双向链表从内核空间到用户空间是直接拷贝的，没有用上mmap

- 为什么epoll支持百万句柄
  - 背景：此前的select和poll都是能支持上千上万的fd，但是再多就不行了
  - 相比select和poll，不用重复传递fd（调用epoll_wait时相当于以往调用），同时返回的直接就是有事件的fd
  - 使用红黑树实现fd的快速查找，插入和删除
- 为什么epoll使用红黑树

  - 早期使用hashmap效率高，但是内存空间占用大（比如说hash要预先分配足够的内存存储散列表，其中有些槽还可能被废用），就改为了红黑树（仅需要为存在的节点分配内存）
  - 同时kernel中有已经实现好的rbtree，没必要重复造轮子
  - 能够实现fd的快速查找，插入和删除（rbtree下上述操作能在O(logn)下完成）
  - 可以参考一下jdk中hashmap的实现，在hash冲突太多的时候，也变为了红黑树来实现了
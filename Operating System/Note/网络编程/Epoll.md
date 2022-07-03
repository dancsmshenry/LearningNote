# PS

- IO多路复用本质上还是阻塞的，进程或线程还是会阻塞在调用select/poll/epoll函数上，真正的非阻塞还得是异步io（也就是proctor），或者是把epoll等函数包装成reactor
- select，poll需要每次把感兴趣的事件全量传入select或者poll方法中，内核每次都需要复制解析一边，浪费系统资源，而epoll维护了一个全局的rbt，不需要每次全量解析





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





# ET,LT

Level Triggered (LT) 水平触发

- socket接收缓冲区不为空 有数据可读 读事件一直触发
- socket发送缓冲区不满 可以继续写入数据 写事件一直触发
- 符合思维习惯，epoll_wait返回的事件就是socket的状态



Edge Triggered (ET) 边沿触发

- socket的接收缓冲区状态变化时触发读事件，即空的接收缓冲区刚接收到数据时触发读事件
- socket的发送缓冲区状态变化时触发写事件，即满的缓冲区刚空出空间时触发读事件
- 仅在状态变化时触发事件



LT的处理过程：

- accept一个连接，添加到epoll中监听EPOLLIN事件
- 当EPOLLIN事件到达时，read fd中的数据并处理
- 当需要写出数据时，把数据write到fd中；如果数据较大，无法一次性写出，那么在epoll中监听EPOLLOUT事件
- 当EPOLLOUT事件到达时，继续把数据write到fd中；如果数据写出完毕，那么在epoll中关闭EPOLLOUT事件



ET的处理过程：

- accept一个一个连接，添加到epoll中监听EPOLLIN|EPOLLOUT事件
- 当EPOLLIN事件到达时，read fd中的数据并处理，read需要一直读，直到返回EAGAIN为止
- 当需要写出数据时，把数据write到fd中，直到数据全部写完，或者write返回EAGAIN
- 当EPOLLOUT事件到达时，继续把数据write到fd中，直到数据全部写完，或者write返回EAGAIN



从ET的处理过程中可以看到，ET的要求是需要一直读写，直到返回EAGAIN，否则就会遗漏事件。而LT的处理过程中，直到返回EAGAIN不是硬性要求，但通常的处理过程都会读写直到返回EAGAIN，但LT比ET多了一个开关EPOLLOUT事件的步骤



LT的编程与poll/select接近，符合一直以来的习惯，不易出错

ET的编程可以做到更加简洁，某些场景下更加高效，但另一方面容易遗漏事件，容易产生bug

这里有两个简单的例子演示了LT与ET的用法(其中epoll-et的代码比epoll要少10行)：

https://github.com/yedf/handy/blob/master/raw-examples/epoll.cc

https://github.com/yedf/handy/blob/master/raw-examples/epoll-et.cc



对于nginx这种高性能服务器，ET模式是很好的，而其他的通用网络库，更多是使用LT，避免使用的过程中出现bug





# 为什么epoll的ET模式必须要用非阻塞IO，而LT模式可以选择不用

- ET模式下，数据来了只会提醒一次（准确的说是缓冲区发生变化了才会有提醒，如果在第一次发送数据后，后面再美哟惧乐，就不会提醒的），所以力争把数据全部读完
- 而实际上，一次read可能无法将所有的数据全部读完，要多次read
- 如果当前是阻塞io的话，就会循环的调用read读数据，可是如果某一次读完了数据，下一次再读的时候是没有数据的，那线程就会阻塞在read上，一直到下一次数据到来的时候，造成了资源的浪费
- 而如果是非阻塞io的话，数据读完了就不会阻塞，返回错误后就可以执行下面的代码了



- 而LT模式下，只要缓冲区还有数据，就会一直提醒，一直要读
- 而如果是阻塞式io的话，提醒有数据后，可以选择只读一次，读不完的话就留着下次再读，都是ok的（不过这里有点小bug，可能epoll返回的时候是可以读的，但是后面校验和发生了错误，缓冲区把数据给丢掉了，那么同样会造成阻塞）
- 非阻塞就不用说了



- 非阻塞io和阻塞io的区别就是，会不会阻塞再read或write函数上面





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





# 对于ET和LT的理解

- ET下一般来说在epoll返回后需要循环把数据读完（否则剩余的数据要一直等到下一次epoll返回才能读了，而下一次返回的时候就不知啥时候了），因此肯定是要设置非阻塞的，否则循环read的时候就会阻塞在read上了
- LT模式可以不读完数据，随便你读几个字节数据都无所谓



et下的坑爹

- 第一次放入的是数据abcdefg
- et的读数据方式设置为每次只读两个字符，那么此时读到的数据就是ab
- 如果此时再来一次数据123456
- 那么此时读到的就是cd，新来的数据是会接到fg后面
- 所以读数据其实都是从socket的内核缓冲区中的读的





# 参考

- https://rebootcat.com/2020/09/26/epoll_cookbook/
- https://www.cnblogs.com/charlesblc/p/6242479.html
- https://blog.csdn.net/wteruiycbqqvwt/article/details/90299610
- https://zhuanlan.zhihu.com/p/392988660
- https://www.zhihu.com/question/23614342/answer/2274377104
- epoll_ctl_mod
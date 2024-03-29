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
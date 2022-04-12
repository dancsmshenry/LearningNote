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
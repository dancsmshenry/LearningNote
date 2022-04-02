事件驱动模式

- 主线程往epoll内核事件表注册socket上的读事件



- 主线程调用epoll_wait等待socket上数据可读
- 当socket可读时，epoll_wait通知主线程，主线程则将socket可读事件放入请求队列
- 睡眠在请求队列上的某个工作线程被唤醒，从socket读取数据，并处理用户请求，然后再往epoll内核时间表中注册socket写就绪事件



- 主线程epoll_wait等待socket可写
- 当socket可写时，epoll_wait通知主线程，主线程将socket可写事件放到请求队列中
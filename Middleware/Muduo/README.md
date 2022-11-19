# muduo



- one loop per thread + eventloop + threadpool



- 每个channel只属于一个eventloop，即只属于某个IO线程，只负责一个fd



- channel，每个fd事件的高度抽象
  - 负责一个fd的read,write的callback
  - muduo不会使用channel，而是用上层封装的tcpconnection
  - channel生命由其owner负责
- pool，用于IO多路复用监控channel
- eventloop，调用poller，同时处理handleevent





tcpserver

- acceptor
- connectionMap



高水位低水位读写



要好好学学epoll的create，wait，ctl

read，write的api



可以通过shared pointer,mutex实现rw mutex

读：用多个指针指向它，引用计数++

写：全局锁，先判断引用计数，多人在读的话就swap数据





https://blog.csdn.net/tabe_/category_11455179.html

https://blog.csdn.net/tabe_/category_11327992.html

https://blog.csdn.net/tabe_/category_10897043.html
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
事件驱动模式

- 主线程往epoll内核事件表注册socket上的读事件



- 主线程调用epoll_wait等待socket上数据可读
- 当socket可读时，epoll_wait通知主线程，主线程则将socket可读事件放入请求队列
- 睡眠在请求队列上的某个工作线程被唤醒，从socket读取数据，并处理用户请求，然后再往epoll内核时间表中注册socket写就绪事件



- 主线程epoll_wait等待socket可写
- 当socket可写时，epoll_wait通知主线程，主线程将socket可写事件放到请求队列中



- 一个套接字上的输入包括那两部分
  - 等待内核数据准备好（等待数据从网络中到达，然后复制到内核缓冲区，即网卡接受数据，网卡向操作系统内核发送中断）
  - 然后，操作系统把数据从内核缓冲区复制引用到进程缓冲区
  - 任意一段发生阻塞都叫做同步IO
  - 阻塞io和非阻塞io的区别只是在于，当前进程是否阻塞在io上（阻塞io是阻塞在io读取数据上，非阻塞io是阻塞在反复向内核询问轮询上），但本质上都是同步io，只有异步io才能达到真正的异步阻塞
  - 而io复用本质上也是同步io，因为它是阻塞在了系统调用io复用函数上
  - 信号驱动io看上去是异步的，但是当数据复制到缓冲区的时候，内核会调用回调函数，从而使得用户态的函数被阻塞了，所以不能说是异步io，还是同步的io
  - 区分异步和同步的一个方法就是，看内核通知用户态函数是什么事件，如果是io完成了通知用户，那就是异步io，否则就是同步io





- IO复用函数本身是阻塞的，能提高程序效率是因为它们具有同时监听多个IO事件的能力



- 同步和异步io的区别：服务器的内核通知进程（线程）的是IO读取事件还是io完成事件
  - 即告诉应用进程的是什么事件



- 阻塞：我的代码/程序没能往下走，堵在了一个位置
- 例如：当前没有数据，但是调用了read，程序就阻塞在read了



服务器项目的亮点

- epoll，select，poll，源码级剖析
- one loop per thread 服务器设计范式
- 线程池/进程池
- 日志
- 定时器



io数据是如何到达的

- 网卡，出现中断
- 内核：将数据从网卡传送到内核
- 内核将数据从内核态复制到用户态





# 常见的服务器模型

模型一

- 单线程io，整个模型中就只有一个线程，在这个线程上进行epoll的loop循环
- 一开始是只有listenfd的，后面监听到新的事件以后，把clientfd同样的加入进来
- 每次epoll监听到有事件来的时候，就开始按照顺序执行，比如下图显式执行listenfd，再执行clientfd，然后往下
- ![](https://pic1.zhimg.com/80/v2-99a277704df747e1d28c36923e2febd3_720w.jpg?source=1940ef5c)
- ![](https://pic2.zhimg.com/80/v2-a2df53ff71d5f0274d0a8e3f44cc6771_720w.jpg)



模型二

- 多线程io，整个模型中有多个线程，每个线程中都有epoll，其中一个主线程有listenfd，用于监听新连接的
- 当有新的连接过来的时候，就可以选择派发给其他的线程，让其他的线程对其进行epoll的操作
- 或者也可以在当前的进程中操作
- ![](https://pic1.zhimg.com/80/v2-066a6f85870e7550172f465fffb30fa3_720w.jpg?source=1940ef5c)



模型三

- 单线程使用epoll，监听到事件后从线程池中取线程执行，用完后放回
- 事件过多的时候对单个epoll的压力太大了
- 这里需要注意的是，事件去线程池拿线程的时候，是要加锁的
  - 线程上对epoll加锁，是不存在的。一般是epoll在选择到可读可写socket后，为了防止惊群现象，先对socket加锁。如果成功，将socket封装为一个上下文context，再将context交给一个线程去执行。而线程内对epoll是没有操作的。这是一个封装完善程度的事情



- 对于短链接比较多的场景，我认为最好的办法就是还是模型二
  - 而现在新的内核版本支持使用reuseport实现多进程对端口监听，这是最好的办法
- 线程池的作用其实是减少线程的销毁和创建



https://zhuanlan.zhihu.com/p/58860015



模型四

- 最平民的多线程（or多进程）网络IO的模式，比较简单，这里就不画图了。
- 就是主线程创建多个线程（pthread或者std::thread），然后每个线程内部开启死循环，循环体内进行accept。
- 当无客户端连接的时候accept是阻塞的，当有连接到时候，则会被激活，accept开始返回。
- 这种模式在上古时代，存在accept的『惊群』问题（**Thundering herd Problem**），即当有某个客户端连接的时候，多个阻塞的线程会被唤醒。当然这个问题在Linux内核2.6版本就已经解决。



模型五

- 半同步半异步模型：将业务逻辑一份为二：第一部分，接收请求数据是异步的，第二部分，在收完数据之后的处理逻辑是同步的
- 具体：epoll把接收到的数据放入队列中，队列加锁，让线程来抢活干
- ![](https://pic4.zhimg.com/80/v2-3dbbd68c99df3126a6b471d87422b04b_720w.jpg)
- 这里返回数据的方式有很多，比如说直接在工作进程（线程）中返回即可



模型六

- 半同步半反应堆：相比模型五，队列里面放的不是数据，而是fd，每个工作线程拿了fd之后，在各自从fd里面读数据
- ![](https://pic4.zhimg.com/80/v2-c1d79285ab5c705569cfaadfdada890b_720w.jpg)





# 对于端口复用的理解（即如何实现多进程或线程对端口进行监听）

使用reuseport来解决端口复用的问题

- 在Linux 3.9版本引入的reuseport多进程多线程端口复用负载均衡的支持下，肯定是多个进程或线程对应多个epoll循环性能更高。reuseport彻底解决了惊群产生的开销问题
- SO_REUSEPORT支持多个进程或者线程绑定到同一端口，提高服务器程序的性能
  - 允许多个套接字 bind()/listen() 同一个TCP/UDP端口
    - 每一个线程拥有自己的服务器套接字
    - 在服务器套接字上没有了锁的竞争
  - 内核层面实现负载均衡
  - 安全层面，监听同一个端口的套接字只能位于同一个用户下面
- 其核心的实现主要有三点：
  - 扩展 socket option，增加 SO_REUSEPORT 选项，用来设置 reuseport。
  - 修改 bind 系统调用实现，以便支持可以绑定到相同的 IP 和端口
  - 修改处理新建连接的实现，查找 listener 的时候，能够支持在监听相同 IP 和端口的多个 sock 之间均衡选择。
- 有了SO_RESUEPORT后，每个进程可以自己创建socket、bind、listen、accept相同的地址和端口，各自是独立平等的。让多进程监听同一个端口，各个进程中`accept socket fd`不一样，有新连接建立时，内核只会唤醒一个进程来`accept`，并且保证唤醒的均衡性
- 总结：在linux3.9以后，可以多进程多线程对端口进行监听，并且保证不会有惊群现象发生



使用fork

- 使用fork多个子进程同时监听端口
- 可能会出现惊群现象
  - 对于操作系统来说，多个进程/线程在等待同一资源时，也会产生类似的效果，其结果就是每当资源可用，所有的进程/线程都来竞争资源，会造成以下后果：
    - 系统对用户进程/线程频繁的做无效的调度、上下文切换，系统性能大打折扣。
    - 为了确保只有一个线程得到资源，用户必须对资源操作进行加锁保护，进一步加大了系统开销
- 解决办法：
  - 方法一：在Linux 2.6版本之前，监听同一个socket的进程会挂在一个等待队列上，当请求到来时，会唤醒所有等待的子进程。
    当时可以使用锁解决这种惊群问题（可以参考nginx的accept_mutex）
  - 方法二：
    - 在Linux 2.6版本之后，通过引入一个标记位，解决掉了惊群问题。内核开发者增加了一个“互斥等待”选项。一个互斥等待的行为与睡眠基本类似，主要的不同点在于：
      1）当一个进程加入等待队列时，如果该进程有 WQ_FLAG_EXCLUSEVE 标志置位，它被添加到等待队列的尾部。没有这个标志，则添加到队列开始。
      2）当 wake_up 在一个等待队列上被调用时，它会唤醒第一个有 WQ_FLAG_EXCLUSIVE 标志的进程后停止。
      也就是说，对于互斥等待的行为，比如对一个Socket，多线程阻塞accept时，系统内核只会唤醒所有正在等待此事件的队列的第一个，队列中的其他进程则继续等待下一次事件的发生，这样就避免的多个线程同时监听同一个socket时的惊群问题。







# 对于数据接收的确认

- 数据被send到对方的服务器不一定代表被完全接收到了，可能对方服务器的线程被阻塞了，没有读取fd的buffer，又或是还有其他的原因导致，所以我们要在更上一层，即应用层再发送一个ACK给对方



- TCP 的 ACK 表示对方的协议栈已经收到了你发的数据，不代表对方的应用程序收到了你发的消息
- 对方的应用程序可能死锁或者阻塞，不会去调用 recv()，那么你发的数据就堆积在对方协议栈的接收缓冲区里了



- 收到信息和处理信息是两码事！





https://zhuanlan.zhihu.com/p/58860015





select或则poll效率不行的根本原因不是什么线性扫描，而是只能遍历每个fd做poll而无法并行，epoll把这部分工作划分给了具体io驱动模块，所以并行度高。





貌似很多人对select的理解存在误区，认为只有监视的fd个数足够多的时候，*由于select的线性扫描fd集合操作效率才比较低，所以就想当然的认为当监视的fd个数不是很多的时候，它的效率可能比摆弄红黑树和链表的epoll要更高*。其实不是，这个扫描效率和fd集合的大小无关，而是和最大的fd的数值有关。比如你只监视一个fd，这个fd是1000，那么它也会从0到1000都扫描一遍。当然这也不排除fd比较少的时候，有更大的概率它的数值一般也比较小，但是我不想玩文字游戏，如果硬要说fd集合小的时候，epoll效率未必最优的话，那也是和poll比，而不是select。

poll没有select那种依赖fd数值大小的弊端，虽然他也是线性扫描的，但是fd集合有多少fd，他就扫描多少。绝不会多。所以在fd集合比较小的时候，poll确实会有由于epoll的可能。但是这种场景使用epoll也完全能胜任。当然poll也并不总是由于select的。因为这两货还有一个操作就是每次select/poll的时候会将监视的fd集合从用户态拷贝到内核态。select用bitmask描述fd，而poll使用了复杂的结构体，所以当fd多的时候，每次poll需要拷贝的字节数会更多。所以poll和select的比较也是不能一概而论的





对reactor的理解

- 一开始有了io多路复用，使得我们只需要阻塞一个线程，就可以实现高效的coding
- 而实际业务中，我们不仅仅是socket，更多的还有数据库http接口等业务逻辑，这时候就可以参考io多路复用的做法，让有事情的时候再来通知
- 而如果让listen_id，session_id等全部都分配到一起监听，或使得代码变得非常的难看
- 所以就可以使用reactor模式，让多个reactor对应的监听不同类型的事件
- 参考：https://www.zhihu.com/question/320829696/answer/2398963959

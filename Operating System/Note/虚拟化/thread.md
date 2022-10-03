# 定义及分类

- 如果是pthread的话，那就是内核线程，由OS管理
- 但如果是go的goroutine，那就是用户线程，由用户态管理
- 而用户态的线程是基于内核态的线程构建的，所以就会有很多的模型，例如一对一模型，多对一模型，多对多模型
  - 存在一个线程中有多个协程（比如项目burger中就是一个线程中有多个协程，轮询消费协程中的事件），也存在多个线程中有多个协程（golang就是）




## 用户线程

- 用户线程的切换由用户态程序自己控制切换，不需要内核干涉，少了进出内核态的消耗，但不能很好的利用多核Cpu
- 就是go里面的goroutine



## 内核线程

- 由操作系统创建和销毁，内核维护进程及线程的上下文信息以及线程切换，一个内核线程由于IO操作而阻塞，不会影响其他（内核）线程的运行（因为linux是以task_struct作为调度的）
- 切换由内核控制，当线程进行切换的时候，由用户态转化为内核态。切换完毕要从内核态返回用户态；可以很好的利用smp，即利用多核cpu。windows线程就是这样的
- 注意Linux2.4版本之前pthread用的LinuxThread实现，和Linux2.5以后pthread用的NPTL（据说比较好支持了POSIX线程标准）,都是系统级别的1:1线程模型，都是系统级线程
- LinuxThread的内核对应的管理实体就是进程，又称LWP（轻量级进程），每个线程的pid是不一样的（但是getpid返回的都是其进程的pid）







# 线程的创建

- fork()函数就是调用系统调用clone()来实现父进程拷贝的从而创建一个新进程的
- clone()里有一个flag参数，这个参数有很多的标志位指定了克隆时需要拷贝的东西，其中标志位CLONE_VM就是定义拷贝时是否使用相同的内存空间。
- fork()调用clone()时没有设置CLONE_VM，所以在内核看来就是产生了两个拥有不同内存空间的进程
- 而pthread_create()里调用clone()时设置了CLONE_VM，所以在内核看来就产生了两个拥有相同内存空间的进程，即生成了一个内核态的线程



- 另外，看到网上很多文章说，POSIX线程是混合模型，有用户级和系统级线程，通过一个参数来选择。等等。我是这样理解的：
- POSIX只是一个协议，各个系统的实现不一样。我只知道LInux的线程是系统级线程，是内核参与调度的，是操作系统可见的。不管LinuxThread还是NPTL都是这样的











# 等待解决的问题

- 进线程，协程的切换，快慢，代价https://blog.csdn.net/weixin_37841366/article/details/109237089
- 进程，线程同步，通信的各种方式
- linux下进线程的调度都是一样的，因为其底层都是task_struct，kernel只要调度task_struct就可以了



- 







# 八股

## 为什么单线程比多线程快

- 多线程慢可能是因为上下文切换导致tlb失效，导致访问页数的时候命中率下降，从而浪费了效率
- 并且，如果执行的任务的瓶颈主要在io上面的话，在单核的情况下，明显单线程更高效一点
- 参考redis此前一直是单线程，6.0才改为多线程的



## 为什么cpp中线程崩溃整个都down，而java中线程崩溃不会down

背景

- 同一个进程中，线程间是共享地址空间的
- 所以如果某个线程对地址的非法访问就会导致内存的不确定性，进而可能会影响到其他线程
- 这种操作是危险的，操作系统会认为这很可能导致一系列严重的后果，于是让整个进程崩溃



崩溃的种类

- 针对只读内存写入数据（对char*进行写入）
- 访问了进程没有权限访问的地址空间（比如访问kernel的空间）
- 访问了不存在的内存（比如访问null）



流程

- 线程发生了上述的事情，kernel发现了有线程崩溃，于是向当前进程发送信号来终止该进程
- 如果进程没有注册自己的信号处理函数，那么操作系统会执行默认的信号处理程序（一般是发送kill信号，一般最后会让进程退出），但如果注册了，则会执行自己的信号处理函数

- 所以，本质上是jvm注册了信号处理函数，对此进行了捕获；而cpp则没有实现，需要自己去实现信号捕获







# 参考

- https://blog.csdn.net/qq_41489540/article/details/109261692
- https://blog.csdn.net/lxq19980430/article/details/102764018
- https://blog.csdn.net/ctthuangcheng/article/details/8914309
- https://blog.csdn.net/gatieme/article/details/51481863
- https://blog.csdn.net/qq_42011541/article/details/102711196
- https://blog.csdn.net/gatieme/category_6225543.html
- https://blog.csdn.net/qq_41055045/article/details/118885500
- https://blog.csdn.net/mccand1234/article/details/118465728
- https://blog.csdn.net/ctthuangcheng/article/details/8914444
- https://blog.csdn.net/gatieme/category_6225543.html
- https://blog.csdn.net/gatieme/category_6393814.html
- https://blog.csdn.net/gatieme/category_1840439.html
- https://www.nowcoder.com/discuss/821457
- https://www.zhihu.com/question/19732473/answer/241673170
- https://www.zhihu.com/question/492983429/answer/2264063636
- https://kernel.blog.csdn.net/article/details/52384965
- https://kernel.blog.csdn.net/article/details/51482122
- https://www.cnblogs.com/charlesblc/p/6242518.html
- https://www.cnblogs.com/wanglulu/p/5522809.html
- http://www.cnitblog.com/tarius.wu/articles/2277.html
- https://pluscb.xyz/2021/10/04/%E7%BB%93%E5%90%88%E5%86%85%E6%A0%B8%E6%80%81%E5%92%8C%E7%BA%BF%E7%A8%8B%E7%BB%93%E6%9E%84%E8%B0%88%E8%B0%88-%E4%B8%BA%E4%BB%80%E4%B9%88%E7%BA%BF%E7%A8%8B%E5%88%87%E6%8D%A2%E6%AF%94%E8%BF%9B%E7%A8%8B%E5%BF%AB/
# Background

上节课讨论的都是单个SQL语句是如何执行的，但是实际上我们很多时候都是多线程执行SQL语句

为什么要多线程并发执行
- 提高性能（比如吞吐量，同时进行100条SQL，然后这100条SQL都能执行完；又或者说一条SQL单线程的情况下，需要8s才能执行完，而多线程只需要2s即可）
- 能够提高应用的响应性和可用性（SQL能够快速的响应）
- 降低开销（提高效率，能够使用更少的时间、更少的电费去实现功能）

<br/>

<br/>

<br/>

# Parallel vs Distributed

并行数据库

- 所有的资源，线程都是在同一个machine上
- 并行数据库之间通信是高速的
- 并行数据库之间线程的通信都是简易和可靠的

<br/>

分布式数据库
- 结点之间可能分割的非常远
- 通信需要互联网（而不是内存）

<br/>

<br/>

<br/>

# Process models

线程模型；在研究执行模型时，将SQL语句的执行抽象为worker（一条SQL将多个不同的算子抽象为不同数量的worker）

<br/>

<br/>

## Process per DBMS Worker

每一个worker分配一个进程去做（依赖于操作系统的调度）

进程间通信（用shared memory通信）
- 执行一条SQL可能会分为不同的算子，这里的意思应该就是将不同的算子给不同的worker，即进程去操作
- 而这些进程间如果需要通信，就用shared memory通信

<br/>

优点：一个进程的crash不会影响其他的进程

缺点：如果并发量非常大的话，就会极度的浪费资源

应用：DB2，Oracle，Postgresql

<br/>

当SQL语句到来的时候，会被dispatcher分配worker去执行语句，worker执行完后就将数据返还给DBMS

<img src="image/process per DBMS Worker.png" style="zoom:150%;" />

<br/>

<br/>

## Process pool

因为多进程会浪费资源，所以想到了复用进程，进而提出进程池

即dispatcher不再是直接创造出进程，而是把从进程池里面找到新的进程给SQL去执行，用完后在返回进程给进程池

应用：DB2，postgresql

<img src="image/process pool.png" style="zoom:150%;" />

<br/>

<br/>

## Thread per DBMS Worker

后面就出来了pthread线程（主要是线程之间的切换小于进程之间的切换，并且线程天生就能够相互通信）

每一个worker就有一个线程

线程之间的调度是由DBMS调度（有点类似用户态线程）

dispatcher的数量不定，一个或者多个

缺点：一个线程的崩溃会将整个进程给崩溃掉（稳定性有点差）

应用：DB2，Oracle，SQL Server，MySQL

<img src="image/thread per worker.png" style="zoom:150%;" />

<br/>

很多DBMS都用了多线程的技术
- 这里的多线程其实是指一个SQL语句由一个worker去跑，多线程是指可以同时跑多个SQL语句
- 而将一条SQL开多线程跑是另一种技术

<br/>

<br/>

<br/>

# Execution parallelism

SQL执行间的并发机制

如何将每条SQL语句分为多个worker去执行

针对每一个执行计划，在哪儿执行，如何执行

把一个执行计划如何切分为小的任务，每个任务应该如何分配资源

<br/>

<br/>

## Inter query parallelism

每个单独的查询，如何并发的执行查询

不同的查询并发的去执行，可以降低延迟，提高吞吐量

如果查询是只读的话，那么多个查询之间的冲突就会很小，就没有并发问题

但是如果查询有读有写，那么就会有并发问题

<br/>

<br/>

## Intra query parallelism

查询的内部并发的执行，一个执行计划切分为不同的线程去做，可以减少延迟（减少等待）

好处：通过单个查询的并行，提高性能

思想上有点像生产者消费者的模型

成熟的DBMS的每一个算子都有并发的版本

并发算子实现的两大思路
- 多个线程都去操作集中的总数据
- 或者将数据分隔开，让多个线程去处理不同部分的数据

例子：比如说之前的grace hash join

- 可以并发的多个线程去处理每个桶之间的数据，即对每个桶进行并发的join

<br/>

<br/>

### Intra-operator(horizontal)

水平切分

把要处理的数据切分为多份，然后分发给多个线程去执行，可以理解为将同一份数据的操作分给了多个线程去做，多个线程对同一份数据的不同部分做同样的操作

还要插入exchange算子（用于数据的拆分聚集的）

<img src="image/intra-operator parallelism_01.png" style="zoom:150%;" />

即上面的算子调用一次exchange算子，然后exchange算子并发的开多个线程A1A2A3去执行，接着把得到的结果汇总给上面的算子

<img src="image/intra-operator parallelism_02.png" style="zoom:150%;" />

<br/>

<br/>

#### Exchange operator

有三种不同的算子
- gather：将下面并发执行的结果收集好分配给上面
- distribute：将数据分发给不同的算子去执行，分配的算子
- repartition：重分配的算子，即把三个算子的结果分配给两个算子去执行

<br/>

<br/>

### Inter-operator(vertical)

垂直分开，即一个SQL语句是由很多个算子的过程组成的，那么就分配多个线程，分别取执行不同的步骤

<img src="image/inter-operator parallelism_01.png" style="zoom:150%;" />

即一个线程在下面执行hash join，另一个线程在执行上面的算子

即每个算子都有一个线程取负责，数据就在线程之间进行传递（每个线程干的话不一样）

缺点：流式模型，即如果有人做事满了，那么就会影响到下一层的人做事的效率

<br/>

<br/>

### Bushy parallelism

是上述两种执行方法的融合版本

<br/>

<br/>

思考：

其实DBMS真正的瓶颈是数据的IO，上面无论做再多的优化，如果磁盘的IO还是很慢的话，这些优化都不值一提

并且，磁盘是瓶颈，但是我们还让不同的线程去读磁盘不同的部分，这会让其变得更糟（即随机IO使得使其变得更糟）

所以要想到如何优化硬盘的性能

<br/>

<br/>

<br/>

# I/O parallelism

磁盘IO的并发优化

一些思路：
- 把不同的数据库放到不同的硬盘上，这样就可以实现并发的同时，减少随机写，从而提高性能
- 一个数据库存到一个硬盘上
- 一个数据表存到一个硬盘上
- 同一个数据库的表拆分到不同的硬盘上

思路：把数据分配到不同的硬盘上，提高并发性能

<br/>

<br/>

## Multi-disk parallelism

RAID0 stripping

- 前面的做法，都是能够感知到数据是被分配到不同的磁盘上的，而使用RAID技术
- RAID：有多个磁盘，但是通过一些配置，使得看起来只有一个磁盘一样（使得DBMS感觉只有一个磁盘一样）
- 即把page1和page4放到第一个盘，page2和page5放到第二个盘
  - 这种操作是OS,hardware和DBMS共同协商控制的
  - 从使用者的角度来看只有一个盘，但是实际上的存储，是放在不同的硬盘上的
- 能够提高并行的读写（如果要同时写page1和page2，那么就可以快速的写）
- 可拓展性高；如果一块硬盘坏了，其他盘中的文件碎片也会失效（因为它是将磁盘的数据分成了一个一个的文件碎片的...）

<br/>

<br/>

RAID1 mirroring

- 同一个数据页存到不同的磁盘中
- 优点：
  - 可靠性高，多备份（其中一个数据盘坏了也不受影响）
  - 可以并行读
- 缺点：利用率低（3个1t的硬盘只能存1T的数据）

<br/>

<br/>

上面其实讲的是磁盘级别硬件级别上的IO并行

换个角度，从数据本身如果想要切开的话，有哪些方法？

一个思路：把不同的数据库放到不同的盘中（常见）

另一个思路：在物理上将数据分为多个表或者多个部分，但是client不知道底层的实现

<br/>

<br/>

## Vertical partitioning

垂直分表，将不同列的数据存放到不同的磁盘中

这个是数据库自己做的（配置一下即可）

比如把age放到D盘，把name放到E盘

好处：可以并发的读写数据

优化：一条数据会有冷热数据，哪些冷的数据可以单独的放到另一张表中存储

<br/>

<br/>

## Horizontal partitioning

水平分表

可以按照某一列的值，将数据分为两个或者多个部分
- 即partitioning key（可以按照hash，或者其他的谓词，或者范围分区）

一些分库分表的中间件也可以做（就像是一个网关，将client的数据分成不同的部分，然后再存储到不同的数据库中，每个数据库就在不同的结点）

<br/>

<br/>

<br/>

# Conclusion

并行是非常重要的（能够降本增效）

至少sql语句之间的并发是都实现了

模型看着简单，但是coding却非常的麻烦

- worker的调度
- worker的并发（lock）
- worker资源上的冲突
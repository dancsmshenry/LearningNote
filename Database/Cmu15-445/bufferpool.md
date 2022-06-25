# 问题二：DBMS如何管理它的内存以及如何在磁盘上来回移动数据





# locks和latches的区别

locks

- 保护数据库的逻辑内容不受其他事务的影响
- 在事务持续时间内保持
- 需要能够回滚更改



latches

- 保护DBMS内部数据结构的关键部分不受其他线程的影响
- 在操作持续时间内保持
- 不需要能够回滚更改
- 有点类似std::mutex





# 内存分配策略

- 全局策略
  - 为全局活跃的事务做决策
- 局部策略
  - 为一个每个事务分配特定的帧而不考虑事务的并发行为
  - 仍然需要共享页面





# 缓冲策略

- 多个缓冲池
- 提前抓取可能需要的页面
- 扫描共享
- 缓冲池





### 多个缓冲池

- 多个缓冲池实例
- 每个数据库独有的缓冲池
- 每种页面的缓冲池



### 提前抓取

- DBMS还可以根据查询计划预取页面
  - 顺序扫描
  - 索引扫描
- 在查询当前页面的时候，猜测下一个有可能读取的页面，然后将其加入到缓冲池中
- ![](image/pre-fetching_01.png)
- ![](image/pre-fetching_02.png)
- 所以DBMS会猜测下一个要取值的页面是page3或者page5





### 扫描共享

- 查询可以重用从存储或者运算符计算中检索的数据
- 允许在扫描表的单个游标上附加多个查询
  - 查询不必相同
  - 中间结果可以分享
- 如果一个查询开始扫描，并且已经有一个这样做了，那么DBMS将附加到第二个查询的游标
  - DBMS跟踪第二个查询与第一个查询连接的位置，以便当它到达数据结构的末尾时能够完成扫描
- 即如果大家都需要共同的数据，第一个查询和第二个查询都要查询共同的数据，那么就可以让后面的查询先跟着前面的查询数据，这样就可以提高查询效率，即重组后一个查询的IO顺序，通过共用数据来提高效率





### buffer pool bypass

- 不将获得到的page数据存储到buffer pool中，因为有些query得到的数据只使用一次，如果放到buffer pool中会导致buffer被污染
- 另外当前query还可以创建一个临时的buffer





# OS页面缓存

- 大多数磁盘操作都通过os的api进行
- 所以大多数的dbms都使用直接I/O*（O_DIRECT）来绕过操作系统的缓存





# 缓冲池的替换策略

- 背景：当DBMS需要释放一个框架来为一个新页腾出空间时，它必须决定从缓冲池中清除哪一个页
- 需求：
  - 正确性
  - 准确性
  - 速度
  - 元数据的开销





### least recently used

- 维护每个页面最后一次被访问的时间戳
- 当DBMS需要删除一个页面时，选择最古老的时间戳的页面删除
- 保持页面有序，减少搜索时间



### Clock

- 用一个时钟指针将页面阻止在一个循环缓冲区中，用指针访问页面的位
- 当访问页面的时候，将页面设置为1
- 清扫时，检查页面的位是否为1，如果是1的话，就设为0；否则就把页面剔除



### 小结

- LRU和CLOCK替换策略容易受到顺序洪泛的影响
  - 查询执行顺序扫描，读取每个页面
  - 这会污染缓冲池，让页面读一次就再也不会读了
  - 最近使用的页面实际上是最不需要的页面



### better policies:LRU-K

- 跟踪最后K个引用的历史作为时间戳，并计算后续访问之间的间隔
- DBMS然后使用这段历史来估计该页面下一次被访问的时间





### better policies:localization

- 根据每个事务查询要驱逐的页面，这样可以最大限度减少每次查询堆缓冲池的污染



### better policies:priority hints

- DBMS知道查询执行期间每个页面的上下文是什么，可以像缓冲池提供关于页面是否重要的提示



# Dirty pages

- 如果缓冲池中的一个页面不是脏的，就直接将它删除
- 否则，DBMS必须写回磁盘，以确保它的更改是持久的
- DBMS的权衡：在快速删除和不会再读脏页之间权衡



- DBMS可以定期遍历页表并将脏页写入磁盘
- 当脏页被安全地写入时，DBMS可以清除该页或取消脏页标志的设置
- PS：不能在日志记录被写入之前写入脏页





# 其他的缓冲区

- 除了元组和索引之外，DBMS还需要内存
- 这些其他内存池可能并不总是由磁盘支持。依赖于实现
  - 排序+连接缓冲区
  - 查询缓存
  - 维护缓冲区
  - 日志缓冲区
  - 字典缓存





# 参考

- https://www.jianshu.com/p/fecd0358cd29
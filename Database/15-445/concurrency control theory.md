# 动机

- 对于同一条数据进行修改，必定会出现竞争的问题（如何避免竞争）
  - 也会出现更新丢失的情况，需要并发控制解决
- 执行多条语句（事务）的时候机房发生短电，该如何处理
  - durability 持久化的问题，需要recovery恢复解决



并发控制和恢复是基于ACID的非常重要的功能



# 事务的定义

- 事务是执行一系列操作（sql语句），以达到一个高级的功能（比如说通过sql语句对账户的余额增减，以实现转账的功能）
- 比如说转账
  - 先检查A账户有没有100块钱
  - 有的话，就减去100块钱
  - 最后给B账户加100块钱
- 如果没有显式的说明事务的话，那么一条sql语句就会被认为是一个事务



一个想当然的想法

- 事务串行化执行（串行化效率低下）
- 或者事务执行的时候，把整个数据库备份一个出来（问题是，磁盘大小会因为不断的copy导致内存不构）



- 需求：事务能够并发的跑，并且维持ACID的性质
- 要维护事务的正确性和公平性
- 如果不设限的话，并发的事务会存在临时性的数据错误和永久性的数据错误



问题

- 数据库只知道数据的读写，不知道事务的逻辑，不知道到底需要干嘛，所以需要一个控制协议让DBMS能够正确的执行并发



- 研究事务不需要知道数据具体放在哪儿
- 事务的研究本质上就是研究数据的读和写（简化模型）



# 数据库操纵事务

- begin显式的告诉数据库事务开始
- commit告诉DBMS事务结束（或者rollback，abort回滚事务）
  - abort有可能是事务本身发出的，也有可能是DBMS发出的







# 事务正确性的标准ACID

- atomicity：原子性，事务要么都执行，要么都不执行
  - all or nothing
- consistency：一致性，比如说两个人的总账户金额为200，A给B转账100后，总金额发生了变化，那就失去了一致性
  - it looks correct to me
- isolation：隔离性，理想的隔离性是指好像数据库中只有这一条事务在操作一样（我做的操作别人看不见，别人做的我也看不见）
  - 存在现实的妥协
  - as if alone
- durability：持久性，事务提交后，它的更新应该是永久的持久的，不能说一停电事务就失败了
  - survive failures



## atomicity

- 事务有两种结局：
  - 所有的sql语句都执行完了，事务都提交了
  - abort终止了，客户端或DBMS终止
- 从业务者的角度来看：所有的sql要么全部执行，要么一个都没有执行（DBMS对部分执行的事务回滚）
- 实现atomicity的方法
  - 方法一：logging，事务每执行一步，都要记录如果此时要发生回滚的话，应该怎么办（undo log）
  - 如果哪一步需要**回滚**，那就按照undo log，一步一步的将数据回滚回去，撤回数据
  - 还有**审计**的作用，查看sql语句到底对DB做了什么，监控的作用
  - 还有**提高sql执行效率**（正常的sql很多都是随机的读写，但是如果OS的IO不行的话，可以把IO延后，即先顺序写日志，后续空闲的时候执行IO）
  - 方法二：shadow paging，事务需要对那些页进行修改，就将那些页备份出来，事务如果commit的话，就将修改好的页替换回去；如果要回滚的话，就把备份的替换回去
  - 很少数据库用这种方法了...



- 日志的两个功能
  - 维护事务的原子性（如果事务执行到一般被abort的话，就用日志来回滚当前的数据）
  - 提高运行的效率（提高性能），因为往往对数据的操作都是随机读写，如果io的性能不行的话，可以把要做的操作先写入日志，写日志是顺序写，效率高，后续在按照顺序把文件的操作一点一点的写入磁盘中，就不需要在当时让用户卡住，随机读写而造成效率低下

- 日志的作用
  - 回滚
  - 监控审计
  - 性能上的考虑



## consistency

- 逻辑上说得通的
- 分为数据库（数据）一致性（后面发生的事务要能够看到前面发生事务的数据）和事务一致性
- 数据库一致性是ACID所保证的
- 而事务一致性是依靠业务保证的
  - 比如说转账系统，A给B转账100，但是你的sql写的却是给A减一百，给B加了150，事务的一致性就出问题了



## isolation

- 好像就只有一个人再用一样，别人提交的修改我也看不见，数据就和事务刚开始的样子一样
- 别人没提交的也看不到，最理想的隔离性
- 为什么
  - 写业务的时候方便（转账只考虑A和B的关系即可，不用考虑别的事情），为了能让用户更好的实现它的业务
  - 即用户可不管这些其他的情况，专心于自身的业务；如果失败了，DBMS就会直接告诉你失败了，然后重新再做即可
- 所以需要设计一种协议，实际上让多个事务能够同时跑起来，但是又能够让用户感觉好像只有他自己的事务在跑一样
- 即并发控制协议：决定用什么顺序让多个事务穿插的执行
- 两大流派
  - pessimistic：悲观类，不让问题发生，在问题发生之前就让他停下来
  - optimistic：乐观类，假设冲突是非常有限的，在真正出问题的地方回滚
- 当某个事务出现问题的时候，不能影响其他的事务（串行影响性能）



- 由转账的例子中，发现有些事务的并发顺序是正确的，而有些是错误的，那DBMS如何知道事务是否正确呢？
- 怎样给数据库设置一种算法，证明数据的正确性
- 如果一种并发执行的安排执行后是等效于串行化的话，就是正确的



- serial schedule（串行化执行，真串行）
- equivalent schedule（等效串行）
  - 如果两种执行的顺序的**结果**是等效的话，那就说明它们是等效的执行安排
  - 如果两种方法的执行效果相同的话，侧重是两种方法是否等效
- serializable schedule（我的执行顺序和真正的串行是等效的）
  - 我的执行方式安排和真串行是等效的
  - 侧重当前方法和真串行是否等效
  - 简称可串行化
  - 可以给数据库的执行更多灵活性，和并发性
- 问题是如何证明这两个东西是等效的



### 冲突的操作（conflicting operations）

- 两个操作是冲突的意味着
  - 操作时来自不同的事务
  - 两个操作都在操作同一个事务，并且一个操作是写
- 读写冲突，写读冲突，写写冲突
- 读写冲突
  - 事务A第一次读的数据是10，事务B修改为19（修改后的数据的是提交了的），事务A第二次读的时候就变为了19，就破坏了隔离性
  - 不可重复读 unrepeatable read
  - 重复读了以后发现数据不一样
  - 不可重复读侧重的是在当前事务中，对一个数据的重复读，数据发生了不同，而这个不同是因为在当前事务的执行过程中，有别的事务（已提交了的）对其进行了修改
- 写读冲突
  - reading uncommited data（dirty reads）读未提交 脏读
  - 事务A修改了数据a（但是还没有提交事务），事务B读取数据的时候读到的数据啊是事务A修改过后的，就读到了脏的数据
  - 是一个没有提交的值
  - 如果事务A发生了回滚，就会出错
  - 即我写了更新了一个值，别人又拿了这个值，但是我的更新是未提交的..
  - 注意：脏读（读未提交）侧重的是读到的是**未提交**的数据，即脏读读到的数据是还没有commited的，造成的后果就是如果写这个数据的事务，发生了回滚，那么就相当于读到的了脏的数据了
- 写写冲突
  - overwriting uncommited data
  - 事务A写了数据a，事务B又写了数据a，导致事务A的操作被覆盖了（即没有看到对方提交的数据）
  - 导致最后留下的数据，不全是一个事务的操作



- 基于冲突的串行化（conflict serializability），大多数DBMS都是基于此做的可串行化
- 基于观察的串行化（view serializability），没有DBMS可以基于此做



基于冲突的串行化等效

- 如果两个序列的事务是相同的，包含的事务是相同的，产生的冲突是一样的
- 即冲突等效



还有一种等效，即移动sql语句执行的时机，如果两个序列的结果依然等效的话

其实后面说了那么多，主要就是几点

- 前面的三种冲突是不可以交换顺序的，因为交换顺序后，语义就发生了变化
- 那就是说，除了上述的冲突外，其他的语句是可以交换顺序的，那么就是说，为了提高并发度，我们可以先来一个串行化的操作，然后再排除掉上述的三种冲突以外的情况下，交换语句的顺序，以此获得更高的并发度
- 所以就有一个思路，就是通过不断调整事务语句的顺序，获取串行化的同时，又能提高并发度



### 依赖图（dependency graphs）

- 如果冲突之间形成的关系成环了，就不能转变为串行化，就永远变不了串行化
- 比如事务A和事务B之间发生了写读冲突，就在事务A上画一条边到事务B上（example 1）（先发生的指向后发生的）
- 如果出现了环，就代表永远无法通过滑动非冲突
- 这个边就是说一个操作一定要在另一个操作之前发生
- 形成了环，就不能可串行化了
- 即如果几个事务的依赖图形成的图没有成环，就代表其是可串行化的，即最后的效果相当于一个一个跑



view serializability

- 根据业务的需求，发现有些情况虽然是成环的，但还是可以等效串行化执行
- 所以，依赖图的做法，可能真的会损坏一些隐藏的可串行化的情况
- 所以view的可串行化范围是大于conflict的，但是编程无法实现
- 基于观察的串行化是ok的，但是难以实现



- view serializability 和 conflict serializability都没法做到完全识别出所有的可串行化，即没法做到不错杀，也是因为数据库没法做到理解数据库的业务
- conflict serializability画依赖图的做法是绝大部分的DBMS都在用的（好实现）
- 也可以做一些优化，比如说都是只读的事务的画，就直接操作就好了





## durability

- 事务的持久性
- 所有的事务的语句，都必须持久化到磁盘中，不存在事务只更新到一半的情况，也不能有部分事务数据留下来的（失败的数据）的情况
- 通过logging或shadow paging来实现的



- 并发控制和恢复是数据库最重要的功能
- 有些数据库不支持事务，是因为要么全部的操作全部转为可并发的，要么就是自己去判断有没有问题，要么就是在业务里面加锁
- 谷歌著名论文设计spanner，很多tidb都是出自这里
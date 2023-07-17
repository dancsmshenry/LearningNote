# QoS
Quality of Service

现在总共有22个服务策略，有些策略是专门为不同的entity专门设计的，比如这里的第二个和第三个就是专门为DataReader设计的

<br/>

![](../image/QoS.png)

<br/>

一些比较常用的QoS策略
- user_data
  - 把应用程序的信息附加到创建的Entity上
  - 比如说创建一个datawriter，就可以将一些安全凭证附加到这个上面
  - ara::com的网络绑定（比如后续的dds网络绑定，服务发现的SPDP协议就是靠这个实现的）
  - 类似的还有TOPIC_DATA（把应用程序的信息附加到topic上），GROUP_DATA
- durability，持久性
  - 将样本发送给订阅端时，本地是否还需要保存样本信息
  - 可以在topic、datareader以及datawriter中配置
  - 如果topic的设置与datareader/datawriter不兼容，则topic不会发送此数据
  - 比如说writer和reader设置的是保留，而topic设置的是不保留，那么此时二者就不能读写topic中的数据
- presentation
  - 控制如何将Data Writer对实例所做的更改呈现给DataReader
  - 可以按照顺序，或者乱序；
- ownership
  - 专门针对data writer的
  - 控制多个data writer是否能够写同一个数据对象实例
  - 所有权可以是独占（只能有一个线程对数据进行读写）或共享（可以有多个线程一起写数据）
- liveliness
  - 控制服务何时以及如何确定参与者是否还活着
  - （有点像心跳包），有两个参与者，但当我想要发送数据的时候，该如何确定对方是否在线
  - 定期发送报文，确认对方是否存活（当然还有更多的策略）
- time_based_filter
  - 控制data reader对数据实例感兴趣的频率
  - 就像报纸的订阅一样，可以只订阅某个感兴趣时段的；用滤波来处理
- partition
  - 分区，允许在一个domain中创建其他的逻辑分区
  - 有点类似子网和子网掩码的概念，不过更加的灵活，比如说可以自定义分区规则
  - 如果在一个分区内就可以通信，不同分区之间不可以通信
- resource_limits
  - 用于控制资源的大小
- lifespan
  - 设置样本数据的到期时间
  - 过期的样本数据是不可以被再发出去了
- history
  - 对于数据的读取和写入，应该如何保存数据的更改
  - 一般是和durability（持久性）一起使用的
  - 如果持久性设置的是保留，那么此前发送的数据都会被保留在本地history中，并且每次数据发送的时候就会将所有保留的数据一并发送给对方
  - 而如果设置的是不保留的，那么发送过了的数据就不会保留在本地，那么每次数据的发送，就只需要发送当前的数据（而不用加上此前发送过的数据）
- reliability
  - 可靠性，表示 data writer 和 data reader 如何处理数据样本
  - 有两种可选的参数：best-effort（尽力而为；即使收到了缺失的数据，也不会重新发送数据），reliable（可靠；如果数据发生了丢失，那么就需要将数据重新发送）
  - 存在冲突：data writer是best-effort，而data reader是reliable，那么reader读到了缺失的数据，会向writer要数据，而writer是best-effort，那么此时writer是不会重新发送数据的（主要是二者的策略不兼容的；但是一般不会有这种情况发生，因为后续二者进行匹配的时候，qos策略不一致则无法匹配上）
- time_based_filter
  - 必须和 deadline 设置一样

- deadline
  - 对于 datawriter 来说，设置了该 qos 后，如果 datawriter 在该时间到达的时候，还没有写入到相应的数据，就会执行相应的回调函数 on_offered_deadline_missed
  - 对于 datareader 来说，设置了该 qos 后，如果 datareader 在该时间到达的时候，还没有读取到相应的数据，就会执行相应的回调函数 on_offered_deadline_missed
  - 当 DW 和 DR 进行关联时，二者的值需要能够相互兼容（DR 的 deadline 要大于或等于 DW 的 deadline）
  - 背景：当 topic 需要定期更新实例的时候才会配置使用（比如一些周期性的数据）


<br/>

# QoS的策略组合
- 如果希望**传输有高可靠性，确保所有数据不丢失**，那么durability持久性这块，就需要设置为保存已发送的数据，不删除；reliability可靠性这块，就需要设置确保所有数据的可靠传输，不接受丢包
- 如果希望传输**具有安全性，要认证信息，需要通信域隔离**，那么user_data，发送端可以通过附加的信息进行授权和认证，接收端可拒绝未授权的信息；partition则设置为划分通信域，只有匹配的收发端能够相互通信

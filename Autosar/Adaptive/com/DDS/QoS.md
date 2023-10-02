# Quality of Service
目前有22个服务策略，有些策略是专门为不同的 entity 专门设计的，比如这里的第二个和第三个就是专门为 DataReader 设计的

<br/>

![](../image/QoS.png)

<br/>

<br/>

<br/>

# user_data

把应用程序的信息附加到创建的 Entity 上

比如说创建一个 DataWriter，就可以将一些安全凭证附加到这个上面

ara::com 的网络绑定（比如后续 dds 的网络绑定，服务发现的 SPDP 协议就是靠这个实现的）

类似的还有 TOPIC_DATA （把应用程序的信息附加到 topic 上），GROUP_DATA

<br/>

<br/>

<br/>

# durability

持久性

将数据发送给订阅端时，本地是否还需要保存数据信息

可以在 topic、DataReader 以及 DataWriter 中配置

如果当前 topic 的配置与 DataReader/DataWriter 不兼容，则 topic 不会发送此数据

比如说 Writer 和 Reader 设置的是保留，而 topic 设置的是不保留，那么此时二者就不能读写 topic 中的数据

我理解为这个和后面的可靠性是挂钩的，因为如果需要可靠性的话，那么发送数据后就应该在本地保存数据

需要 Topic，DataReader 和 DataWriter 在这个策略上都一致，才能够相互兼容，从而收发数据

比如说 DataWriter 和 DataReader 设置的是保留发送的数据，而 Topic 设置的是不保留，那么此时二者就不能对 Topic 的数据进行读写

这里的数据保留和 History 其实是不同的，比如说数据发送给了 DataReader1，那么我是否还要保留呢？

后续可能还有 DataReader2，DataReader3，他们要不要读取这个数据？那么就是这个策略决定的

<br/>

<br/>

<br/>

# presentation

控制如何将 DataWriter 对实例所做的更改（即数据）呈现给 DataReader

可以按照**顺序**或者**乱序**

（具体看上层业务是如何规定的）目前来说是规定它必然是有序的

<br/>

<br/>

<br/>

# ownership

控制多个 DataWriter 是否能够写同一个数据对象实例

所有权可以是独占（只能有一个线程对数据进行读写）或共享（可以有多个线程一起写数据）

<br/>

<br/>

<br/>

# liveliness

控制服务何时以及如何确定参与者是否还活着，有点类似心跳包

假设有两个参与者，但当我想要发送数据的时候，该如何确定对方是否在线

定期发送报文，确认对方是否存活（当然还有更多的策略）

<br/>

<br/>

<br/>

# time_based_filter

控制 DataReader 对数据实例感兴趣的频率

就像报纸的订阅一样，可以只订阅某个感兴趣时段的

<br/>

<br/>

<br/>

# partition

分区，允许在一个 domain 中创建其他的逻辑分区

有点类似子网和子网掩码的概念，不过更加的灵活，比如说可以自定义分区规则

如果在一个分区内就可以通信，不同分区之间不可以通信

<br/>

<br/>

<br/>

# resource_limits

用于控制资源的大小

<br/>

<br/>

<br/>

# lifespan

设置样本数据的到期时间

过期的样本数据是不可以被再发出去的

<br/>

<br/>

<br/>

# history

对于数据的读取和写入，应该如何保存数据的更改

一般是和 durability（持久性）一起使用的

如果持久性设置的是保留，那么此前发送的数据都会被保留在本地 history 中，并且每次数据发送的时候就会将所有保留的数据一并发送给对方

而如果设置的是不保留的，那么发送过了的数据就不会保留在本地，那么每次数据的发送，就只需要发送当前的数据（而不用加上此前发送过的数据）

<br/>

<br/>

<br/>

# reliability

可靠性，表示 DataWriter 和 DataReader 如何处理数据样本

有两种可选的参数：

- best-effort（尽力而为；即使数据发生了丢失，也不会重新发送数据）

- reliable（可靠；如果数据发生了丢失，那么就需要将数据重新发送）

存在冲突：

DataWriter 是 best-effort，而 DataReader 是 reliable

那么 Reader 读到了缺失的数据，会向 Writer 要数据

而 Writer 是 best-effort，那么此时 Writer 是不会重新发送数据的

（主要是二者的策略不兼容的；但是一般不会有这种情况发生，因为后续二者进行匹配的时候，qos策略不一致则无法匹配上）

<br/>

<br/>

<br/>

# deadline

对于 DataWriter 来说，设置了该 qos 后，如果 DataWriter 在该时间到达的时候，还没有写入到相应的数据，就会执行相应的回调函数 on_offered_deadline_missed

对于 DataReader 来说，设置了该 qos 后，如果 DataReader 在该时间到达的时候，还没有读取到相应的数据，就会执行相应的回调函数 on_offered_deadline_missed

当 DW 和 DR 进行关联时，二者的值需要能够相互兼容（DR 的 deadline 要大于或等于 DW 的 deadline）

背景：当 topic 需要定期更新实例的时候才会配置使用（比如一些周期性的数据）

<br/>

<br/>

<br/>

# QoS的策略组合
如果希望**传输有高可靠性，确保所有数据不丢失**，那么durability持久性这块，就需要设置为保存已发送的数据，不删除；reliability可靠性这块，就需要设置确保所有数据的可靠传输，不接受丢包

如果希望传输**具有安全性，要认证信息，需要通信域隔离**，那么user_data，发送端可以通过附加的信息进行授权和认证，接收端可拒绝未授权的信息；partition则设置为划分通信域，只有匹配的收发端能够相互通信

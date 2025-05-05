# publisher

publisher 作为 DataWriter 的工厂类和容器类，会对下层的 DataWriter 进行添加、删除、查找等操作

## member

`domainparticipant* participant_` 表示当前是挂载在哪一个 participant 下面

`publisherqos qos_` pub 端的 qos 

`map<string, vector<weak_ptr<datawriter>>> writers_` 存放不同 topic 下的 datawriter

- pub 端可以有多个 DW ，不同的 DW 也可以对应不同的 topic

`map<string, shared_ptr<datawriter>> builtin_writers_` 存放的 builtin datawriter

- 内置的 publisher 一般来说，每个 topic 都只有一个 DW

`publisherlistener`

`default_datawriter_qos`（每个 DW 都会有默认的 qos）

<br/>

## function

`returncode enable()` 使用该 publisher 的时候需要用到（调用所有 writer 的 enable 函数）

- 调用链：`domainparticipant::enable->publisher::enable->writer::enable`

`void disable()` 对应 enable （调用所有 writer 的 disable 函数）

- 调用链和上面相似

`shared_ptr<DataWriter>` 调用 participant 的 createwriter 创建 rtps::writer

- rtps::writer 里面就涉及很多qos策略的实现

<br/>

<br/>

<br/>

# datawriter

继承自 DomainEntity

<br/>

## member

- `shared_ptr<innerwriterlistener>` 内置的 listener
  - 继承自 rtps 层的 listener
  - `DataWriter* data_writer_` 指向当前 datawriter 的指针
- `*publisher_` 指向 publisher 的指针
- `shared_ptr<topic>` 指向使用的 topic
- `shared_ptr<rtps::writer>` RTPS 层的 writer
- `datawriterqos` 当前 DW 的 qos
- `Guid` 全局 id
- `shared_ptr<datawriterhistory>` 存放需要 write 的 cachechange
- `shared_ptr<datawriterlistener>`
- `core::io::eventloop` 当前的 DW 是在哪个 eventloop 中运行
- `core::io::timer` 当前 DW 的定时器

<br/>

## function

- `write(T& data)` 写数据，实际上是调用 createnewchange 的函数接口
- `createnewchange` 创建 change ，并调用 docreatenewchange
- `enable()` 使当前节点可用，本质上是 

<br/>

<br/>

<br/>

# publisher_listener

继承自datawriterlistener

<br/>

<br/>

<br/>

# datawriter_listener

不继承任何class

<br/>

<br/>

<br/>

# datawriter_history

继承自 RTPS::writerhistory

<br/>

## member
`historyqospolicy`

- 继承自 QosPolicy ，用来实现 qos 策略中的 history
- 有两个属性： historyqospolicykind 和 depth

`resourcelimitqospolicy`

- 继承自 QosPolicy ，用来实现 qos 策略中的 resource_limits
- 有五个属性：巴拉巴拉....

`topicattributes` ，在 rtps 层记录 topic 的相关属性

`map<instancehandle, datawriterinstance>`

- 对于 writer 来说，他要将数据写给对应的实例，因此需要将数据根据不同的实例来进行存储
- 其中 instancehandle 可以认为是实例 id
- 而 datawriterinstance ，比较重要的：
  - `vector<shared_ptr<RTPS::cachechange>>` 存放每条cachechange

<br/>

<br/>

<br/>

# 总结

一条数据是如何发送的，只从 datawriter 的角度来说
- datawriter::write(T& data) ->
- datawriter::CreateNewChange() ->
- datawriter::docreatenewchange() ->
- datawriterhistory::addpubchange() ->
- -------分割线，上面都是 DCPS 层的内容-------
- writerhistory::AddChange() ->
- writerhistory::add_change() ->
- writerhistory::unsentchangeaddedtohistory()
  - to read list:it seems that like callback for writer for rtps.
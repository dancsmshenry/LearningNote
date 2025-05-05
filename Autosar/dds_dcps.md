# DCPS（Data-Centric Publish-Subscribe）

DCPS的模型主要分为五大模块：

domain module（域模块）

- 域模块：DomainEntity，DomainParticipant，充当DDS服务的入口/也是DDS服务的其他实体的容器

infrastructure module（基础设施模块）
- 基础设施模块：QosPolicy，Entity，StatusCondition，WaitSet以及Listenser，定义抽象类和其他模块细化的接口

publication module（发布模块）
- 发布模块：Publisher，DataWriter及相关Listener类，实现发布端所需的接口

subscription module（订阅模块）
- 订阅模块：Subscriber，DataReader及相关Listener类，实现订阅端所需的接口

topic-definition module（话题模块）
- 话题模块：Topic，Data，与应用程序定义的Data关联（比如说控制一些QoS的策略）


![](../../image/DCPS 架构.png)

<br/>

<br/>

<br/>

# 对 DCPS 的理解

分为两部分：Domain 和 Entity

Domain是之前说过的域的概念，而Entity则是实体，上述所有的实例对象都会继承这个Entity

Entity是一个抽象实体，会让所有的派生类都继承它，并支持以下特性：
- QoS策略
- Listener，监听器，异步的；可以通知数据是否到达
  - 还可以加一个stateconditions，当到某个条件的时候，就要执行某个时间，这里是同步的



# domain module

# domain_participant

继承自 entity

- `domain_id`
- `participant_id`
- `domain_participant_qos`
- `domain_participant_listener`
- `rtps_participant`
- `map<string, weak_ptr<topic>> topics_`（存放 topic）
- `map<instancehandle, weak_ptr<publisher>> publishers_`（存放 publisher）
- `map<instancehandle, weak_ptr<subscriber>> subscribers_`（存放 subscriber）
- `default_publisher_qos`（pub 端默认的 qos）
- `default_subscriber_qos`（sub 端默认的 qos）
- `builtin_subscriber_`
- `builtin_publisher_`
- `map<string, shared_ptr<topic>> builtin_topics_`（存储当前 domain_participant 中所有的 builtin topics）

<br/>

<br/>

<br/>

# domain_participant_factory

单例模式

- `map<domainid, vector<weak_ptr<domainparticipant>>> participants_` 存放每个 domain 里面的 participant
- `map<domainid, shared_ptr<rtps::domain>> rtps_domains_` 将 DCPS 的 domain 和 RTPS 的 domain 进行映射
- `domain_participant_factory_qos`
- `domain_participant_default_qos`

<br/>

<br/>

<br/>

# domain_participant_listener

继承自 publisherlistener，subscriberlistener，topiclistener

<br/>

# publication module

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



# subscription module

# subscriber

## number

`domainparticipant* participant_` 指向 participant 的指针

`subscriberqos qos_` sub 端的 qos 策略

`map<string, vector<weak_ptr<datareader>>> readers_` 存放不同 topic 下的 datareader

`subscriberlistener`

`map<string, shared_ptr<datareader>> builtin_readers_` 存放内置 topic 的 datareader

- 每个 builtin topic 都只有一个DR

`default_datareader_qos` （每个DR都有会默认的 qos）

<br/>

## function

`enable()` 循环调用 readers_ 的 enable

`disable()` 循环调用 readers_ 的 disable

setqos：判断是否符合切换qos的要求；并且会更新其下面所有topic中所有的DR的qos

`shared<DataReader> createdatareader` 根据对应的 reader_qos， topic 和 listener 生成对应的 reader

`notifydatareaders()`

<br/>

<br/>

<br/>

# datareader

继承自 DomainEntity

<br/>

## number

`subscriber*` 指向 sub 端的指针

`shared_ptr<rtps::reader>` 对应 `RTPS` 的 reader

`shared_ptr<topicdescription>` 存放 topic 的相关信息

- 至于为什么在 datawriter 端存放的是 topic ，因为 topic 是继承自 domainentity 和 topicdescription 的
- 并且 topicdescription 是一个虚基类，因此这里必定是父类指针指向子类指针
- 那如何找到其对于的 qos ，我理解就是它有个接口 getparticipant ，可以找到对应的 participant ，从而找到真正的 topic ，也就找到了其 qos 

`shared_ptr<rtps::readerHistory>` 存放 cachechange

- 感觉是代码没写完，因为对应的 writer 在上层新建了一个 DataWriterHistory ，继承自 rtps::WriterHistory

`shared_ptr<innerreaderlistener>`，有一个指向 datareader 的指针

`shared_ptr<DataReaderListener>`

`DataReaderQos qos_`  DR 端的 qos

`Guid guid_` 全局 id

<br/>

## function

`enable()` 在内部组装 rtps::reader 的属性，涉及到一些底层的 qos 策略



# topic module

# topic_description

string `topic_name` topic的名字

string `type_name`

<br/>

<br/>

<br/>

# topic

继承自 **domain_entity** 和 **topic_description**

domainparticipant* 指向参与者的指针

topicqos 当前 topic 的 qos

shared_ptr<topiclistener>

<br/>

<br/>

<br/>

# typesupport

继承自 enable_shared_from_this，表示可以将当前类作为共享指针在其成员函数内使用

<br/>

<br/>

<br/>

# topic_type

string `topic_type_name` topic 的类型

<br/>

<br/>

<br/>

# topic_listener

topic 的 listener

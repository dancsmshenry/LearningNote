---
title: DDS 协议详解
top: false
cover: false
toc: true
mathjax: true
date: 2025-03-13 21:48:57
password:
summary:
tags:
categories:
---



# 常用缩写

| 缩写                                  | 全称                            |
| ------------------------------------- | ------------------------------- |
| Real-Time Publish Subscribe           | RTPS 实时发布订阅协议           |
| Globally Unique Identifier            | GUID 全局唯一标识符             |
| Participant Discovery Protocol        | PDP 参与者发现协议              |
| Endpoint Discovery Protocol           | EDP 端点发现协议                |
| Simple Participant Discovery Protocol | SPDP 简单参与者发现协议         |
| Simple Endpoint Discovery Protocol    | SEDP 简单端点发现协议           |
| Data-Centric Publisher-Subscriber     | DCPS 以数据为中心的发布订阅模型 |
| Quality of Service                    | QoS 服务质量                    |
| Topic                                 | 主题                            |
| Publisher                             | 发布者                          |
| Subscriber                            | 订阅者                          |
| DataWriter                            | 数据写入者                      |
| DataReader                            | 数据接收者                      |

<br/>

<br/>

<br/>

# DCPS

## Domain

包含了 domainparticipant，是服务的入口，是许多类的工厂，也是其他对象的容器

<br/>

## Infrastructure

包含了一些基本类型和抽象类，比如 condition，qos 等

<br/>

## Publication

发布模块，包含了 publisher 和 datawriter，publisherlistener 和 datawriterlistener

<br/>

## Subscription

<br/>

## Topic

<br/>

<br/>

# RTPS

## Structure module

主要介绍了 rtps 层的各个 entity，并且会与上层 dcps 中各个实体进行映射

<br/>

## Message module

主要介绍了一条消息的各个组成，比如说 submessage 的 submessageheader，submessageelement

<br/>

## Behavior module

主要介绍了一条消息的传递中，各个接口是如何做关联的，以及 stateless 和 stateful。同时介绍了消息的分片，wlp 保活机制

<br/>

## Discovery module

主要介绍了端点和参与者的发现机制

分为两个部分：Participant Discovery Protocol （PDP）和 Endpoint Discovery Protocol（EDP），两个协议本质上是相互独立的

PDP 协议是用于在网络总线上，帮助两个参与者进行相互发现的。二者相互发现成功后，使用 SEDP 交换持有的 endpoint 信息

在 rtps 层，有四个内置的 topic，dcpsParticipant, dcpsSubscription, dcpsPublication, dcpsTopic，其中都有对应的 datawriter 和 datareader；内置的 writer 和 reader，是用来发布一些 detail 信息的

其中的 dcpsParticipant 是用来做 participant 的相互发现的，也就是 spdp。而后的 dcpsSubscription，dcpsPublication 和 dcpsTopic 是用来做 sedp 的，也就是 本地的 topic，reader 和 writer 的相互发现

对于每个参与者，都会创建两个内置的 endpoint，SPDPbuiltinParticipantWriter 和 SPDPbuiltinParticipantReader。对于 writer 来说，里面始终只有一条 change，记录的是当前 participant 的一些配置属性，一旦有发生变化，则会有新的 change 替换



# DDS 基本概念

可以理解为发布者是一个报社，订阅者是读者，话题是邮局。

这种中间件就是建立了发布者和订阅者的模型；会使得发送者和接收者之间的关系非常的松散，即发送者不需要管接收者在哪儿，接收者也不需要管理发送者在哪儿

发送者和接收者只需要知道各自的 Topic 即可，然后通过 Topic 进行通信，就行了

Topic 的存在，就是为了适应发布订阅的模式

<br/>

## Domain

域代表的是一个通信平面，由一个 uid 作为唯一的标识

只有在同一个域内的实体才可以进行通信；不同域之间的实体是不可以进行通信的

<br/>

## Domain Participant

域参与者，表示域中通信者的成员

<br/>

## Topic

对数据的一个抽象的概念，由一个 name（string）进行标识

如果将车内所有的 Topic 聚集在一起，就形成了一个虚拟的全局数据空间

<br/>

## Publisher

发布者，用于发布 Topic 数据，将数据发送至 Topic 中

至少与一个 DataWriter 进行关联，通过调用 DataWriter 的某些函数，将数据发送出去

<br/>

## DataWriter

真正去实现发布动作的端点，会将数据从应用层，写入到网络上

<br/>

## Subscriber

订阅者，可以理解为是数据的接收者，会与底层的 DataReader 进行关联

<br/>

## DataReader

真正去实现读取数据的端点，会将数据从传输层传给应用层

<br/>

<br/>

<br/>

# DCPS 模型

DCPS（数据中心发布订阅）模型将 DDS 分为五大模块：

The Infrastructure（基础设施）Module

The Domain（域） Module

The Topic-Definition （话题） Module

The Publication （发布） Module

The Subscription （订阅） Module

![](/Users/hengrui.shen/Code/learning_note/Autosar/image/DCPS 模型.png)

<br/>

<br/>

<br/>

# RTPS 基本概念

**R**eal-**T**ime **P**ublish **S**ubscribe，实时发布订阅协议

RTPS 主要分为四个模块：

- structure module（结构模块）

- message module（消息模块）

- behavior module（行为模块）

- discovery module（发现模块）

<br/>

<br/>

<br/>

# DDS 的用途

在 dds 中传输的数据一般有以下几种类型：

周期性数据（periodic）：可能是持续不断发生的传感器数据，数据定期更新，可能有多个 sub 端接收同一个 topic 的数据，可能要求出现故障也可以及时的恢复数据（比如 camera）

状态和位置数据（state and states）：偶尔会发生变化的连续数据，新加入网络的数据需要获取最后发布的数据以明确当前的状态和位置信息（比如 GPS）

时间和命令（events and commands）信令，需要高可靠性

![](/Users/hengrui.shen/Code/learning_note/Autosar/image/dds各层的交互关系简图.png)

应用程序将数据对象（Data object）传递给DCPS层

DCPS层通过历史缓存将数据传递给RTPS层

RTPS层以RTPS消息的形式将序列化后的数据传输给UDP/IP协议栈传输

<br/>

- historycache是DCPS层与RTPS层之间交互接口的一部分
- 在写入者端，它包括数据对象变更的部分历史记录
- 在读取端，它包括可存储的部分数据对象变更
- historycache的内容取决于DDS QOS策略以及读取者的通信状态



# qos

# Quality of Service

目前有22个服务策略，有些策略是专门为不同的 entity 专门设计的，比如这里的第二个和第三个就是专门为 DataReader 设计的

<br/>

![](/Users/hengrui.shen/Code/learning_note/Autosar/image/QoS.png)

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
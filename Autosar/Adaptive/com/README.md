# 服务接口的组成

Method（是由服务器提供的功能**接口**；客户端通过RPC或IPC的方式使用这些方法），主要分为以下两类

- request response
- fire and forget

Event（是某类时间发生时由服务器产生并发送的**数据**）
- 客户端需要订阅才能收到event的数据
- 服务器可一次向多个客户端发送event
- 是没有初始值的

Field（表示实体当前处于某种状态）
- 客户端可向服务器订阅field改变的通知
- 服务器可一次向多个客户端发送event
- field有初始值且在服务有效期间**一直存在**
- field有getter和setter方法

<br/>

<br/>

<br/>

com组件主要是用于实现应用程序之间面向服务的通信
- 我的理解就是用于解决ara上层中，不同app的通信（无论是同一个process还是不同process的）



- com 组件负责建立和管理上层应用之间的通信，包括远程应用和本地应用
- 它作为基础设施，能够建立在不同机器上的，AutoSar ap 应用的通信
- com 的文档，包含的是各个 API 用途规范，其提供的功能，以及 API 与其中各个模型之间的关系
- com 组件分为以下几个部分：
  - 语言绑定 language binding
  - 端到端信息传递的安全保护机制 end-to-end communication protection
  - 网络绑定 communication/network binding
  - 交流管理软件 communication management software



# Network binding

## DDS

### 服务发现模块

- 需要给服务实例分配一个DomainParticipant

- 需要为每一个event中的服务接口中的VariableDataPrototype分配一个DDS topic和DDS DataWriter

- 需要分配一个DDS request topic（请求主题）和DDS reply topic（回复主题），并为之创建相应的DDS datawriter和DDS datareader（我理解，主要是为了实现com组件中event及rpc的概念）

<br/>

- domainparticipant的域id来自manifest，其中


- Publisher和Subscriber对象可以跨服务实例提供的事件和其他资源重用；因此，在封闭的域名参与者（domainparticipant）被销毁之前，不得将其移除。
- subscribe


笔记

- 前端和后端，各有自己的骨架和代理
- 无论是someip还是dds，前端都是一样的（配置文件），解析了这个配置文件后，后面的后端代码是不一样的。
- 前端定义基本的数据类型



理解SOA之前必须要了解RPC的调用过程

- 因为是调用远端的函数，和调用本地函数不同的地方就是，我们其实是不知道这个函数名字是什么（比如说我想要调用cpp client的函数sum，但是我们都知道cpp编译运行时会给函数名加上一些前缀，更有甚者还包括很多同名函数的重载），因此需要在本地存储对端函数的映射id，以便调用（至于这里如何存储，就会涉及到服务的发现注册，看了下互联网的主要实现是有一个中心化的注册中心，客户端定期向这个注册中心获取服务端的信息；而汽车电子这一块主要是利用底层的SPDP和SEDP来实现服务的发现，唉，也就是广播自己，然后每个人都在本地存储新节点的信息，需要用到它的时候再调用）
- 要传入的参数是什么，比如说我们可能向函数传入自定义的结构体，但还是那个问题，不同语言如何对该数据进行读取，就我怎么知道你传过来的数据是啥，也就是说需要对数据的格式进行限定和说明（有点接近protobuf了，但是protobuf更加优秀，它深知网络传输中数据传输的消耗，因此使用特定算法对数据进行序列化，降低传输时的损耗）
- 最后就是网络模型的探讨了，即网络库的实现，以及IO的优化


SOA

- 如何确定服务B是否运行（如何在网络中发现对应的服务）
- 如何确定服务B正确的运行
- 如何发现服务B的位置（是在同一个主机上（IPC），还是不同主机上（DDS，SOME/IP）；比如说我们如何知道服务B的ip、端口以及所用的传输协议）

<br/>

- 这里对rpc的返回内容，需要包含是对哪个进程的返回，是对进程中哪个函数服务的返回，再加上具体的返回值

<br/>

- 如果每一个函数我们都作为一个服务，那么整个系统中服务之间的依赖关系就会变得复杂，不好维护
- 因此才会有我们之前说的，多个event、method都挂靠在同一个服务下

<br/>

# COM 组件

服务之间是松耦合的，需要被发现才能够使用；服务是可重用的

接口和协议的实现与语言无关

服务接口的组成：method event field

服务接口的组成：majorversion minorversion，主版本更新表示不兼容的升级；此版本更新表示向后兼容的升级

对于 event，客户端需要订阅才能够收到 event；服务器可以一次向多个 client 发送 event

Event 没有初始值，而 field 有初始值

采用面向服务的通信架构，可以在进程内，同一个 machine 的进程间以及不同 machine 的进程间

使用了 proxy/skeleton 模式

## Com 的组成

E2E 通信保护（在传输的数据前加上E2E的头保护，保证数据的可靠传输）

Com api 的 c++11 的绑定

## 其他

当服务暂时失效时，客户端不需要释放 proxy 实例

等到实例恢复后，proxy自动恢复连接

## 网络绑定

some/ip 服务发现，payload 数据的序列化

Ipc 通信协议，进程间通信

Dds 发布订阅体系，以数据为中心

S2S 信号和服务之间相互转换，实现 ap 和 cp 之间的通信

Com 组件支持多重网络的动态部署

## 动态部署

InstanceIdentifier：对于某个服务，针对某个具体的网络绑定层做出实例化部署

InstanceSpecifier：对于某个服务，在多个网络绑定层做出部署，或者是一个服务在同一个网络绑定下同时部署多个实例

## Comdeamon

Com 的一个平台级应用程序，支持 some/ip 以及 ipc 的绑定，处理 some/ip-sd 的消息传输，路由 some/ip 消息给感兴趣的应用程序
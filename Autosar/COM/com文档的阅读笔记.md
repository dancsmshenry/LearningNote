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
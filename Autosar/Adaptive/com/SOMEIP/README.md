在理解了someip基本的method，event，group，field，sd协议等基本概念之后

就需要理解它的网络绑定是如何实现的了

看了 someip 的 toml 文件之后，发现在当前的一个配置文件中，是可以同时部署多个不同的服务的

PS：本次分析基本是参考 someip 中的 proxy 端进行分析的

因此，就出现了 proxyfactorymap ，其中的数据结构 `std::unordered_map<com::ServiceIdentifier, com::proxy::ProxyFactory*>` ，就是用来存储不同服务对应的代理工厂

这里用到的是多态，即 proxyfactory 父类指针指向子类对象

而代理工厂就是用来生成对应的服务实例



Scalable Service-Oriented MiddlewarE over IP

采用 C/S 架构，由 client 和 server 组成，各节点的通信数据被封装成服务进行通信
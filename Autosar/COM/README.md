服务接口的组成
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
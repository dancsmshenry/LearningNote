# 基本概念

**S**calable Service-**O**riented **M**iddlewar**E** over **IP**

<br/>

# 通用 Header

2 字节的 service id，表示当前报文是属于什么服务的。

2 字节的 method id，其最高位为 0 表示的是 method，最高位为 1 表示为 event 或者 notification。

<br/>

4 字节的 length，表示除去包头之后，还有多少的数据。

<br/>

2 字节的 client id，表示请求的 client 是哪一个。

2 字节的 session id，表示该请求是当前 client 的哪一次请求。

<br/>

1 字节的 Protocal Version，表示当前SOME/IP协议的版本号。

1 字节的 Interface Version，表示接口版本号。

1 字节的 message type，表示当前的报文类型。

1 字节的 return code

<br/>

# sd 协议

## header

和通用的 header 是一样的结构，但是其中的报文内容是固定的

Message ID 固定为 FFFF 8100。

Length 与一般的无异。

<br/>

ClientId 与一般的无异。

SessionID 在初始化配置为 1，每发送一次数据就加一。

<br/>

Protocal Version 固定为 0x01。

Interface Version 固定为 0x01。

Message Type 固定为 0x02。

Return Code 固定为 0x00。

<br/>

## Body

任意数量的 entry，表示对于某个服务，当前的节点是 find，offer 还是 stopoffer
# Computer-Networks

This is depository which records the notes of computer network and some personal opinions.



## books

- UNIX Network Programming Volume 1
- TCP & IP ILLustrated Volume 1 The Protocols
- Computer Networking: A Top-Down Approach



## audition experience

TCP

- 报文的基本内容
- ISN是否是固定的
- 三次握手和四次挥手的基本内容
- 为什么TIME_WAIT状态需要经过2MSL才能返回到CLOSE状态
- 为什么四次挥手释放连接时，需要等待2MSL
- 为什么要四次挥手，三次握手
- 三次握手的过程中可以携带数据吗
- 全连接和半连接队列
- 滑动窗口、超时重传的基本概念
- RTO，RTT
- 解释拥塞控制的四大算法（满开始，拥塞避免，快重传，快恢复）
- 为什么快速重传是重复发送3次ack
- tcp与udp的区别（从整个流程谈起）
- tcp如何保障可靠传输（从tcp的整个传输流程讲起：确认和重传，数据校验，数据合理分片和排序，流量控制，拥塞控制）
- 发生粘包、拆包的时候如何处理
- 建立tcp连接的服务器和客户端的系统调用（bind，listen，accept，connect）
- SYN攻击
- TCP的四个计时器
  - 重传/持续/保活/时间等待
- TCP4次挥手每次丢失后会发生什么



others

- cmd中的ping一下的工作原理





## Open System Interconnection

- 物理层
- 数据链路层
- 网络层
- 传输层
- 会话层
- 表示层
- 应用层

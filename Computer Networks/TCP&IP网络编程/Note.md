# 第一章 理解网络编程和套接字

## 1.1 理解网络编程和套接字

- 调用socket函数（安装电话机，创建套接字）

  - ```c
    #include <sys/socket.h>
    int socket(int domain, int type, int protocol);
    ```

- 调用bind函数（分配电话号码，分配IP地址和端口号）

  - ```c
    #include <sys/socket.h>
    int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
    ```

- 调用listen函数（连接电话线，监听端口，转为可接听状态）

  - ```c
    #include <sys/socket.h>
    int listen(int sockfd, int backlog);
    ```

- 调用accept函数（拿起话筒，接收对方的连接请求）

  - ```c
    #include <sys/socket.h>
    int accept(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
    ```

- 客户端：调用socket函数和connect函数，与服务器段共同允许以收发字符串数据

- 服务端：调用socket，bind，listen，accept，write函数

- 打开文件的函数

  - ```c
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    
    int open(const char *path, int flag);
    ```

- 关闭文件的函数

  - ```c
    #include <unistd.h>
    
    int close(int fd);
    ```

- 写入数据的函数

  - ```c
    #include <unistd.h>
    
    ssize_t write(int fd, const void* buf, size_t nbytes);
    ```



# 第二章 套接字类型与协议设置

## 2.1 套接字协议及其数据传输特性

- ```c
  #include <sys/socket.h>
  int socket(int domain, int type, int protocol);
  /**
  //domain 套接字中使用的协议族信息
  //type 套接字数据传输类型信息
  //protocol 计算机间通信中使用的协议信息
  
  //domain 协议族类型
  //PE_INET IPV4互联网协议族
  //PE_INET6 IPV6互联网协议族
  //PE_LOCAL 本地通信的UNIX协议族
  //PE_PACKET 底层套接字的协议族
  //PE_IPX IPX Novell协议族
  
  //Type 套接字类型
  1、面向连接的套接字（SOCK_STREAM）
  把所有的数据都接收完了再一起接收（到了但是没有接收的数据会放到缓冲数组）
  特点：传输过程中数据不会消失，按序传输数据，传输的数据不存在数据边界
  补充：传输出错会重传，缓存满了就先read一部分；套接字连接必须一一对应
  总结：可靠的，按序传递的、基于字节的面向连接的数据传输方式的套接字
  2、面向消息的套接字（SOCK_DGRAM）
  特点：快速传输；数据可能丢失损毁；数据有边界；限制每次传输的数据的大小
  总结：不可靠的、不按序传递的、以数据的高速传输为目的的套接字
  
  //
  **/
  ```



# 第三章 地址族与数据序列

## 3.1 分配给套接字的IP地址与端口号

- IP地址分为两种：IPv4（4字节），IPv6（16字节）
- 数据是先传入路由器的
- 网络地址分类与主机地址边界：A、B、C类地址
- 用于区分套接字的端口：可分配的端口号范围0-65535，但0-1023是知名端口



## 3.2 地址信息的表示

- ```c
  struct sockaddr_in{//表示IPv4地址的结构体
      sa_family_t sin_family;//地址族
      uint16_t sin_port;//16位TCP/UDP端口号
      struct in_addr sin_addr;//32位IP地址
      char sin_zero[8];//不使用
  }
  /**
  //sin_family
  AF_INET IPv4网络协议中使用的地址簇
  AF_INET6 IPV6网络协议中使用的地址簇
  AF_LOCAL 本地通信中采用的UNIX协议的地址簇
  
  //sin_port
  保存16位端口号
  
  //sin_addr
  保存32位IP地址信息
  
  //sin_zero
  **/
  ```



## 3.3 网络字节序与地址变换

- 背景：不同CPU中，4字节整数型值1在内存空间的保存方式是不同的，比如1，可以顺序保存也可以倒序保存
- CPU向内存保存数据的方式：大端序（高位字节存放到低位地址），小端序（高位字节存放到高位地址）
- 比如数字1234567：
  - 大端：从左往右写，1234567（地址：0x20，0x21，0x22，0x23）
  - 小端：从右往左写，7654321（地址：0x20，0x21，0x22，0x23）
- 网络字节序统一为大端序



## 3.4 网络地址的初始化与分配

- 网络地址初始化

- ```c
  struct sockaddr_in addr;
  char *serv_ip = "211.217.168.13";//声明IP地址字符串
  char *serv_port = "9190";//声明端口号字符串
  memset(&addr, 0, sizeof(addr));//结构体变量addr的所有成员初始化为0
  addr.sin_family = AF_INET;//指定地址族
  addr.sin_addr.s_addr = inet_addr(serv_ip);//基于字符串的IP地址初始化
  addr.sin_port = htos(atoi(serv_port));//基于字符串的端口号初始化
  ```

- 



# 第四章 基于TCP的服务器/客户端（1）

## 4.1 理解TCP和UDP

- 应用层->TCP/UDP层->IP层->链路层
- 链路层：负责物理连接，两台主机通过网络进行数据交换
- IP层（网络层）：面向消息的、不可靠的协议（数据不是一次性直接传入目标主机的，而是由路由器转接的），解决数据传输中的路径选择问题
- TCP/UDP层（ 传输层）：通过传输层（TCP）来保证数据的可靠传入
- 应用层：在套接字通信过程中，上述的过程都是自动处理的，选择数据传输路径、数据确认过程都被隐藏到套接字内部



## 4.2 实现基于TCP的服务器端/客户端

- TCP服务器端的默认函数调用顺序
  - socket()（创建套接字）
  - bind()（分配套接字地址）
  - listen()（等待连接请求状态）
  - accept()（允许连接）
  - read()/write()（数据操作）
  - close()（断开连接）
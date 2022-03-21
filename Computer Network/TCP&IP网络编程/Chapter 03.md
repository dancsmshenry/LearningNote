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
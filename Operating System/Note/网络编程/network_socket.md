```cpp
#include <sys/types.h>
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```

- domain：协议族，常用的协议族有，AF_INET、AF_INET6、AF_LOCAL(或称AF_UNIX，Unix域socket）、AF_ROUTE、PF_PACKET等等。协议族决定了socket地址的类型，在通信中也必须使用对应的协议类型，比如AF_INET就决定了要用ipv4地址(32位)，AF_UNIX决定了要用一个绝对路径名作为地址
- type: 指定socket类型，常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等
- protocol: 指定协议，常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC、ETH_P_ALL等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议。当protocol为0时，会自动选择type类型对应的默认协议



https://zhuanlan.zhihu.com/p/458414504
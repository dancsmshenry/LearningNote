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

- dd
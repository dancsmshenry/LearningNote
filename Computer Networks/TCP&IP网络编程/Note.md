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



# 第十章 多进程服务端

## 10.2 进程和僵尸进程

- 僵尸进程的定义：进程完成工作后（执行完main函数中的程序后）应被销毁，但有时这些进程将变成僵尸进程，占用系统中的重要资源

- 产生僵尸进程的原因

  - 传递参数并调用exit函数和饥饿main函数中执行return语句并返回值都会传递给操作系统，但是操作系统不会销毁子进程
  - 只到把这些值传递给产生该子进程的父进程，操作系统才会销毁子进程（只有父进程主动发起请求时，操作系统才会传递该值）

- 僵尸进程的销毁

  - 应该向创建子进程的父进程传递子进程的exit参数或return语句的返回值
  - 如果父进程为主动要求获得子进程的结束状态值，操作系统将一直保存，并让子进程长时间处于僵尸进程

- 销毁僵尸进程的方法

  - 1、利用wait函数

  - ```c
    #include <sys/wait.h>
    
    pid_t wait(int* statloc);//成功时返回终止的子进程ID，失败时返回
    //调用wait函数时，如果没有已终止的子进程，那么程序将阻塞直到有子进程终止
    
    //调用此函数时，如果已有子进程终止，那么子进程终止时传递的返回值（exit函数的参数值，main函数的return返回值）将保存到该函数的参数所指内存空间
    ```
    
  - 2、使用waitpid函数
  
  - ```c
    #include <sys/wait.h>
    
    pid_t waitpid(pid_t pid, int* statloc, int options);
    //pid，等待终止的目标子进程的ID，若传递-1，则与wait函数相同，可以等待任意子进程终止
    //statloc，与wait函数的statloc参数具有相同含义
    //options，传递头文件中声明的常量WNOHANG，即使没有终止的子进程也不会进入阻塞状态，而是返回0并退出函数
    
    //调用waitpid不会使程序阻塞
    ```



## 10.3 信号处理

- 





# 第十八章 多线程服务器端实现

## 18.2 线程创建及运行

- ```c
  #include <stdio.h>
  #include <unistd.h>
  #include <pthread.h>
  void* thread_main(void *arg);
  
  int main(int argc, char *argv[]){
          pthread_t t_id;
          int thread_param = 5;
  
          if (pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0){
                  puts("pthread_create() error!");
                  return -1;
          };
          sleep(10);//上面再遍历过线程函数以后，是一边执行线程，一边执行主函数的（所以如果sleep的参数变为了2，就无法执行完这个线程的）
          puts("end of main");
          return 0;
  }
  
  void* thread_main(void *arg){
          int i;
          int cnt = *((int*)arg);
  
          for (i = 0; i < cnt; i ++ ){
                  sleep(1);
                  puts("running thread");
          }
          return NULL;
  }
  
  ```

- ```c
  #include <pthread.h>
  
  int pthread_create(pthread_t* restrict thread, const pthread_attr_t* restrict attr, void*(* start_routine)(void*), void* restrict arg);
  
  //thread 保存新创建线程ID的变量地址值，线程与进程相同，也需要区分不同线程的ID
  //attr 用于传递线程属性的参数，传递为NULL时，创建默认属性的线程
  //start_routine 相当于线程main函数的、在单独执行流中执行的函数地址值（函数指针）
  //arg 通过第三个参数传递调用函数时包含参数信息的变量地址值
  ```

- ```c
  #include <pthread.h>
  
  int pthread_join(pthread_t thread, void** status);
  //thread 该参数值ID的线程终止后才会从该函数返回
  //status 保存线程的main函数返回值的指针变量地址值
  /*
  调用该函数的进程（或线程）将进入等待状态，直到第一个参数为ID的线程终止为值，而且可以得到线程的main函数返回值
  */
  ```

- 根据临界区是否引起问题，函数可分为以下2类：

  - 线程安全函数：被多个线程同时调用时也不会引发问题
  - 非线程安全函数：被同时调用时会引发问题

- 线程安全函数的名称后缀一般加上_r

- 多线程访问同一个全局变量会出问题的



## 18.3 线程存在的问题和临界区

- 多个线程改变全局变量的情况，有可能是说，第一个复制数据进行修改，然后在第一个还在修改数据的过程中，第二个线程可能会也会修改这个值，但是此时的值还是原来的，即如果想要的是第二个线程修改的是第一个线程修改后得到的值的话，就会出现问题
- 两条不同的语句由不同线程同时执行时，可能构成临界区（访问同一内存空间）



## 18.4 线程同步

- 需要同步的情况：
  - 同时访问同一内存空间时发生的情况
  - 需要指定访问同一内存空间的线程执行顺序的情况
- 互斥量
  - 表示不允许多个进程同时访问，主要用于解决线程同步访问的问题
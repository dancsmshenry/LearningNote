- ```cpp
  int connect(int socket, const struct sockaddr *address, socklen_t address_len);
  ```



udp是可以调用connect的

而tcp的connect是在第二次握手的时候返回的（因此调用connect会触发三次握手）

而对于udp，只会将调用connect将对端的ip和port记录下来

UDP中可以多次调用connect

TCP只能调用一次connect

UDP多次调用connect有两种用途:

1,指定一个新的ip&port连结

2,断开和之前的ip&port的连结.指定新连结,直接设置connect第二个参数即可.断开连结,需要将connect第二个参数中的sin_family设置成 AF_UNSPEC即可.



# 参考

https://blog.csdn.net/weixin_30315507/article/details/114008133

https://zhuanlan.zhihu.com/p/380109394

https://zhuanlan.zhihu.com/p/459771034
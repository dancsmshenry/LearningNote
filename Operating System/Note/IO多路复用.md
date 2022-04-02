# Epoll

### 内部结构

- 用一个红黑树记录添加的socket，用一个双向链表接收内核触发的事件

- 是系统级别的支持

- ```cpp
  struct eventpoll {
      struct rb_root rbr;//红黑树的根节点，这棵树中存储所有添加到epoll中的需要监控的事件
      struct list_head rdlist;//双向链表中存放着将要通过epoll_wait返回给用户的满足条件的事件
  };
  ```

- 为什么支持百万句柄

  - 不用重复传递，调用epoll_wait时相当于以往调用

- 为什么用红黑树

  - 早期使用hashmap效率高，但是内存空间占用大，就改为了红黑树
  - 同时kernel中有现有的rbtree，而没有通用的hashtable



# Select



# Poll



- 



# 
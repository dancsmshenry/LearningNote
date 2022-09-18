# 函数原型

- ```cpp
  #include <sys/types.h>
  #include <sys/socket.h>
  int listen(int sockfd, int backlog);
  //	sockfd是前面socket得到的fd
  //	backlog：在tcp三次握手的时候，第一次握手发送SYN=1的，server端接收到之后，在回复了Ack=1之后，会把这个还未完成3次握手的连接放入到一个队列中，这个队列需要指定一个长度，该参数就是用来指定这个半连接队列长度的，在linux中该参数默认值由cat /proc/sys/net/ipv4/tcp_max_syn_backlog决定
  
  #cat /proc/sys/net/ipv4/tcp_max_syn_backlog
  1024
  ```





# 功能

- 将TCP设置为listening状态







# 实现

- 先通过fd找到对应的socket实例，接着调整连接队列的长度（队列长度不能超过进程允许的最大连接数），最后调用inet_listen()函数

- ```cpp
  SYSCALL_DEFINE2(listen, int, fd, int, backlog)
  {
  	return __sys_listen(fd, backlog);
  }
  
  int __sys_listen(int fd, int backlog)
  {
  	struct socket *sock;
  	int err, fput_needed;
  	int somaxconn;
      //	这个函数调用在bind的实现中也存在调用，都是通过fd来找到socket实例
  	sock = sockfd_lookup_light(fd, &err, &fput_needed);
  	if (sock) {
          //	最大连接数和backlog比较，队列长度不能超过进程允许的最大连接数
  		somaxconn = sock_net(sock->sk)->core.sysctl_somaxconn;
  		if ((unsigned int)backlog > somaxconn)
  			backlog = somaxconn;
                  // SELInux相关的处理
  		err = security_socket_listen(sock, backlog);
  		if (!err) // 调用 inet_listen()函数
  			err = sock->ops->listen(sock, backlog);
  
  		fput_light(sock->file, fput_needed);
  	}
  	return err;
  }
  ```





- 判断socket和tcp的状态；设置backlog；调用inet_csk_listen_start

- ```cpp
  const struct proto_ops inet_stream_ops = {
  	.family		   = PF_INET,
  	.owner		   = THIS_MODULE,
  	.release	   = inet_release,
  	.bind		   = inet_bind,
  	.connect	   = inet_stream_connect,
  	.socketpair	   = sock_no_socketpair,
  	.accept		   = inet_accept,
  	.getname	   = inet_getname,
  	.poll		   = tcp_poll,
  	.ioctl		   = inet_ioctl,
  	.listen		   = inet_listen,  // listen在这里
  	.shutdown	   = inet_shutdown,
  	.setsockopt	   = sock_common_setsockopt,
  	.getsockopt	   = sock_common_getsockopt,
  	.sendmsg	   = inet_sendmsg,
  	.recvmsg	   = inet_recvmsg,
          ......
  };
  
  /*
   *	Move a socket into listening state.
   */
  int inet_listen(struct socket *sock, int backlog)
  {
  	struct sock *sk = sock->sk;
  	unsigned char old_state;
  	int err, tcp_fastopen;
  
  	lock_sock(sk);
  
  	err = -EINVAL;
          // socket状态判断 类型判断
  	if (sock->state != SS_UNCONNECTED || sock->type != SOCK_STREAM)
  		goto out;
  
          // TCP的状态判断
  	old_state = sk->sk_state;
  	if (!((1 << old_state) & (TCPF_CLOSE | TCPF_LISTEN)))
  		goto out;
  
  	/* Really, if the socket is already in listen state
  	 * we can only allow the backlog to be adjusted.
  	 */
  	if (old_state != TCP_LISTEN) {
  		/* Enable TFO w/o requiring TCP_FASTOPEN socket option.
  		 * Note that only TCP sockets (SOCK_STREAM) will reach here.
  		 * Also fastopen backlog may already been set via the option
  		 * because the socket was in TCP_LISTEN state previously but
  		 * was shutdown() rather than close().
  		 */ 
                  // TFO（TCP Fast Open）将数据交互提前的相关处理
  		tcp_fastopen = sock_net(sk)->ipv4.sysctl_tcp_fastopen;
  		if ((tcp_fastopen & TFO_SERVER_WO_SOCKOPT1) &&
  		    (tcp_fastopen & TFO_SERVER_ENABLE) &&
  		    !inet_csk(sk)->icsk_accept_queue.fastopenq.max_qlen) {
  			fastopen_queue_tune(sk, backlog);
  			tcp_fastopen_init_key_once(sock_net(sk));
  		}
  
  		err = inet_csk_listen_start(sk, backlog);
  		if (err)
  			goto out;
  		tcp_call_bpf(sk, BPF_SOCK_OPS_TCP_LISTEN_CB, 0, NULL);
  	}
  	sk->sk_max_ack_backlog = backlog;
  	err = 0;
  
  out:
  	release_sock(sk);
  	return err;
  }
  ```



- **core**部分

- 创建连接请求队列；设置tcp状态；判断是否有绑定端口，没有的话就自动绑定一个；将用于listening的socket注册到全局hash表中

- 其中调用了下面的reqsk_queue_alloc函数

- ```cpp
  int inet_csk_listen_start(struct sock *sk, int backlog)
  {
  	struct inet_connection_sock *icsk = inet_csk(sk);
  	struct inet_sock *inet = inet_sk(sk);
  	int err = -EADDRINUSE;
  
          // 创建连接请求的队列
  	reqsk_queue_alloc(&icsk->icsk_accept_queue);
  
          // backlog赋值
  	sk->sk_max_ack_backlog = backlog;
  	sk->sk_ack_backlog = 0; // 初始化计量
  	inet_csk_delack_init(sk);
  
  	/* There is race window here: we announce ourselves listening,
  	 * but this transition is still not validated by get_port().
  	 * It is OK, because this socket enters to hash table only
  	 * after validation is complete.
  	 */
          // 这里TCP状态设置为 TCP_LISTEN
  	inet_sk_state_store(sk, TCP_LISTEN);
          // 判断是否调用过bind绑定port，如果没有则这里自动绑定一个
  	if (!sk->sk_prot->get_port(sk, inet->inet_num)) {
  		inet->inet_sport = htons(inet->inet_num);
  
  		sk_dst_reset(sk);
                  // 处于监听状态的socket注册到全局hash表中(struct inet_hashinfo)->listening_hash
                  // 实际调用的是inet_hash
  		err = sk->sk_prot->hash(sk);
  
  		if (likely(!err))
  			return 0;
  	}
  
          // 处理异常则设置TCP状态为 TCP_CLOSE
  	inet_sk_set_state(sk, TCP_CLOSE);
  	return err;
  }
  ```



- 创建请求队列

- ```cpp
  void reqsk_queue_alloc(struct request_sock_queue *queue)
  {
  	spin_lock_init(&queue->rskq_lock);
  
  	spin_lock_init(&queue->fastopenq.lock);
  	queue->fastopenq.rskq_rst_head = NULL;
  	queue->fastopenq.rskq_rst_tail = NULL;
  	queue->fastopenq.qlen = 0;
  
  	queue->rskq_accept_head = NULL;  // 全连接队列
  }
  ```



- 处于监听状态的socket注册到全局hash表中

- ```cpp
  int inet_hash(struct sock *sk)
  {
  	int err = 0;
  
          // 刚才状态已经是TCP_LISTEN了
  	if (sk->sk_state != TCP_CLOSE) {
  		local_bh_disable();
  		err = __inet_hash(sk, NULL);
  		local_bh_enable();
  	}
  
  	return err;
  }
  
  int __inet_hash(struct sock *sk, struct sock *osk)
  {
  	struct inet_hashinfo *hashinfo = sk->sk_prot->h.hashinfo;
  	struct inet_listen_hashbucket *ilb;
  	int err = 0;
  
          // TCB状态一定是TCP_LISTEN，不满足此条件
  	if (sk->sk_state != TCP_LISTEN) {
  		inet_ehash_nolisten(sk, osk);
  		return 0;
  	}
  	WARN_ON(!sk_unhashed(sk));
  	ilb = &hashinfo->listening_hash[inet_sk_listen_hashfn(sk)];
  	spin_lock(&ilb->lock);
  	if (sk->sk_reuseport) {
  		err = inet_reuseport_add_sock(sk, ilb);
  		if (err)
  			goto unlock;
  	}
          // 加入全局hash表
  	if (IS_ENABLED(CONFIG_IPV6) && sk->sk_reuseport &&
  		sk->sk_family == AF_INET6)
  		__sk_nulls_add_node_tail_rcu(sk, &ilb->nulls_head);
  	else
  		__sk_nulls_add_node_rcu(sk, &ilb->nulls_head);
  	inet_hash2(hashinfo, sk);
  	ilb->count++;
  	sock_set_flag(sk, SOCK_RCU_FREE);
  	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
  unlock:
  	spin_unlock(&ilb->lock);
  
  	return err;
  }
  ```







# 总结

- 设置socket的backlog，并创建半连接队列、全连接队列
- 设置TCP状态为TCP_LISTEN
- 处于监听状态的socket注册到全局hash表中
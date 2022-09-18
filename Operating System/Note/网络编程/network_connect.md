# 函数原型

- ```cpp
  #include <sys/types.h>
  #include <sys/socket.h>
  //	客户端调用
  int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  //	sockfd是socket fd
  //	addr是用来指定服务端的addr地址信息，对这个addr发起连接
  //	addrlen是addr的长度
  ```

- 返回值：成功则返回一个新的fd，这个fd用来和对端进行通信；失败则返回-1，并且设置errno；







# 功能

- 发起连接server操作，在其内部会进行3次握手触发，在**第二次握手成功**就会返回一个fd
- TCP下只能调用一次（TCP调用conncet的作用是开始三次握手）



关于udp的socket编程

- udp的client是可以调用connect的，这里的作用是将对端的ip和port记录下来（因此udp下是可以多次调用conect的）

- 多次调用connect的用途：
  - 指定一个新的ip&port连结
  - 断开和之前的ip&port的连结.指定新连结,直接设置connect第二个参数即可.断开连结,需要将connect第二个参数中的sin_family设置成 AF_UNSPEC即可
  
- udp调用connect的好处：
  - 指明目的地址和端口，可以直接使用send函数发送数据，而不用sendto每次都将数据和地址一同传递（因为sendto传输信息会把地址和端口也附上，存在浪费资源的情况）
  
  - ```cpp
    ssize_t sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
    ```
  
  - 如果调用了connect，内核中就已经维护了一个”连接”，就可以调用send函数来进行发送数据了，内核中维护的这个 连接，包含了 发送端和接收端的地址， 并且永久维护一个数据结构，存储这些地址信息
  
  - 不用connect，kernel每次都可能要做路由查询，connect可以减小这部分开销



- 当一个 UDP socket 去 connect 对端 时，并没有发送任何的数据包，其效果仅仅是在内核建立了一个五元组映射，该映射的作用正是为了和 UDP 带外的 ICMP 控制通道捆绑在一起。当调用了connect之后，内核协议栈就维护了一个从源到目的地的单向连接。当下层有ICMP错误信息返回时，内核就可以根据这个五元组找到是那个UDP socket发的包失败了，进而可以把错误信息传输给该socket，应用程序就可以得到该错误信息了。

  但是对于一个没有connect的udp socket， 内核将数据发出去之后，没有维护五元组，ICMP有错误返回的时候，内核就找不到是哪个 udp socket出的错，所以用户层也就无法收到这个错误信息的。

- 如果不connect的话，那么错误就不会上报（比如说ICMP的报错）








# 实现

- main部分，通过fd找到socket，接着将addr数据拷贝到kernel 空间中，然后调用**__inet_stream_connect**部分

- ```cpp
  SYSCALL_DEFINE3(connect, int, fd, struct sockaddr __user *, uservaddr,
  		int, addrlen)
  {
  	return __sys_connect(fd, uservaddr, addrlen);
  }
  
  int __sys_connect(int fd, struct sockaddr __user *uservaddr, int addrlen)
  {
  	struct socket *sock;
  	struct sockaddr_storage address;
  	int err, fput_needed;
  
      //	通过fd找到socket实例
  	sock = sockfd_lookup_light(fd, &err, &fput_needed);
  	if (!sock)
  		goto out;
      //	addr的数据从用户空间copy到内核空间
  	err = move_addr_to_kernel(uservaddr, addrlen, &address);
  	if (err < 0)
  		goto out_put;
  
  	err =
  	    security_socket_connect(sock, (struct sockaddr *)&address, addrlen);
  	if (err)
  		goto out_put;
      //	这里调用的是inet_stream_connect
  	err = sock->ops->connect(sock, (struct sockaddr *)&address, addrlen,
  				 sock->file->f_flags);
  out_put:
  	fput_light(sock->file, fput_needed);
  out:
  	return err;
  }
  
  const struct proto_ops inet_stream_ops = {
  	.family		   = PF_INET,
  	.owner		   = THIS_MODULE,
  	.release	   = inet_release,
  	.bind		   = inet_bind,
  	.connect	   = inet_stream_connect,  // connect调用这里
  	.socketpair	   = sock_no_socketpair,
          ........
  };
  
  int inet_stream_connect(struct socket *sock, struct sockaddr *uaddr,
  			int addr_len, int flags)
  {
  	int err;
  	
      //	我猜这里要上锁的一个原因可能就是防止多个进程同时对socket进程connect操作
  	lock_sock(sock->sk);
  	err = __inet_stream_connect(sock, uaddr, addr_len, flags, 0);
  	release_sock(sock->sk);
  	return err;
  }
  ```





- 通过状态机根据当前socket的状态进行下一步的操作；设置socket连接的超时时间；同时进行三次握手操作

- ```cpp
  /*
   *	Connect to a remote host. There is regrettably still a little
   *	TCP 'magic' in here.
   */
  //	core代码
  int __inet_stream_connect(struct socket *sock, struct sockaddr *uaddr,
  			  int addr_len, int flags, int is_sendmsg)
  {
  	struct sock *sk = sock->sk;
  	int err;
  	long timeo;
  
  	/*
  	 * uaddr can be NULL and addr_len can be 0 if:
  	 * sk is a TCP fastopen active socket and
  	 * TCP_FASTOPEN_CONNECT sockopt is set and
  	 * we already have a valid cookie for this socket.
  	 * In this case, user can call write() after connect().
  	 * write() will invoke tcp_sendmsg_fastopen() which calls
  	 * __inet_stream_connect().
  	 */
  	if (uaddr) {
  		if (addr_len < sizeof(uaddr->sa_family))
  			return -EINVAL;
  
  		if (uaddr->sa_family == AF_UNSPEC) {
  			err = sk->sk_prot->disconnect(sk, flags);
  			sock->state = err ? SS_DISCONNECTING : SS_UNCONNECTED;
  			goto out;
  		}
  	}
  
      //	socket实例状态判断
  	switch (sock->state) {
  	default:
  		err = -EINVAL;
  		goto out;
  	case SS_CONNECTED:
  		err = -EISCONN;
  		goto out;
  	case SS_CONNECTING:
  		if (inet_sk(sk)->defer_connect)
  			err = is_sendmsg ? -EINPROGRESS : -EISCONN;
  		else
  			err = -EALREADY;
  		/* Fall out of switch with err, set for this state */
  		break;
  	case SS_UNCONNECTED:
  		err = -EISCONN;
  		if (sk->sk_state != TCP_CLOSE)  // TCP初始化状态必须是 TCP_CLOSE
  			goto out;
  
  		if (BPF_CGROUP_PRE_CONNECT_ENABLED(sk)) {
  			err = sk->sk_prot->pre_connect(sk, uaddr, addr_len);
  			if (err)
  				goto out;
  		}
          // 如果使用的是TCP，则sk_prot为tcp_prot，connect为        tcp_v4_pre_connect()
          // 发送第一个SYN包
  		err = sk->sk_prot->connect(sk, uaddr, addr_len);
  		if (err < 0)
  			goto out;
  
  		sock->state = SS_CONNECTING; //	修改socket状态为连接中
  
  		if (!err && inet_sk(sk)->defer_connect)
  			goto out;
  
  		/* Just entered SS_CONNECTING state; the only
  		 * difference is that return value in non-blocking
  		 * case is EINPROGRESS, rather than EALREADY.
  		 */
  		err = -EINPROGRESS;
  		break;
  	}
  
      //	发送超时时间
  	timeo = sock_sndtimeo(sk, flags & O_NONBLOCK);
  
      //	已经发送SYN包，等待3次握手
  	if ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV)) {
  		int writebias = (sk->sk_protocol == IPPROTO_TCP) &&
  				tcp_sk(sk)->fastopen_req &&
  				tcp_sk(sk)->fastopen_req->data ? 1 : 0;
  
  		/* Error code is set above */ // 阻塞等待3次握手完成
  		if (!timeo || !inet_wait_for_connect(sk, timeo, writebias))
  			goto out;
  
  		err = sock_intr_errno(timeo);
  		if (signal_pending(current))
  			goto out;
  	}
  
  	/* Connection was closed by RST, timeout, ICMP error
  	 * or another process disconnected us.
  	 */
  	if (sk->sk_state == TCP_CLOSE)
  		goto sock_error;
  
  	/* sk->sk_err may be not zero now, if RECVERR was ordered by user
  	 * and error was received after socket entered established state.
  	 * Hence, it is handled normally after connect() return successfully.
  	 */
      //	3次捂手成功后修改socket实例状态
  	sock->state = SS_CONNECTED;
  	err = 0;
  out:
  	return err;
  
  sock_error:
  	err = sock_error(sk) ? : -ECONNABORTED;
  	sock->state = SS_UNCONNECTED;
  	if (sk->sk_prot->disconnect(sk, flags))
  		sock->state = SS_DISCONNECTING;
  	goto out;
  }
  ```



- 三次握手实现的main函数

- ```cpp
  struct proto tcp_prot = {
  	.name			= "TCP",
  	.owner			= THIS_MODULE,
  	.close			= tcp_close,
  	.pre_connect		= tcp_v4_pre_connect,
  	.connect		= tcp_v4_connect,
  	.disconnect		= tcp_disconnect,
          ......
  }
  
  /* This will initiate an outgoing connection. */
  //	这个函数主要是发送第一次握手的SYN包
  int tcp_v4_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len)
  {
  	struct sockaddr_in *usin = (struct sockaddr_in *)uaddr;
  	struct inet_sock *inet = inet_sk(sk);
  	struct tcp_sock *tp = tcp_sk(sk);
  	__be16 orig_sport, orig_dport;
  	__be32 daddr, nexthop;
  	struct flowi4 *fl4;
  	struct rtable *rt;
  	int err;
  	struct ip_options_rcu *inet_opt;
  	struct inet_timewait_death_row *tcp_death_row = &sock_net(sk)->ipv4.tcp_death_row;
  
  	if (addr_len < sizeof(struct sockaddr_in))
  		return -EINVAL;
  
  	if (usin->sin_family != AF_INET)
  		return -EAFNOSUPPORT;
  
  	nexthop = daddr = usin->sin_addr.s_addr;
  	inet_opt = rcu_dereference_protected(inet->inet_opt,
  					     lockdep_sock_is_held(sk));
  	if (inet_opt && inet_opt->opt.srr) {
  		if (!daddr)
  			return -EINVAL;
  		nexthop = inet_opt->opt.faddr;
  	}
  
  	orig_sport = inet->inet_sport;
  	orig_dport = usin->sin_port;
  	fl4 = &inet->cork.fl.u.ip4;
  	rt = ip_route_connect(fl4, nexthop, inet->inet_saddr,
  			      RT_CONN_FLAGS(sk), sk->sk_bound_dev_if,
  			      IPPROTO_TCP,
  			      orig_sport, orig_dport, sk);
  	if (IS_ERR(rt)) {
  		err = PTR_ERR(rt);
  		if (err == -ENETUNREACH)
  			IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTNOROUTES);
  		return err;
  	}
  
  	if (rt->rt_flags & (RTCF_MULTICAST | RTCF_BROADCAST)) {
  		ip_rt_put(rt);
  		return -ENETUNREACH;
  	}
  
  	if (!inet_opt || !inet_opt->opt.srr)
  		daddr = fl4->daddr;
  
  	if (!inet->inet_saddr)
  		inet->inet_saddr = fl4->saddr;
  	sk_rcv_saddr_set(sk, inet->inet_saddr);
  
  	if (tp->rx_opt.ts_recent_stamp && inet->inet_daddr != daddr) {
  		/* Reset inherited state */
  		tp->rx_opt.ts_recent	   = 0;
  		tp->rx_opt.ts_recent_stamp = 0;
  		if (likely(!tp->repair))
  			WRITE_ONCE(tp->write_seq, 0);
  	}
  
  	inet->inet_dport = usin->sin_port;
  	sk_daddr_set(sk, daddr);
  
  	inet_csk(sk)->icsk_ext_hdr_len = 0;
  	if (inet_opt)
  		inet_csk(sk)->icsk_ext_hdr_len = inet_opt->opt.optlen;
  
  	tp->rx_opt.mss_clamp = TCP_MSS_DEFAULT;  // 设置协商MSS最大段的值
  
  	/* Socket identity is still unknown (sport may be zero).
  	 * However we set state to SYN-SENT and not releasing socket
  	 * lock select source port, enter ourselves into the hash tables and
  	 * complete initialization after this.
  	 */
  	tcp_set_state(sk, TCP_SYN_SENT);  // TCP状态设置为TCP_SYN_SENT:发送完第一次握手之后
  	err = inet_hash_connect(tcp_death_row, sk);
  	if (err)
  		goto failure;
  
  	sk_set_txhash(sk);
  
  	rt = ip_route_newports(fl4, rt, orig_sport, orig_dport,
  			       inet->inet_sport, inet->inet_dport, sk);
  	if (IS_ERR(rt)) {
  		err = PTR_ERR(rt);
  		rt = NULL;
  		goto failure;
  	}
  	/* OK, now commit destination to socket.  */
  	sk->sk_gso_type = SKB_GSO_TCPV4;
  	sk_setup_caps(sk, &rt->dst);
  	rt = NULL;
  
  	if (likely(!tp->repair)) {
  		if (!tp->write_seq)
  			WRITE_ONCE(tp->write_seq,
  				   secure_tcp_seq(inet->inet_saddr,
  						  inet->inet_daddr,
  						  inet->inet_sport,
  						  usin->sin_port));
  		tp->tsoffset = secure_tcp_ts_off(sock_net(sk),
  						 inet->inet_saddr,
  						 inet->inet_daddr);
  	}
  
  	inet->inet_id = prandom_u32();
  
  	if (tcp_fastopen_defer_connect(sk, &err))
  		return err;
  	if (err)
  		goto failure;
  
  	err = tcp_connect(sk);
  
  	if (err)
  		goto failure;
  
  	return 0;
  
  failure:
  	/*
  	 * This unhashes the socket and releases the local port,
  	 * if necessary.
  	 */
  	tcp_set_state(sk, TCP_CLOSE);
  	ip_rt_put(rt);
  	sk->sk_route_caps = 0;
  	inet->inet_dport = 0;
  	return err;
  }
  ```





- 阻塞等待3次握手的完成，此时进程处于睡眠状态，会等待3次握手中的第二个ACK包的唤醒，唤醒之后会调用sock_def_wakeup函数

- ```cpp
  static long inet_wait_for_connect(struct sock *sk, long timeo, int writebias)
  {
  	DEFINE_WAIT_FUNC(wait, woken_wake_function);
  
  	add_wait_queue(sk_sleep(sk), &wait);
  	sk->sk_write_pending += writebias;
  
  	/* Basic assumption: if someone sets sk->sk_err, he _must_
  	 * change state of the socket from TCP_SYN_*.
  	 * Connect() does not allow to get error notifications
  	 * without closing the socket.
  	 */
          // 如果状态变为TCP_ESTABLISHED，握手完成则退出阻塞
  	while ((1 << sk->sk_state) & (TCPF_SYN_SENT | TCPF_SYN_RECV)) {
  		release_sock(sk);
  		timeo = wait_woken(&wait, TASK_INTERRUPTIBLE, timeo);
  		lock_sock(sk);
  		if (signal_pending(current) || !timeo)
  			break;
  	}
  	remove_wait_queue(sk_sleep(sk), &wait);
  	sk->sk_write_pending -= writebias;
  	return timeo;
  }
  ```



- 唤醒ACK 包的到来唤醒

- ```c
  static void sock_def_wakeup(struct sock *sk)
  {
  	struct socket_wq *wq;
  
  	rcu_read_lock();
  	wq = rcu_dereference(sk->sk_wq);
  	if (skwq_has_sleeper(wq))
  		wake_up_interruptible_all(&wq->wait);
  	rcu_read_unlock();
  }
  ```





- 后面调用链很长，最终会调用到tcp_finish_connect，这里会把tcp状态置为TCP_ESTABLISHED，上面提到的__inet_stream_connect内部也就解除阻塞，connect也就得以成功返回.

  ```c
  void tcp_finish_connect(struct sock *sk, struct sk_buff *skb)
  {
  	struct tcp_sock *tp = tcp_sk(sk);
  	struct inet_connection_sock *icsk = inet_csk(sk);
          // 设置3吃 次握手成功
  	tcp_set_state(sk, TCP_ESTABLISHED);
  	icsk->icsk_ack.lrcvtime = tcp_jiffies32;
  
  	if (skb) {
  		icsk->icsk_af_ops->sk_rx_dst_set(sk, skb);
  		security_inet_conn_established(sk, skb);
  		sk_mark_napi_id(sk, skb);
  	}
  
  	tcp_init_transfer(sk, BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB);
  
  	/* Prevent spurious tcp_cwnd_restart() on first data
  	 * packet.
  	 */
  	tp->lsndtime = tcp_jiffies32;
  
  	if (sock_flag(sk, SOCK_KEEPOPEN))
  		inet_csk_reset_keepalive_timer(sk, keepalive_time_when(tp));
  
  	if (!tp->rx_opt.snd_wscale)
  		__tcp_fast_path_on(tp, tp->snd_wnd);
  	else
  		tp->pred_flags = 0;
  }
  ```





# 总结

- 该函数是**在client端使用的**，用来发起对server端的连接，主要实现的功能如下：
  - 发送第一个SYN包
  - 阻塞等待内核协议栈完成后2次握手
  - 握手完成后被唤醒，返回
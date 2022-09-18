# 函数原型

- ```cpp
  #include <sys/socket.h>
  
  int bind(int sockfd, const struct sockaddr *address, socklen_t address_len);
  //	sockfd：socket文件描述符
  //	dress：一个ip+端口组成的结构体，类型为struct sockaddr
  //	dress_len：地址参数的长度sizeof(address)
  ```

- 返回值：成功返回0，失败返回-1, 并且设置errno







# 功能

- 给socket绑定一个地址，这样client对这个地址的相应收发数据就能和socket相关联
- 服务端: 必须要调用bind进行绑定
- 客户端: 非必须调用（如不调用，则系统自动分配一个端口和本地地址来进行和socket绑定）





# 实现

- ```cpp
  SYSCALL_DEFINE3(bind, int, fd, struct sockaddr __user *, umyaddr, int, addrlen)
  {
  	return __sys_bind(fd, umyaddr, addrlen);
  }
  
  //	bind实际调用的函数
  int __sys_bind(int fd, struct sockaddr __user *umyaddr, int addrlen)
  {
  	struct socket *sock;
  	struct sockaddr_storage address;
  	int err, fput_needed;
  
      //	这里通过入参的fd寻找到socket结构体数据
  	sock = sockfd_lookup_light(fd, &err, &fput_needed);
  	if (sock) {
          //	把addr数据从用户空间copy到内核空间，转变为struct sockaddr_storage结构体
  		err = move_addr_to_kernel(umyaddr, addrlen, &address);
  		if (err >= 0) {
              //	SELInux相关的处理
  			err = security_socket_bind(sock,
  						   (struct sockaddr *)&address,
  						   addrlen);
  			if (!err)
                  //	如果是SOCK_STREAM的话调用的是inet_bind()
  				err = sock->ops->bind(sock,
  						      (struct sockaddr *)
  						      &address, addrlen);
  		}
  		fput_light(sock->file, fput_needed);
  	}
  	return err;
  }
  
  //	通过入参的fd寻找对应的socket
  static struct socket *sockfd_lookup_light(int fd, int *err, int *fput_needed)
  {
      //	从当前task_struct->files中找到fd实例
  	struct fd f = fdget(fd);
  	struct socket *sock;
  
  	*err = -EBADF;
  	if (f.file) {
          //	通过file找到socket实例
  		sock = sock_from_file(f.file, err);
  		if (likely(sock)) {
  			*fput_needed = f.flags & FDPUT_FPUT;
  			return sock;
  		}
  		fdput(f);
  	}
  	return NULL;
  }
  
  const struct proto_ops inet_stream_ops = {
  	.family		   = PF_INET,
  	.owner		   = THIS_MODULE,
  	.release	   = inet_release,
  	.bind		   = inet_bind,  // 这就是bind的实现func
  	.connect	   = inet_stream_connect,
  	.socketpair	   = sock_no_socketpair,
  	.accept		   = inet_accept,
  	.getname	   = inet_getname,
          ......
  };
  
  //	对socket中的数据进行填充
  int inet_bind(struct socket *sock, struct sockaddr *uaddr, int addr_len)
  {
  	struct sock *sk = sock->sk;
  	int err;
  
  	/* If the socket has its own bind function then use it. (RAW) */
  	if (sk->sk_prot->bind) {
  		return sk->sk_prot->bind(sk, uaddr, addr_len);
  	}
  	if (addr_len < sizeof(struct sockaddr_in))
  		return -EINVAL;
  
  	/* BPF prog is run before any checks are done so that if the prog
  	 * changes context in a wrong way it will be caught.
  	 */
  	err = BPF_CGROUP_RUN_PROG_INET4_BIND(sk, uaddr);
  	if (err)
  		return err;
          // 进行sk内部的一些成员赋值
  	return __inet_bind(sk, uaddr, addr_len, false, true);
  }
  
  int __inet_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len,
  		bool force_bind_address_no_port, bool with_lock)
  {
  	struct sockaddr_in *addr = (struct sockaddr_in *)uaddr;
  	struct inet_sock *inet = inet_sk(sk);  // INET实例: 这个函数其实是给sk赋值
  	struct net *net = sock_net(sk);   // sk->sk_net会被赋值
  	unsigned short snum; // 端口
  	int chk_addr_ret;   // 地址类型: 单播 多播 广播
  	u32 tb_id = RT_TABLE_LOCAL;
  	int err;
  
          // 非inet协议簇
  	if (addr->sin_family != AF_INET) {
  		/* Compatibility games : accept AF_UNSPEC (mapped to AF_INET)
  		 * only if s_addr is INADDR_ANY.
  		 */
  		err = -EAFNOSUPPORT;
  		if (addr->sin_family != AF_UNSPEC ||
  		    addr->sin_addr.s_addr != htonl(INADDR_ANY))
  			goto out;
  	}
  
          // 查找地址类型
  	tb_id = l3mdev_fib_table_by_index(net, sk->sk_bound_dev_if) ? : tb_id;
  	chk_addr_ret = inet_addr_type_table(net, addr->sin_addr.s_addr, tb_id);
  
  	/* Not specified by any standard per-se, however it breaks too
  	 * many applications when removed.  It is unfortunate since
  	 * allowing applications to make a non-local bind solves
  	 * several problems with systems using dynamic addressing.
  	 * (ie. your servers still start up even if your ISDN link
  	 *  is temporarily down)
  	 */
  	err = -EADDRNOTAVAIL;
  	if (!inet_can_nonlocal_bind(net, inet) &&
  	    addr->sin_addr.s_addr != htonl(INADDR_ANY) &&
  	    chk_addr_ret != RTN_LOCAL &&
  	    chk_addr_ret != RTN_MULTICAST &&
  	    chk_addr_ret != RTN_BROADCAST)
  		goto out;
  
  	snum = ntohs(addr->sin_port);  // 绑定的端口进行字节序转换
  	err = -EACCES;
  	if (snum && snum < inet_prot_sock(net) &&
  	    !ns_capable(net->user_ns, CAP_NET_BIND_SERVICE))
  		goto out;
  
  	/*      We keep a pair of addresses. rcv_saddr is the one
  	 *      used by hash lookups, and saddr is used for transmit.
  	 *
  	 *      In the BSD API these are the same except where it
  	 *      would be illegal to use them (multicast/broadcast) in
  	 *      which case the sending device address is used.
  	 */
  	if (with_lock)
  		lock_sock(sk);
  
          // 如果状态不是初始的TCP_CLOSE则报错
  	/* Check these errors (active socket, double bind). */
  	err = -EINVAL;
  	if (sk->sk_state != TCP_CLOSE || inet->inet_num)
  		goto out_release_sock;
  
  	inet->inet_rcv_saddr = inet->inet_saddr = addr->sin_addr.s_addr;
  	if (chk_addr_ret == RTN_MULTICAST || chk_addr_ret == RTN_BROADCAST)
  		inet->inet_saddr = 0;  /* Use device */
  
           // 如果没有传端口，则随机选择一个端口，注意:0~1024需要特权
  	/* Make sure we are allowed to bind here. */
  	if (snum || !(inet->bind_address_no_port ||
  		      force_bind_address_no_port)) {
  		if (sk->sk_prot->get_port(sk, snum)) {
  			inet->inet_saddr = inet->inet_rcv_saddr = 0;
  			err = -EADDRINUSE;
  			goto out_release_sock;
  		}
  		err = BPF_CGROUP_RUN_PROG_INET4_POST_BIND(sk);
  		if (err) {
  			inet->inet_saddr = inet->inet_rcv_saddr = 0;
  			goto out_release_sock;
  		}
  	}
  
  	if (inet->inet_rcv_saddr)
  		sk->sk_userlocks |= SOCK_BINDADDR_LOCK;
  	if (snum)
  		sk->sk_userlocks |= SOCK_BINDPORT_LOCK;
  	inet->inet_sport = htons(inet->inet_num);
  	inet->inet_daddr = 0;
  	inet->inet_dport = 0;
  	sk_dst_reset(sk);
  	err = 0;
  out_release_sock:
  	if (with_lock)
  		release_sock(sk);
  out:
  	return err;
  }
  ```





- 先调用__sys_bind（将用户态的地址数据传入内核态空间中）
- 在__sys_bind中调用sockfd_lookup_light（通过入参的fd找到对应的socket对象）
- 在__sys_bind中接着调用inet_bind（将地址和端口号填充到socket中）
- 在inet_bind中调用__inet_bind
  - 其中会检查当前的state，如果是tcp_close就会报错
  - 会将传入的端口号进行大小端的转换（因为协议栈要求是大端存储，而一般os的存储都是小端存储的）
  - 如果没有指定端口号，就会随机找一个（排除0到1024之间的端口号）







# 总结

- 通过给定的fd找到对应的socket实例
- 对传入的地址和端口进行参数上的校验
- 将地址和端口赋值到对应的socket上（同时作为状态机对数据进行判断）
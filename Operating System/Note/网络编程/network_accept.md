# 函数原型

- ```cpp
  #include <sys/types.h>
  #include <sys/socket.h>
  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  //	sockfd是fd，即listening socket
  //	addr是用来接收对端d连接地址信息
  //	addrlen是addr的长度
  ```

- 若成功的话则返回一个新的fd，这个fd用来和对端通信；失败的话就返回-1，并且设置errno







# 功能

- 当socket模式设置为阻塞模式时，accept函数的功能是阻塞等待client发起三次握手，**当3次握手完成的时候，accept解除阻塞**，并从全连接队列中取出一个socket，就可以对这个socket连接进行读写操作







# 实现

- 当connect中发起第一次握手，accept内部实现会被内核协议栈中完成的3次握手成功后被解除阻塞状态，并返回一个fd

- ```cpp
  //	accept的函数原型
  SYSCALL_DEFINE3(accept, int, fd, struct sockaddr __user *, upeer_sockaddr,
  		int __user *, upeer_addrlen)
  {
  	return __sys_accept4(fd, upeer_sockaddr, upeer_addrlen, 0);
  }
  
  //	本质上是调用这个函数
  int __sys_accept4(int fd, struct sockaddr __user *upeer_sockaddr,
  		  int __user *upeer_addrlen, int flags)
  {
  	struct socket *sock, *newsock;
  	struct file *newfile;
  	int err, len, newfd, fput_needed;
  	struct sockaddr_storage address;
  
  	if (flags & ~(SOCK_CLOEXEC | SOCK_NONBLOCK))
  		return -EINVAL;
  
  	if (SOCK_NONBLOCK != O_NONBLOCK && (flags & SOCK_NONBLOCK))
  		flags = (flags & ~SOCK_NONBLOCK) | O_NONBLOCK;
          //	通过fd找到socket实例
  	sock = sockfd_lookup_light(fd, &err, &fput_needed);
  	if (!sock)
  		goto out;
  
  	err = -ENFILE;
          //	创建一个新的socket
  	newsock = sock_alloc();
  	if (!newsock)
  		goto out_put;
  	
      //	组装新的socket
  	newsock->type = sock->type;
  	newsock->ops = sock->ops;
  
  	/*
  	 * We don't need try_module_get here, as the listening socket (sock)
  	 * has the protocol module (sock->ops->owner) held.
  	 */
  	__module_get(newsock->ops->owner);
          //	分配一个新的fd
  	newfd = get_unused_fd_flags(flags);
  	if (unlikely(newfd < 0)) {
  		err = newfd;
  		sock_release(newsock);
  		goto out_put;
  	}
          //	创建file对象
  	newfile = sock_alloc_file(newsock, flags, sock->sk->sk_prot_creator->name);
  	if (IS_ERR(newfile)) {
  		err = PTR_ERR(newfile);
  		put_unused_fd(newfd);
  		goto out_put;
  	}
  
  	err = security_socket_accept(sock, newsock);
  	if (err)
  		goto out_fd;
          //	这里调用inet_accept()，该函数内获取到新连接的client，并实例化socket实例
      	//	这里的accept存储的是一个函数指针，调用到的就是下面的inet_accept
  	err = sock->ops->accept(sock, newsock, sock->file->f_flags, false);
  	if (err < 0)
  		goto out_fd;
  
          // client的addr从内核空间copy到用户空间
  	if (upeer_sockaddr) {
  		len = newsock->ops->getname(newsock,
  					(struct sockaddr *)&address, 2);
  		if (len < 0) {
  			err = -ECONNABORTED;
  			goto out_fd;
  		}
  		err = move_addr_to_user(&address,
  					len, upeer_sockaddr, upeer_addrlen);
  		if (err < 0)
  			goto out_fd;
  	}
  
  	/* File flags are not inherited via accept() unlike another OSes. */
          // fd和file绑定
  	fd_install(newfd, newfile);
  	err = newfd;
  
  out_put:
  	fput_light(sock->file, fput_needed);
  out:
  	return err;
  out_fd:
  	fput(newfile);
  	put_unused_fd(newfd);
  	goto out_put;
  }
  ```





- 在业务场景下，accept是处于阻塞状态的，3次握手的后2次是在协议栈中处理，accept仅仅是从accept队列里面取出一个连接
  - 如果没有已完成3次握手的连接，则inet_csk_wait_for_connect就发送阻塞，等待有新的连接产生
  - 如果有连接完成了3次握手，则这个队列中就会有数据，就从这个队列将节点移走，生成一个sock对象

- ```cpp
  struct proto tcp_prot = {
  	.name			= "TCP",
  	.owner			= THIS_MODULE,
  	.close			= tcp_close,
  	.pre_connect		= tcp_v4_pre_connect,
  	.connect		= tcp_v4_connect,
  	.disconnect		= tcp_disconnect,
  	.accept			= inet_csk_accept,  // 调用这里
  	.ioctl			= tcp_ioctl,
          ......
  }
  
  //	该函数内获取到新连接的client，并实例化socket实例
  int inet_accept(struct socket *sock, struct socket *newsock, int flags,
  		bool kern)
  {
  	struct sock *sk1 = sock->sk;
  	int err = -EINVAL;
          // 这里调用的是 tcp_prot->inet_csk_accept() 
          // sk_prot = tcp_prot
  	struct sock *sk2 = sk1->sk_prot->accept(sk1, flags, &err, kern);
  
  	if (!sk2)
  		goto do_err;
  
  	lock_sock(sk2);
  
  	sock_rps_record_flow(sk2);
      //	检查socket的状态
  	WARN_ON(!((1 << sk2->sk_state) &
  		  (TCPF_ESTABLISHED | TCPF_SYN_RECV |
  		  TCPF_CLOSE_WAIT | TCPF_CLOSE)));
  
  	sock_graft(sk2, newsock);
  	
      //	设置新得到的socket的状态
  	newsock->state = SS_CONNECTED;  
  	err = 0;
  	release_sock(sk2);
  do_err:
  	return err;
  }
  
  //	所以这个函数的主要目的就是从队列中取出已经完成三次握手了的socket/没有的话就一直阻塞在这里
  struct sock *inet_csk_accept(struct sock *sk, int flags, int *err, bool kern)
  {
  	struct inet_connection_sock *icsk = inet_csk(sk);
  	struct request_sock_queue *queue = &icsk->icsk_accept_queue;
  	struct request_sock *req;
  	struct sock *newsk;
  	int error;
  
  	lock_sock(sk);
  
  	/* We need to make sure that this socket is listening,
  	 * and that it has something pending.
  	 */
  	error = -EINVAL;
      //	如果当前socket的状态不是listening的话，就报错
  	if (sk->sk_state != TCP_LISTEN)
  		goto out_err;
  
  	/* Find already established connection */
  	if (reqsk_queue_empty(queue)) { //	如果队列中没有数据，就要在这里阻塞
  		long timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);
  
  		/* If this is a non blocking socket don't sleep */
  		error = -EAGAIN;
  		if (!timeo)
  			goto out_err;
          //	这里会阻塞等待
  		error = inet_csk_wait_for_connect(sk, timeo);
  		if (error)
  			goto out_err;
  	}
  	req = reqsk_queue_remove(queue, sk); // 队列不为空了，就从队列中移除一个节点
  	newsk = req->sk;
  
  	if (sk->sk_protocol == IPPROTO_TCP &&
  	    tcp_rsk(req)->tfo_listener) {
  		spin_lock_bh(&queue->fastopenq.lock);
  		if (tcp_rsk(req)->tfo_listener) {
  			/* We are still waiting for the final ACK from 3WHS
  			 * so can't free req now. Instead, we set req->sk to
  			 * NULL to signify that the child socket is taken
  			 * so reqsk_fastopen_remove() will free the req
  			 * when 3WHS finishes (or is aborted).
  			 */
  			req->sk = NULL;
  			req = NULL;
  		}
  		spin_unlock_bh(&queue->fastopenq.lock);
  	}
  
  out:
  	release_sock(sk);
  	if (newsk && mem_cgroup_sockets_enabled) {
  		int amt;
  
  		/* atomically get the memory usage, set and charge the
  		 * newsk->sk_memcg.
  		 */
  		lock_sock(newsk);
  
  		/* The socket has not been accepted yet, no need to look at
  		 * newsk->sk_wmem_queued.
  		 */
  		amt = sk_mem_pages(newsk->sk_forward_alloc +
  				   atomic_read(&newsk->sk_rmem_alloc));
  		mem_cgroup_sk_alloc(newsk);
  		if (newsk->sk_memcg && amt)
  			mem_cgroup_charge_skmem(newsk->sk_memcg, amt);
  
  		release_sock(newsk);
  	}
  	if (req)
  		reqsk_put(req);
  	return newsk;
  out_err:
  	newsk = NULL;
  	req = NULL;
  	*err = error;
  	goto out;
  }
  ```



函数的调用流程：

- __sys_accept4（本质上就是调用这个函数：通过给定的fd找到对应的listening socket，然后用这个listening socket初始化新的socket，同时建立好fd，socket，file对象三者的关系；接着调用inet_accept函数；同时将client的端口地址等信息copy到用户态空间）
- inet_accept（获取到新连接的client，并实例化socket实例；如果没有socket可获得，就阻塞；同时修改socket的state）
- inet_csk_accept（在inet_accept中被调用，所以这个函数的主要目的就是从队列中取出已经完成三次握手了的socket/没有的话就一直阻塞在这里）





# 总结

- 创建一个socket实例（建立fd，socket，file三者的关系）
- 阻塞等待accept队列，直到有已就绪的连接，则从队列中取走
- socket和新连接做绑定

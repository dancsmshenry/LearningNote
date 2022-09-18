# 函数原型

- ````cpp
  #include<unistd.h>
  int close(int fd);
  //	fd是socket
  ````

- 调用成功返回0，否则返回-1并设置errno







# 功能

- 用于释放系统分配给socket的资源







# 实现

- ```cpp
  SYSCALL_DEFINE1(close, unsigned int, fd)
  {	
  	//	files是当前进程的file table
  	int retval = __close_fd(current->files, fd); 
  
  	/* can't restart close syscall because file table entry was cleared */
  	if (unlikely(retval == -ERESTARTSYS ||
  		     retval == -ERESTARTNOINTR ||
  		     retval == -ERESTARTNOHAND ||
  		     retval == -ERESTART_RESTARTBLOCK))
  		retval = -EINTR;
  
  	return retval;
  }
  
  /*
   * The same warnings as for __alloc_fd()/__fd_install() apply here...
   */
  int __close_fd(struct files_struct *files, unsigned fd)
  {
  	struct file *file;
  	struct fdtable *fdt;
      //	files_table上锁，为了正确并发
  	spin_lock(&files->file_lock);
      //	从进程的files中找到fd对应的file
  	fdt = files_fdtable(files);
  	if (fd >= fdt->max_fds) // fd大于当前的最大fd
  		goto out_unlock;
  	file = fdt->fd[fd];   //	去table中找对应的fd
  	if (!file)
  		goto out_unlock;
  	rcu_assign_pointer(fdt->fd[fd], NULL);
  	__put_unused_fd(files, fd);
  	spin_unlock(&files->file_lock);
      
     	//	close fd的本质就是删掉file
  	return filp_close(file, files);
  
  out_unlock:
  	spin_unlock(&files->file_lock);
  	return -EBADF;
  }
  
  /*
   * "id" is the POSIX thread ID. We use the
   * files pointer for this..
   */
  int filp_close(struct file *filp, fl_owner_t id)
  {
  	int retval = 0;
  
  	if (!file_count(filp)) {
  		printk(KERN_ERR "VFS: Close: file count is 0\n");
  		return 0;
  	}
          // 如果存在flush方法则flush
  	if (filp->f_op->flush)
  		retval = filp->f_op->flush(filp, id);
  
  	if (likely(!(filp->f_mode & FMODE_PATH))) {
  		dnotify_flush(filp, id);
  		locks_remove_posix(filp, id);
  	}
  	fput(filp);  // 调用fput进行释放
  	return retval;
  }
  
  void fput(struct file *file)
  {
  	fput_many(file, 1);
  }
  
  void fput_many(struct file *file, unsigned int refs)
  {
  	if (atomic_long_sub_and_test(refs, &file->f_count)) {
  		struct task_struct *task = current;
  
  		if (likely(!in_interrupt() && !(task->flags & PF_KTHREAD))) {
  			init_task_work(&file->f_u.fu_rcuhead, ____fput);
  			if (!task_work_add(task, &file->f_u.fu_rcuhead, true))
  				return;
  			/*
  			 * After this task has run exit_task_work(),
  			 * task_work_add() will fail.  Fall through to delayed
  			 * fput to avoid leaking *file.
  			 */
  		}
                  // 通过延迟调度来处理，加入到队列中
  		if (llist_add(&file->f_u.fu_llist, &delayed_fput_list))
  			schedule_delayed_work(&delayed_fput_work, 1);
  	}
  }
  
  static DECLARE_DELAYED_WORK(delayed_fput_work, delayed_fput);
  
  static void delayed_fput(struct work_struct *unused)
  {
  	struct llist_node *node = llist_del_all(&delayed_fput_list);
  	struct file *f, *t;
  
  	llist_for_each_entry_safe(f, t, node, f_u.fu_llist)
  		__fput(f);  // 调用__fput进行释放资源
  }
  ```





- ```cpp
  /* the real guts of fput() - releasing the last reference to file
   */
  static void __fput(struct file *file)
  {
  	struct dentry *dentry = file->f_path.dentry;
  	struct vfsmount *mnt = file->f_path.mnt;
  	struct inode *inode = file->f_inode;
  
  	if (unlikely(!(file->f_mode & FMODE_OPENED)))
  		goto out;
  
  	might_sleep();
  
  	fsnotify_close(file);
  	/*
  	 * The function eventpoll_release() should be the first called
  	 * in the file cleanup chain.
  	 */
  	eventpoll_release(file);
  	locks_remove_file(file);
  
  	ima_file_free(file);
  	if (unlikely(file->f_flags & FASYNC)) {
  		if (file->f_op->fasync)
  			file->f_op->fasync(-1, file, 0);
  	}
  	if (file->f_op->release)  // 这里调用socket_file_ops->release
  		file->f_op->release(inode, file);
  	if (unlikely(S_ISCHR(inode->i_mode) && inode->i_cdev != NULL &&
  		     !(file->f_mode & FMODE_PATH))) {
  		cdev_put(inode->i_cdev);
  	}
  	fops_put(file->f_op);
  	put_pid(file->f_owner.pid);
  	if ((file->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ)
  		i_readcount_dec(inode);
  	if (file->f_mode & FMODE_WRITER) {
  		put_write_access(inode);
  		__mnt_drop_write(mnt);
  	}
  	dput(dentry);
  	mntput(mnt);
  out:
  	file_free(file);
  }
  ```



- ```cpp
  static int sock_close(struct inode *inode, struct file *filp)
  {
  	__sock_release(SOCKET_I(inode), inode);
  	return 0;
  }
  static void __sock_release(struct socket *sock, struct inode *inode)
  {
  	if (sock->ops) {
  		struct module *owner = sock->ops->owner;
  
  		if (inode)
  			inode_lock(inode);
  		sock->ops->release(sock);  // inet_stream_ops->inet_release
  		sock->sk = NULL;
  		if (inode)
  			inode_unlock(inode);
  		sock->ops = NULL;
  		module_put(owner);
  	}
  
  	if (sock->wq->fasync_list)
  		pr_err("%s: fasync list not empty!\n", __func__);
  
  	if (!sock->file) {
  		iput(SOCK_INODE(sock));
  		return;
  	}
  	sock->file = NULL;
  }
  ```



- ```cpp
  const struct proto_ops inet_stream_ops = {
  	.family		   = PF_INET,
  	.owner		   = THIS_MODULE,
  	.release	   = inet_release, // 调用这里
  	.bind		   = inet_bind,
          ......
  }
  
  int inet_release(struct socket *sock)
  {
  	struct sock *sk = sock->sk;
  
  	if (sk) {
  		long timeout;
  
  		/* Applications forget to leave groups before exiting */
  		ip_mc_drop_socket(sk);
  
  		/* If linger is set, we don't return until the close
  		 * is complete.  Otherwise we return immediately. The
  		 * actually closing is done the same either way.
  		 *
  		 * If the close is due to the process exiting, we never
  		 * linger..
  		 */
  		timeout = 0;
  		if (sock_flag(sk, SOCK_LINGER) &&
  		    !(current->flags & PF_EXITING))
  			timeout = sk->sk_lingertime;
  		sk->sk_prot->close(sk, timeout); // tcp_prot->tcp_close
  		sock->sk = NULL;
  	}
  	return 0;
  }
  ```



- tcp_close第一次挥手

- ```cpp
  void tcp_close(struct sock *sk, long timeout)
  {
  	struct sk_buff *skb;
  	int data_was_unread = 0;
  	int state;
  
  	lock_sock(sk);
  	sk->sk_shutdown = SHUTDOWN_MASK;
  
  	if (sk->sk_state == TCP_LISTEN) {
  		tcp_set_state(sk, TCP_CLOSE);
  
  		/* Special case. */
  		inet_csk_listen_stop(sk);
  
  		goto adjudge_to_death;
  	}
  
  	/*  We need to flush the recv. buffs.  We do this only on the
  	 *  descriptor close, not protocol-sourced closes, because the
  	 *  reader process may not have drained the data yet!
  	 */
  	while ((skb = __skb_dequeue(&sk->sk_receive_queue)) != NULL) {
  		u32 len = TCP_SKB_CB(skb)->end_seq - TCP_SKB_CB(skb)->seq;
  
  		if (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
  			len--;
  		data_was_unread += len;
  		__kfree_skb(skb);
  	}
  
  	sk_mem_reclaim(sk);
  
  	/* If socket has been already reset (e.g. in tcp_reset()) - kill it. */
  	if (sk->sk_state == TCP_CLOSE)
  		goto adjudge_to_death;
  
  	/* As outlined in RFC 2525, section 2.17, we send a RST here because
  	 * data was lost. To witness the awful effects of the old behavior of
  	 * always doing a FIN, run an older 2.1.x kernel or 2.0.x, start a bulk
  	 * GET in an FTP client, suspend the process, wait for the client to
  	 * advertise a zero window, then kill -9 the FTP client, wheee...
  	 * Note: timeout is always zero in such a case.
  	 */
  	if (unlikely(tcp_sk(sk)->repair)) {
  		sk->sk_prot->disconnect(sk, 0);
  	} else if (data_was_unread) {
  		/* Unread data was tossed, zap the connection. */
  		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONCLOSE);
  		tcp_set_state(sk, TCP_CLOSE);
  		tcp_send_active_reset(sk, sk->sk_allocation);
  	} else if (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingertime) {
  		/* Check zero linger _after_ checking for unread data. */
  		sk->sk_prot->disconnect(sk, 0);
  		NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPABORTONDATA);
  	} else if (tcp_close_state(sk)) {
  		/* We FIN if the application ate all the data before
  		 * zapping the connection.
  		 */
  
  		/* RED-PEN. Formally speaking, we have broken TCP state
  		 * machine. State transitions:
  		 *
  		 * TCP_ESTABLISHED -> TCP_FIN_WAIT1
  		 * TCP_SYN_RECV	-> TCP_FIN_WAIT1 (forget it, it's impossible)
  		 * TCP_CLOSE_WAIT -> TCP_LAST_ACK
  		 *
  		 * are legal only when FIN has been sent (i.e. in window),
  		 * rather than queued out of window. Purists blame.
  		 *
  		 * F.e. "RFC state" is ESTABLISHED,
  		 * if Linux state is FIN-WAIT-1, but FIN is still not sent.
  		 *
  		 * The visible declinations are that sometimes
  		 * we enter time-wait state, when it is not required really
  		 * (harmless), do not send active resets, when they are
  		 * required by specs (TCP_ESTABLISHED, TCP_CLOSE_WAIT, when
  		 * they look as CLOSING or LAST_ACK for Linux)
  		 * Probably, I missed some more holelets.
  		 * 						--ANK
  		 * XXX (TFO) - To start off we don't support SYN+ACK+FIN
  		 * in a single packet! (May consider it later but will
  		 * probably need API support or TCP_CORK SYN-ACK until
  		 * data is written and socket is closed.)
  		 */
  		tcp_send_fin(sk);  // 这里发起4次挥手的第一次fin包
  	}
  
  	sk_stream_wait_close(sk, timeout);
  
  adjudge_to_death:
  	state = sk->sk_state;
  	sock_hold(sk);
  	sock_orphan(sk);
  
  	local_bh_disable();
  	bh_lock_sock(sk);
  	/* remove backlog if any, without releasing ownership. */
  	__release_sock(sk);
  
  	percpu_counter_inc(sk->sk_prot->orphan_count);
  
  	/* Have we already been destroyed by a softirq or backlog? */
  	if (state != TCP_CLOSE && sk->sk_state == TCP_CLOSE)
  		goto out;
  
  	/*	This is a (useful) BSD violating of the RFC. There is a
  	 *	problem with TCP as specified in that the other end could
  	 *	keep a socket open forever with no application left this end.
  	 *	We use a 1 minute timeout (about the same as BSD) then kill
  	 *	our end. If they send after that then tough - BUT: long enough
  	 *	that we won't make the old 4*rto = almost no time - whoops
  	 *	reset mistake.
  	 *
  	 *	Nope, it was not mistake. It is really desired behaviour
  	 *	f.e. on http servers, when such sockets are useless, but
  	 *	consume significant resources. Let's do it with special
  	 *	linger2	option.					--ANK
  	 */
  
  	if (sk->sk_state == TCP_FIN_WAIT2) {
  		struct tcp_sock *tp = tcp_sk(sk);
  		if (tp->linger2 < 0) {
  			tcp_set_state(sk, TCP_CLOSE);
  			tcp_send_active_reset(sk, GFP_ATOMIC);
  			__NET_INC_STATS(sock_net(sk),
  					LINUX_MIB_TCPABORTONLINGER);
  		} else {
  			const int tmo = tcp_fin_time(sk);
  
  			if (tmo > TCP_TIMEWAIT_LEN) {
  				inet_csk_reset_keepalive_timer(sk,
  						tmo - TCP_TIMEWAIT_LEN);
  			} else {
  				tcp_time_wait(sk, TCP_FIN_WAIT2, tmo);
  				goto out;
  			}
  		}
  	}
  	if (sk->sk_state != TCP_CLOSE) {
  		sk_mem_reclaim(sk);
  		if (tcp_check_oom(sk, 0)) {
  			tcp_set_state(sk, TCP_CLOSE);
  			tcp_send_active_reset(sk, GFP_ATOMIC);
  			__NET_INC_STATS(sock_net(sk),
  					LINUX_MIB_TCPABORTONMEMORY);
  		} else if (!check_net(sock_net(sk))) {
  			/* Not possible to send reset; just close */
  			tcp_set_state(sk, TCP_CLOSE);
  		}
  	}
  
  	if (sk->sk_state == TCP_CLOSE) {
  		struct request_sock *req = tcp_sk(sk)->fastopen_rsk;
  		/* We could get here with a non-NULL req if the socket is
  		 * aborted (e.g., closed with unread data) before 3WHS
  		 * finishes.
  		 */
  		if (req)
  			reqsk_fastopen_remove(sk, req, false);
  		inet_csk_destroy_sock(sk);
  	}
  	/* Otherwise, socket is reprieved until protocol close. */
  
  out:
  	bh_unlock_sock(sk);
  	local_bh_enable();
  	release_sock(sk);
  	sock_put(sk);
  }
  ```



## 一些细节

- close一个socket的缺省行为是把该socket标记为关闭，然后立即返回到调用进程（然后该进程是不能继续使用这个fd的）
  - PS：即在总的file table中它不一定会被删除掉
- close只是使对应的socket描述符的引用计数-1，而只有当引用计数为0的时候，才会终止连接请求（为啥要引用计数？）
  - 在unix和linux平台需要考虑多进程的情况，fork时，子进程继承父进程所拥有的文件描述符，需要所有拥有者都close文件描述符才会把资源销毁，所以需要使用引用计数





# 总结

- close本质上只是让socketfd对应的file的被引用计数-1，所以只有引用计数为0的时候才会把socket真正给关掉
  - 否则，只是不让本process使用该socketfd罢了
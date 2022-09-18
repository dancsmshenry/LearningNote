# 函数原型

- ```cpp
  #include <sys/types.h>
  #include <sys/socket.h>
  int socket(int domain, int type, int protocol);
  
  //	domain：协议族，常用的协议族有，AF_INET、AF_INET6、AF_LOCAL(或称AF_UNIX，Unix域socket）、AF_ROUTE、PF_PACKET等等。协议族决定了socket地址的类型，在通信中也必须使用对应的协议类型，比如AF_INET就决定了要用ipv4地址(32位)，AF_UNIX决定了要用一个绝对路径名作为地址
  
  //	type: 指定socket类型，常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等等
  
  //	protocol: 指定协议，常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC、ETH_P_ALL等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议。当protocol为0时，会自动选择type类型对应的默认协议
  ```

- PS：并不是上面的type和protocol可以随意组合的，例如:SOCK_STREAM不可以跟IPPROTO_UDP组合







# 实现

- 该结构体是用来描述socket的

- ```cpp
  **
   *  struct socket - general BSD socket
   *  @state: socket state (%SS_CONNECTED, etc)
   *  @type: socket type (%SOCK_STREAM, etc)
   *  @flags: socket flags (%SOCK_NOSPACE, etc)
   *  @ops: protocol specific socket operations
   *  @file: File back pointer for gc
   *  @sk: internal networking protocol agnostic socket representation
   *  @wq: wait queue for several uses
   */
  struct socket {
  	socket_state		state; //	当前socket的状态
  
  	short			type;
  
  	unsigned long		flags;
  
  	struct socket_wq	*wq;
  
  	struct file		*file; //	socket对应的文件
  	struct sock		*sk;
  	const struct proto_ops	*ops;
  };
  ```





- 系统调用在内核中的入口都是sys_xxx，但其实Linux的系统调用都改为SYSCALL_DEFINE定义的：定义的{kernel}/include/linux/syscalls.h

- ```c
  #ifndef SYSCALL_DEFINE0
  #define SYSCALL_DEFINE0(sname)					\
  	SYSCALL_METADATA(_##sname, 0);				\
  	asmlinkage long sys_##sname(void);			\
  	ALLOW_ERROR_INJECTION(sys_##sname, ERRNO);		\
  	asmlinkage long sys_##sname(void)
  #endif /* SYSCALL_DEFINE0 */
  
  #define SYSCALL_DEFINE1(name, ...) SYSCALL_DEFINEx(1, _##name, __VA_ARGS__)
  #define SYSCALL_DEFINE2(name, ...) SYSCALL_DEFINEx(2, _##name, __VA_ARGS__)
  #define SYSCALL_DEFINE3(name, ...) SYSCALL_DEFINEx(3, _##name, __VA_ARGS__)
  #define SYSCALL_DEFINE4(name, ...) SYSCALL_DEFINEx(4, _##name, __VA_ARGS__)
  #define SYSCALL_DEFINE5(name, ...) SYSCALL_DEFINEx(5, _##name, __VA_ARGS__)
  #define SYSCALL_DEFINE6(name, ...) SYSCALL_DEFINEx(6, _##name, __VA_ARGS__)
  
  #define SYSCALL_DEFINE_MAXARGS	6
  
  #define SYSCALL_DEFINEx(x, sname, ...)				\
  	SYSCALL_METADATA(sname, x, __VA_ARGS__)			\
  	__SYSCALL_DEFINEx(x, sname, __VA_ARGS__)
  ```



- socket的实现：先校验参数，然后创建结构体（sock_create），最后处理socket,fd,file的关系（sock_map_fd）

- ```cpp
  SYSCALL_DEFINE3(socket, int, family, int, type, int, protocol)
  {
  	return __sys_socket(family, type, protocol);
  }
  
  int __sys_socket(int family, int type, int protocol)
  {
  	int retval;
  	struct socket *sock;
  	int flags;
  
  	/* Check the SOCK_* constants for consistency.  */
  	BUILD_BUG_ON(SOCK_CLOEXEC != O_CLOEXEC);
  	BUILD_BUG_ON((SOCK_MAX | SOCK_TYPE_MASK) != SOCK_TYPE_MASK);
  	BUILD_BUG_ON(SOCK_CLOEXEC & SOCK_TYPE_MASK);
  	BUILD_BUG_ON(SOCK_NONBLOCK & SOCK_TYPE_MASK);
  
          //校验参数
  	flags = type & ~SOCK_TYPE_MASK;
  	if (flags & ~(SOCK_CLOEXEC | SOCK_NONBLOCK))
  		return -EINVAL;
  	type &= SOCK_TYPE_MASK;
  
  	if (SOCK_NONBLOCK != O_NONBLOCK && (flags & SOCK_NONBLOCK))
  		flags = (flags & ~SOCK_NONBLOCK) | O_NONBLOCK;
  
          // 初始化/创建socket结构体
  	retval = sock_create(family, type, protocol, &sock);
  	if (retval < 0)
  		return retval;
  
          // 处理(socket结构体，fd，file)的映射关系，并返回fd
  	return sock_map_fd(sock, flags & (O_CLOEXEC | O_NONBLOCK));
  }
  ```





- sock_create：先创建socket结构体

- ```cpp
  int sock_create(int family, int type, int protocol, struct socket **res)
  {
  	return __sock_create(current->nsproxy->net_ns, family, type, protocol, res, 0);
  }
  
  int __sock_create(struct net *net, int family, int type, int protocol,
  			 struct socket **res, int kern)
  {
          int err;
  	struct socket *sock;
  	const struct net_proto_family *pf;
          ....
          /*
  	 *	Allocate the socket and allow the family to set things up. if
  	 *	the protocol is 0, the family is instructed to select an appropriate
  	 *	default.
  	 */
  	sock = sock_alloc(); // 这里创建socket结构体数据
  	if (!sock) {
  		net_warn_ratelimited("socket: no more sockets\n");
  		return -ENFILE;	/* Not exactly a match, but its the
  				   closest posix thing */
  	}
  
  	sock->type = type;
  #ifdef CONFIG_MODULES
  	/* Attempt to load a protocol module if the find failed.
  	 *
  	 * 12/09/1996 Marcin: But! this makes REALLY only sense, if the user
  	 * requested real, full-featured networking support upon configuration.
  	 * Otherwise module support will break!
  	 */
  	if (rcu_access_pointer(net_families[family]) == NULL)
  		request_module("net-pf-%d", family);
  #endif
  
  	rcu_read_lock();
  	pf = rcu_dereference(net_families[family]);
  	err = -EAFNOSUPPORT;
  	if (!pf)
  		goto out_release;
  
  	/*
  	 * We will call the ->create function, that possibly is in a loadable
  	 * module, so we have to bump that loadable module refcnt first.
  	 */
  	if (!try_module_get(pf->owner))
  		goto out_release;
  
  	/* Now protected by module ref count */
  	rcu_read_unlock();
  
          // 注意这里，这里调用的是 inet_family_ops->create
          // 再调用inet_create，最后调用到sock_init_data()，里面会设置TCP_CLOSE状态
  	err = pf->create(net, sock, protocol, kern);
  	if (err < 0)
  		goto out_module_put;
  
  	/*
  	 * Now to bump the refcnt of the [loadable] module that owns this
  	 * socket at sock_release time we decrement its refcnt.
  	 */
  	if (!try_module_get(sock->ops->owner))
  		goto out_module_busy;
  
  	/*
  	 * Now that we're done with the ->create function, the [loadable]
  	 * module can have its refcnt decremented
  	 */
  	module_put(pf->owner);
  	err = security_socket_post_create(sock, family, type, protocol, kern);
  	if (err)
  		goto out_sock_release;
  	*res = sock;
  
  	return 0;
  
  out_module_busy:
  	err = -EAFNOSUPPORT;
  out_module_put:
  	sock->ops = NULL;
  	module_put(pf->owner);
  out_sock_release:
  	sock_release(sock);
  	return err;
  
  out_release:
  	rcu_read_unlock();
  	goto out_sock_release;
  }
  
  struct socket *sock_alloc(void)
  {
  	struct inode *inode;
  	struct socket *sock;
  
      //	这里创建inode，inode是由sockfs文件系统文件系统创建的，创建的结构体是 struct socket_alloc
  	inode = new_inode_pseudo(sock_mnt->mnt_sb);
  	if (!inode)
  		return NULL;
  
      //	这里通过inode成员变量定位到 struct socket_alloc里面的socket成员变量就是本次创建的struct socket
  	sock = SOCKET_I(inode);
  
  	inode->i_ino = get_next_ino();
  	inode->i_mode = S_IFSOCK | S_IRWXUGO;
  	inode->i_uid = current_fsuid();
  	inode->i_gid = current_fsgid();
  	inode->i_op = &sockfs_inode_ops;
  
  	return sock;
  }
  ```





- SOCKET_I的实现：注意这里struct socket_alloc结构体中socket和inode是一同创建的，这里是通过inode找socket地址 或者通过socket找inode地址

- ```cpp
  struct socket_alloc {
  	struct socket socket;
  	struct inode vfs_inode;
  };
  
  static inline struct socket *SOCKET_I(struct inode *inode)
  {
          // container_of 是一个宏，思想是通过元素找该元素的容器，然后offsetof到容器中socket成员的地址
          // 这就找到了struct socket_alloc中的socket
          // 通过containof宏就可以计算出socket的地址
  	return &container_of(inode, struct socket_alloc, vfs_inode)->socket;
  }
  
  static inline struct inode *SOCK_INODE(struct socket *socket)
  {
          // 这里和上面是一样的原理，通过socket找inode，后面会有地方用到
  	return &container_of(socket, struct socket_alloc, socket)->vfs_inode;
  }
  ```





- sock_map_fd函数：

- ```cpp
  static int sock_map_fd(struct socket *sock, int flags)
  {
  	struct file *newfile;
          
      //	按照当前进程的fd限制条件，分配一个未被使用的fd
      //	比如: ulimit -n 限制 
  	int fd = get_unused_fd_flags(flags);
  	if (unlikely(fd < 0)) {
          //	获取失败则释放sock
  		sock_release(sock);
  		return fd;
  	}
  
      //	为socket创建一个struct file结构
      //	这里通过socket找到inode，进行 socket inode file 的相互关联
  	newfile = sock_alloc_file(sock, flags, NULL);
  	if (likely(!IS_ERR(newfile))) {
                  // fd和file进行关联，并且把fd加入到fdtable中:
  		fd_install(fd, newfile); // fd_install
  		return fd;
  	}
  
      // 创建file失败，把fd put进task_struct->files->next_fd中，即把fd给还回去，下一次分配的时候可以直接用
  	put_unused_fd(fd);
  	return PTR_ERR(newfile);
  }
  ```



- fd_install函数的实现，**current是一个宏，具体是代表当前task**，把fd加入到当前task_struct->files->fdtable中

- ```cpp
  void fd_install(unsigned int fd, struct file *file)
  {
          // 这个current的实现是一个宏定义
  	__fd_install(current->files, fd, file);
  }
  
  DECLARE_PER_CPU(struct task_struct *, current_task);
  
  static __always_inline struct task_struct *get_current(void)
  {
  	return this_cpu_read_stable(current_task);
  }
  
  #define current get_current()
  
  void __fd_install(struct files_struct *files, unsigned int fd,
  		struct file *file)
  {
  	struct fdtable *fdt;
  
  	rcu_read_lock_sched();
  
  	if (unlikely(files->resize_in_progress)) {
  		rcu_read_unlock_sched();
          //	给files上锁，并发
  		spin_lock(&files->file_lock);
  		fdt = files_fdtable(files);
  		BUG_ON(fdt->fd[fd] != NULL);
  		rcu_assign_pointer(fdt->fd[fd], file); // 添加到table中
  		spin_unlock(&files->file_lock);
  		return;
  	}
  	/* coupled with smp_wmb() in expand_fdtable() */
  	smp_rmb();
  	fdt = rcu_dereference_sched(files->fdt);
  	BUG_ON(fdt->fd[fd] != NULL);
  	rcu_assign_pointer(fdt->fd[fd], file);
  	rcu_read_unlock_sched();
  }
  ```





# 总结

- 创建struct socket、struct inode、int fd、struct file
- 相互关联绑定socket、inode、fd、file
- 加入到task_struct->files中
- 设置TCP_CLOSE状态
- 返回int fd
- 即让每个fd都能对应得到socket
- [参考](https://zhuanlan.zhihu.com/p/458414504)
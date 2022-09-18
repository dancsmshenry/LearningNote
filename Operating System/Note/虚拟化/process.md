进程退出后所有的线程也会退出



进程的切换一定发生在中断/异常/系统调用处理过程中



https://blog.csdn.net/a745233700/article/details/120866618



![](../image/process的地址空间.jpg)



- 进程的数据结构：
  - 标识符： 跟这个进程相关的唯一标识符，用来区别其他进程
  - 状态: 进程的几个状态（等待、运行、停止）
  - 优先级: 进程的优先级
  - 程序计数器: 程序中即将被执行的下一条指令的地址。
  - 内存指针：包括程序代码和进程相关数据的指针，还有和其他进程共享的内存块的指针
  - 上下文数据：进程执行时处理器的寄存器中的数据
  - I/O状态信息：包括显示的I/O请求,分配给进程的I/O设备和被进程使用的文件列表
  - 记账信息：可能包括处理器时间总和，使用的时钟数总和，时间限制，记账号等-
- 这些所有的信息都存放在一个进程的数据结构中task_struct, 也叫PCB。每个进程在内核中都有一个进程控制块(PCB)来维护进程相关的信息,Linux内核的进程控制块是task_struct结构体. 它在进程的运行时会被加载到RAM中





- 对task_struct结构体的分析

  - ```cpp
    /* Open file information: */
    struct files_struct   *files;
    //	是一个指针，指向被打开了的文件表
    ```

  - ```cpp
    /* Signal handlers: */
      struct signal_struct    *signal;
      struct sighand_struct __rcu   *sighand;
      sigset_t      blocked;
      sigset_t      real_blocked;
      /* Restored if set_restore_sigmask() was used: */
      sigset_t      saved_sigmask;
      struct sigpending   pending;
    //	信号处理字段
    ```

  - ```cpp
    //	进程的状态
    volatile long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
    
    #define TASK_RUNNING        0//进程要么正在执行，要么准备执行
    #define TASK_INTERRUPTIBLE  1 //可中断的睡眠，可以通过一个信号唤醒
    #define TASK_UNINTERRUPTIBLE    2 //不可中断睡眠，不可以通过信号进行唤醒
    #define __TASK_STOPPED      4 //进程停止执行
    #define __TASK_TRACED       8 //进程被追踪
    /* in tsk->exit_state */ 
    #define EXIT_ZOMBIE     16 //僵尸状态的进程，表示进程被终止，但是父进程还没有获取它的终止信息，比如进程有没有执行完等信息。                     
    #define EXIT_DEAD       32 //进程的最终状态，进程死亡
    /* in tsk->state again */ 
    #define TASK_DEAD       64 //死亡
    #define TASK_WAKEKILL       128 //唤醒并杀死的进程
    #define TASK_WAKING     256 //唤醒进程
    ```

  - ```cpp
    //	进程的唯一标识
    pid_t pid;//进程的唯一标识
    pid_t tgid;// 线程组的领头线程的pid成员的值
    //在Linux系统中，一个线程组中的所有线程使用和该线程组的领头线程（该组中的第一个轻量级进程）相同的PID，并被存放在tgid成员中。只有线程组的领头线程的pid成员才会被设置为与tgid相同的值。注意，getpid()系统调用返回的是当前进程的tgid值而不是pid值。（线程是程序运行的最小单位，进程是程序运行的基本单位。）
    ```

  - ```cpp
    //	进程的亲属关系
    struct task_struct *real_parent; /* real parent process */ // 指向其父进程，如果创建它的父进程不再存在，则指向PID为1的init进程
    struct task_struct *parent; /* recipient of SIGCHLD, wait4() reports */ // 指向其父进程，当它终止时，必须向它的父进程发送信号。它的值通常与real_parent相同
    struct list_head children;    /* list of my children */ // 表示链表的头部，链表中的所有元素都是它的子进程（进程的子进程链表）
    struct list_head sibling;    /* linkage in my parent's children list */ // 用于把当前进程插入到兄弟链表中（进程的兄弟链表）
    struct task_struct *group_leader;    /* threadgroup leader */ // 指向其所在进程组的领头进程
    ```

  - [参考](https://blog.csdn.net/qq_52703909/article/details/123664176)
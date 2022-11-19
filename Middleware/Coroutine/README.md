# 前置知识

## getcontext

- 获取当前的CPU上下文，并填充到对应的ucontext_t（即填充到ucp中）

- ```cpp
  #include <ucontext.h>
  int getcontext(ucontext_t *ucp);
  ```



## setcontext

- 将当前的CPU上下文修改为ucp指定的上下文中

- ```cpp
  #include <ucontext.h>
  int setcontext(const ucontext_t *ucp);
  ```



## makecontext

- 修改ucp所指向的上下文，ucp是被getcontext()所初始化的上下文。当这个上下文采用swapcontext()或者setcontext()被恢复，程序的执行会切换到func的调用，通过makecontext()调用的argc传递func的参数

- ```cpp
  #include <ucontext.h>
  void makecontext(ucontext_t *ucp, void (*func)(void), int argc, ...);
  ```

- 我的理解：让当前的coroutine在ucp的ucontext_t上下文中执行func函数



## swapcontext

- 保存当前的上下文到oucp所指向的数据结构，并且将当前上下文设置为ucp所指向的上下文

- ```cpp
  #include <ucontext.h>
  int swapcontext(ucontext_t *restrict oucp, const ucontext_t *restrict ucp);
  ```

- 我的理解：将当前coroutine的上下文保存好，接着切换到main coroutine中
- 即控制权就回到了coroutine schedule的main coroutine中





对coroutine中共享栈stack的理解

- 通过makecontext等的设置，将在栈上开辟的一块空间用于coroutine的运行空间
- 因此每次上下文的切换都要顾及这块空间的切换
- 是怎样被yield出去的？





### 对ucontext_t的理解

- ```cpp
  typedef struct ucontext_t
  {
      unsigned long int __ctx(uc_flags);
      struct ucontext_t *uc_link; //下一个要resume回来继续执行的栈空间，当为空时结束进程
      stack_t uc_stack;           //栈空间
      mcontext_t uc_mcontext;     //保存的寄存器信息，saved registers
      sigset_t uc_sigmask;        //阻塞的信号signals being blocked
      struct _libc_fpstate __fpregs_mem;
  } ucontext_t;
  
  typedef struct
  {
      void *ss_sp;	//	指向的栈（这里的栈不是进程中的栈，准确来说是当前上下文执行的空间）的开头
      int ss_flags;
      size_t ss_size;	//	栈的大小
  } stack_t;
  ```





# ~~缺点~~

- 云凤的协程是用setcontext实现的，但是这只是在linux下，windows下他建议可以用windows的fiber去实现
- 他实现的协程是无栈协程不用担心溢出的问题（同一调度器共享栈空间）



https://blog.csdn.net/weixin_43679037/article/details/121444824

https://blog.codingnow.com/2012/07/c_coroutine.html

https://www.cyhone.com/articles/analysis-of-cloudwu-coroutine/
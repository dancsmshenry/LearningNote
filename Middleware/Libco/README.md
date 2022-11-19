# 前置知识

## 寄存器

- 以常见的64位处理器作为例子

- | 标号 | 作用         |
  | ---- | ------------ |
  | %rax | 返回值       |
  | %rbx | 被调用者保存 |
  | %rcx | 第4个参数    |
  | %rdx | 第3个参数    |
  | %rsi | 第2个参数    |
  | %rdi | 第1个参数    |
  | %rbp | 被调用者保存 |
  | %rsp | 栈指针       |
  | %r8  | 第5个参数    |
  | %r9  | 第6个参数    |
  | %r10 | 调用者保存   |
  | %r11 | 调用者保存   |
  | %r12 | 被调用者保存 |
  | %r13 | 被调用者保存 |
  | %r14 | 被调用者保存 |
  | %r15 | 被调用者保存 |

- 而协程的切换，不需要考虑**%r10和%r11**这两个寄存器上的值



## calloc

- calloc在动态分配完内存后，自动初始化该内存空间为零，而malloc不做初始化，分配到的空间中的数据是随机数据
- void* calloc（unsigned int num，unsigned int size）
- num：对象个数，size：对象占据的内存字节数，相较于malloc函数，calloc函数会自动将内存初始化为0





# coroutine的函数

## co_create

- 先检查是否有放置thread的上下文，如果没有放置，就调用co_init_curr_thread_env()初始化当前thread的上下文
- 参数：
  - ppco为指向指针的指针，即最后生成的coroutine会被该指针指向
  - attr是__
  - pfn为coroutine需要执行的函数
  - arg为传入的参数
- 最后调用co_create_env生成coroutine



## co_create_env

- 



## co_get_curr_thread_env

- 获取当前thread的上下文



## co_init_curr_thread_env

- 初始化当前thread的上下文


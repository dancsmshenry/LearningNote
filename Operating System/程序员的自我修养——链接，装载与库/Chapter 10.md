# 10.1 程序的内存布局

10.1 程序的内存布局

- 在32位的系统里，内存空间拥有4GB的寻址能力，用户可以使用一个32位的指针访问任意内存位置
- windows默认将高地址的2GB空间分配给内核
- linux默认将高地址的1GB分配给内核
- 剩余空间是用户空间



- 栈：用于维护函数调用的上下文，离开了栈函数调用就没法实现
  - 栈通常在用户空间的最高地址处分配
- 堆：用来容纳应用程序动态分配的内存区域
  - 当使用malloc或new分配内存时，得到的内存就在堆里
  - 堆通常在栈下方，没有固定统一的存储区域
- 可执行文件映像：可执行文件在内存里的映像
- 保留区：是对内存中收到保护而禁止访问的内存区域的总成
- <img src="images/linux进程地址空间布局.png" style="zoom:150%;" />
- 动态链接库映射区：用于映射装载的动态链接库



- 段错误，非法操作
  - 当指针指向一个不允许读或写的内存地址，而程序却试图利用指针来读或来写该地址的时候，就会报错





10.2 栈与调用惯例

10.2.1 什么是栈

- 用户可以将数据压入栈中，也可以将已经压入栈中的数据弹出
- 先入栈的数据后出栈
- 栈顶由称esp的寄存器进行定位，压栈的操作使栈顶的地址减小，弹出的操作使栈顶地址增大
- 栈顶的地址时0xbffffff4



- 栈保存了一个函数调用所需要的维护信息，称为堆栈帧或**活动记录**，堆栈帧的内容：
  - 函数的返回地址和参数
  - 临时变量：包括函数的非静态局部变量以及编译器自动生成的其他临时变量
  - 保存的上下文：包括函数调用前后需要保持不变的寄存器



# 10.2 栈与调用惯例



# 10.3 堆与内存管理



# 10.4 本章小结
# new 和 delete 的实现

- new 的实现：
  - 首先调用名为 operator new 的标准库函数，分配足够大的原始为类型化的内存，以保存指定类型的一个对象
  - 接下来运行该类型的一个构造函数，用指定初始化构造对象
  - 最后返回指向新分配并构造后的的对象的指针
  - 另一种说法（关于new）：
    - 简单类型直接调用operator new分配内存
    - 对于复杂结构，先调用operator new分配内存，然后在分配的内存上调用构造函数
  - 另一种说法（关于new[]）：
    - 对于简单类型，new[]计算好大小后调用operator new
    - 对于复杂数据结构，new[]先调用operator new[]分配内存，然后在p的前四个字节写入数组大小n，然后调用n次构造函数，针对复杂类型，new[]会额外存储数组大小
- delete 的实现：
  - 首先对指针指向的对象运行适当的析构函数
  - 然后通过调用名为 operator delete 的标准库函数释放该对象所用内存
  - 另一种说法
    - 简单数据类型默认只是调用free函数；复杂数据类型先调用析构函数再调用operator delete
    - 针对简单类型，delete和delete[]等同
    - 假设指针p指向new[]分配的内存。因为要4字节存储数组大小，实际 分配的内存地址为[p-4]，系统记录的也是这个地址。delete[]实际释放的就是p-4指向的内存。而delete会 直接释放p指向的内存，这个内存根本没有被系统记录，所以会崩溃
- 需要在 new [] 一个对象数组时，需要保存数组的维度，C++ 的做法是在分配数组空间时多分配了 4  个字节的大小，专门保存数组的大小，在 delete [] 时就可以取出这个保存的数，就知道了需要调用析构 函数多少次了





# new/delete 与 malloc/free 的异同

相同点：

- 都是用于内存的动态申请和释放



不同点：

- 前者是C++运算符（不支持重载），后者是C/C++语言标准库函数（支持覆盖）

- 前者不需要头文件，后者需要 stdlib.h 头文件

- new 自动计算要分配的空间大小，malloc 需要手工计算

- new 是类型安全的（好像是有内部的异常机制），malloc 不是

  - ```cpp
    int *p = new float[2]; //编译错误
    int *p = (int*)malloc(2 * sizeof(double));//编译无错误
    ```

- malloc 和 free 返回的是 void 类型指针（所以要进行类型转换），new 和 delete 返回的是具体类型指针

- malloc 和 free 仅仅分配或回收空间，不调用析构或构造函数（所以要手动构造和析构）

- new调用名为operator new的标准库函数分配足够空间并调用相关对象的构造函数，delete对指针所指 对象运行适当的析构函数；然后通过调用名为operator delete的标准库函数释放该对象所用内存。后者均没有相关调用

- new是封装了malloc，直接free不会出错（但是这只是释放了内存，没有析构对象）





# 为什么要new和free

- 在对非基本数据类型的对象使用的时候，对象创建的时候还需要执行构造函数，销毁的时候要执行析构函数
- 而malloc/free是库函数，是已经编译的代码，所以不能把构造函数和析构函数的功能强加给 malloc/free
- 所以new/delete是必不可少的





# 多次delete

- 经过一次delete之后，指针就变成了悬空指针或者野指针，也就是说它执行的地方是随机的
- 所以如果再一次delete的话，就可能删除了其他进程的重要数据，使得其他进程codedown
- 我认为吧，为了防止意外发生，最好还是在指针被delete之后让他指向nullptr，防止使用者乱用.....





# free如何知道要free多大的空间

- malloc函数的实现是以块分配内存，在被分配的块中包括两部分。第一部分中存储含有报头的元数据，它其中包含有分配块的大小信息，是一个常量；第二部分中存储实际用户数据。而使用malloc分配内存返回的是第二部分用户数据的地址。而块的两个部分在内存中的存储取决有编译器的实现，一般有两种情况，第一种是最常见的，即元数据和用户数据是连续的，存储在连续空间位置。第二种是两部分分开存储。
- 所以如果申请一段数组，访问array[-1]也是可以的





# free后的内存是返还给操作系统吗

- 不是，被free回收的内存首先被ptmalloc使用双链表保存起来，当用户下一次申请内存的时候，会尝试从这些内存中寻找合适的返回
- 这样就避免了频繁的系统调用，占用过多的系统资源。同时ptmalloc 也会尝试对小块内存进行合并，避免过多的内存碎片







# delete和delete[]的区别

- delete只会调用一次析构函数
- delete[]会调用数组中的每个元素的析构函数
- PS：
  - 其实如果是普通的数组或者是单个变量，都是可以用delete的（为了规范才用[]）（而且我怀疑其实普通的数组和类对象的数组是不一样的构造的...）
  - 但是如果是类对象的数组的话，就不能用delete了，因为只会触发一次析构





# new和malloc的区别

- new/delete是C++关键字，需要编译器支持。malloc/free是库函数，需要头文件支持
- 使用new操作符申请内存分配时无须指定内存块的大小，编译器会根据类型信息自行计算。而malloc 则需要显式地指出所需内存的尺寸
-  new操作符内存分配成功时，返回的是对象类型的指针，类型严格与对象匹配，无须进行类型转 换，故new是符合类型安全性的操作符。而malloc内存分配成功则是返回void * ，需要通过强制类型转换 将void*指针转换成我们需要的类型
- new内存分配失败时，会抛出bac_alloc异常。malloc分配内存失败时返回NULL
- new会先调用operator new函数，申请足够的内存（通常底层使用malloc实现）。然后调用类型的构 造函数，初始化成员变量，最后返回自定义类型指针。delete先调用析构函数，然后调用operator delete 函数释放内存（通常底层使用free实现）。malloc/free是库函数，只能动态的申请和释放内存，无法强制 要求其做自定义类型对象构造和析构工作





# malloc，realloc，calloc的区别

- ```cpp
  void* malloc(unsigned int num_size);
  int *p = malloc(20*sizeof(int));//申请20个int类型的空间；
  
  void* calloc(size_t n,size_t size);
  int *p = calloc(20, sizeof(int));//省去了人为空间计算
  
  void realloc(void*, size_t new_size);//给 动态分配的空间 分配 额外的空间，用于扩充容量
  ```

- malloc申请的空间的值是随机初始化的，calloc申请的空间的值是初始化为0的





# malloc与free实现原理

- 在标准C库中，提供了malloc/free函数分配释放内存，这两个函数底层是由brk、mmap、，munmap这些系统调用实现的



- brk是将数据段(.data)的最高地址指针
- _edata往高地址推
- mmap是在进程的虚拟地址空间中（堆和栈中间，称为文件映射区域的地方）找一块空闲的虚拟内存。
- 这两种方式分配的都是虚拟内存，没有分配物 理内存。在第一次访问已分配的虚拟地址空间的时候，发生缺页中断，操作系统负责分配物理内存，然 后建立虚拟内存和物理内存之间的映射关系



- malloc小于128k的内存，使用brk分配内存，将_edata往高地址推；
- malloc大于128k的内存，使用 mmap分配内存，在堆和栈之间找一块空闲内存分配；
- brk分配的内存需要等到高地址内存释放以后才能 释 放 ， 而 mmap 分 配 的 内 存 可 以 单 独 释 放 
- 当 最 高 地 址 空 间 的 空 闲 内 存 超 过 128K （ 可 由 M_TRIM_THRESHOLD选项调节）时，执行内存紧缩操作（trim）。在上一个步骤free的时候，发现最 高地址空闲内存超过128K，于是内存紧缩





- malloc是从堆里面申请内存，也就是说函数返回的指针是指向堆里面的一块内存
- 操作系统中有一个记录空闲内存地址的链表
- 当操作系统收到程序的申请时，就会遍历该链表，然后就寻找第一个空间大于所申请空间的堆结点，然后就将该结点从空闲结点链表中删除，并将该结点的空间分配给程序





# malloc申请的空间能用delete释放吗

- malloc/free的操作对象都是必须明确大小的，而且不能用于动态类上
- malloc/free不能执行构造函数和析构函数，所以动态对象是不行的







# delete[]

- 数组中的元素按逆序的顺序进行销毁
- 动态数组管理new一个数组时，[]中必须是一个整数，但是不一定是常量整数，普通数组必须是一个常量整数
- new动态数组返回的并不是数组类型，而是一个元素类型的指针
- new在内存分配上面有一些局限性，new的机制是将内存分配和对象构造组合在一起，同样的， delete也是将对象析构和内存释放组合在一起的。allocator将这两部分分开进行，allocator申请一部分内存，不进行初始化对象，只有当需要的时候才进行初始化操作





# 几种类型的new

plain new

- 普通的new

- 因此plain new在空间分配失败的情况下，抛出异常std::bad_alloc而不是返回NULL，因此通过判断返回 值是否为NULL是徒劳的

- ```cpp
  void* operator new(std::size_t) throw(std::bad_alloc);
  void operator delete(void *) throw();
  ```



nothrow new

- nothrow new在空间分配失败的情况下不抛出异常，而是返回nullptr

- ```cpp
  void * operator new(std::size_t,const std::nothrow_t&) throw();
  void operator delete(void*) throw();
  ```



placement new

- 这种new允许在一块已经分配成功的内存上重新构造对象或对象数组。placement new不用担心内存分配 失败，因为它根本不分配内存，它做的唯一一件事情就是调用对象的构造函数

- ```cpp
  void* operator new(size_t,void*);
  void operator delete(void*,void*);
  ```

- PS:

  - palcement new的主要用途就是反复使用一块较大的动态分配的内存来构造不同类型的对象或者他们的 数组
  - placement new构造起来的对象数组，要显式的调用他们的析构函数来销毁（析构函数并不释放对象的内存），千万不要使用delete，这是因为placement new构造起来的对象或数组大小并不一定等于原来 分配的内存大小，使用delete会造成内存泄漏或者之后释放内存时出现运行时错误。



https://blog.csdn.net/TABE_/article/details/123098479

https://www.zhihu.com/question/33979489



malloc分配空间时，小于128k的用brk

大于的用mmap
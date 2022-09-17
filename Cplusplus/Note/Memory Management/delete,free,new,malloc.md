# malloc

## malloc，realloc，calloc的区别

- ```cpp
  void* malloc(unsigned int num_size);
  int *p = malloc(20*sizeof(int));//申请20个int类型的空间；
  
  void* calloc(size_t n,size_t size);
  int *p = calloc(20, sizeof(int));//省去了人为空间计算
  
  void realloc(void*, size_t new_size);//给 动态分配的空间 分配 额外的空间，用于扩充容量
  ```

- malloc申请的空间的值是随机初始化的，calloc申请的空间的值是初始化为0的



## 实现

- 在C标准库中，提供了malloc/free函数分配释放内存，这两个函数底层是由brk、mmap、munmap这些系统调用实现的

  - brk是将数据段(.data)的最高地址指针_edata往高地址推

  - mmap是在进程的虚拟地址空间中（堆和栈中间，称为文件映射区域的地方）找一块空闲的虚拟内存

- 这两种方式分配的都是虚拟内存，没有分配物理内存。在第一次访问已分配的虚拟地址空间的时候，发生缺页中断，操作系统负责分配物理内存，然后建立虚拟内存和物理内存之间的映射关系

- malloc小于128k的内存，使用brk分配内存
- malloc大于128k的内存，使用 mmap分配内存
- brk分配的内存需要等到高地址内存释放以后才能释放，而mmap分配的内存可以单独释放 
- 当 最 高 地 址 空 间 的 空 闲 内 存 超 过 128K （ 可 由 M_TRIM_THRESHOLD选项调节）时，执行内存紧缩操作（trim）。在上一个步骤free的时候，发现最 高地址空闲内存超过128K，于是内存紧缩

- malloc是从堆里面申请内存，也就是说函数返回的指针是指向堆里面的一块内存
- 操作系统中有一个记录空闲内存地址的链表
- 当操作系统收到程序的申请时，就会遍历该链表，然后就寻找第一个空间大于所申请空间的堆结点，然后就将该结点从空闲结点链表中删除，并将该结点的空间分配给程序

- https://zhuanlan.zhihu.com/p/105651237







# new

## 实现

- 首先调用名为 operator new 的标准库函数，分配足够大的原始为类型化的内存，以保存指定类型的一个对象
  - 如果是简单类型，就直接operator new分配内存
  - 如果是复杂类型，就先operator new分配内存，然后调用对象的构造函数
- 最后返回指向新分配并构造后的的对象的指针

- ```cpp
  Object* obj;
  try{
      void* mem = operator new(sizeof(Object)); //分配内存
      obj = static_cast<Object*>(mem);        //指针转换
      obj->Objcect::Object();                //原地构造
  }
  catch( std::bad_alloc ){
      //失败就不执行构造
  }
  ```



而对于new[]来说，是这样的：

- 对于简单类型，new[]计算好大小后调用operator new
- 对于复杂数据结构，new[]先调用operator new[]分配内存，然后在指针的前四个字节写入数组大小n，然后调用n次构造函数
  - 即针对复杂类型，new[]会额外存储数组大小



## 几种类型的new

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







# free

## free如何知道要free多大的空间

- malloc函数的实现是以块分配内存，在被分配的块中包括两部分。第一部分中存储含有报头的元数据，它其中包含有分配块的大小信息，是一个常量；第二部分中存储实际用户数据。而使用malloc分配内存返回的是第二部分用户数据的地址。而块的两个部分在内存中的存储取决有编译器的实现，一般有两种情况，第一种是最常见的，即元数据和用户数据是连续的，存储在连续空间位置。第二种是两部分分开存储。
- 所以如果申请一段数组，访问array[-1]也是可以的



## 为什么free后指针不指向null

- 因为传入free的是一个值，无论怎么修改都改变不了一级指针真正的指向
- 或者说可以传入二级指针来解决，但如果二级指针指向的是一个const指针就又不行了



## free后的内存是返还给操作系统吗

- 不是，被free回收的内存首先被ptmalloc使用双链表保存起来，当用户下一次申请内存的时候，会尝试从这些内存中寻找合适的返回
- 这样就避免了频繁的系统调用，占用过多的系统资源。同时ptmalloc 也会尝试对小块内存进行合并，避免过多的内存碎片







# delete

## 实现

- 针对不同的对象有不同的处理
  - 简单类型的数据类型，只是调用free函数
  - 复杂类型的函数则要先调用析构函数，再调用operator delete 的标准库函数释放该对象所用内存
- PS：针对简单类型，delete和delete[]是相同的

- - 针对简单类型，delete和delete[]等同
  - 假设指针p指向new[]分配的内存。因为要4字节存储数组大小，实际 分配的内存地址为[p-4]，系统记录的也是这个地址。delete[]实际释放的就是p-4指向的内存。而delete会 直接释放p指向的内存，这个内存根本没有被系统记录，所以会崩溃



## 为什么不能多次delete

- 经过一次delete之后，指针就变成了悬空指针或者野指针，也就是说它执行的地方是随机的
- 所以如果再一次delete的话，就可能删除了其他进程的重要数据，使得其他进程codedown
- 我认为吧，为了防止意外发生，最好还是在指针被delete之后让他指向nullptr，防止使用者乱用.....



## delete和delete[]的区别

- delete只会调用一次析构函数
- delete[]会调用数组中的每个元素的析构函数
- PS：
  - 其实如果是普通的数组或者是单个变量，都是可以用delete的（为了规范才用[]）（而且我怀疑其实普通的数组和类对象的数组是不一样的构造的...）
  - 但是如果是类对象的数组的话，就不能用delete了，因为只会触发一次析构



## delete[]

- 数组中的元素按逆序的顺序进行销毁
- 动态数组管理new一个数组时，[]中必须是一个整数，但是不一定是常量整数，普通数组必须是一个常量整数
- new动态数组返回的并不是数组类型，而是一个元素类型的指针
- new在内存分配上面有一些局限性，new的机制是将内存分配和对象构造组合在一起，同样的， delete也是将对象析构和内存释放组合在一起的。allocator将这两部分分开进行，allocator申请一部分内存，不进行初始化对象，只有当需要的时候才进行初始化操作



## 为什么delete指向的内存不能用

- 当delete后，相当于把内存归还给了os或者allocater，虽然我们仍然可以用指针来操控这段内存，但是有可能os或者allocater把内存给了其他的用途，这时后访问就是UB行为了
  - 所以delete的语义其实是指针不要了这块内存，然后释放拥有权，后续有其他人去接管，但如果你继续去用它的话，其实是一件很没品的事情



- 从OS的角度考虑，我们用到的都是虚拟内存，在mmu映射过后才会得到真正的物理内存的，如果你释放了内存，那么地址有可能后续不指向有效的内存空间，这时候有可能访问成功（但是会修改别人的数据，导致coredump），有可能访问失败（比如说映射到了只读内存或内核空间内存），这一切都是UB行为
  - 当然，如果在没有mmu的系统的话，就不会有这种情况发生了，就都可以访问，只是不能保证语义上的正确







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

- new是C++关键字，需要编译器支持；malloc是库函数，需要头文件支持

- new操作符申请内存分配时无须指定内存块的大小，编译器会根据类型信息自行计算；而malloc则需要显式地指出所需内存的尺寸

- new操作符内存分配成功时，返回的是对象类型的指针，类型严格与对象匹配，无须进行类型转换；而malloc内存分配成功则是返回void * ，需要强制类型转换

- new内存分配失败时，会抛出bac_alloc异常；malloc分配内存失败时返回NULL







# new，delete出现的背景

- 在对非基本数据类型的对象使用的时候，对象创建的时候还需要执行构造函数，销毁的时候要执行析构函数
- 而malloc/free是库函数，是已经编译的代码，所以不能把构造函数和析构函数的功能强加给malloc/free







# malloc申请的空间能用delete释放吗

- malloc/free的操作对象都是必须明确大小的，而且不能用于动态类上
- malloc/free不能执行构造函数和析构函数，所以动态对象是不行的



# 为什么指针不用了以后必须要置空

- https://www.zhihu.com/question/531243779/answer/2469998116
- 如果不置空，极有可能出现二进制漏洞的情况





# 参考

- https://www.zhihu.com/question/531243779

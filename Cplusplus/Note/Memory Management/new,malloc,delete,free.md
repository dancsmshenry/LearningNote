## 4、new 和 delete 的实现原理

- new 的实现：
  - 如果是简单类型，就直接调用 operator new 分配内存
  - 首先调用名为 operator new 的标准库函数，分配足够大的原始为类型化的内存，以保存指定类型的一个对象
  - 接下来运行该类型的一个构造函数，用指定初始化构造对象
  - 最后返回指向新分配并构造后的的对象的指针
- delete 的实现：
  - 首先对指针指向的对象运行适当的析构函数
  - 然后通过调用名为 operator delete 的标准库函数释放该对象所用内存

## 5、new/delete 与 malloc/free 的异同

- 相同点：

  - 都是用于内存的动态申请和释放

- 不同点：

  - 前者是C++运算符（不支持重载），后者是C/C++语言标准库函数（支持覆盖）

  - 前者不需要头文件，后者需要 stdlib.h 头文件

  - new 自动计算要分配的空间大小，malloc 需要手工计算

  - new 是类型安全的（好像是有内部的异常机制），malloc 不是

    - ```cpp
      int *p = new float[2]; //编译错误
      int *p = (int*)malloc(2 * sizeof(double));//编译无错误
      ```

  - malloc 和 free 返回的是 void 类型指针（所以要进行类型转换），new 和 delete 返回的是具体类型指针

  - malloc 和 free 仅仅分配或回收空间，不调用析构或构造函数



- 有了malloc为什么还需要new
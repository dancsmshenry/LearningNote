# NULL 和 nullptr 的区别

只有NULL的时候

- 在C中只有 NULL ，用来表示空指针


- 而在CPP中，NULL被定义为整数0（因为 cpp 是强类型语言， void* 是不能隐式转换成其他类型，所以引入0来当作空指针）

  - 这里钻了语法中指针地址不会为0的空子，人为规定当指针为0时就是空指针。但无论怎么说0就是0，他就是个int而不是ptr，在类型推导时会出问题

- ```cpp
  #ifndef NULL
      #ifdef __cplusplus
          #define NULL 0
      #else
          #define NULL ((void *)0)
      #endif
  #endif
  ```





nullptr出现的背景

- 背景一

  - 因为CPP中指针必须有明确的类型定义，但是将NULL定义为0带来的问题是无法与整数的0区分，因为CPP中允许有函数重载

  - ```cpp
    void func(int a);  // A
    
    void func(int* a); // B
    
    func(NULL);    // 该调用哪个？
    func(nullptr); // 确定调用B
    ```

  - 所以容易造成以上尴尬

  - 为了解决这些问题，引入nullptr，nullptr可以明确区分整型和指针类型，能够根据环境自动转换成相应的指针类型，但不会被转换成任何整型，所以不会造成参数传递错误

- 背景二

  - NULL会被模板推断为int，但nullptr可以完美转发至T*

- 在C里面，0，NULL，（void*）0都代表了空指针；但是在CPP里面，void *不能作为右值，即不能 int * p = (void*)0，所以在CPP里面NULL只能是0

  - 而在CPP里面，0有是整型变量，有时空指针，容易造成编译器误导
  - 为了防止误导，引入nullptr；为了兼容C，保留NULL
  - PS：C语言不支持函数重载





nullptr的实现方式

- 一种可能的实现方式（所以nullptr可以转为int*）

- ```cpp
  struct nullptr_t
  {
      void operator&() const = delete;  // Can't take address of nullptr
  
      template <class T>
      inline operator T*() const
      {
          return 0;
      }
  
      template <class C, class T>
      inline operator T C::*() const
      {
          return 0;
      }
  };
  ```

- nullptr还可以抛出异常

- 同时nullptr是指针类型，不会与整形变量相混淆





nullptr的缺点

- ```cpp
  void fun(char* p)
  {
   cout<< "char* p" <<endl;
  }
  void fun(int* p)
  {
   cout<< "int* p" <<endl;
  }
  void fun(int p)
  {
   cout<< "int p" <<endl;
  }
  int main()
  {
   fun((char*)nullptr);//语句1（char* p）
   fun(nullptr);//语句2(不知道用呢一个)
   fun(NULL);//语句3（int p）
   return 0;
  }
  ```







# 总结

- 使用nullptr可以不用担心整型和指针类型的重载，不会产生二义性导致编译失败
- 0和空指针分别表示不同的含义，使用nullptr可以更好的支持模板编程
- 使用nullptr使代码更安全，让用户编写代码更清晰直观







# 参考

- https://blog.csdn.net/qq_18108083/article/details/84346655
- effective modern cpp一书
- https://www.zhihu.com/question/55936870/answer/147640578
- https://zhuanlan.zhihu.com/p/270390408


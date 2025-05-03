# using

- ```cpp
  // 起别名
  typedef void (* FUN_) (int, int);	//	有点模糊
  using FUN_ = void(*)(int, int);		//	简洁明了
  
  // 引入命名空间
  using namespace std; // z
  
  // 给模板起别名（typename不支持给模板起别名，所以得用using）
  template<typename T, int C>
  class A {
      T i;
      int a = C;
  };
  
  template<typename T>
  using B = A<T, 6>;
  B<int> a1;
  ```







# typedef

- ```cpp
  typedef int INTINT;//将int定义为INTINT
  typedef unsigned int UINT;//同上
  
  typedef void (*voidfunc)(int a, int b)//定义一个函数指针，用于回调函数
      
  typedef decltype(func) Func2  // Func2是函数类型；
  typedef decltype(func) *Func2P // Func2是函数指针类型；
  ```

- C++编译器不支持使用typedef关键词为模板类设置别名，但是使用using的方式声明一个关键词却是允许的，只是这个是C++11标准才有的，如果在编译时不加上--std=c++11使用新的标准的话，编译器一样会报错



### 与define的区别

- \#define 进行简单的进行字符串替换。 #define 宏定义可以使用 #ifdef、#ifndef 等来进行逻辑判断，还可以使用 #undef 来取消定义。
- typedef 是为一个类型起新名字。typedef 符合（C语言）范围规则，使用 typedef 定义的变量类型，其作用范围限制在所定义的函数或者文件内（取决于此变量定义的位置），而宏定义则没有这种特性







# 参考

- https://blog.csdn.net/liitdar/article/details/80069638

# using

- ```cpp
  typedef void (* FUN_) (int, int);//有点模糊
  using FUN_ = void(*)(int, int);//简洁明了
  
  using namespace std;
  
  template<typename T, int C>
  class A {
      T i;
      int a = C;
  };
  
  template<typename T>
  using B = A<T, 6>;
  B<int> a1;
  
  using F = int(int*, int);
  using PF = int(*)(int*,int);
  F  f1(int);    //错误： F是函数类型
  PF  f1(int);   //正确： PF是函数指针类型
  ```

- https://www.jianshu.com/p/6ecfd541ec04





# typedef

- ```cpp
  typedef int INTINT;//将int定义为INTINT
  typedef unsigned int UINT;//同上
  
  typedef void (*voidfunc)(int a, int b)//定义一个函数指针，用于回调函数
      
  typedef decltype(func) Func2  // Func2是函数类型；
  typedef decltype(func) *Func2P // Func2是函数指针类型；
  ```

- C++编译器不支持使用typedef关键词为模板类设置别名，但是使用using的方式声明一个关键词却是允许的，只是这个是C++11标准才有的，如果在编译时不加上--std=c++11使用新的标准的话，编译器一样会报错

- https://blog.csdn.net/liitdar/article/details/80069638


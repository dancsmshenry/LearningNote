# noexcept

作用

- 表示其修饰的函数不会抛出异常

- 预先知道函数不会抛出异常有助于简化调用该函数的代码，而且编译器确认函数不会抛出异常，它就能执行某些特殊的优化操作

- 如果noexcept修饰的函数抛出了异常，编译器可以选择直接调用std::terminate()函数来终止程序的运行（以确保遵守不在运行时抛出异常的承诺），这比基于异常机制的throw()在效率上会高一些
  - 因为异常机制会带来一些额外开销，比如函数抛出异常，会导致函数栈被依次地展开（unwind），并依帧调用在本帧中已构造的自动变量的析构函数等

- ```cpp
  void func(int x) throw();// 没有noexcept之前
  ```

- 还有一点，有些函数本身就是不会出现异常的，所以调用的时候要注意

  - https://blog.csdn.net/fl2011sx/article/details/119452341





从另一个角度考虑

- gcc在生成汇编代码的时候，会考虑到代码如果出现异常的话应该怎么办，会生成保护栈上对象安全析构的代码
- 而如果你告诉它代码不会爆出异常，那么编译器就不会生成相应的代码，从而实现优化
- https://www.zhihu.com/question/496351156/answer/2208472912
- 拓展
  - c语言很多函数的实现后面都加上了_THROW，即相当于throw()，表明它不会爆出异常






用法

- noexcept说明出现在函数的所有声明语句和定义语句中
- 可以在函数指针的声明和定义中指定noexcept
- 在typedef和类型别名中不可以出现noexcept
- 在成员函数中，noexcept需要跟在const以及引用限定符之后，在final、override或虚函数=0之前

```cpp
void func(int x) noexcept(true);  //不抛出异常
void func(int x) noexcept(false); //抛出异常
```



noexcept运算符

- 返回值是一个bool类型的右值常量表达式，用于表示给定的表达式是否会抛出异常

- ```cpp
  noexcept(f());   //如果f()不抛出异常则结果为true，否则为false
  noexcept(e);     //当e调用的所有函数都做了步抛出说明且e本身不含有throw语句时，表达式为true，否则返回false
  ```







# ifdef

作用一

- 一般，源程序中所有的行都参加编译，但是有时希望对其中一部分内容只在满足一定条件下进行编译，也就是对一部分内容指定编译条件，这就是条件编译
- 有时，希望当满足某条件时对一 组语句进行编译，而当条件不满足时则编译另一组语句

- ```cpp
  #ifdef
  //	程序段1
  #else // else也可以没有的
  //	程序段2
  #endif
  //	当标识符已经被定义过，则对段1进行编译，否则就对段2进行编译
  ```





作用2

- 在一个大的软件工程里面，可能会有多个文件同时包含一个头文件，当这些文件编译链接成一个可执行文件上时，就会出现大量“重定义”错误
- 在头文件中使用#define、#ifndef、#ifdef、#endif能避免头文件重定义
- 侯捷的课里就说过头文件一定要用其包住







# extern

### 作用一

- 是C/C++语言中表明函数和全局变量作用范围的关键字，作用是告诉编译器其声明的函数和变量可以在本模块或其他模块中使用



- 如果一个变量的定义是在main函数的后面的话，那么在main中用到它之前就要加上extern

  - 这里一个坑爹的地方就是，int i;就代表已经定义了
  - 如果在变量定义之前要使用该变量，则应在使用之前加 extern 声明变量，使作用域扩展到从声明开始到本文件结束

- ```c
  #include <iostream>
  
  extern int i; 
  // 如果不加上这一句的话，过不了编译的（链接是指多个文件，这里是只有一个文件，所以是编译错误）
  // int i; // 这相当于定义了
  
  int main() {
      std::cout << i << std::endl;
  }
  
  int i = 10;
  ```



- 或者说，在A文件中想要用B文件中的变量，就要在我的前面事先声明

- ```c
  /****max.c****/
  #include <stdio.h>
  /*外部变量声明*/
  extern int g_X;
  extern int g_Y;
  int max()
  {
      return (g_X > g_Y ? g_X : g_Y);
  }
  
  /***main.c****/
  #include <stdio.h>
  /*定义两个全局变量*/
  int g_X = 10;
  int g_Y = 20;
  int max();
  int main(void)
  {
      int result;
      result = max();
      printf("the max value is %d\n", result);
      return 0;
  }
  ```

- 总结：在c/cpp中，使用extern对变量事先声明，方便后使用或链接





### extern "c"

- 被extern "C"修饰的代码部分会按照C语言方式编译和链接的

- **挖坑**：看下面两篇文章

  - https://www.jianshu.com/p/5d2eeeb93590

  - https://www.cnblogs.com/TenosDoIt/p/3163621.html







# enum

- 枚举类型

- ```cpp
  enum week{ Mon, Tues, Wed, Thurs, Fri, Sat, Sun };
  // 默认对应的数字是从0-6
  enum week{ Mon = 1, Tues = 2, Wed = 3, Thurs = 4, Fri = 5, Sat = 6, Sun = 7 };
  // 也可以自定义开始数字
  
  #include <iostream>
  
  enum test{a, aa, aaa};
  
  int main() {
      enum test a1 = aa;
      std::cout << sizeof(a1) << std::endl; // 4
  }
  ```

- 其中的值都是常量，不可赋值

- 存放的一般是一个int，sizeof得到的是4







# union

- union数据结构中的数据是共用内存地址的

- ```cpp
  #include <iostream>
  
  union myun {
      struct {
          int x;
          int y;
          int z;
      } u;
      int k;
  } a;
  int main() {
      a.u.x = 4;
      a.u.y = 5;
      a.u.z = 6;
      a.k = 0;
      printf("%d %d %d\n", a.u.x, a.u.y, a.u.z);
      // 0 5 6
      // 首先，union会按照最大的结构对象来确立地址空间
      // 其次，后面给k赋值的时候，会把k的值赋到原来x的位置
      // 所以就是0 5 6
      return 0;
  }
  ```

- 不能具有定义了构造函数、析构函数或赋值操作符的类类型的成员

- 不能具有静态数据成员或引用成员

- 不能作为基类使用，所以成员函数不能为虚函数

- 共用体占用的内存等于最长的成员占用的内存

  - 共用体使用了内存覆盖技术，同一时刻只能保存一个成员的值，如果对新的成员赋值，就会把原来成员的值覆盖掉







# RAII

- 如果一个函数有多处return，我想每个return都加一些相同的处理，最好怎么实现？
- 这里最好的写法就是RAII模式的应用。不过很多时候我们也不必每次新建一个RAII模式的类。可以使用用unique_ptr来完成







# 函数指针和函数类型

- https://www.jianshu.com/p/6ecfd541ec04

- 函数指针指向的是函数而非对象，和其他指针类型一样，函数指针指向某种特定类型

- 函数类型由它的返回值和参数类型决定，与函数名无关

- ```cpp
  bool length_compare(const string &, const string &); // 函数类型
  bool (*pf)(const string &, const string &); // 函数指针
  
  pf = length_compare;
  // 当把函数名作为一个值使用时，该函数自动的转换成指针
  
  typedef bool Func(const string &, const string &) // Func是函数类型
  typedef bool (*FuncP)(const string &, const string &) // FuncP是函数指针类型
  
  typedef decltype(length_compare) Func2  // Func2是函数类型
  typedef decltype(length_compare) *Func2P // Func2是函数指针类型
  ```



- 函数类型传参后会被隐式的转化为函数指针

- ```cpp
  using FTtype = int(int,int); //函数类型
  typedef int (*pf)(int, int); //函数指针
  
  int func(int a, int b){return a+b;}
  void print(int a, int b, FTtype fn){
      // 编译器将其隐式转化成函数指针
      // 等价于void print(int a, int b, pf fn);
      // 但是平常用的时候只能直接用函数指针
      cout << fn(a,b) << endl;
  }
  
  int main() {
      print(1,2,func);
      cout << typeid(FTtype).name() << endl;  // FiiiE
      cout << typeid(func).name() << endl;    // FiiiE
      cout << typeid(decltype(func)).name() << endl;  // FiiiE
      cout << typeid(pf).name() << endl;  // PFiiiE
      return 0;
  }
  
  using F = int(int*, int);
  using PF = int(*)(int*,int);
  F  f1(int);    //错误： F是函数类型
  PF  f1(int);   //正确： PF是函数指针类型
  ```





# size_t

- ```cpp
  int main() {
      std::vector<int> f(0, 0);
      for (int i = 0; i < f.size() - 1; i++) {
          std::cout << "i = " << i << std::endl;
      }
  }
  ```

- 因为f.size()得到的是一个size_t无符号整数，就会导致f.size()-1变成一个很大的正数，就会出现意想不到的结果

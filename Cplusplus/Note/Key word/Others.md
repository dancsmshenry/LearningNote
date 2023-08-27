# 有关数组传参的问题

```c++
void func(int arr[10][10]) {} // ok
void func(int arr[][]) {} // error
void func(int** arr, int n, int m) {} // ok
void func(int arr[1][]) {} // error
void func(int arr[][1]) {} // error

void func(int arr[102]) {} // ok
void func(int* arr) {} // ok
void func(int arr[]) {} // o
```

<br/>

<br/>

<br/>

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

<br/>

<br/>

<br/>

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

<br/>

<br/>

<br/>

# extern

## extern 声明

- 是C/C++语言中表明函数和全局变量作用范围的关键字，作用是告诉编译器其声明的函数和变量可以在本模块或其他模块中使用
- extern 变量表示声明一个变量，表示该变量是全局变量，extern修饰的变量是全局变量，是保存在静态存储区，初始化为0保存在BSS段，不初始化为0保存在DATA段
- extern 置于变量声明或者函数声明前表示变量或者函数的定义在别的文件，提示编译器遇到时去其他文件中寻找其定义



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





## extern "c"

- 被extern "C"修饰的代码部分会按照C语言方式编译和链接的

- **挖坑**：看下面两篇文章

  - https://www.jianshu.com/p/5d2eeeb93590
  - https://www.cnblogs.com/TenosDoIt/p/3163621.html
  
- 想要在C++编译器下编译部分C语言写的代码

  - ```cpp
    extern "C" {
        void sum() {}
        void sum(int i) {}
    }//	PS：在cpp下会报错
    ```

- 一段代码，在cpp中是cpp编译，在c中是c编译

  - ```cpp
    #ifdef _cplusplus
    extern "C" {
    #endif
        int sum(int a, int b) {
            return a + b;
        }
    #ifdef _cplusplus
    }
    #endif
    ```

  - 因为c语言中没有_cplusplus这个宏

<br/>

<br/>

<br/>


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

<br/>

<br/>

<br/>

# RAII

- 如果一个函数有多处return，我想每个return都加一些相同的处理，最好怎么实现？
- 这里最好的写法就是RAII模式的应用。不过很多时候我们也不必每次新建一个RAII模式的类。可以使用用unique_ptr来完成

<br/>

<br/>

<br/>

# 函数指针和函数类型

https://www.jianshu.com/p/6ecfd541ec04

函数指针指向的是函数而非对象，和其他指针类型一样，函数指针指向某种特定类型

函数类型由它的返回值和参数类型决定，与函数名无关

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



函数类型传参后会被隐式的转化为函数指针

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

<br/>

<br/>

<br/>

# 如何把对象只分配到栈上

- 将new operator函数定义为private，或者定义为delete函数

<br/>

<br/>

<br/>

# enable_shared_from_this

<br/>

<br/>

<br/>

# 运算符的顺序

```c++
void add_1(int *a) {
    *a ++ ; // 先取值，然后再 ++，不修改原来的值
}

void add_2(int *a) {
    ++ *a; // 在其原来的基础上 
}
```

<br/>

<br/>

<br/>

`std::cout << std::boolalpha ` 会使得后面的 true 和 false 都以字符串的形式输出

<br/>

<br/>

<br/>

装饰器模式

<br/>

<br/>

<br/>

# 萃取

C++ 萃取：

利用类模板的偏特化，根据目标数据类型的不同，从而做出不同的操作

（例如可以给当前类带上一个 string 的变量，标注用来存储数据类型的名字，然后再利用偏特化，给每个类对象的成员变量 string 标记为对象的名称）

主要就是利用类模板偏特化，using 或者 typename 来针对不同的数据类型，做出不同的操作

[mp.weixin.qq.com](https://mp.weixin.qq.com/s?__biz=MzU2NzI5MjQzMQ==&mid=2247484011&idx=1&sn=28396d55ece2aceac3107b50da7fef93)

```C++
struct __TrueType {
  bool Get() { return true; }
};
struct __FalseType {
  bool Get() { return false; }
};
// 自定义类型一般不特化

template <class _T> struct TypeTraits {
  typedef __FalseType __IsPODType;
};
// 下面是对常见的几种内置类型的特化，当然内置类型还有很多，我只是举几个常见的；

template <> struct TypeTraits<bool> {
  typedef __TrueType __IsPODType;
};
template <> struct TypeTraits<char> {
  typedef __TrueType __IsPODType;
};

template <> struct TypeTraits<short> {
  typedef __TrueType __IsPODType;
};

template <> struct TypeTraits<int> {
  typedef __TrueType __IsPODType;
};

template <> struct TypeTraits<long> {
  typedef __TrueType __IsPODType;
};

template <> struct TypeTraits<unsigned long long> {
  typedef __TrueType __IsPODType;
};

template <> struct TypeTraits<float> {
  typedef __TrueType __IsPODType;
};

template <> struct TypeTraits<double> {
  typedef __TrueType __IsPODType;
};
```

<br/>

<br/>

发现关于函数传参的规律

对于函数原型

```c++
void t1(int i) { std::cout << "t1" << std::endl; }
```

无论传入的参数是 int 的，还是 double 的，都会调用到这个函数

而对于函数原型

```c++
void t1(int i) { std::cout << "t1" << std::endl; }

void t1(double i) { std::cout << "t2" << std::endl; }
```

会根据传入参数类型更加能转换为对应的类型而调用

比如传入的是 int 或 long long，那么输出的就是 t1

而如果传入的是 double 或 float，那么输出的就是 t2

---

但是，不能根据函数的返回值作为函数直接不同的区别条件

```c++
int v2() { return 1; }
// double v2() { return 1.0; } // error
```

<br/>

<br/>

```c++
template <typename T> void v1(T t1, T t2, T t3) {
  std::cout << "T" << std::endl;
}

template <typename T> void v1(T t1, T t2, int t3) {
  std::cout << "int" << std::endl;
}

v1<int>(1, 2, 3); // ambiguous
```

这样调用会有歧义，根本调用不了

与其这样写，不如直接上特化

```c++
template <typename T> void v1(T t1, T t2, T t3) {
  std::cout << "T" << std::endl;
}

template <> void v1(int t1, int t2, int t3) { std::cout << "int" << std::endl; }
```

而且，之前的那种做法（`void v1(T t1, T t2, int t3)`），还会导致 int 的偏特化版本写不了

<br/>

<br/>

关于数组传参的多个疑问，编译器到底是如何辨别传参不同的

```c++
void ttt(int arr[1][1]) {} // right

void ttt(int a[]) {} // right

// 这里是如何分辨出指针类型的不同的，传入的不都是地址吗

//////////

void func(int arr[][1]) {} // right

//////////

void func(int arr[1][]) {} // error

// 这样写为什么会出错，而上面就不会
```

<br/>

<br/>

```C++
std::string *a = new std::string("test");
delete a;
if (a == nullptr) {
    std::cout << "333\n";
}
// without 333
// delete 后，指针指向的地址前后不变，即没有指回 nullptr（记得知乎上有个问题就是问为什么不指向 nullptr）
```

<br/>

<br/>

列表初始化数据不可以自动的转换数据类型

```C++
std::vector<int> vec1(10, 0);
long long n{vec1.size()}; // error
long long n{static_cast<long long>(vec1.size())}; // correct
```

<br/>

关于运算符的操作及运算的顺序

```C++
int num = 7 & 3;
// 这里的 & 等价于二进制中的 与操作

int b = 10, a = 3;
b += b *= b %= a++; // 计算的顺序是从右往左的
// b = 2 a = 4
```

<br/>

<br/>

关于结构体

```C++
// 构建临时的结构体对象
struct {
    int i;
} c1;

// 另类的定义结构体的方法
typedef struct {
    int i;
} color;

color c1;
c1.i = 1;
```

<br/>

<br/>

如何理解多文件编译：

把 a.cc 和 b.cc 同时编译为一个可执行文件，假如在 a.cc 中创建了一个全局或 namespace 的变量，这个变量的构造函数输出了一行数据，那么这个数据会不会在执行时输出》

会的，因为将两个 .cc 合并在一起执行，那么就是同一个编译单元，就可以理解为是一个全局变量

<br/>

<br/>

在 c 中，函数的定义与实现的参数列表不同（例如定义时是一个传参，实现时是 2个或者 3个），代码依旧可以运行（这里调用的时候要和定义时相同即可）

无论是在同一个编译单元的（main.c,test.h.test.c 在一个编译单元），还是不在同一个编译单元的（main.c，test.h和test.c不在同一个编译单元）

而在 c++ 中，则会出现链接失败的情况

```c
// 声明（函数的声明是不会被写入汇编的）
void test(); // 或者 void test(int i);

// 实现
void test(int i, int j, int k, int l) {}
```

<br/>

<br/>

在 c 中，是不允许定义多个名字相同的函数，而如果在声明时有多个名字相同的函数，在特定条件下是可以的

```C
// 定义，这种情况下是不会报错
void test();
void test(int i);

// 定义，但是这种情况下会报错
void test(int i);
void test(int i, int j);
```

原因：在 c 中，编译单元的链接中，函数的链接是有缺陷的（在链接时，只检查函数的名字是否匹配），而不会校验函数的入参和返回值

即，假设声明时只有1个入参，而定义时有2个入参，那么在调用该函数时就会读取到未知的数据

解决办法：在函数定义的位置（例如这里的test.c中），引入 test.h 文件，确保函数的声明和定义保持一致性

<br/>

<br/>

外部链接和内部链接

外部链接：当前编译单元能够向其他编译单元提供相关函数或变量的定义或实现，并让其他编译单元使用，那么这个变量或函数是外部链接的

内部链接：不能将变量对外展示，例如说 static 修饰的函数变量，或者是 inline 修饰的（因为 inline 会展开函数，从而没有了函数的概念）


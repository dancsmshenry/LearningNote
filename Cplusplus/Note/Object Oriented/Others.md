# 如何实现只能静态分配和只能动态分配

- 背景：
  - 静态创建：静态建立一个类对象，就是由编译器为对象在栈空间中分配内存
  - 动态创建：A *p = new A();动态建立一个类对象，就是使用new运算符为对象在堆空间中分配内存。 这个过程分为两步，第一步执行operator new()函数，在堆中搜索一块内存并进行分配；第二步调用类构造函数构造对象
- 只能静态分配：把new和delete运算符重载为privated属性（只有使用new运算符，对象才会被创建在堆上，因此只要限制new运算符就可以实现类对象只能建立在栈上，即把new运算符设为私有）
- 只能动态分配：把构造、析构函数设为protected属性，再用子类动态创建







# 继承下对象的转换

- 向上类型转换
  - 将派生类指针或引用转换为基类的指针或引用被称为向上类型转换
  - 向上类型转换会自动进行，**向上类型转换是安全的**
- 向下类型转换
  - 将基类指针或引用转换为派生类指针或引用被称为向下类型转换
  - 向下类型转换不会自动进行，因为一个基类对应几个派生类，所以向下类型转换时不知道对应哪个派生类，所以在向下类型转换时必须加动态类型识别技术（RTTI技术，用dynamic_cast进行向下类型转换）
  - 因为父子类的结构不一样，可能子类有多个虚函数指针，强转导致数据出错，**向下类型转换是不安全的**







# 空类默认提供的函数

- ```cpp
  A(); //默认构造函数
  ~A(); //默认析构函数
  A（const A&); //默认拷贝构造函数
  A& operator=(const A &); //默认赋值函数。
  ```

- 析构函数
- 拷贝构造函数
  - 如果是A a1(b1)这种，而类里面都是一般属性（比如int，long等，或是没有定义拷贝函数的class），那就不会构造拷贝函数，而是直接值拷贝过去
  - 而如果有string之类的成员，那么就会调用拷贝构造，去调用对应的拷贝构造函数

- 缺省构造函数
- 赋值运算符







# 如何阻止类被拷贝

- 本质上就是组织用户调用copy构造函数和=运算符
- 可以将copy构造函数和=运算符设为private，防止被调用（但缺点就是friend函数对象，或是类的成员函数可以调用）
  - 而如果只声明不定义，就会有链接错误
- 因此最佳解是定义一个base类，在base类中将拷贝构造函数和拷贝赋值函数设置成private，那么派生类中编译器将不会自动生成这两个函数

- 当然也可以用cpp11的关键字delete，直接=delete即可







# 如何阻止类被实例化

- 将类定义为抽象基类或者将构造函数声明为private







# 如何阻止类被继承

## 方法一

- ```cpp
  class B;
  //设计一个不能被继承的类
  class A
  {
         friend B;
  private:
         A() {}
  };
  class B :virtual public A
  {
  public:
         B() {}
  };
  ```

- 我们可以声明一个辅助的类A，把类A的构造函数声明为私有的，并使得B是A的友元类，且B虚继承A。让B是A的友元类的目的在于能够让B访问A的私有构造函数，这样继承自A的B才可以被实例化

- 假设现在有一个类D继承B，在D初始化的时候会先调用B类的构造函数，但是由于B虚继承A，所以为了防止产生二义性，D必须先调用A的构造函数，由于A的构造函数是私有的不可访问，所以会产生错误，继承会失败



## 方法二

- ```cpp
  class CParent
  {
  private:
      CParent(int v){m_v = v;}
      ~CParent(){}
  
      int m_v;
      static CParent * m_instance;
  public:
      static CParent * getInstance(int v);
  };
  
  CParent *CParent::getInstance(int v)
  {
      return new CParent(v);
  }
  ```

- 相当于写一个单例模式吧



## 方法三

- cpp11中的final修饰符







# 如何统计一个类生成的个数

- 为类设计一个static静态变量count作为计数器
- 类定义结束后初始化count
- 对于默认构造函数，拷贝构造函数，复制构造函数，移动拷贝构造函数，在进行上述函数时进行count+1操作
- 在析构函数中对count进行-1







# 成员函数的调用过程

- ```cpp
  #include <iostream>
  
  class A {
  public:
      void test() {
          std::cout << "hello" << std::endl;
          //std::cout << i << " " << std::endl;
      }
      int i{};
  };
  
  int main() {
      A *a1 = nullptr;
      a1 -> test();
  }
  ```

- 如果注释掉了i的那一行，代码可以运行吗，可以的

- 先了解一下成员函数是如何调用的，成员函数的调用本质上会加上一个对象的指针进去的，即this指针

- 换句话说，如果函数里面没有触及这个this指针，那么即使this为nullpr，也是可以运行的







# trivial函数，standard-layout和POD

https://zhuanlan.zhihu.com/p/479755982

背景

- ```cpp
  class A
  {
  public:
      // ...
      A() {}          // 定义一个空的默认构造函数
      A() = default;  // 主动让编译器生成默认构造函数
      // ...
  };
  ```

- 这两种构造函数有何区别



trivial type的定义

- 没有虚函数或虚基类
- 由编译器生成默认的特殊成员函数，包括默认构造函数、拷贝构造函数、移动构造函数、赋值运算符、移动赋值运算符和析构函数
- 数据成员同样需要满足上述两个条件



Standard Layout的定义

- 没有虚函数或虚基类

- 所有非静态数据成员都具有相同的访问说明符（`public` / `protected` / `private`）

- 在继承体系中最多只有一个类中有非静态数据成员。

- 子类中的第一个非静态成员的类型与其基类不同（具体的原因可以参考下面的博文）
  - 因为在cpp的标准里面，如果基类没有任何数据成员，基类应不占用空间，所以允许派生类的第一个成员与基类共享同一地址空间

  - 如果派生类的第一个成员和基类的类型相同，而cpp标准要求相同的类型不同的对象的地址必须有所区分，所以编译器就会为基类分派一个字节的地址空间

  - ```cpp
    #include <iostream>
    #pragma  pack(1)
    
    struct A
    {
    };
    
    struct B : A
    {
    	// A a; // 这样写大小为6
    	int i;
    	A a; // 这样写大小为5
    };
    
    struct C
    {
    };
    
    struct D : A
    {
    	C c;
    	int i;
    };
    
    int main()
    {
    	B b;
    	A &a1 = b;
    	// &b == &a1 == &b.a - 1
    	std::cout << &b << std::endl;
    	std::cout << &a1 << std::endl;
    	std::cout << &b.a << std::endl;
    	std::cout << sizeof(B) << std::endl;
    	std::cout << "-------------" << std::endl;
    
    	D d;
    	A &a2 = d;
    	// &d == &a2 == &d.c
    	std::cout << &d << std::endl;
    	std::cout << &a2 << std::endl;
    	std::cout << &d.c << std::endl;
    	std::cout << sizeof(D) << std::endl;
    }
    ```

  - 这就直接导致的结果是，同样是一个空类加上一个int，不同的排列方法会导致大小的不同

  - 探讨对象B的内存布局

  - 如果是先A a;，再int i;，那么编译器为了区分B和A，对象布局就是第一层用一个字节表示对象B，第二层用一个字节来区分表示对象A，第三层用四个字节表示对象int i，这样一共就用了6个字节

  - 而如果是先int i;，再A a;，那么编译器就不需要去区分B和A了，则对象布局时第一层用四个字节表示int i；，这里顺带也会用来表示对象B，然后第二层用一个字节表示对象A a，这样一共就用了5个字节

  - 而这里为什么对象D同样是把空类放到最前面，但是大小却依然是5，是因为对象C和对象D没有父子关系，即使再同一个地址编译器也能够区分

- 总结：一切都是因为cpp的标准说，相同类型的不同对象的地址必须不同，编译器为了实现，就为那个不同的对象分配一个字节的地址空间



plain old data的定义

- 代表一个对象是一个普通类型；Old 代表一个对象可以与 C 语言兼容
- 可以使用字节赋值，比如用 `memset`、`memcpy` 对 POD 类型对象进行赋值操作。
- 与 C 语言内存布局兼容，POD 类型的数据可以使用 C 函数进行操作且是安全的。
- 保证了静态初始化的安全有效







# 对面向对象的理解





# 父类调用子类函数

```c++
#include <iostream>

template <typename T>
class Base {
public:
  virtual ~Base() = default;
  virtual void fun() { std::cout << "Base::fun()" << std::endl; }

  void callChildMethod() { static_cast<T &>(*this).show(); }
};

class Sub : public Base<Sub> {
public:
  void fun() override { std::cout << "Sub::fun()" << std::endl; }

  virtual void show() { std::cout << "Sub::show()" << std::endl; }
};

int main() {
  Sub s1;
  std::cout << "s1.fun()--------------" << std::endl;
  s1.fun();
  std::cout << "s1.callChildMethod()----------" << std::endl;
  s1.callChildMethod();
}
```





# to do list

A继承自父类B和C，如果使用B的指针ptr1和C的指针ptr2同时指向一个A对象，则ptr1和ptr2的地址是否一致？（经过测试，是不一样的，但是有个问题就是如果A，B，C都是空类的话，那地址是不是一样的，答是不一样的，为啥？？）





# 关于多继承中函数调用的顺序

A

B->C（C 继承于 B）

C,A ->D（D 继承于 C A）

构造的调用顺序：先构造 B，再构造 C ，接着构造 A，最后构造 D

析构的调用顺序：先析构 D，再析构 A，接着析构 C，最后析构 B

构造和析构的顺序完全相反

```c++
class A {
public:
  A() { std::cout << "A()" << std::endl; }
  ~A() { std::cout << "~A()" << std::endl; }
};

class B {
public:
  B() { std::cout << "B()" << std::endl; }
  ~B() { std::cout << "~B()" << std::endl; }
};

class C : public B {
public:
  C() { std::cout << "C()" << std::endl; }
  ~C() { std::cout << "~C()" << std::endl; }
};

class D : public C, public A {
public:
  D() { std::cout << "D()" << std::endl; }
  ~D() { std::cout << "~D()" << std::endl; }
};

void test() {
  D d1;
}
// B()
// C()
// A()
// D()
// ~D()
// ~A()
// ~C()
// ~B()
```

有个问题：既然要隐藏实现，那为什么不直接写一个 .h 文件，然后把具体的一些实现函数放到 .cc 文件中，这样也可以实现只暴露规范提供的接口。问题一：外部实现函数无法访问 private 变量

在构造函数中，不要把 this 指针传递给别的函数，可以理解为不要注册回调（不是安全的），即使是在函数的最后一行

因为当前类可能会被其他类继承，而此时的 this 并没有构造完成

一个比较好的方式就是，构造函数+initialize 两段式构造

[muduo网络库:01---线程安全的对象生命期管理之(多线程中对象的构造与析构)_mb6128aabee41d4的技术博客_51CTO博客](https://blog.51cto.com/u_15346415/5223440)



<br/>

<br/>

如何分析类的大小以及内存对齐

题外话：当前 vscode 的跳转有问题，我编译的 g++ 是 tdm-gcc-64 的，但是跳转的却是 llvm 里面的

```c++
class c2 {
public:
  char s[17]; // 17 (+3)
  int i1; // 4
  double d1; // 8
  int i2; // 4 (+4)
};

  std::cout << sizeof(c2) << std::endl;
  std::cout << offsetof(c2, i1) << " " << offsetof(c2, i2) << std::endl;
```

<br/>

<br/>

子类调用父类的虚函数（除了 static_cast ，还有其他方法吗）

```c++
// 子类调用父类的虚函数（除了 static_cast，还有其他方法吗）
class a1 {
public:
    virtual void func() {std::cout << "a1" << std::endl;}
};

class b1 {
public:
    virtual void func() override {std::cout << "b1" << std::endl;}
};
b1 bb;
(static_cast<a1>(bb)).func();
```

<br/>

<br/>

```c++
// 浅拷贝的问题
class Animal {
public:
    int *name;
    Animal() {
        name = new int(1);
        std::cout << "Animal()" << std::endl;
    }
    // 如果不写这个拷贝构造函数，使用编译器默认提供的，那么就会出现问题
    Animal(const Animal& other) {
        name = new int(*other.name);
    }
    ~Animal() {
        std::cout << "~Animal()" << std::endl;
        delete name;
        name = nullptr;
        // 崩溃的原因是，同一个指针多次 delete 不会有问题，但是多个指向同一个对象的指针进行 delete ，就会 oom
    }
}

// 结论是，使用深拷贝和浅拷贝都没有问题，但要注意浅拷贝可能会造成对一个对象的多次析构，从而造成 oom
```

而这里如果把 int 替换为了 string，那么即使不重写拷贝构造函数，也不会有问题（此时把 delete 操作给删除了）


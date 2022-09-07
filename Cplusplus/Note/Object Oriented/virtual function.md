# 虚函数为什么慢

- 和虚函数表有些许关系
- 虚函数其实最主要的性能开销在于它阻碍了编译器内联函数和各种函数级别的优化，导致性能开销较大
- 在普通函数中log(10)会被优化掉，它就只会被计算一次，而如果使用虚函数，log(10)不会被编译器优化，它就会被计算多次
- 如果代码中使用了更多的虚函数，编译器能优化的代码就越少，性能就越低
- 简而言之，就是虚函数阻止了编译器对函数的优化



先看一下两份代码的运行时间

- ```cpp
  #include <cmath>
  // #include "timer.h"
  #include <iostream>
  
  using namespace std;
  
  struct Base {
     public:
      virtual int f(double i1, int i2) { return static_cast<int>(i1 * log(i1)) * i2; }
  };
  
  int main() {
      // TimerLog t("timer");
      Base *a = new Base();
      int ai = 0;
      for (int i = 0; i < 1000000000; i++) {
          ai += a->f(i, 10);
      }
      cout << ai << endl;
  }
  
  
  #include <cmath>
  #include "timer.h"
  struct Base {
     public:
      int f(double i1, int i2) { return static_cast<int>(i1 * log(i1)) * i2; }
  };
  
  int main() {
      TimerLog t("timer");
      Base *a = new Base();
      int ai = 0;
      for (int i = 0; i < 1000000000; i++) {
          ai += a->f(i, 10);
      }
      cout << ai << endl;
  }
  
  ```

- 上面两份代码的运行时间都差不多（都是12、13s的样子）

- 由此可以证明虚函数表的重定向基本上不影响程序的性能



再看下面的代码

- ```cpp
  #include <cmath>
  #include "timer.h"
  struct Base {
     public:
      virtual int f(double i1, int i2) { return static_cast<int>(i1 * log(i1)) * i2; }
  };
  
  int main() {
      TimerLog t("timer");
      Base *a = new Base();
      int ai = 0;
      for (int i = 0; i < 1000000000; i++) {
          ai += a->f(10, i); // 这里有改动
      }
      cout << ai << endl;
  }
  
  
  #include <cmath>
  #include "timer.h"
  struct Base {
     public:
      int f(double i1, int i2) { return static_cast<int>(i1 * log(i1)) * i2; }
  };
  
  int main() {
      TimerLog t("timer");
      Base *a = new Base();
      int ai = 0;
      for (int i = 0; i < 1000000000; i++) {
          ai += a->f(10, i); // 这里有改动
      }
      cout << ai << endl;
  }
  ```

- 第一个代码运行时间为436ms，而第二个代码运行时间为154ms，相差数倍



总结

- 通过第一二个代码的对比，实际开销的时间几乎一样，所以发现虚函数表导致的那一次函数间接调用并不浪费时间，所以虚函数的开销并不在重定向上，即虚函数的重定向并不影响性能
- 而通过第三四个代码的对比，实际开销的时间相差3倍，发现实际上的性能开销在于虚函数阻碍了编译器内联函数和各种级别函数的优化，导致性能开销过大（即在普通函数中log(10)会被优化掉，它就只会被计算一次，而如果使用虚函数，log(10)不会被编译器优化，它就会被计算多次）
- 所以虽然查虚函数表固然需要不少的时间，但是主要的开销还是因为编译器没能对函数进行优化
  - 真正原因是编译器在编译时通常并不知道它将要调用哪个函数，所以它不能被内联优化和其它很多优化，因此就会增加很多无意义的指令（准备寄存器、调用函数、保存状态等），而且如果虚函数有很多实现方法，那分支预测的成功率也会降低很多，分支预测错误也会导致程序性能下降



正常的函数调用

- 复制栈上的一些寄存器，以允许被调用的函数使用这些寄存器；
- 将参数复制到预定义的位置，这样被调用的函数可以找到对应参数；
- 入栈返回地址；
- 跳转到函数的代码，这是一个编译时地址，因为编译器/链接器硬编码为二进制
  - 但是如果是虚函数调用的话，就要先从对象那里得到虚表指针，根据虚表（一个存放函数地址的数组）找到对于的函数地址，最后再放到寄存器中，接着再跳转到该函数中
- 从预定义的位置获取返回值，并恢复想要使用的寄存器



参考

- https://mp.weixin.qq.com/s?__biz=MzkyODE5NjU2Mw==&mid=2247485056&idx=1&sn=5a3e5b93f6d8872aa5fdfeee4e509a9f&chksm=c21d343cf56abd2a6abfaef8caff16dd6fb835bdaf3d4901f55e26eea45a059411c1d1bd94ea&mpshare=1&scene=1&srcid=0218A758oDsFaQngFjuWy7zZ&sharer_sharetime=1613619319357&sharer_shareid=054214e3287ede8cff93de9018c6d7da#rd





# 对虚函数表的理解

- 派生类中包含并且可以使用它从基类继承而来的成员，为了使用这些成员，派生类必须知道他们是什 么。 所以必须定义而非声明。

- 多态只能适用于虚函数

  - 即如果有一个父类的指针指向子类，然后调用两个类都有的那个同名的虚函数，那么这就叫做多态，就会发生调用子类函数的情况
  - 但是，如果是调用两个类都有的同名的一个函数（非虚函数），那么会直接调用到父类的那个函数那里

- 对于一个多态的小bug

  - 如果父类的virtual函数设为了private的话，那就无法使用多态了（代码测验过）

- 能说一下虚继承的底层实现吗？或者多态（虚函数表）的底层实现也可以

- A继承自父类B和C，如果使用B的指针ptr1和C的指针ptr2同时指向一个A对象，则ptr1和ptr2的地址是否一致？

- B是父类，派生出A，B中有虚函数f并被A重写，使用B的指针指向A对象，则： 若B的构造函数中调用f则调用A的f还是B的f以及为什么； 如果B中有成员函数g，g中调用了f，而B的构造函数调用了g，则是调用了谁的f以及为什么

- 如何解释下列代码

  - ```cpp
    class A{
        public:
            A(){}
            A(A &a){cout << "A &a" << endl;}
            A(const A &a){cout << "const A &a" << endl;}
    };
    
    int main(){
        const A a;
        A a1(a);//调用A(const A &a){cout << "const A &a" << endl;}
        
        A a;
        A a2(a);//调用A(A &a){cout << "A &a" << endl;}
    }
    ```

  - 是否可以参照侯捷之前说的，如果两个函数const版本和非const版本同时存在，const只能调用const的版本，非const版本只能调用非const的版本呢？





# 虚函数为什么不能和缺省参数一起调用





# 虚函数实现原理





# 模板和虚函数

- 在模板类中可以使用虚函数，也可以继承模板类通过虚函数实现多态
- 但是模板成员函数不可以是虚函数
  - 因为在实例化模板类时，需要创建virtual table
  - 在模板类被实例化完成之前不能确定函数模板会被实例化出多少个
  - 因为虚函数必须要知道有多少个实例化出来的例子，方便存储函数的地址，而模板成员函数是不知道有多少个实例化出来的例子的，所以模板就不支持虚函数





# 虚函数的调用

- 其实调用虚函数不一定会走虚函数表的逻辑，如果在子类函数中调用父类虚函数，是可以直接调用的，这种情况下因为指定了作用域会直接 cal 基类的虚函数



- ```cpp
  class A {
  public:
      virtual void tt() {
          cout << "A" << endl;
      }
      void test() {
          tt();
      }
  };
  
  class B: public A {
  public:
      virtual void tt() {
          cout << "B" << endl;
      }
  };
  
  int main() {
      B *b1 = new B();
      b1 -> test(); 
  }
  ```

- 
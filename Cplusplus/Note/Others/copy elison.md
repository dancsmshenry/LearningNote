# 背景

- 在 C++11 之前，返回一个本地对象意味着这个对象会被拷贝，但是如果编译器发现可以做返回值优化（named return value optimization，或 NRVO），它会把对象直接构造到调用者的栈上，这样减少对象的拷贝
- 从 C++11 开始，返回值优化仍可以发生，但在没有返回值优化的情况下，编译器将试图把本地对象**移动出去**，而不是拷贝出去。这一行为不需要程序员手工用 `std::move` 进行干预，使用 `std::move` 对于移动行为没有帮助，反而会影响返回值优化。
- C++11以后，g++ 编译器默认开启复制省略（copy elison）选项，可以在以值语义传递对象时避免触发复制、移动构造函数
- copy elison又分为
  - 函数返回的是值语义时（RVO）
  - 函数参数是值语义时



没有NRV的时候

- ```cpp
  class X;
  X bar() {
      X x1;
      return x1;
  }
  X x2 = bar();
  
  //	会变为下面的样子
  void bar(X& __result) { // 加上一个额外参数
      X x1;  // 预留内存空间，并未有函数初始化
      x1.X::X();	// 编译器产生的默认构造函数的调用，  
      __result.X::X(x1);	// 编译器产生的拷贝操作
      return;  
  }  
  
  X x2;	// 预留内存空间，并未调用初始化函数  
  bar(x2); 
  ```

- 所以会调用一次拷贝一次构造函数（gcc关闭编译器优化即可达到的效果）







# RVO

- 避免返回过程触发复制 / 移动构造函数
- 根据返回的是否为匿名对象，可以分为两类：
  - 具名返回值优化 `NRVO` （Named Return Value Optimization，NRVO）（返回的是有名字的局部变量）
  - 匿名返回值优化 `URVO`（Unknown Return Value Optimization，URVO）（返回的是无名的临时变量）



- ```cpp
  #include <iostream>
  
  class Foo
  {
  public:
      Foo() { std::cout << "default" << std::endl; }
  
      Foo(const Foo &rhs) { std::cout << "ctor" << std::endl; }
      Foo(Foo &&rhs) { std::cout << "mtor" << std::endl; }
  };
  
  Foo return_urvo_value()
  {
      return Foo{};
  }
  
  Foo return_nrvo_value()
  {
      Foo local_obj;
      return local_obj;
  }
  
  int main(int argc, char const *argv[])
  {
  
      auto x = return_urvo_value();
      auto y = return_nrvo_value();
      return 0;
  }
  
  //	g++ test.cpp -o test;./test
  //	default
  //	default
  
  //	关闭编译器优化
  //	g++ -fno-elide-constructors test.cpp -o test;./test
  //	default
  //	mtor
  //	mtor
  //	default
  //	mtor
  //	mtor
  ```



分析：

- URVO
  - 调用了一次普通构造函数，两次移动构造函数
  - 一次默认构造函数是指构造出这个对象出来
  - 第一次移动构造函数是指基于return的`Foo{}`构造`return_urvo_value`函数的返回值，触发一次
  - 第二次移动构造函数是指基于`return_urvo_value`函数返回的右值构造`x`，触发一次
  - 而其中的两次移动构造是可以避免的，即直接把对象构造在x上即可，所以**优化后就只用一次默认构造函数**
- NRVO
  - 调用了一次普通构造函数，两次移动构造函数
  - 一次默认构造函数是指构造出这个对象出来
  - 第一次移动构造函数是指编译器将这个局部变量移动到返回值上（发现是临时对象，所以优先选择移动构造函数）
  - 第二次移动构造是指编译器将返回值移动到y上
  - 而其中编译器发现local_obj是一个局部变量，函数退出后生命周期随之消失，所以不如直接把局部变量作为函数的返回值，就只用一次构造即可





# 坑

不会出现返回值优化的情况

- ```cpp
  A get_A() {
      A a1;
      return std::move(a1);
  }
  // 这种写法下不会触发返回值优化，造成的结果就是调用了一次默认构造，一次移动构造，两次析构
  
  A get_A() {
      return A{};
  }
  // 这种写法就会调用返回值优化，就只会调用一次构造
  ```

- ```cpp
  struct B {
      A a;
  };
  
  a foo() {
      return B().a;
  }
  
  int main() {
      auto a = foo();
  }
  // 返回对象成员也不会有返回值优化
  ```

- ```cpp
  A getA_unnamed()
  {
      A a1;
      A a2;
   
      return (rand() > 42) ? a1: a2;
  }
  // 运行时才知道的，也不能优化
  ```





# 参考

- https://www.jianshu.com/p/1766fbca894e
- https://mp.weixin.qq.com/s?__biz=MzkyMjIxMzIxNA==&mid=2247484770&idx=1&sn=460a07d3abaec0ca0d88721c7fb4d2fb&scene=19#wechat_redirect
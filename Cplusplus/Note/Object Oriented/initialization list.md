# 调用过程

- 操作初始化列表，以适当顺序在构造函数之内安插初始化操作，并且在任何显示用户代码前
- list中的项目顺序是由类中的成员声明顺序决定的，不是初始化列表中的排列顺序决定的





# 概念

- 在类的构造函数中，不在函数体内对成员变量赋值，而是在构造函数的花括号前面使用冒号和初始化列表赋值
- cpp11才有的





# 为什么要用

- 当初始化一个引用变量时
- 当初始化一个const成员变量时
- 当调用一个基类的构造函数，而构造函数拥有一组参数时
- 当调用一个成员类的构造函数时，他拥有一组参数





# 为什么快

- 用初始化列表会快一些的原因是，对于类型，它少了一次调用构造函数的过程，而在函数体中赋值则会多一次调用。而对于内置数据类型则没有差别

- ```cpp
  #include <bits/stdc++.h>
  using namespace std;
  class A
  {
  public:
      A()
      {
          cout << "默认构造函数A()" << endl;
      }
      A(int a)
      {
          value = a;
          cout << "A(int " << value << ")" << endl;
      }
      A(const A &a)
      {
          value = a.value;
          cout << "拷贝构造函数A(A& a): " << value << endl;
      }
      int value;
  };
  class B
  {
  public:
      B() : a(1)
      {
          b = A(2);
      }
      A a;
      A b;
  };
  int main()
  {
      B b;
  }
  //输出结果：
  // A(int 1)
  //默认构造函数A()
  // A(int 2)
  ```

- 如果有些成员是类，那么在进入构造函数之前，会先调用一次默认构造函数，进入构造函数后所做的事其实是一次赋值操作

- 所以如果是在构造函数体内进行赋值的话，等于是一次默认构造加一次赋值（生成了临时对象，效率降低），而初始化列表只做一次赋值操作





# 和赋值初始化的对比

- 赋值初始化：通过函数体内进行赋值初始化
- 列表初始化：在冒号后使用初始化列表初始化
- 区别：
  - 列表初始化是给数据成员分配内存空间时就进行初始化，就是说分配一个数据成员只要冒号后有此数据成员的赋值表达式(此表达式必须是括号赋值表达式)
  - 那么分配了内存空间后在进入函数体之前给数据成员赋值，就是说初始化这个数据成员此时函数体还未执行
- 有几种情况是必须要用列表初始化的，同时，列表初始化的顺序是按照数据**在类中定义的顺序从而进行初始化的**



# 需要注意的地方

- 在类对象的初始化列表中，对成员对象使用 std::move() 并不会调用到该对象的移动构造函数

- 因为返回的是一个右值引用，本质上是一个左值，最后还是会调用到该对象的拷贝构造函数上
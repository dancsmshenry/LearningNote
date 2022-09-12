# 定义

- 友元提供了不同类的成员函数之间、类的成员函数和一般函数之间进行数据共享的机制
- 通过友元，一个不同函数或者另一个类中的成员函数可以访问类中的私有成员和保护成员
- 友元的正确使用能提高程序的运行效率，但同时也破坏了类的封装性和数据的隐藏性，导致程序可维护性变差





# 友元函数

- 友元函数是定义在类外的普通函数，不属于任何类，可以访问其他类的私有成员

- 但是需要在类的定义中声明所有可以访问它的友元函数

- 一个函数可以是多个类的友元函数，但是每个类中都要声明这个函数

- 友元函数必须在类内声明

  - 因为编译器必须能够读取这个结构的声明以理解这个数据类型的大、行为等方面的所有规则。 有一条规则在任何关系中都很重要，那就是谁可以访问我的私有部分

- ```cpp
  #include <iostream>
  using namespace std;
  class A
  {
  public:
      friend void set_show(int x, A &a); //该函数是友元函数的声明
  private:
      int data;
  };
  void set_show(int x, A &a) //友元函数定义，为了访问类A中的成员
  {
      a.data = x;
      cout << a.data << endl;
  }
  int main(void)
  {
      class A a;
      set_show(1, a);
      return 0;
  }
  ```





# 友元类

- 友元类的所有成员函数都是另一个类的友元函数，都可以访问另一个类中的隐藏信息（包括私有成员和保护成员）

- 但是另一个类里面也要相应的进行声明

- PS：

  - 友元关系不能继承
  - 友元关系是单向的，不具有交换性，若类B是类A的友元，类A不一定是类B的友元，要看在类中是否有相应的声明
  - 友元关系不具有传递性

- ```cpp
  #include <iostream>
  using namespace std;
  class A
  {
  public:
      friend class C; //这是友元类的声明
  private:
      int data;
  };
  class C //友元类定义，为了访问类A中的成员
  {
  public:
      void set_show(int x, A &a)
      {
          a.data = x;
          cout << a.data << endl;
      }
  };
  int main(void)
  {
      class A a;
      class C c;
      c.set_show(1, a);
      return 0;
  }
  ```





# 对friend封装性的理解

- ```cpp
  class A1 {
      // ...
  public:
      void SetXXX(int x) { xxx = x; }
      int GetXXX() const { return xxx; }
  private:
      int xxx;
      int yyy;
      int zzz;
  };
  
  class A2 {
      // ...
  private:
      friend B;
      int xxx;
      int yyy;
      int zzz;
  };
  ```

- 说到封装性，就必须要和具体的场景作比较，比如说这里的set/get和friend

- 如果需要的是只有B可以对对象的属性进行修改的话，那显然友元比set/get组合拳更好一点

- 但是如果说是要对XXX属性进行查看修改的话，那显然get/set具有更加好的鲁棒性

- 采用一个我喜欢的博主所说的话

  - C++比其它的语言提供了更多的特性，其实就是提供了更多的选择，给程序员更精细的控制粒度。代价无非就是多付出点学习时间而已，我自己的体验，我觉得获得更好的控制粒度是非常值得的，这也是写C++的时候最好的体验之一

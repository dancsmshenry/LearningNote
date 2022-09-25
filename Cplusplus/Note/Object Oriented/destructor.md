# destructor的调用顺序

- 先调用本身的destructor
- 接着是成员对象的destructor
- 最后是父类对象的destructor

- ```cpp
  #include <iostream>
  #include <vector>
  #include <stack>
  #include <deque>
  
  class Test {
  public:
      Test() {std::cout << "Test" << std::endl;}
      ~Test() {std::cout << "~Test" << std::endl;}
      Test(const Test &p) {std::cout << "Test copy" << std::endl;}
      Test(const Test &&p) {std::cout << "Test move" << std::endl;}
      Test(int age) {std::cout << "Test age" << std::endl;}
  };
  
  class A{
  public:
      A() {std::cout << "A()" << std::endl;}
      ~A() {std::cout << "~A()" << std::endl;}
  };
  
  class C{
  public:
      C() {std::cout << "C()" << std::endl;}
      ~C() {std::cout << "~C()" << std::endl;}
  };
  
  class B: public A{
  public:
      C c1;
      B() {std::cout << "B()" << std::endl;}
      ~B() {std::cout << "~B()" << std::endl;}
  };
  
  int main() {
      B b1;
  }
  ```

- ```cpp
  #include <iostream>
  
  using namespace std;
  
  class A {
  public:
  	A() {std::cout << "A()" << std::endl;}
  	~A() {std::cout << "~A()" << std::endl;}
  };
  
  class B {
  public:
  	B() {std::cout << "B()" << std::endl;}
  	~B() {std::cout << "~B()" << std::endl;}
  };
  
  class C: public B {
  public:
  	C() {std::cout << "C()" << std::endl;}
  	~C() {std::cout << "~C()" << std::endl;}
  };
  
  class D: public C, public A {
  public:
  	D() {std::cout << "D()" << std::endl;}
  	~D() {std::cout << "~D()" << std::endl;}
  };
  
  int main() {
  	D d1;
  }
  B()
  C()
  A()
  D()
  ~D()
  ~A()
  ~C()
  ~B()
  ```

- 





# 八股

## 为什么destructor要是virutal function

- 如果是父类指针指向子类对象的话，实际上会发生指针偏移的情况，也就是说父类指针会指向子类中属于父类的那一部分

- 对于一般的非虚函数，我们都是静态绑定的，即编译的时候就知道要调用谁，即如果是父类指针指向子类对象，那么析构的时候默认调用的就是父类的析构函数

- 而对于虚函数，我们是执行的时候才知道到底要执行谁的（即动态绑定）；同时如果父类的析构函数是虚函数，那么子类的也都是虚函数

- 所以即使我们是一个父类指针，只要析构是虚函数，那么就会动态绑定到正确的对象上面

- 所以析构函数如果不是虚函数，就会导致析构不完全

- 角度2：

  - 是为了降低内存泄漏的可能性。举例来说就是，⼀个基类的指针指向⼀个派⽣类的对象，在使⽤完毕准备销毁时，如果基类的析构函数没有定义成虚函数，那 么编译器根据指针类型就会认为当前对象的类型是基类，调⽤基类的析构函数 （该对象的析构函数的函数地址早就被绑定为基类的析构函数），仅执⾏基类的析构，派⽣类的⾃身内容将⽆法被析构，造成内存泄漏
  - 如果基类的析构函数定义成虚函数，那么编译器就可以根据实际对象，执⾏派⽣类的析构函数，再执⾏基类的析构函数，成功释放内存
  - 说白了，就是为了解决多态造成的一个问题（指针使用不当导致内存泄漏）

- 角度3：

  - 基类的 virtual 析构函数是为了解决一个问题：当用基类类型的指针去delete一个派生类的实例的时候，可以让派生类的析构函数被调用

  - 考虑一下场景

  - ```cpp
    class B {
        virtual ~B(){}
    }
    
    class A : public B {
       ~A(){}
    }
    
    B *p = new A();
    delete p;
    ```

  - 如果在 class B 的 析构函数不是虚函数，那么当 delete p 时候 ~A() 是不会被调用的，如果需要在A对象析构时做些必要操作，那么就必须把 ~B()定义成虚函数。

    那么这时候  ~ B()还有没有机会执行呢，有的，析构函数的机制就是子类的析构会自动调用父类的析构函数，~B()实际是被 ~A()调用的，这就形成一个完美的析构链条

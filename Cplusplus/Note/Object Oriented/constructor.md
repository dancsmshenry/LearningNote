# construct的种类

- 默认构造函数（没有参数）

- 初始化构造函数（带有参数，可以是A& A）

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
    } // 如果两个函数const版本和非const版本同时存在，const只能调用const的版本，非const版本只能调用非const的版本
    ```

- 拷贝构造函数（参数是const& A）

- 移动构造函数（参数是const&& A，也叫做转移构造函数）

- 委托构造函数（在参数列表里面调用其他class的constructor）

- 转换构造函数（返回值是一个类型，比如int，double等等）







# constructor的调用顺序

- 先调用virtual父类的构造constructor（多个虚拟基类则按照继承的顺序执行构造函数）

- 接着普通父类的constructor（多个普通基类也按照继承的顺序执行构造函数）

- 再调用成员类的constructor（按照成员类的init顺序）

- 最后调用本身的constructor

- 附上实验代码：

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







# copy constructor的调用时机

- 函数以值传参的形式时（非引用传递）
- 函数以值形式作为返回值时
  - 背景：（Named return Value）NRV优化
  - g++下开优化，值返回和局部对象的引用都不会调用发生拷贝构造函数（gcc关闭优化后，就会调用拷贝构造函数）
  - 而Windows + VS2019在值返回的情况下发生拷贝构造函数，引用返回方式则不发生拷贝构造函数

- 用已有的class构造对象时（但如果对象是普通对象的话，会直接值拷贝，而不会调用copy constructor）







# copy constructor的构造时机

- 传统上，大家认为如果我们没有定义一个自己的拷贝构造函数，编译器会帮助我们合成一个拷贝构造函数

- 这个合成的拷贝构造函数，也是在 **必要**的时候才会被编译器合成出来

- ```cpp
  A a1;
  a1.a = 10;
  A a2 = a1;//这里没有为其合成拷贝构造函数
  //这里其实是编译器内部的一种手法，成员变量初始化手法，比如int这种简单类型，直接就按值拷贝过去，编译器不需要合成拷贝构造函数就可以实现
  //同时，这是递归实现的，即如果A里面还有一个对象A1，A1里面有int类型的话，那么也是会递归的去按值拷贝的
  //这种按值拷贝会出现在所有的拷贝构造函数里面
  ```

- 某些情况下，如果我们不写自己的拷贝构造函数，编译器就会帮助我们合成出拷贝函数来

  - 第一种情况：如果一个类A没有拷贝构造函数，但是含有一个**类类型**CTB的成员变量，该CTB含有拷贝构造函数，那么当代码中有涉及到类A的拷贝构造时，编译器就会为类A合成一个拷贝构造函数
  - 第二种情况：如果一个类A没有拷贝构造函数，但是它的**父类**CTB有拷贝构造构造函数，那么当代码中有涉及到类A的拷贝构造时，编译器就会为类A合成一个拷贝构造函数
  - 第三种情况：如果一个类A没有拷贝构造函数，但是该类声明了或继承了**虚函数**，那么当代码中有涉及到类A的拷贝构造时，编译器就会为类A合成一个拷贝构造函数（这个语句的含义是，设定类对象的虚函数指针值，虚函数表指针，虚函数表等概念）
  - 第四种情况：如果一个类A没有拷贝构造函数，但是该类继承了**虚基类**，那么当代码中有涉及到类A的拷贝构造时，编译器就会为类A合成一个拷贝构造函数

- 编译器合成的拷贝构造函数往往都是干一些特殊的事情，如果只是一些类成员变量值的拷贝，是不用专门生成拷贝构造函数的，内部就会干的







# move constructor

- 移动构造函数的参数是一个右值或者将亡值的引用
- 也就是说只用一个右值，或者将亡值初始化另一个对象的时候，才会调用移动构造函数
- move语句将一个左值变为将亡值







# 八股

## constructor中可以调用virtual function吗

- 可以在构造函数中调用虚函数，只是[不符合预期](https://blog.csdn.net/songchuwang1868/article/details/96481853)

- 虚函数在构造函数里面不起作用

- 总结：在构造函数里面，调用的函数都是静态绑定的（调用的成员函数中this都是当前的class，因此不会走virtual table）

- ```cpp
  #include <iostream>
  
  using namespace std;
  
  class A{
  public:
      A() {
          
      }
      virtual void fun() {
          cout << "A::fun()" << endl;
      }
  };
  
  class B: public A {
  public:
      B() {
          fun();
      }
      virtual void fun() {
          cout << "B::fun()" << endl;
      }
  };
  
  int main() {
      B b1; // B::fun()
  }
  ```



## constructor为什么不能是virtual function

- 角度1：
  - 背景：虚函数的存在是因为编译期间没法确定具体调用对象，才会有虚函数，虚函数表这么个东西
  - c++在编译期间就能确定你要创建的对象的具体类型，而这个具体类型包含了什么，继承了什么在编译期间也是明确的，所以要构造什么也都是明确的，根本没必要存在虚构造函数
- 角度2：
  - 构造函数的一个作用就是将虚函数指针指向虚函数表，因此在指向虚函数表之前，虚函数的功能是不存在的
- 角度3：
  - 虚函数需要依赖对象中指向类的虚函数表的指针，而这个指针是在构造函数中初始化的(这个工作是编译器做的，对程序员来说是透明的)，如果构造函数是虚函数的话，那么在调用构造函数的时候，而此时虚函数表指针并未初始化完成，这就会引起错误



## copy constructor的参数为什么必须是引用

- 如果是值传参的话，那就会陷入递归的情况
- 是值传递，然后又要调用copy constructor，接着递归死循环
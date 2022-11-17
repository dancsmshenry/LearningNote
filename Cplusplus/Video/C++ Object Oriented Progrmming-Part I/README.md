#### Chapter01、C++编程简介

- 面向对象
  - 学习classes之间的关系
    - 继承
    - 复合
    - 委托
- 基于对象
  - class without pointer members（Complex）
  - class with pointer members（String）
- Cpp的历史
  - C++98（1.0）
  - C++11（2.0）
- Cpp的组成
  - Cpp语言
  - Cpp标准库
- 推荐书籍
  - C++ Primer 5th
  - The C++ Programming Language
  - Effective C++ 3th
  - The C++ Strandard Library
  - Stl 源码剖析
- C vs C++
  - 在c语言中，数据和函数是分离开的
  - 而在cpp中，数据和函数（方法）共同组成了对象



#### Chapter02、头文件与类的声明

- 两种基本的设计方式

  - object based：面对的是单一class的设计
  - object oriented：面对的是多重classes的设计，classes和classes之间的关系

- 代码的基本方式

  - .h，.hpp，.cpp等拓展名

- include的方式

  - 在c语言中，`#include<stdio.h>`
  - 在cpp中，`#include<cstdio>`

- header（头文件）中的防卫式声明

  - ```cpp
    #ifndef __COMPLEX__//这里需要改为文件的名字
    #define __COMPLEX__//同上
    
    //代码部分
    
    #endif
    ```

  - 第一次引入这个头文件，就会把这个`__COMPLEX__`给定义了先，如果后续又引入了这个文件，就可以直接跳过（防止重复引用）

- 头文件的布局

  - 前置声明（因为友元和静态函数的缘故，有些函数或类名需要在最开始先声明一遍）
  - 类声明（比如类里面的函数，只定义而不写全）
  - 类定义（补全之前定义的函数）

- class的声明：class head，class body

- class template的简介



#### Chapter03、构造函数

- inline（内联）函数

  - 较为复杂的函数即使把它声明为了inline，编译器也不会视为inline（inline只是建议）
  - 函数若在class body内部定义完成，便会变为inline

- access level（访问级别）

  - public，private，protected

- constructor（ctor，构造函数）

  - ```cpp
    class complex{
      public:
        complex(double r = 0, double i = 0):re(r), im(i){}
        //默认实参，初始值列表
        //初始值列表是一种大气的写法，能够避免很多的问题，能够同时定义初始化赋值
        
      private：
          double im, re;
    };
    ```

  - 创建对象的时候自己调用

  - 函数没有返回值，名称要和类名相同

  - 构造函数可以有很多个，也可以被重载（原理是编译器部会对函数的名字重写一遍）



#### Chapter04、参数传递与返回值

- ctors放在private区（参考单例模式）

- const member functions（常量成员函数）

  - 背景：如果对象是一个const对象，表示该对象的数据不能被修改，但是你的函数名因为没有加上const而修改了数据内容，就发生错误了（即设计不好）

  - 在函数的最后面加上const，表明该函数的内容不能改变对象的数据内容

  - 如果类被定义为const，那么它只能调用const的常量函数

  - ```cpp
    class complex{
      public:
        double real() const {return re;}
        double imag() const {return im;}
       
      private:
        double re, im;
    };
    ```

- 参数传递：pass by value and pass by reference(to const)

  - 传引用更快一点，传的是指针（就4个字节）
  - 不过也要看具体对象的大小来定
  - 防止因为传入指针而修改了原来的变量，所以可以在传入引用对象的时候在前面加上const，表明该变量只读，不可修改

- 返回值传递：return by value and return by reference(to const)

  - 什么时候不用引用传递：返回的是局部变量的时候

- friend（友元）

  - 在类里面声明定义该函数为类的友元函数（或在类外定义），友元函数可以访问类的私有成员

  - friend打破了类的封装性

  - 相同class的各个objects互为friends

    - ```cpp
      class complex{
        public:
          complex(double r = 0, double i = 0):re(r) im(i){
              
          }
          
          int func(const complex& param){
              return param.re + param.im;
          }
          
        private:
          double re, im;
      };
      ```

- 好的编程习惯

  - 数据放在private
  - 用引用来传递参数，看情况加const
  - 以引用的方式返回参数
  - 在类本体的函数，应该加上const的就要加上
  - 构造函数要用初始值列表



#### Chapter05、操作符重载与临时对象

- operator overloading(操作符重载-1，成员函数) this

  - 任何非静态的成员函数都有一个隐藏的this指针

- return by reference语法分析

  - 传递者不需要知道接收者是以reference形式接收（特别是返回引用，在链式编程上特别好使）

- temp object（临时对象）

  - 需要以值返回，但是又不能返回local object的时候，就用temp object

  - ```cpp
    inline complex operator + (const complex& x, const complex& y){
        return complex(real(x) + real(y), imag(x) + imag(y));
    }
    ```

  - 没有名字的对象就是临时对象，它存在于完整的表达式的生存期间。也就是说，当表达式计算结束后就会被释放（即不会像临时对象一样）

  - 返回临时对象的话要以值传递，不能是引用传递

- 接下来就是无聊的操作符重载：+，-，==

- 不要把<<写作成员函数，要变为全局函数

  - 注意，传入ostream的cout的时候，不要把它设为const，因为cout的状态一直都在改变



#### Chapter06、复习Complex类的实现过程

- 本节是重复之前写complex类的过程，所以就总结一下什么是良好的编程习惯：
  - 书写头文件要有防卫式声明
  - 构造函数的初始化要用初始化列表
  - 传入参数最好传入引用
  - 如果函数不会改变类的数据，最好在它的后面加上const
  - 把数据放到私有部分
  - 如果像一些操作符会涉及链式操作的（a1+=a2+=a3）的话，需要注意返回值的类型
  - 思考操作符到底要不要设计为成员函数（比如加号，可能感觉是只有复数加上复数，但是实际上又会有实数，例如int类型加上复数）
  - 注意像cout这样的变量，在传参的时候不要给他们加上const



#### Chapter07、三大函数：拷贝构造，拷贝赋值，析构

- Big Three：拷贝构造，拷贝赋值，析构函数

  - 注意在析构函数中，要被对象本身含有的其他对象也一并清零

  - ```cpp
    String *p = new String("Hello");//这样也会调用拷贝构造函数
    ```

  - 注意拷贝函数（拷贝赋值）中，如果有指针类的对象，要注意深拷贝和浅拷贝（否则编译器提供的就是浅拷贝）

  - 注意拷贝赋值函数，先要进行自我赋值检测（而后的操作是：先删掉自己的数据，然后创建空间，接着把数据放入创建好的空间中。最后返回引用对象）

    - 如果不进行自我赋值检测，会造成说直接就把原来的数据给删掉了的情况



#### chapter08、堆、栈与内存管理

- String的output函数（写成成员函数）

- 栈（stack）

  - 存在于某个作用域（scope）的一块内存空间，例如当你调用函数，函数本身即会形成一个stack用来放置它所接收的参数，以及返回地址
    - 在函数本体内声明的任何变量，其所使用的内存块都取自上述stack

- 堆（heap）

  - 是指由操作系统提供的一块global内存空间，程序可动态分配（dynamic allocated）从某中获得若干区域（blocks）

- stack的生命期：离开了作用域就会消失

  - 但是static的生命会在作用域结束后仍然存在，直到整个程序结束
  - global object也是一样，作用域是整个程序

- heap的生命期：其生命在它被delete之际结束

  - 如果不delete，就会造成内存泄漏

  - ```cpp
    //可以这样创建对象的啊！！
    Complex* p = new Complex;
    ```

- new，先分配memory，再调用ctor

  - ```cpp
    Complex* pc = new Complex(1, 2);
    
    //在编译器内部会转化为
    Complex *pc;
    void* mem = operator new(sizeof(Complex));//分配内存，其中operator new调用的是malloc(n)的内存分配函数
    pc = static_cast<Complex*>(mem);//转型
    pc -> Complex::Complex(1, 2);//构造函数
    ```

- delete，先调用dtor，再释放memory

  - ```cpp
    delete pc;
    
    //在编译器内部会转化为
    Complex::~Complex(pc);//析构函数
    operator delete(pc);//释放内存，在delete的内部调用free(pc)
    ```

- 动态分配所得的内存块（memory block）

  - 对象所占用的内存：对象自己的大小，padding（结构体对齐），以及两个cookie（？，一共8个字节的cookie）

- 动态分配的array

  - 对象所占用的内存：一个记录数组长度的大小，对象自己的大小乘以长度，padding，以及两个cookie（？，一共8个字节的cookie）

- array new一定要搭配array delete

  - 如果对于数组对象，没有delete[]，就会造成只释放了第一个对象，后面的对象都没能被释放，造成内存泄漏



#### Chapter09、复习String类的实现过程

- 设计String类的思路：
  - 防卫式声明
  - 使用字符数组char还是字符串指针char*（因为不知道数组的长度，所以最好还是用string）
  - 接着考虑构造函数，拷贝构造函数，拷贝运算符，析构函数
  - 然后是对于传入的参数，如果不对其改变的话，就加上const；同理，对于函数也要有同样的思考
  - 构造函数（传入的是一个字符串的指针，就要先判断是不是0，再继续下面的操作）
  - 析构函数（要把char的内存释放掉）
  - 拷贝构造函数（直接复制值即可）
  - 拷贝赋值函数（需要先检验是否是自我赋值；还有考虑返回值是void还是对象的引用，这里要看需求决定；还有，返回的时候是一个对象，但是调用是如何接收的，是值返回或者引用返回都是可以的）



#### Chapter10、关键字与模板的补充

- 关键词static

  - 加上static的成员存在于类之外的区域中，无论对象有多少个，该数据都只有一个

  - 静态函数也是类似，单独存在于外边

  - 所以静态函数无法调用类的属性以及函数（因为它不属于类对象的，它是单独存在于某个区域），只能调用静态变量和静态函数

  - 而静态变量需要在类外进行定义初始化

    - ```cpp
      class A{
        public:
          static double m_rate;
      };
      
      double A::m_rate = 8.0;
      ```

  - 调用static函数的两种方式：通过object调用（类似作用域），通过class name调用（类似普通函数）

  - 单例模式就是通过static来实现的(singleton)

    - ```cpp
      class A{
        public:
          static A& getInstance(){
              return a;
          }
          setup(){}
          
        private:
          A();
          A(const A& rhs);
      };
      
      A& A::getInstance(){
          static A a;
          return a;
      }
      ```

- 关键词cout

  - 底层使用了很多重载使得其能用于浮点数，整数，字符串上面

- class template

  - ```cpp
    template <typename T>
    class complex{
        public:
        	complex(T r = 0, T i = 0):re(r), im(i){}
        private:
        	T re, im;
    };
    
    complex<double> c1(1.1, 1.2);
    ```

  - 相当于用T来代替class中所有的代码

- function template

  - ```cpp
    template<typename T>
    inline const T& min(const T& a, const T& b){
        return b < a ? b : a;
    }
    
    int a = 10, b = 1, c = 100;
    c = min(a, b);//编译器会对函数模板进行引数推导
    ```

  - 所以对于每个类，只需要重载小于号即可，这样就可以统一调用min函数

- 关键字namespace

  - 把代码都放到这样一个命名空间里面，进行封装，有助于防止变量同名
  - 标准库的所有代码都放在std里面
  - 可以分段写（即namespace是共享的，这样可以防止代码过长）
  - 使用namespace： using namespace std;



#### Chapter11、组合与继承

- 类与类之间的关系：
  - composition（复合），表示has-a
    - 在stl源码里面，queue的底层大多数都是套用deque来实现的，即queue中有一个deque
    - queue的很多功能都是通过调用deque的函数来实现的
    - 构造函数是由内而外的，先构造里面的component，再构造外面的container
    - 析构函数是由外而内的，先析构外面的container，再析构里面的component
  - delegation（委托）
    - 对象里面维护一个指针，指向另一个对象
    - 和复合的区别是，复合里面是真的有这个对象，但是委托指针拥有这个对象的指针而已
    - 不过设计指针，就一定要注意深拷贝和浅拷贝的关系
    - copy on write，即多个指针指向同一个目标，如果有一个指针要修改其指向的对象，就单独拎一个出来进行修改
  - inheritance（继承），表示is-a
    - 涉及三种继承：public，private，protected
    - 构造函数是由内而外的，先构造里面的base，再构造外面的derived
    - 析构函数是由外而内的，先析构外面的derived，再析构里面的base



#### Chapter12、虚函数和多态

- 类与类之间的关系：复合，委托，继承（对于函数，继承是继承了函数的调用权）

- non-virtual 函数：不希望 derived class 重新定义它（override）

- virutal 函数：希望derived class 重新定义它（override），且对它已经有了默认定义

- pure virtual 函数：希望derived class 一定要重新定义它（override），并且对其没有默认定义

- ```cpp
  class A{
    public:
      //如果子类要重写这个虚函数的话，那么就要把原函数的所有修饰词都抄下来，包括const
      virtual void draw() const = 0;//pure virtual
      virtual void error();//impure virtual
      int objectID() const;//non-virtual
  };
  ```

- 通过子类对象调用父类函数，而在父类函数里面有调用在子类中定义好的纯虚函数（设计模式：template method），很多框架的实现都是这样的

  - 而这种实现，就是依赖虚函数表（因为是在子类调用的父类函数，所以传入的this也是子类对象）

- 继承（inheritance）和复合（composition）的构造和析构

  - 子类继承父类，子类中又复合一个类对象
    - derived object中包含了base part和component
    - 两者的构造顺序上（在我的机器上，gcc9.2，windows，64位机器上），是先调用base part，再调用component，最后调用derived object
    - 析构的顺序就全部相反了，先derived object，再component，最后base part
  - 子类继承父类，父类中又复合一个类对象
    - base part中有一个component，derived object继承了base part（即component最里层，base part第二层，derived object第三层）
    - 先调用component，再调用base part，最后调用derived object
    - 析构则倒过来执行

- 委托（delegation）和继承（inheritance）



#### Chapter13、委托相关设计

- 委托（delegation）和继承（inheritance）
  - 设计模式中的composite模式，组合模式
    - 文件夹里面放文件和文件夹，里面的文件夹又可以放文件和文件夹
    - 因此，抽象出一个具有两者共性的类component，一个文件夹类composite，和一个文件类primitive
    - 然后，让composite和primitive继承component（继承），其中composite又具有一个vector，这个vector装载component类（委托）
  - 设计模式中的prototype模式，原型模式
    - 通过一个抽象原型类，去实现多个具体原型类
    - 背景：对于一个照片，未来可能会有很多的照片，但我现在不知道这些照片的类型究竟有多少，所以就有了这种设计模式
    - 即对于每一个新的照片，我都准备一个**clone函数**（这里的clone要在父类中设为纯虚函数），用来创建一个新的自己，同时给这个类准备一个**静态的编号**，并把这个编号填入原型类的一个数组当中（或者不是储存编号，而是直接把这个对象储存到里面）
    - 原型类就可以通过编号调用创建不同的类了
    - 细节：为什么会有一个protected的构造函数？
      - 因为正常的构造函数会把一个函数原型添加到原型类的数组当中，如果当我们clone一个新的对象的是时候，调用的又是这个构造函数，那么又会添加一个重复的函数原型。为了防止这种情况发生，就新写一个带参数的构造函数，让clone调用的是这个带参数的构造函数
      - 不能放在公有区域，加一个参数是为了区分原来的构造函数
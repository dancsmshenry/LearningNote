# 条款05：了解C++默默编写并调用哪些函数

对于一个空类，编辑器会为其写下这些代码（以下函数都是public且inline的）：

- default构造函数
- copy构造函数和copy assignment操作符
  - 单纯地将来源对象的每一个non-static成员变量拷贝到目标对象
- 析构函数（是non-virtual的）

<br/>

- 如果声明了一个构造函数，编辑器是不会创建default函数了的
- 引用是不可以被修改绑定的
  - 所以，如果一个类里面的成员包含引用的话，必须重写copy assignment操作符
  - 如果有string的话感觉也是同理

<br/>

总结：

- 编辑器可以暗自为class创建default构造函数，copy构造函数，copy assignment操作符以及析构函数

<br/>

<br/>

# 条款06：若不想使用编译器自动生成的函数，就该明确拒绝

- 如果不想对象被赋值或者赋值的话，有以下解决方案
  - 将这个copy函数和赋值运算符变为私有
    - 但是friend函数和member函数会调用的到这个函数
  - 将copy函数和赋值运算符变为私有且只有函数声明
    - 但是会在连接器的位置发生报错
  - 设计一个base类，其copy和赋值函数设为私有，然后把我们需要的类继承该类
    - 即设一个uncopyable类，把我们需要用到的类都继承该类

<br/>

总结：

- 为驳回编译器自动（暗自）提供的机能，可将相应的成员函数声明为private并且不予实现。或使用向uncopyable这样的base class也是一种做法

<br/>

<br/>

# 条款07：为多态基类声明virtual析构函数

- 前提：当一份derived class对象经由一个base class指针被删除，而该base class带着一个non-virtual析构函数，结果是：实际执行时通常发生的是对象的derived成分没被销毁（因为只是调用了base class的析构函数，没有调用到derived class的析构函数），从而造成资源泄漏

- 解决办法：给base class的析构函数变为虚函数

- 如果不是base class，最好不要给析构函数加上virtual

  - 因为virtual需要虚函数表和其指针，所以会是class变大

- 当对象调用某一virtual函数，实际被调用的函数取决于该对象的vptr所指的那个vtbl-编译器在其中寻找适当的函数指针

- 注意：stl中的容器，包括string都是不带virtual析构函数的class

- pure virtual 函数，使得class变得abstract，不能被实例化

- 希望有抽象函数的办法：给他的析构函数变为纯虚函数（在类外需要给其一个定义，如果不给定义的话，那么他的子类就无法调用父类的析构函数）

  - ```cpp
    class AWOV{
        public:
        	virutal ~AWOV() = 0;
    }
    
    AWOV::~AWOV() = 0;
    ```

<br/>

总结：

- 带多态性质的base class应该声明一个virtual析构函数，如果class带有任何virtual函数，它就应该拥有virtual析构函数
- classes的设计目的如果不是作为base classes使用，或不是为了具备多态性，就不因该声明析构函数

<br/>

<br/>

# 条款08：别让异常逃离析构函数

- 不能让析构函数吐出异常，因为这可能会使程序过早结束或出现不明确行为

- 解决办法：

  - 在析构函数中运用try catch，即如果抛出了异常就结束程序，通常通过调用abort完成

    - ```cpp
      DBConn::~DBConn(){
          try{db.close();}
          catch(...){
              std::abort();
          }
      }
      ```

  - 或者不用abort，直接记录下此次异常

<br/>

总结：

- 析构函数绝对不要吐出异常（即不要因此而退出结束程序），如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕获异常，然后吞下它们（不传播）或结束程序
- 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么classes应该提供一个普通函数执行该操作

<br/>

<br/>

# 条款09：绝不再构造和析构过程中调用virtual函数

- 对于一个子类，如果其父类的构造函数中调用了一个虚函数，效果会和设计者所想的截然不同

  - 一个虚函数决定它到底调用的是谁的虚函数看的是当前的对象是谁，如果是在父类里面调用，那就是父类的虚函数
    - 理由：调用子类函数必须要初始化子类的属性和对象的，而此时是还在父类函数里面，所以不可能调用得到子类函数的
    - 还有，在base class的构造期间对象的类型还是base class类型
  - 而设计者肯定是一位调用的是子类的虚函数类型（毕竟是创建一个子类嘛），所以是错误的
  - 相同的道理也适用于析构函数

- 而如果想要达到说，根据子类的不同调用函数，可以这样写

  - ```cpp
    class A{
      public:
        explicit A(const string& logInfo){
            logTransaction(logInfo);
        }
        void logTransaction(const string& logInfo) const;
    };
    
    class B: public A{
        public:
        	B(parameters):A(createLogString(parameters)){
            /*B的构建顺序是：先走B的构造函数，然后发现有初始值列表，则先初始化一个A对象（其实可以认为他的父类也是他的一个成员属性）*/
        	}
        private:
        	static string createLogString(parameters);
    }
    ```

  - 虽然我们无法使用virtual函数从base class向下调用对象，但是可以借助初始值列表，在子类构造的时候传入我们想要传入的信息给父类，从而达到这一点

  - 同时，下面的private和static函数也就不可能以外指向B类中未被初始化的成员便来给你parameters

<br/>

总结：

- 在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class（比起当前执行构造函数和析构函数的那层）

<br/>

<br/>

# 条款10：令operator= 返回一个reference to *this

- 该条款不仅适用于以上的标准赋值形式，也适用于所有赋值相关运算

- 当需要连锁形式（链式编程）的时候，最好写成这样

  - ```cpp
    Widget& operator=(const Widget& rhs){
        //参数的const表示不可以改变传进来的蚕食，&表示是以引用接收的，节省空间
        //而上面的返回类型中，可以是void，但为了链式编程，就要改为Widget；用&同理，节省空间
        
        //而在返回方面，直接返回当前的对象，也是为了链式编程
        return *this;
    }
    ```

- 不过具体该如何写，还是得看具体的情况

<br/>

总结：

- 令赋值操作符返回一个reference to *this

<br/>

<br/>

# 条款11：在operator=中处理“自我赋值”

在设计等于号的时候，容易出现自己给自己赋值的情况，如：两个指针都是指向同一个对象

如果不稍加注意的话，就会导致错误

所以，有以下几种解决办法：

方法一：

- ```cpp
  Widget& Widget::operator=(const Widget& rhs) {
      if (this == &rhs) return *this;//	先判断两者是否是指向同一个对象
      //	证同测试，如果是自我赋值，就不做任何事情
      delete pb;
      pb = new Bitmap(*rhs.pb);
      return *this;
  }
  ```
  
- 缺点，缺乏异常安全性：如果new的过程出现问题，widget会指向一个错误的空间

方法二：

- ```cpp
  Widget& Widget::operator=(cosnt Widget& rhs) {
      Bitmap* pOrig = pb;
      pb = new Bitmap(*rhs.pb);
      delere pOrig;
      return *this;
  }
  ```

方法三：自定义一个swap函数

- ```cpp
  Widfet& Widget::operator=(const Widget& rhs) {
      Widget temp(rhs);
      swap(temp);
      return *this;
  }
  ```

<br/>

总结

- 确保当对象自我复制时operator=有良好行为。其中技术包括比较“来源对象”和“目标对象”的地址、精心周到的语句顺序、以及copy-and-swap
- 确定任何函数如果操作一个以上的对象，二其中多个对象是同一个对象时，其行为仍然正确

<br/>

<br/>

# 条款12：复制对象时勿忘其每一个成分

特别是对于子类的拷贝构造函数和赋值运算符，要从两方面注意：
- 复制该类的所有local成员变量
- 调用所有base class 内的适当的copying函数
  - 这里最好直接在初始值列写出（有一个好处就是如果base类中多加了一个属性，那么子类也不需要做很大的改动）

<br/>

总结

- copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”
- 不要尝试以某个copying函数实现另一个copying函数，应该将共同机能放进第三个函数中，并由两个coping函数共同调用